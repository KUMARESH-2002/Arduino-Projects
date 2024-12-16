
// Pin Definitions
const int IR_SENSOR_IN = 2;       
const int IR_SENSOR_OUT = 3;      
const int ULTRASONIC_TRIG = 4;    
const int ULTRASONIC_ECHO = 5;    
const int SEGMENT_PINS[] = {6, 7, 8, 9, 10, 11, 12};

int peopleCount = 0;
float measureDistance() {
  digitalWrite(ULTRASONIC_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG, LOW);
  
  float duration = pulseIn(ULTRASONIC_ECHO, HIGH);
  return (duration * 0.034) / 2; // Convert to cm
}
void displayNumber(int number) {
  const bool segmentMap[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 0, 1, 1}  // 9
  };
  
  for (int i = 0; i < 7; i++) {
    digitalWrite(SEGMENT_PINS[i], segmentMap[number % 10][i]);
  }
}
void updatePeopleCount() {
  bool entryDetected = digitalRead(IR_SENSOR_IN) == HIGH;
  bool exitDetected = digitalRead(IR_SENSOR_OUT) == HIGH;
  float distance = measureDistance();

  if (entryDetected && distance < 30) {
    peopleCount++;
    delay(500); // Debounce delay
  } else if (exitDetected && distance < 30) {
    peopleCount--;
    delay(500); // Debounce delay
  }
}

void setup() {
  pinMode(IR_SENSOR_IN, INPUT);
  pinMode(IR_SENSOR_OUT, INPUT);
  pinMode(ULTRASONIC_TRIG, OUTPUT);
  pinMode(ULTRASONIC_ECHO, INPUT);

 
  for (int i = 0; i < 7; i++) {
    pinMode(SEGMENT_PINS[i], OUTPUT);
  }
  
  Serial.begin(9600);
}

void loop() {
  updatePeopleCount();
  displayNumber(peopleCount);
  
  Serial.print("People Count: ");
  Serial.println(peopleCount);
}
