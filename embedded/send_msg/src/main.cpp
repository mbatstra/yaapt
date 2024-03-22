#include <M5Stack.h>
#include "yaapt.h"

void setup() {
  M5.begin();
  Serial.begin(115200);
  Serial.println("hello");
}

void loop() {
  M5.update();
  if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 200)) {
    M5.Lcd.fillScreen(RED);
    // Serial.println("A");
    Serial.write("A", 1);
    M5.Lcd.print('A');
  }
  else if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 200)) {
    M5.Lcd.fillScreen(GREEN);
    Serial.println("B");
    M5.Lcd.print('B');
  }
  else if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 200)) {
    M5.Lcd.fillScreen(BLUE);
    Serial.println("C");
    M5.Lcd.print('C');
  }
  M5.Lcd.setCursor(0, 0);
}
