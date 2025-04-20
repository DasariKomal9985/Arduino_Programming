#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16x2 or 20x4 LCD (adjust based on your module)
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  // Initialize the LCD
  lcd.init();
  
  // Turn on the backlight
  lcd.backlight();
  
  // Print a message to the LCD.
  lcd.setCursor(0, 0); // Start at the first column, first row
  lcd.print("Hello,Komal");
  
  lcd.setCursor(0, 1); // Start at the first column, second row
  lcd.print("I2C Test done");
}

void loop() {
  // Add your code here if needed
}
