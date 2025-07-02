// Include the configured library
#include <TFT_eSPI.h>
#include <SPI.h>

// Create an instance of the TFT_eSPI class
TFT_eSPI tft = TFT_eSPI();

void setup() {
  // Initialize the display
  tft.init();
  
  // Set the screen rotation. 0 & 2 are portrait, 1 & 3 are landscape.
  // The correct orientation depends on your screen's internal layout.
  // Try 0, 1, 2, or 3 to see which one is correct.
  tft.setRotation(1); 

  // Fill the screen with black
  tft.fillScreen(TFT_BLACK);
  
  // Set the text color to white and the background to black
  tft.setTextColor(TFT_WHITE, TFT_BLACK); 
  
  // Set the text "datum" (font size) to 4
  tft.setTextDatum(MC_DATUM); // Middle-Center alignment
  tft.setTextSize(2);

  // Print text to the screen
  // tft.drawString(text, x, y);
  tft.drawString("Hello from Arduino R4!", tft.width() / 2, tft.height() / 2 - 20);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.drawString("Screen: RM68140 320x480", tft.width() / 2, tft.height() / 2 + 20);
}

void loop() {
  // Nothing to do here for this example
}