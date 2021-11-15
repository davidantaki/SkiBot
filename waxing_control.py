# Uses Cytron MDD3A motor driver board
# RPI4

import RPi.GPIO as gpio
import time
import busio
import adafruit_vl6180x

# BOARD Pin definitions
# SCL1 = 5
# SDA1 = 3
# M1Apin = 10
# M1Bpin = 12
# M2Apin = 7
# M2Bpin = 8

# BCM Pin definitions
SCL1 = 3
SDA1 = 2
M1Apin = 15
M1Bpin = 18
M2Apin = 4
M2Bpin = 14

i2c1Bus = None

def setup():
    gpio.cleanup()

    freq = 10000
    gpio.setmode(gpio.BCM)

    # motor1
    gpio.setup(M1Apin, gpio.OUT, initial=gpio.LOW)   #M1A
    gpio.setup(M1Bpin, gpio.OUT, initial=gpio.LOW)	#M1B

    # motor2
    gpio.setup(M2Apin, gpio.OUT, initial=gpio.LOW)	#M2A
    gpio.setup(M2Bpin, gpio.OUT, initial=gpio.LOW)	#M2B

    # Vcsel sensors
    global i2c1Bus 
    i2c1Bus = busio.I2C(SCL1, SDA1)
    

def teardown():
    gpio.cleanup()


def moveLeft():
    gpio.output(M1Bpin, gpio.LOW)
    gpio.output(M2Bpin, gpio.LOW)
    gpio.output(M1Apin, gpio.HIGH)
    gpio.output(M2Apin, gpio.HIGH)

def moveRight():
    gpio.output(M1Bpin, gpio.HIGH)
    gpio.output(M2Bpin, gpio.HIGH)    
    gpio.output(M1Apin, gpio.LOW)
    gpio.output(M2Apin, gpio.LOW)

def moveStop():
    gpio.output(3, gpio.LOW)
    gpio.output(7, gpio.LOW)    
    gpio.output(5, gpio.LOW)
    gpio.output(8, gpio.LOW)



def moveAuto(i2c1Bus):
    # Create sensor instance.
    vcselLeft = adafruit_vl6180x.VL6180X(i2c1Bus, 0x29)
    # vcselRight._write_8(0x212, 0x29)
    vcselRight = adafruit_vl6180x.VL6180X(i2c1Bus, 0x28)
    
    moveLeft()

    # main loop
    while True:
        # Read the range in millimeters and print it.
        vcselRightRange_mm = vcselRight.range
        print("vcselRightRange_mm: {0}mm".format(vcselRightRange_mm), end='')
        vcselLeftRange_mm = vcselLeft.range
        print("\t\tvcselRightRange_mm: {0}mm".format(vcselLeftRange_mm))

        if vcselRightRange_mm > 150:
            moveLeft()
        elif vcselLeftRange_mm > 120:
            moveRight()
        time.sleep(0.1)

def main():
    print("Running...\n")
    setup()
    print("setup() done\n")

    moveAuto(i2c1Bus)


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print('Interrupted')
        teardown()
        exit(0)


