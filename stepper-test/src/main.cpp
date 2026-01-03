#include <Arduino.h>
#include <AccelStepper.h>

const int stepperDirPin = 2;
const int stepperStepPin = 3;

AccelStepper stepper(AccelStepper::DRIVER, stepperStepPin, stepperDirPin);

void setup() {
  stepper.setMaxSpeed(1000);
  stepper.setSpeed(500);
}

void loop() {
  stepper.runSpeed();
  delay(0.25);
}
