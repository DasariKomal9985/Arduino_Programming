#include <Servo.h>  // Include the Servo library

Servo myServo;      // Create a servo object

int servoPin = 9;   // Pin where the servo is connected

void setup() {
  myServo.attach(servoPin);  // Attach the servo to pin 9
}

void loop() {
  // Rotate servo from 0 to 180 degrees
  for (int pos = 0; pos <= 180; pos++) {
    myServo.write(pos);      // Move servo to the current position
    delay(15);               // Wait 15 ms to reach the position
  }

  // Rotate servo from 180 to 0 degrees
  for (int pos = 180; pos >= 0; pos--) {
    myServo.write(pos);      // Move servo to the current position
    delay(15);               // Wait 15 ms to reach the position
  }
}
