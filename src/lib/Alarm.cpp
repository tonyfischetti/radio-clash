
#include "Alarm.h"

Alarm::Alarm() noexcept
    : is_armed_p          {false},
      target_hour         {7},
      target_display_hour {7},
      target_minute       {0},
      is_pm_p             {false} {
}

void Alarm::arm() noexcept {
    deebug("alarm", "arming alarm");
    is_armed_p = true;
}

void Alarm::disarm() noexcept {
    deebug("alarm", "disarming alarm");
    is_armed_p = false;
}

uint8_t Alarm::getHour() const noexcept {
    return target_hour;
}

uint8_t Alarm::getDisplayHour() const noexcept {
    return target_display_hour;
}

uint8_t Alarm::getMinute() const noexcept {
    return target_minute;
}

void Alarm::setHour(uint8_t _hour) noexcept {
    target_hour = _hour;
    if (target_hour >= 12)
        is_pm_p = true;
    else
        is_pm_p = false;
    target_display_hour = target_hour % 12;
    if (target_display_hour == 0)
        target_display_hour = 12;
}

void Alarm::setMinute(uint8_t _minute) noexcept {
    target_minute = _minute;
}

uint8_t Alarm::isPm() const noexcept {
    return is_pm_p;
}

uint8_t Alarm::isArmed() const noexcept {
    return is_armed_p;
}

