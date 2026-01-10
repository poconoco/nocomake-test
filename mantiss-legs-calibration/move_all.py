import yaml
import time
import board

from utils import PcaPool, Servo


def main():

    i2c = board.I2C()
    pca_pool = PcaPool(i2c)

    with open('config.yaml', 'r') as config_file:
        config = yaml.safe_load(config_file)

    servos = (
        Servo(pca_pool, config['legs']['left_rear']['coxa']['servo']),
        Servo(pca_pool, config['legs']['right_rear']['coxa']['servo']),
        Servo(pca_pool, config['legs']['left_middle']['coxa']['servo']),
        Servo(pca_pool, config['legs']['right_middle']['coxa']['servo']),
        Servo(pca_pool, config['legs']['left_front']['coxa']['servo1']),
        Servo(pca_pool, config['legs']['left_front']['coxa']['servo2']),
        Servo(pca_pool, config['legs']['right_front']['coxa']['servo1']),
        Servo(pca_pool, config['legs']['right_front']['coxa']['servo2']),

        Servo(pca_pool, config['legs']['left_rear']['femur']['servo']),
        Servo(pca_pool, config['legs']['right_rear']['femur']['servo']),
        Servo(pca_pool, config['legs']['left_middle']['femur']['servo']),
        Servo(pca_pool, config['legs']['right_middle']['femur']['servo']),
        Servo(pca_pool, config['legs']['left_front']['femur']['servo']),
        Servo(pca_pool, config['legs']['right_front']['femur']['servo']),

        Servo(pca_pool, config['legs']['left_rear']['tibia']['servo']),
        Servo(pca_pool, config['legs']['right_rear']['tibia']['servo']),
        Servo(pca_pool, config['legs']['left_middle']['tibia']['servo']),
        Servo(pca_pool, config['legs']['right_middle']['tibia']['servo']),
        Servo(pca_pool, config['legs']['left_front']['tibia']['servo']),
        Servo(pca_pool, config['legs']['right_front']['tibia']['servo']),

        Servo(pca_pool, config['tail']['servo']),
    )

    angle_base = 0
    angle_delta = 0
    increment = 1
    while True:
        angle_delta += increment
        if angle_delta > 10 or angle_delta == 0:
            increment = -increment

        angle = angle_base + angle_delta

        for servo_ in servos:
            servo_.move(angle)

        time.sleep(0.05)

if __name__ == "__main__":
    main()
