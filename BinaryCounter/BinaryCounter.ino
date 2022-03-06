#include <Adafruit_CircuitPlayground.h>

int pixel[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int digits = 10;

void clearit()  {
  for (int led = 0; led <= digits; led++) {
    CircuitPlayground.setPixelColor(led, 0, 80, 80);
    delay(100);
  }
}

void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();
  clearit();
}

int wait = 1000;

void loop() {

  delay(wait);

  for (int decimalNumber = 1; decimalNumber <= pow(2, digits) - 1; decimalNumber++) {
    for (int binaryDigit = 1; binaryDigit <= digits; binaryDigit++) {
      int power = pow(2, binaryDigit);
      int num = int(power);
      int denom = int(power / 2);
      pixel[binaryDigit - 1] = decimalNumber % num / denom;
    }
    for (int led = 0; led <= digits; led++) {
      if (pixel[led] == 1) {
        CircuitPlayground.setPixelColor(led, 255, 0, 0);
      }
      else {
        CircuitPlayground.setPixelColor(led, 0, 0, 0);
      }
    }

    delay(wait);
  }
  clearit();
}
