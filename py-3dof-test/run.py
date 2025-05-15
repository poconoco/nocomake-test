import yaml
import board
import time

from adafruit_motor import servo
from adafruit_pca9685 import PCA9685


from submodules.py_kinematics.ik3dof import IK3DOF
from submodules.py_kinematics.point3d import Point3D
from submodules.bt_remote.receivers.python.tcp_rc_receiver import TcpRcReceiver, rc_state_to_str


class Leg:
    def __init__(self, leg_config: dict, pca: PCA9685):
        self.ik = IK3DOF()
        self.ik.coxa_h_offset = leg_config['coxa'].get('h_offset', 0.0)
        self.ik.coxa_v_offset = leg_config['coxa'].get('v_offset', 0.0)

        self.ik.femur_length = leg_config['femur'].get('length', 0.0)
        self.ik.tibia_length = leg_config['tibia'].get('length', 0.0)

        self.ik.coxa_angle_for_forward = leg_config['coxa']['angle_for_forward']
        self.ik.femur_angle_for_horizontal = leg_config['femur']['angle_for_horizontal']

        # angle_phisical_delta is used for femur that are Г-shaped, and it's easier to 
        # calibrate angles for the straight part of the tibia, but the real tibia is diagonal
        # between the ends of Г
        self.ik.tibia_angle_for_femur_parallel = leg_config['tibia']['angle_for_femur_parallel'] + \
            leg_config['tibia'].get('angle_phisical_delta', 0.0) * leg_config['tibia'].get('multiplier', 1.0) 

        self.ik.coxa_multiplier = leg_config['coxa'].get('multiplier', 1.0)
        self.ik.femur_multiplier = leg_config['femur'].get('multiplier', 1.0)
        self.ik.tibia_multiplier = leg_config['tibia'].get('multiplier', 1.0)

        self.coxa_servo = self._get_servo(leg_config['coxa']['servo'], pca)
        self.femur_servo = self._get_servo(leg_config['femur']['servo'], pca)
        self.tibia_servo = self._get_servo(leg_config['tibia']['servo'], pca)

    def reach(self, point: Point3D):
        coxa_angle, femur_angle, tibia_angle = self.ik.get_angles(point)

        if coxa_angle is not None:
            coxa_angle = _clamp(coxa_angle, 0, 180)
            self.coxa_servo.angle = coxa_angle

        if femur_angle is not None:    
            femur_angle = _clamp(femur_angle, 0, 180)
            self.femur_servo.angle = femur_angle

        if tibia_angle is not None:
            tibia_angle = _clamp(tibia_angle, 0, 180)
            self.tibia_servo.angle = tibia_angle

    def detach(self):
        self.coxa_servo.angle = None
        self.femur_servo.angle = None
        self.tibia_servo.angle = None
        

    def _get_servo(self, servo_config, pca):
        return servo.Servo(pca.channels[servo_config['channel']], min_pulse=servo_config['min_pulse'], max_pulse=servo_config['max_pulse'])


def main():
    with open('config.yaml', 'r') as config_file:
        config = yaml.safe_load(config_file)

    i2c = board.I2C()
    pca = PCA9685(i2c)
    pca.frequency = 50

    left_leg = Leg(config['left_first'], pca)
    right_leg = Leg(config['right_first'], pca)

    rc = TcpRcReceiver(print_debug=True)

    left_center_point = Point3D(-30, 100, -30)
    right_center_point = Point3D(30, 100, -30)
    scale = 0.5

    print("\nPress Ctrl+C key to exit...")
    try:
        while True:
            if rc.is_connected():
                print('\r'+rc_state_to_str(rc), end='', flush=True)
                rc.send(f'Live for: {round(rc.get_connected_time())}s')

                left_leg.reach(left_center_point + Point3D(rc.get_x1(), rc.get_y1(), 0) * scale)
                right_leg.reach(right_center_point + Point3D(rc.get_x2(), rc.get_y2(), 0) * scale)
            else:
                left_leg.detach()
                right_leg.detach()

            time.sleep(0.01)
    except KeyboardInterrupt:
        print("\nExiting...")
    finally:
        left_leg.detach()
        right_leg.detach()
        pca.deinit()


def _clamp(value, min_value, max_value):
    return min(max(value, min_value), max_value)


if __name__ == "__main__":
    main()
