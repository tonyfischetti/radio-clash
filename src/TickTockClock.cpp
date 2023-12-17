
#include "TickTockClock.h"

TickTockClock::TickTockClock()
    : year          {2023},
      month         {4},
      day           {25},
      hour          {2},
      display_hour  {2},
      minute        {46},
      is_pm_p       {false} {
    RTC_DS3231 rtc;
}


void TickTockClock::init() {
    rtc.begin();
}

// TODO: maybe I can do the snprintf-ing in main under a time
//       to reduce the amount of time each time tick takes
void TickTockClock::update() {
    now     = rtc.now();
    year    = now.year();
    month   = now.month();
    day     = now.day();
    hour    = now.hour();
    minute  = now.minute();

    snprintf(the_date, 11, "%d-%02d-%02d", year, month, day);

    setDisplayHour(hour);

    snprintf(the_time, 9, "%2d:%02d %s", display_hour, minute,
            is_pm_p ? "pm" : "am");
    snprintf(the_temp, 5, "%2d C",
            static_cast<int>(round(rtc.getTemperature())));
}


uint8_rc TickTockClock::lostPowerP() {
    return rtc.lostPower();
}


void TickTockClock::setTime(DateTime _dt) {
    rtc.adjust(_dt);
}

char* TickTockClock::getDate() {
    return the_date;
}

char* TickTockClock::getTime() {
    return the_time;
}

char* TickTockClock::getTemp() {
    return the_temp;
}

uint16_rc TickTockClock::getYear() const {
    return year;
}

uint8_rc TickTockClock::getMonth() const {
    return month;
}

uint8_rc TickTockClock::getDay() const {
    return day;
}

uint8_rc TickTockClock::getHour() const {
    return hour;
}

uint8_rc TickTockClock::getDisplayHour() const {
    return display_hour;
}

uint8_rc TickTockClock::getMinute() const {
    return minute;
}

void TickTockClock::setDisplayHour(uint8_rc _hour) {
    hour = _hour;
    if (hour >= 12) {
        is_pm_p = true;
    }
    else {
        is_pm_p = false;
    }
    display_hour = hour % 12;
    if (display_hour == 0) {
        display_hour = 12;
    }
}

uint8_rc TickTockClock::isPm() const {
    return is_pm_p;
}
