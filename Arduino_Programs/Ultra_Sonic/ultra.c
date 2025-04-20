// Define pins for ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;

// Variable for the duration of the pulse and the calculated distance
long duration;
int distance;

void setup() {
  // Initialize the serial communication for debugging
  Serial.begin(9600);
  
  // Set the trigger pin as output and the echo pin as input
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Trigger the ultrasonic sensor by setting the trigger pin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echo pin, which returns the time in microseconds for the sound wave to bounce back
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance: speed of sound is ~343 m/s or ~0.0343 cm/microsecond
  distance = duration * 0.0343 / 2;
  
  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Small delay to prevent overwhelming the sensor
  delay(200);
}
