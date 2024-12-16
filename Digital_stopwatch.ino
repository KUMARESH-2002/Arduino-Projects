
#include <LiquidCrystal.h>

// LCD pin configuration
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Button pins
const int startStopButtonPin = 6;
const int resetButtonPin = 7;

// Stopwatch variables
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
bool running = false;
bool lastStartStopButtonState = LOW;
bool lastResetButtonState = LOW;

void setup() {
  lcd.begin(16, 2);  // Initialize a 16x2 LCD display
  pinMode(startStopButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);
  
  lcd.setCursor(0, 0);
  lcd.print("Simple Stopwatch");
  delay(1000);
  lcd.clear();
}

void loop() {
  // Read the current state of the buttons
  bool startStopButtonState = digitalRead(startStopButtonPin) == LOW;
  bool resetButtonState = digitalRead(resetButtonPin) == LOW;

  // Check if the start/stop button was pressed
  if (startStopButtonState && !lastStartStopButtonState) {
    running = !running;  // Toggle stopwatch running state
    if (running) {
      startTime = millis() - elapsedTime;  // Continue from where we stopped
    }
  }
  lastStartStopButtonState = startStopButtonState;

  // Check if the reset button was pressed
  if (resetButtonState && !lastResetButtonState) {
    running = false;
    elapsedTime = 0;
  }
  lastResetButtonState = resetButtonState;

  // Update the elapsed time if the stopwatch is running
  if (running) {
    elapsedTime = millis() - startTime;
  }

  // Display the elapsed time on the LCD
  displayTime(elapsedTime);
}

void displayTime(unsigned long time) {
  unsigned long totalSeconds = time / 1000;
  unsigned long minutes = totalSeconds / 60;
  unsigned long seconds = totalSeconds % 60;
  unsigned long milliseconds = (time % 1000) / 10;

  lcd.setCursor(0, 0);
  lcd.print("Time:");
  lcd.setCursor(0, 1);
  lcd.print(minutes < 10 ? "0" : "");  // Add leading zero if < 10
  lcd.print(minutes);
  lcd.print(":");
  lcd.print(seconds < 10 ? "0" : "");  // Add leading zero if < 10
  lcd.print(seconds);
  lcd.print(".");
  lcd.print(milliseconds < 10 ? "0" : "");  // Add leading zero if < 10
  lcd.print(milliseconds);
}
