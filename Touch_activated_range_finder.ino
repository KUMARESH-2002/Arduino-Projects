#include <SevSeg.h>
SevSeg sevseg;
#define ECHO_PIN 13
#define TRIG_PIN 5
#define button 25


void setup() {
  Serial.begin(115200);
  byte numDigits = 4;
  byte digitPins[] = {0, 3, 4, 2};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12 ,13};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(button, INPUT);
}


int readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

int prevDistance=400;
bool buttonState = false;

void loop() {
  int distance=readDistanceCM();
  buttonState = digitalRead(button);
  if (buttonState == HIGH){
  sevseg.setNumber(distance);
  delay(5);
  sevseg.refreshDisplay();
}
  prevDistance=distance;
}
