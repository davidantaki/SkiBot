# Uses Cytron MDD3A motor driver board
# RPI4

import RPi.GPIO as gpio
import time



def setup():
    freq = 10000
    gpio.setmode(gpio.BOARD)

    # motor1
    gpio.setup(3, gpio.OUT, initial=gpio.LOW)   #M1A
    gpio.setup(5, gpio.OUT, initial=gpio.LOW)	#M1B

    # motor2
    gpio.setup(7, gpio.OUT, initial=gpio.LOW)	#M2A
    gpio.setup(8, gpio.OUT, initial=gpio.LOW)	#M2B

def teardown():
    gpio.cleanup()


def moveLeft():
    gpio.output(5, gpio.LOW)
    gpio.output(8, gpio.LOW)
    gpio.output(3, gpio.HIGH)
    gpio.output(7, gpio.HIGH)

def moveRight():
    gpio.output(3, gpio.LOW)
    gpio.output(7, gpio.LOW)    
    gpio.output(5, gpio.HIGH)
    gpio.output(8, gpio.HIGH)

def main():
    print("Running...\n")
    setup()
    print("setup() done\n")

    while True:
        moveLeft()
        time.sleep(4)
        moveRight()
        time.sleep(4)
    
    print("tearing down...\n")
    teardown()
    print("teardown() down\n")


if __name__ == "__main__":
    main()


