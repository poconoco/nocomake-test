#include <Servo.h>

#include "ServoController.h"

#define BUTTON_UP 2
#define BUTTON_RIGHT 3
#define BUTTON_DOWN 4
#define BUTTON_LEFT 5
#define PIN_ANALOG_X 0
#define PIN_ANALOG_Y 1

#define TURN_PIN 9
#define ARM1_PIN 10
#define ARM2_PIN 11
#define GRIP_PIN 12

#define DELAY 10

#define GRIP_OPEN 150
#define GRIP_CLOSED 180

void setup() {

  ServoController sTurn(
    TURN_PIN,  // pin
    360,  // max speed, degrees per second
    400,  // acceleration
    400,  // braking acceleration
    90);  // start pos, degrees

  ServoController sArm1(
    ARM1_PIN,  // pin
    360,  // max speed, degrees per second
    400,  // acceleration
    400,  // braking acceleration
    90);  // start pos, degrees

  ServoController sArm2(
    ARM2_PIN,  // pin
    360,  // max speed, degrees per second
    400,  // acceleration
    400,  // braking acceleration
    90);  // start pos, degrees

  Servo sGrip;
  sGrip.attach(GRIP_PIN);
  
  // to enable build-in pull up first set pin mode
  // to input and then make that pin HIGH
  pinMode(BUTTON_UP, INPUT);
  digitalWrite(BUTTON_UP, HIGH);

  pinMode(BUTTON_RIGHT, INPUT);
  digitalWrite(BUTTON_RIGHT, HIGH);

  pinMode(BUTTON_DOWN, INPUT);
  digitalWrite(BUTTON_DOWN, HIGH);
 
  pinMode(BUTTON_LEFT, INPUT);
  digitalWrite(BUTTON_LEFT, HIGH);

  // float, because we want to enable increments less than 0
  float arm2Val = 90;
  float gripVal = GRIP_OPEN;

  while (true) {
    int x = analogRead(PIN_ANALOG_X);
    int y = analogRead(PIN_ANALOG_Y);

    int turnVal = map(x, 0, 1023, 180, 0);
    int arm1Val = map(y, 0, 1023, 0, 180);

    sTurn.write(turnVal);
    sArm1.write(arm1Val);

    const float arm2Increment = 0.5;
    if(digitalRead(BUTTON_UP) == LOW) 
      arm2Val = min(arm2Val + arm2Increment, 180);
    else if (digitalRead(BUTTON_DOWN) == LOW)
      arm2Val = max(arm2Val - arm2Increment, 0);

    const float gripIncrement = 0.1;
    if(digitalRead(BUTTON_RIGHT) == LOW) 
      gripVal = max(gripVal - gripIncrement, GRIP_OPEN);
    else if (digitalRead(BUTTON_LEFT) == LOW)
      gripVal = min(gripVal + gripIncrement, GRIP_CLOSED);

    sArm2.write(arm2Val);
    sGrip.write(gripVal);

    sTurn.tick();
    sArm1.tick();
    sArm2.tick();
    delay(DELAY);
  }

}



void loop() {}
