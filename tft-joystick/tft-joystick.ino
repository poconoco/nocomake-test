/*
 * (c) Leonid Yurchenko
 * https://www.youtube.com/@nocomake
 */

#include <TFT.h>
#include <SPI.h>

#define CS     10
#define DC     9
#define RESET  8

#define JOY_X  0
#define JOY_Y  1

#define R 10

TFT myScreen = TFT(CS, DC, RESET);
int prevX = -100;
int prevY = -100;

void setup() {
  myScreen.begin();
  myScreen.setRotation(0);
  myScreen.background(0,0,0);
}

void loop() {
  int x = analogRead(JOY_X);
  int y = analogRead(JOY_Y);

  x = map(x, 0, 1023, R, myScreen.width() - R - 1);
  y = map(y, 0, 1023, myScreen.height() - R - 1, R);

  if (prevX != x || prevY != y) {  // Lowers the flickering
    myScreen.stroke(0, 0, 0);
    myScreen.circle(prevX, prevY, R);

    myScreen.stroke(255,255,255);
    myScreen.circle(x, y, R);
    prevX = x;
    prevY = y;
  }

  delay(20);
}
