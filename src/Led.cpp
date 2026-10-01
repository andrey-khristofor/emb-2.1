#include "Led.h"

constexpr int blinkDebounceMs = 200;

Led::Led(uint8_t _pin)
{
    pin = _pin;
    pinMode(pin, OUTPUT);
}

void Led::setMode(LedMode _mode)
{
    mode = _mode;
}

void Led::update()
{
    switch (mode)
    {
    case LedMode::Off:
        digitalWrite(pin, LOW);
        break;

    case LedMode::On:
        digitalWrite(pin, HIGH);
        break;

    case LedMode::Blink:
        if (millis() - lastToggle > blinkDebounceMs)
        {
            digitalWrite(pin, !digitalRead(pin));
            lastToggle = millis();
        }
        break;
    }
}
