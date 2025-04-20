// Define joystick pins
int joyX = A0;  // X-axis connected to A0
int joyY = A1;  // Y-axis connected to A1
int joyButton = 8;  // Button connected to pin 8

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
  
  // Set the button pin as input with an internal pull-up resistor
  pinMode(joyButton, INPUT_PULLUP);
}

void loop() {
  // Read the joystick position values
  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);
  
  // Read the button state (LOW when pressed)
  int buttonState = digitalRead(joyButton);
  
  // Print joystick X and Y values to the serial monitor
  Serial.print("X-axis: ");
  Serial.print(xValue);
  Serial.print(" | Y-axis: ");
  Serial.print(yValue);
  
  // Check if the button is pressed
  if (buttonState == LOW) {
    Serial.println(" | Button Pressed");
  } else {
    Serial.println(" | Button Released");
  }
  
  // Small delay to avoid overwhelming the serial monitor
  delay(200);
}
