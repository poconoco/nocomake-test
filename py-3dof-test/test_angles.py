import time

from adafruit_motor import servo
from adafruit_pca9685 import PCA9685


def main():

    # Init servo controller attaced via I2C
    i2c = board.I2C()
    pca = PCA9685(i2c)
    pca.frequency = 50

    # Init servos, servos [0, 2, 4] is one limb, [1, 3, 5] is the other
    coxa_servo = servo.Servo(pca.channels[0])
    femur_servo = servo.Servo(pca.channels[2])
    tibia_servo = servo.Servo(pca.channels[4])

    coxa_servo.angle = 90
    femur_servo.angle = 90
    tibia_servo.angle = 90

    print(f"Angles: {coxa_servo.angle}, {femur_servo.angle}, {tibia_servo.angle}")

    time.sleep(5)

    pca.deinit()
    print("Servo controller deinitialized.")
    

if __name__ == "__main__":
    main()
