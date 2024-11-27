#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 or 0x3F for a 16x2 LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Replace 0x27 with your LCD address

void setup() {
  // Initialize the LCD
  lcd.init();
  
  // Turn on the backlight
  lcd.backlight();
  
  // Print a message to the LCD
  lcd.setCursor(0, 0);   // Set cursor to the first column, first row
  lcd.print("Hello Komal");  // Print message

  lcd.setCursor(0, 1);   // Set cursor to the first column, second row
  lcd.print("Welcome");
}

void loop() {
  // Optionally, update the display in the loop
  delay(5000);  // Wait for 1 second
  
  lcd.clear();  // Clear the display
  lcd.setCursor(0, 0);
  lcd.print("Counting: ");
  
  static int count = 0;
  lcd.setCursor(10, 0);  // Set cursor for counting
  lcd.print(count++);
  
  delay(1000);  // Wait for 1 second
}
