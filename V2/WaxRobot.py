import RPi.GPIO as gpio
import time

freq = 10000

gpio.setmode(gpio.BOARD)

gpio.setup(8, gpio.OUT)		#EN
gpio.setup(10, gpio.OUT)	#ENB
gpio.setup(32, gpio.OUT)	#PWM1
gpio.setup(33, gpio.OUT)	#PWM2

pwm1 = gpio.PWM(32, freq)
pwm2 = gpio.PWM(33, freq)

gpio.output(8, gpio.HIGH)
gpio.output(10, gpio.LOW)

while True:
	pwm2.stop()
	pwm1.start(100)

	time.sleep(4)

	pwm1.stop()
	time.sleep(2)

	pwm2.start(100)

	time.sleep(4)


pwm1.stop()
pwm2.stop()
gpio.cleanup()




