#include "DRV8825.h"
#include <Arduino.h>

// using a 200-step motor (most common)
#define MOTOR_STEPS 200
// configure the pins connected
#define DIR A0
#define STEP A1
#define ENABLE A2
#define MS1 A3
#define MS2 A4
#define MS3 A5
DRV8825 stepper(MOTOR_STEPS, DIR, STEP, ENABLE, MS1, MS2, MS3);

void setup() {
  // Set target motor RPM to 1RPM and microstepping to 1 (full step mode)
  stepper.begin(100, 1);
  stepper.setEnableActiveState(LOW);
  Serial.begin(115200);
  delay(2000);
  Serial.println("Setup!");
}

void loop() {
  // Tell motor to rotate 360 degrees. That's it.
  // Serial.println(digitalRead(A5));
  // digitalWrite(A4, HIGH);
  Serial.println("loop");
  // stepper.rotate(10000);
  stepper.enable();
  stepper.move(360);
  stepper.disable();
  delay(10000);
  // Serial.println(digitalRead(A5));
  // digitalWrite(A4, LOW);
  // delay(1000);
}