#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

const int buzzerPin = 4;

const int redPin   = 5;
const int greenPin = 6;
const int bluePin  = 9;

const int buttonPin = 12;

int safeDistance = 0;
bool armed = false;
bool alarmActive = false;

unsigned long buttonPressTime = 0;
bool buttonPressed = false;

void setup() {
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);

  pinMode(buzzerPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  Wire.begin();
  sensor.init();
  sensor.setTimeout(500);

  setColor(0, 255, 0);
}

void setColor(int red, int green, int blue) {
  analogWrite(redPin,   255 - red);    // Common Anode: invert values
  analogWrite(greenPin, 255 - green);
  analogWrite(bluePin,  255 - blue);
}

void resetSystem() {
  armed = false;
  alarmActive = false;
  safeDistance = 0;
  digitalWrite(buzzerPin, LOW);
  setColor(0, 255, 0); // Green
}

void loop() {
  int distance = sensor.readRangeSingleMillimeters();
  if (distance < 30) {
    delay(100);
    return;
  }

  // Button Handling
  if (digitalRead(buttonPin) == LOW) {
    if (!buttonPressed) {
      buttonPressed = true;
      buttonPressTime = millis();
    }

    if (millis() - buttonPressTime > 800) {   // Hold 800ms to reset
      resetSystem();
      delay(300);
      while (digitalRead(buttonPin) == LOW);
      buttonPressed = false;
    }
  } 
  else {
    if (buttonPressed) {
      if (!armed && !alarmActive) {
        safeDistance = distance;
        armed = true;
        setColor(255, 0, 0); // Red - Armed
      }
      buttonPressed = false;
    }
  }

  // Alarm Logic
  if (armed && distance < safeDistance - 40) {
    alarmActive = true;
  }

  if (alarmActive) {
    digitalWrite(buzzerPin, HIGH);
    setColor(255, 0, 0);
    delay(220);

    digitalWrite(buzzerPin, LOW);
    setColor(0, 0, 255);
    delay(220);
  } 
  else if (armed) {
    setColor(255, 0, 0);
    digitalWrite(buzzerPin, LOW);
    delay(150);
  } 
  else {
    setColor(0, 255, 0);
    digitalWrite(buzzerPin, LOW);
  }

  delay(50);
}
