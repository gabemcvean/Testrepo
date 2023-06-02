#include <Adafruit_CircuitPlayground.h>

volatile int ModeControl = 0;

const int switchPin = 7;
const int leftButtonPin = 4;
const int rightButtonPin = 5;

void setup() {
  CircuitPlayground.begin();
  attachInterrupt(digitalPinToInterrupt(leftButtonPin), decreaseMode, FALLING);
  attachInterrupt(digitalPinToInterrupt(rightButtonPin), increaseMode, FALLING);
  attachInterrupt(digitalPinToInterrupt(switchPin), switchMode, CHANGE);
}

void loop() {
  switch (ModeControl) {
    case 0:
      rainbow();
      break;
    case 1:
      flash();
      break;
    case 2:
      twinkle();
      break;
    case 3:
      pulse();
      break;
    case 4:
      fade();
      break;
    default:
      break;
  }
}

void decreaseMode() {
  ModeControl--;
  if (ModeControl < 0) {
    ModeControl = 4;
  }
}

void increaseMode() {
  ModeControl++;
  if (ModeControl > 4) {
    ModeControl = 0;
  }
}

void switchMode() {
  if (CircuitPlayground.slideSwitch()) {
    CircuitPlayground.clearPixels();
    CircuitPlayground.setBrightness(0);
  } else {
    CircuitPlayground.setBrightness(100);
  }
}

void rainbow() {
  uint32_t offset = millis() / 100;
  for (int i = 0; i < 10; ++i) {
    CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(((i * 256 / 10) + offset) & 255));
  }
  delay(50);
}

void flash() {
  for (int i = 0; i < 10; ++i) {
    CircuitPlayground.setPixelColor(i, 0, 0, 255);
  }
  delay(100);
  for (int i = 0; i < 10; ++i) {
    CircuitPlayground.setPixelColor(i, 0, 0, 0);
  }
  delay(100);
}

void twinkle() {
  int randomIndex = random(0, 10); // generate a random number between 0 and 9
  CircuitPlayground.setPixelColor(randomIndex, 255, 0, 0); // light up the randomly selected LED
  delay(500);
  CircuitPlayground.setPixelColor(randomIndex, 0, 0, 0); // turn off the LED
  delay(500);
}


void pulse() {
  for (int i = 0; i <= 255; ++i) {
    int brightness = abs(i - 128);
    for (int j = 0; j < 10; ++j) {
      CircuitPlayground.setPixelColor(j, brightness, brightness, brightness);
    }
    delay(5);
  }
}

void fade() {
  for (int i = 0; i <= 200; ++i) {
    int brightness = i;
    for (int j = 0; j < 10; ++j) {
      CircuitPlayground.setPixelColor(j, brightness, 0, brightness);
    }
    delay(5);
  }
  for (int i = 200; i >= 0; --i) {
    int brightness = i;
    for (int j = 0; j < 10; ++j) {
      CircuitPlayground.setPixelColor(j, brightness, 0, brightness);
    }
    delay(5);
  }
}
