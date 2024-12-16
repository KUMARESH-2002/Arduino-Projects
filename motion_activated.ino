
// Pin definitions
const int pirPin = 2;    // PIR sensor input pin
const int buzzerPin = 8; // Buzzer output pin

// State variables
bool movementDetected = false;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  Serial.begin(9600);  // Initialize Serial Monitor
  Serial.println("Motion detection started");
}

void loop() {
  // Read PIR sensor
  int pirState = digitalRead(pirPin);
  
  // Check if motion is detected
  if (pirState == HIGH && !movementDetected) {
    movementDetected = true; // Set the movement detected flag
    
    // Sound the buzzer
    digitalWrite(buzzerPin, HIGH);
    delay(200); // Buzzer sounds for 200ms
    digitalWrite(buzzerPin, LOW);
    
    // Log the timestamp of detection
    logTimestamp();
    
    // Add a small delay to avoid multiple triggers
    delay(1000);
  } else if (pirState == LOW) {
    movementDetected = false; // Reset the flag when no movement is detected
  }
}

void logTimestamp() {
  // Get the current timestamp in milliseconds since start
  unsigned long currentMillis = millis();
  
  // Convert milliseconds to seconds and minutes for readability
  unsigned long seconds = currentMillis / 1000;
  unsigned long minutes = seconds / 60;
  seconds = seconds % 60;
  
  Serial.print("Movement detected at: ");
  Serial.print(minutes);
  Serial.print(" min ");
  Serial.print(seconds);
  Serial.println(" sec");
}
