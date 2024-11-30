#include <Servo.h>
#include <EEPROM.h>

#include "IK.h"

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

#define DELAY 5

#define GRIP_OPEN 150
#define GRIP_CLOSED 180

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {

  IK3DOF manipulator(
    TURN_PIN, 
    ARM1_PIN,
    ARM2_PIN,
    9,     // mm, arm1 horizontal offset
    31,    // mm, arm1 vertical offset
    40,    // mm, tip h offset (69 for the tip, 40 for the grip area)
    -6,    // mm, tip v offset
    80,    // mm, arm1 length
    80,    // mm, arm2 length
    0,     // Angle to write to servo so turn is at zero degrees to X axis (looks straignt to the right)
    170,   // Angle to write to servo so the arm1 is parallel to table
    145,   // Angle to write to servo so the arm2 is parallel to table or arm1 if (arm2RelativeToArm1)
    false, // Turn inverted
    true,  // arm1 inverted
    false, // arm2 inverted
    false  // arm2 relative to arm1,
  );

  Servo sGrip;
  sGrip.attach(GRIP_PIN);
  sGrip.write(GRIP_CLOSED);

  // // Line movement
  // int x = -100;
  // const int y = 135;
  // const int z = 40;
  // while (true) {
  //   while (x <= 100) {
  //     x++;
  //     manipulator.write(x, y, z);
  //     delay(DELAY);
  //   }

  //   while (x >= -100) {
  //     x--;
  //     manipulator.write(x, y, z);
  //     delay(DELAY);
  //   }

  // }

  // // Circle movement
  // float z = 10;
  // float cx = 0;
  // float cy = 150;
  // float r = 40;

  // float alpha = 0;  // degrees
  // float alphaDelta = 0.75;  // degrees
  // float circleDelay = 2; // ms
  // while (true) {
  //   const float alphaRad = alpha * PI / 180;
  //   const float x = cx + r * cos(alphaRad); 
  //   const float y = cy + r * sin(alphaRad);

  //   manipulator.write(x, y, z);

  //   alpha += alphaDelta;
  //   if (alpha >= 360)
  //     alpha -= 360;

  //   delay(circleDelay);
  // }

  
  // Pad controlled movement

  // To enable build-in pull up first set pin mode
  // to input and then make that pin HIGH
  pinMode(BUTTON_UP, INPUT);
  digitalWrite(BUTTON_UP, HIGH);

  pinMode(BUTTON_RIGHT, INPUT);
  digitalWrite(BUTTON_RIGHT, HIGH);

  pinMode(BUTTON_DOWN, INPUT);
  digitalWrite(BUTTON_DOWN, HIGH);
 
  pinMode(BUTTON_LEFT, INPUT);
  digitalWrite(BUTTON_LEFT, HIGH);

  float x = 0;
  float y = 120;
  float z = 40;
  float grip = GRIP_CLOSED;

  while (true) {
    const int xTrim = 2;
    const int yTrim = -14;
    const int xInput = analogRead(PIN_ANALOG_X) + xTrim;
    const int yInput = analogRead(PIN_ANALOG_Y) + yTrim;

    const float joyDelta = 1;
    const float xDelta = fmap(xInput, 0, 1023, -joyDelta, joyDelta);
    const float yDelta = fmap(yInput, 0, 1023, -joyDelta, joyDelta);

    x += xDelta;
    y += yDelta;

    const float zDelta = 0.5;
    if(digitalRead(BUTTON_UP) == LOW) 
      z += zDelta;
    else if (digitalRead(BUTTON_DOWN) == LOW)
      z -= zDelta;

    const float gripDelta = 0.2;
    if(digitalRead(BUTTON_RIGHT) == LOW) 
      grip = max(grip - gripDelta, GRIP_OPEN);
    else if (digitalRead(BUTTON_LEFT) == LOW)
      grip = min(grip + gripDelta, GRIP_CLOSED);

    sGrip.write(grip);

    manipulator.write(x, y, z);

    delay(DELAY);
  }

}



void loop() {}
