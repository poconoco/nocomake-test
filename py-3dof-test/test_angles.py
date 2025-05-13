import yaml
import time
import board

from adafruit_motor import servo
from adafruit_pca9685 import PCA9685


def get_servo(pca, servo_config):
    return servo.Servo(pca.channels[servo_config['channel']], min_pulse=servo_config['min_pulse'], max_pulse=servo_config['max_pulse'])


def set_angle(servo_, servo_config, angle):
    servo_angle = servo_config['angle'] + (servo_config.get('angle_phisical_delta', 0) + angle) * servo_config.get('multiplier', 1)
    print(f'angle: {servo_angle}')
    servo_.angle = servo_angle


def move(pca, config, leg_name, ca, fa, ta):
    leg_config = config[leg_name]

    coxa_config = leg_config['coxa']
    femur_config = leg_config['femur']
    tibia_config = leg_config['tibia']

    coxa_servo = get_servo(pca, coxa_config['servo'])
    femur_servo = get_servo(pca, femur_config['servo'])
    tibia_servo = get_servo(pca, tibia_config['servo'])

    set_angle(coxa_servo, coxa_config, ca)
    set_angle(femur_servo, femur_config, fa)
    set_angle(tibia_servo, tibia_config, ta)

    time.sleep(1)

    coxa_servo.angle = None
    femur_servo.angle = None
    tibia_servo.angle = None
    print("Servo controller deinitialized.")

def main():

    with open('test_config.yaml', 'r') as config_file:
        config = yaml.safe_load(config_file)

    i2c = board.I2C()
    pca = PCA9685(i2c)
    pca.frequency = 50

#    move(pca, config, 'left_first', -90, -60, -90)
    move(pca, config, 'right_first', 90, -60, -90)

    pca.deinit()


if __name__ == "__main__":
    main()
