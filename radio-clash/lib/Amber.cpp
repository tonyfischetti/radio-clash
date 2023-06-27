
#include "Amber.h"

Amber::Amber(const uint8_t _address, TickTockClock& _rtc)
    : rtc(_rtc), seg_address{_address}, brightness{15} {
}

void Amber::init() {
    seg7.begin(seg_address);
}

void Amber::update() {
    int tmp = static_cast<int>(rtc.getDisplayHour()) * 100 + rtc.getMinute();
    seg7.print(tmp);
    seg7.drawColon(true);
    seg7.writeDisplay();
}

void Amber::setBrightness(const uint8_t new_brightness) {
    brightness = new_brightness;
    if (brightness > 15)
        brightness = 0;
    deebug("amber", "new brightness: %d", brightness);
    seg7.setBrightness(brightness);
}

void Amber::nextBrightness() {
    setBrightness(brightness + 5);
}
