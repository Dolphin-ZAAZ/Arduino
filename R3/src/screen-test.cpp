#include <MCUFRIEND_kbv.h>

MCUFRIEND_kbv tft;

void setup() {
  Serial.begin(9600);
  tft.begin(0x9486);
  tft.fillScreen(0xF800); // Red screen
  delay(2000);
  tft.fillScreen(0x0000); // Black screen
  delay(1000);
}

void loop() {
  tft.fillScreen(0xF800); // Red screen
  delay(2000);
  tft.fillScreen(0x0000); // Black screen
  delay(1000);
}