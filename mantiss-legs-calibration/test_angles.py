import yaml
import time
import board

from utils import PcaPool, Servo

def main():

    i2c = board.I2C()
    pca_pool = PcaPool(i2c)

    with open('config.yaml', 'r') as config_file:
        config = yaml.safe_load(config_file)


    test_servo = Servo(pca_pool, config['legs']['left_rear']['tibia']['servo'])

    test_servo.move(10)


if __name__ == "__main__":
    main()
