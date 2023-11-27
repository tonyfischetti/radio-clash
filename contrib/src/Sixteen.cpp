
#include <stdint.h>
#include <Arduino.h>

#include "Sixteen.h"


void clear_line(char* aline) {
    memset(aline, '\0', 17);
}


Sixteen::Sixteen(const uint8_t address) : lcd(address, 16, 2) {
    clear_line(line0);
    clear_line(line1);
    clear_line(actual_line0);
    clear_line(actual_line1);
}

void Sixteen::clearLine0() {
    clear_line(actual_line0);
}

void Sixteen::clearLine1() {
    clear_line(actual_line1);
}

void Sixteen::init() {
    lcd.init();
    lcd.backlight();
}

void Sixteen::update() {

    // check if line0 has changed
    if (strcmp(line0, actual_line0)) {
        clear_line(actual_line0);
        strncpy(actual_line0, line0, 17);
        clear_line(line0);
        lcd.setCursor(0, 0);
        lcd.print(actual_line0);
    }

    // check if line1 has changed
    if (strcmp(line1, actual_line1)) {
        clear_line(actual_line1);
        strncpy(actual_line1, line1, 17);
        clear_line(line1);
        lcd.setCursor(0, 1);
        lcd.print(actual_line1);
    }
}

