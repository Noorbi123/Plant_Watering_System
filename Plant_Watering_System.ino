// Pin definitions
const int soilSensorPin = A0;    // Analog pin for soil moisture sensor
const int relayPin = 7;          // Digital pin for relay module
const int dryThreshold = 600;    // Moisture threshold (adjust based on your sensor)
const int wetThreshold = 400;    // Moisture threshold (adjust based on your sensor)

// Variables
int soilMoistureValue = 0;
bool pumpState = false;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(relayPin, OUTPUT);
  pinMode(soilSensorPin, INPUT);
  
  // Ensure pump is off at startup
  digitalWrite(relayPin, HIGH);  // HIGH = off for most relay modules
}

void loop() {
  // Read soil moisture value
  soilMoistureValue = analogRead(soilSensorPin);
  
  // Print value to serial monitor for debugging
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoistureValue);
  
  // Check if soil is too dry and pump is off
  if (soilMoistureValue > dryThreshold && !pumpState) {
    digitalWrite(relayPin, LOW);  // Turn on pump
    pumpState = true;
    Serial.println("Pump ON - Soil too dry");
  }
  
  // Check if soil is wet enough and pump is on
  else if (soilMoistureValue < wetThreshold && pumpState) {
    digitalWrite(relayPin, HIGH); // Turn off pump
    pumpState = false;
    Serial.println("Pump OFF - Soil moist enough");
  }
  
  // Add delay to prevent rapid switching
  delay(1000);  // Check every 1 second
}
