#include <SoftwareSerial.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
// Define pins
#define DHTPIN 2           // DHT11 data pin
#define DHTTYPE DHT11      // Define DHT type
#define GAS_SENSOR_PIN A0  // Gas sensor analog pin
#define RELAY_PIN 9        // Relay control pin (connected to relay IN pin)
#define BUZZER_PIN 10        // Buzzer pin
#define GSM_TX 7           // SIM900A TX pin
#define GSM_RX 8           // SIM900A RX pin
#define FLAME_SENSOR_PIN 11  // Flame sensor digital
#define TEMP_THRESHOLD 50  // Temperature threshold
#define GAS_THRESHOLD 70   // Gas threshold

#define IN1 4    // Motor driver IN1 pin connected to Arduino pin 4
#define IN2 5    // Motor driver IN2 pin connected to Arduino pin 5

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
// Set up SoftwareSerial for GSM communication
SoftwareSerial sim900(GSM_TX, GSM_RX);
int flame_data=0;

void setup() {
  Serial.begin(9600);
  sim900.begin(9600);      // Start communication with SIM900A at 9600 baud rate
  dht.begin();             // Initialize the DHT sensor
  lcd.init();         // Initialize the LCD
  lcd.backlight();      // Turn on the LCD backlight

  pinMode(GAS_SENSOR_PIN, INPUT);  // Gas sensor pin as input
  pinMode(RELAY_PIN, OUTPUT);      // Relay control pin as output
  // digitalWrite(RELAY_PIN, HIGH);    // Initially turn the relay off
     digitalWrite(IN1, HIGH);  // IN1 HIGH
  digitalWrite(IN2, LOW);   // IN2 LOW (forward direction)
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  pinMode(FLAME_SENSOR_PIN, INPUT); 

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Initialize GSM SIM900A module
  sim900.println("AT");  // Send AT command to initialize
  delay(1000);
  sim900.println("AT+CMGF=1");  // Set SMS to text mode
  delay(1000);
  sim900.println("AT+CSMP=17,167,0,0");  // Configure message format
  delay(1000);

  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read temperature, humidity, and gas sensor values
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int gasValue = analogRead(GAS_SENSOR_PIN);
  int gasPercentage = map(gasValue, 0, 1023, 0, 100);  // Map gas value to 0-100 percentage
  int flameDetected = digitalRead(FLAME_SENSOR_PIN);  // Flame sensor is active LOW

  // Print readings on serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");
  
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  
  Serial.print("Gas Level (0-100): ");
  Serial.println(gasPercentage);

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");
  
  lcd.setCursor(0, 1);
  lcd.print("Gas: ");
  lcd.print(gasPercentage);
  lcd.print("%");

   lcd.setCursor(8, 1);
  lcd.print("F: ");
  lcd.print(flameDetected);

  // Check if temperature or gas level exceeds the thresholds
  if (temperature > TEMP_THRESHOLD || gasPercentage > GAS_THRESHOLD || flameDetected == LOW) {
    // digitalWrite(RELAY_PIN, LOW);  // Turn relay ON (motor ON)
    digitalWrite(IN1, HIGH);  // IN1 HIGH
    digitalWrite(IN2, LOW);   // IN2 LOW (forward direction)
    digitalWrite(BUZZER_PIN, HIGH); // Turn on buzzer
    sendSMS(temperature, humidity, gasPercentage, flameDetected);  // Send alert via SMS
    Serial.println("Relay ON");
    Serial.println("BUZZER ON");
    Serial.println("Flame Detected");
  } else {
    // digitalWrite(RELAY_PIN, HIGH);   // Turn relay OFF (motor OFF)
    digitalWrite(IN1, LOW);  // IN1 HIGH
    digitalWrite(IN2, LOW);   // IN2 LOW (forward direction)
    digitalWrite(BUZZER_PIN, LOW); // Turn on buzzer
    Serial.println("Relay OFF");
    Serial.println("BUZZER OFF");
    Serial.println("Flame NOT Detected");
  }

  delay(5000);  // Wait for 5 seconds before next reading
}

// Function to send SMS
void sendSMS(float temp, float hum, int gasPercentage, bool flameDetected) {
  String message = "Alert! Temp: " + String(temp) + "C, Hum: " + String(hum) +
                   "%, Gas: " + String(gasPercentage) + "%";
if (!flameDetected) {
    message += ", Flame Detected!";
  }
  
  // Prepare to send SMS
  sim900.println("AT+CMGS=\"+919951017708\"");  // Replace with actual phone number
  delay(1000);
  sim900.println(message);  // Send the message
  delay(100);
  sim900.write(26);  // Send Ctrl+Z to end the SMS command
  delay(5000);  // Wait for SMS to send

  Serial.println("SMS Sent!");
}
