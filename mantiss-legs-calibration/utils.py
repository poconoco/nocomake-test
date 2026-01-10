from adafruit_motor import servo
from adafruit_pca9685 import PCA9685

class PcaPool:
    def __init__(self, i2c):
        self.i2c = i2c
        self.pca_dict = {}

    def __del__(self):
        for pca in self.pca_dict.values():
            pca.deinit()

    def get_pca(self, address):
        if address not in self.pca_dict:
            pca = PCA9685(i2c_bus=self.i2c, address=address)
            pca.frequency = 50
            self.pca_dict[address] = pca

        return self.pca_dict[address]

class Servo:
    def __init__(self, pca_pool, servo_config):
        pca = pca_pool.get_pca(servo_config['i2c_address'])
        self.servo = servo.Servo(pca.channels[servo_config['channel']], min_pulse=servo_config['min_pulse'], max_pulse=servo_config['max_pulse'])
        self.rest_angle = servo_config.get('rest_angle', 0)
        self.angle_phisical_delta = servo_config.get('angle_phisical_delta', 0)
        self.multiplier = servo_config.get('multiplier', 1)

    def move(self, angle):
        servo_angle = self.rest_angle + (self.angle_phisical_delta + angle) * self.multiplier
        self.servo.angle = servo_angle
