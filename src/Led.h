#pragma once

#include <Arduino.h>

#include "led-mode.h"

class Led
{
private:
    uint8_t pin;
    LedMode mode = LedMode::Off;
    unsigned long lastToggle = 0;

public:
    Led(uint8_t);

    void setMode(LedMode);
    void update();
};