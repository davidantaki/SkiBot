/**
 *
 * HX711 library for Arduino - example file
 * https://github.com/bogde/HX711
 *
 * MIT License
 * (c) 2018 Bogdan Necula
 *
**/
#include "HX711.h"
#include "twoPtCalCurve.h"


// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = PF0;
const int LOADCELL_SCK_PIN = PF1;

// 1.1kg
const float kgWeightCal1refY = 1.1;
const float kgWeightCal1expX = 1.17687; // from get_units()


// 6.75kg
const float kgWeightCal2refY = 6.75;
const float kgWeightCal2expX = 6.85205; // from get_units()


const float calWeightKg = 0.5251; // The weight of the known weight
const float calWeightKgSCALE = 110410.00; // From get_units()
const float SCALE = calWeightKgSCALE/calWeightKg; // Passed to set_scale()

HX711 scale;

void doCalibration(){
  delay(1000);
  Serial.print("is_ready(): ");
  Serial.println(scale.is_ready());

  Serial.println("\n\nSetting up scale\n");
  scale.set_scale();
  scale.tare();
  Serial.println("\n\nPut known wait onto load cell\n");
  delay(5000);
  float tempCalWeightKgSCALE = scale.get_units(10);
  Serial.print("get_units(): ");
  Serial.println(tempCalWeightKgSCALE);
  scale.set_scale(calWeightKg/calWeightKgSCALE);
  exit(0);
}

void setup() {
  TwoPtCalCurve<float>::CalPoint calPt1;
  calPt1.expX = kgWeightCal1expX;
  calPt1.refY = kgWeightCal1refY;

  TwoPtCalCurve<float>::CalPoint calPt2;
  calPt2.expX = kgWeightCal2expX;
  calPt2.refY = kgWeightCal2refY;

  TwoPtCalCurve<float> calCurve(calPt1, calPt2);

  Serial.begin(9600);
  Serial.println("\n\nHX711 Demo");

  Serial.println("Initializing the scale");

  // Initialize library with data output pin, clock input pin and gain factor.
  // Channel selection is made by passing the appropriate gain:
  // - With a gain factor of 64 or 128, channel A is selected
  // - With a gain factor of 32, channel B is selected
  // By omitting the gain factor parameter, the library
  // default "128" (Channel A) is used here.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  // doCalibration();


  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());			// print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));  	// print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);	// print the average of 5 readings from the ADC minus tare weight (not set) divided
						// by the SCALE parameter (not set yet)



  scale.set_scale(SCALE);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();				        // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
						// by the SCALE parameter set with set_scale

  Serial.println("Readings:");

  while(1){
    Serial.print("Time (ms): \t");
    Serial.print(millis());
    Serial.print("\tone reading (kg):\t");
    Serial.print(scale.get_units(), 5);
    // Serial.print("\t| average (kg):\t");
    // Serial.print(scale.get_units(10), 5);
    Serial.print("\t| calCurve average (kg):\t");
    Serial.println(calCurve.calibrateVal(scale.get_units(1)), 5);
  }
}

void loop() {
  // Serial.print("one reading (kg):\t");
  // Serial.print(scale.get_units(), 5);
  // Serial.print("\t| average (kg):\t");
  // Serial.print(scale.get_units(10), 5);
  // Serial.print("\t| calCurve average (kg):\t");
  // Serial.println(calCurve.calibrateVal(scale.get_units(10)), 5);
  

  // scale.power_down();			        // put the ADC in sleep mode
  // delay(1000);
  // scale.power_up();
}