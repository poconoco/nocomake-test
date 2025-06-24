#include <Arduino.h>
#include <Encoder.h>

const int encoderPinA = 5;
const int encoderPinB = 6;

Encoder encoder(encoderPinA, encoderPinB);

void setup() {
  int lastPosition = 99999;
  int position = 0;
  encoder.write(0);

  Serial.begin(9600);

  Serial.println("Encoder Test");
  encoder.write(0);

  while (true) {
    position = encoder.read();
    if (position != lastPosition) {
      Serial.print("Position: ");
      Serial.println(position);
      lastPosition = position;
    }
    delay(1);  }
}

