#include <TFT.h>
#include <SPI.h>

#define CS   10
#define DC   9
#define RESET  8

#define JOY_X 0
#define JOY_Y 1

TFT myScreen = TFT(CS, DC, RESET);
int prevX = -100;
int prevY = -100;

void setup() {
  myScreen.begin();
  myScreen.setRotation(0);
  myScreen.background(0,0,0);
  delay(200);
}


void loop() {
  int x = analogRead(JOY_X);
  int y = analogRead(JOY_Y);

  x = map(x, 0, 1024, 10, myScreen.width()-10);
  y = map(y, 0, 1024, myScreen.height()-11, 9);

  myScreen.stroke(0, 0, 0);
  myScreen.circle(prevX, prevY, 10);

  myScreen.stroke(255,255,255);
  myScreen.circle(x, y, 10);

  prevX = x;
  prevY = y;

  delay(20);
}

