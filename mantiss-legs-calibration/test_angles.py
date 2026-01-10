import yaml
import time
import board

from adafruit_motor import servo
from adafruit_pca9685 import PCA9685


def get_servo(pca, servo_config):
    return servo.Servo(pca.channels[servo_config['channel']], min_pulse=servo_config['min_pulse'], max_pulse=servo_config['max_pulse'])



def move(servo_, servo_config, angle):
    servo_angle = servo_config['rest_angle'] + (servo_config.get('angle_phisical_delta', 0) + angle) * servo_config.get('multiplier', 1)
    print(f'Servo moved to angle: {servo_angle}')
    servo_.angle = servo_angle

    time.sleep(2)

    servo_.angle = None
    print("Servo deinitialized.")

def main():

    with open('config.yaml', 'r') as config_file:
        config = yaml.safe_load(config_file)

#    servo_config = config['tail']

    servo_config = config['legs']['left_front']['femur']['servo']


    i2c = board.I2C()
    pca = PCA9685(i2c_bus=i2c, address=servo_config.get('i2c_address'))
    pca.frequency = 50

    test_servo = get_servo(pca, servo_config)


    move(test_servo, servo_config, -90)

    #move(test_servo, servo_config, -45)
    #move(test_servo, servo_config, 45)
    #move(test_servo, servo_config, -45)
    #move(test_servo, servo_config, 45)

    pca.deinit()


if __name__ == "__main__":
    main()
