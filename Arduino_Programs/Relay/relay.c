// Define the pin connected to the relay
int relayPin = 7;

void setup() {
  // Initialize the relay pin as an output
  pinMode(relayPin, OUTPUT);
  
  // Ensure the relay is off initially
  digitalWrite(relayPin, LOW);
}

void loop() {
  // Turn the relay ON (HIGH state)
  digitalWrite(relayPin, HIGH);
  
  // Wait for 5 seconds
  delay(1000);
  
  // Turn the relay OFF (LOW state)
  digitalWrite(relayPin, LOW);
  
  // Wait for 5 seconds
  delay(1000);
}
