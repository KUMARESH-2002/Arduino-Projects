const int trigPin = 7;
const int echoPin = 6;
const int touchPin = 8;

// Define countdown timer
int countdownTime = 10; 
const int obstacleDistanceThreshold = 10;  
bool countdownActive = false;


const int segmentPins[] = {2, 3, 4, 5, 9, 10, 11, 12}; 


unsigned long startTime;
int displayValue = countdownTime;


void setupPins() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(touchPin, INPUT);
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
}

// Function to measure distance
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}


void displayNumber(int num) {
  const byte digitCode[10] = {
    0b11000000, // 0
    0b11111001, // 1
    0b10100100, // 2
    0b10110000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b10000010, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b10010000  // 9
  };
  
  if (num >= 0 && num <= 9) {
    byte segments = digitCode[num];
    for (int i = 0; i < 8; i++) {
      digitalWrite(segmentPins[i], !(segments & (1 << i)));
    }
  }
}


void displayError() {
  byte errorCode = 0b10000110; // Code to display "E"
  for (int i = 0; i < 8; i++) {
    digitalWrite(segmentPins[i], !(errorCode & (1 << i)));
  }
}


void startCountdown() {
  countdownActive = true;
  startTime = millis();
}


void resetCountdownIfObstacleDetected() {
  if (getDistance() < obstacleDistanceThreshold) {
    startCountdown();  
    displayValue = countdownTime; 
  }
}
void updateCountdownDisplay() {
  int elapsed = (millis() - startTime) / 1000;
  displayValue = countdownTime - elapsed;
  if (displayValue >= 0) {
    displayNumber(displayValue);
  } else {
    countdownActive = false;
    displayError(); // Show "E" if countdown completes
  }
}

void setup() {
  setupPins();
  Serial.begin(9600);
  displayNumber(countdownTime);
}

void loop() {
  
  if (digitalRead(touchPin) == HIGH && !countdownActive) {
    startCountdown();
  }
  if (countdownActive) {
    resetCountdownIfObstacleDetected();
    updateCountdownDisplay();
  }
}
