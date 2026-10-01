#include <Arduino.h>

#include "Led.h"
#include "led-mode.h"

constexpr uint8_t LED_GPIO = 5;
constexpr uint8_t BUTTON_GPIO = 7;

constexpr uint8_t DEBOUNCE = 80;

Led led(LED_GPIO);

LedMode mode = LedMode::Off;
LedMode nextMode();

volatile bool isButtonPressed = false;

uint32_t lastPress = 0;

IRAM_ATTR void handleButton()
{
  isButtonPressed = true;
}

void setup()
{
  Serial.begin(115200);

  pinMode(BUTTON_GPIO, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(BUTTON_GPIO), handleButton, RISING);
}

void loop()
{
  if (isButtonPressed)
  {
    isButtonPressed = false;

    uint32_t now = millis();

    if (now - lastPress >= DEBOUNCE)
    {
      mode = nextMode();
      led.setMode(mode);
      Serial.println(mode);
    }

    lastPress = now;
  }

  led.update();
}

LedMode nextMode()
{
  switch (mode)
  {
  case LedMode::Off:
    return LedMode::Blink;
  case LedMode::Blink:
    return LedMode::On;
  case LedMode::On:
    return LedMode::Off;
  }
}
