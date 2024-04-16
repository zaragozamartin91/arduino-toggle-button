# arduino-toggle-button

[![PlatformIO Registry](https://badges.registry.platformio.org/packages/zaragozamartin91/library/ArduinoToggleButton.svg)](https://registry.platformio.org/libraries/zaragozamartin91/ArduinoToggleButton)

Allows for toggling of components based on push buttons.

Example usage of toggle button to control a dimmable led:

```C++
#include <Arduino.h>
#include "ToggleButton.h"

int READ_PIN=PIN6;
int LED_PIN=9;

int LED_POWER_LEVELS[] = {0, 1, 2, 4, 8, 16, 32, 64, 128, 255};
int LED_POWER_LEVELS_L = sizeof(LED_POWER_LEVELS) / sizeof(LED_POWER_LEVELS[0]);

int v_ledPowerLevel = 0;

/* Declaring Toggle button */
void dimLed(int pressCount) {
  int powerLevelIndex = pressCount % LED_POWER_LEVELS_L;
  v_ledPowerLevel = LED_POWER_LEVELS[powerLevelIndex];
}
int readButtonSignal(int pin) {return digitalRead(pin);}
mz::ToggleButton v_toggle(READ_PIN, &readButtonSignal, &dimLed);

int v_pressCount = 0;

void setup() {
  pinMode(READ_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
  while(!Serial){};
}

void loop() {
  v_toggle.update();

  v_pressCount = v_toggle.getPressCount();
  Serial.print("v_pressCount: ");Serial.print(v_pressCount);Serial.print(" ; v_ledPowerLevel: ");Serial.println(v_ledPowerLevel);

  analogWrite(LED_PIN, v_ledPowerLevel);

  delay(100);
}
```

ToggleButton expects 2 parameters when constructed:
- toggleCallback: function to be invoked whenever a toggle happens. The number of total presses is passed as a function parameter.
- buttonSignalSupplier: function that reads a button signal and returns an integer value where 0 is OFF and 1 is ON

More features will come.
