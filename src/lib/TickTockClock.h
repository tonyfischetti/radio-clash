
#pragma once

#include "deebug.hpp"
#include "common.h"

#include <RTClib.h>


class TickTockClock {
    public:
        TickTockClock()                       noexcept;
        void init()                           noexcept;
        void update()                         noexcept;
        uint8_t lostPowerP()                  noexcept;
        void setTime(DateTime)                noexcept;
        char* getDate()                       noexcept;
        char* getTime()                       noexcept;
        char* getTemp()                       noexcept;
        uint16_t getYear()              const noexcept;
        uint8_t getMonth()              const noexcept;
        uint8_t getDay()                const noexcept;
        uint8_t getHour()               const noexcept;
        uint8_t getDisplayHour()        const noexcept;
        uint8_t getMinute()             const noexcept;
        void setDisplayHour(uint8_t)          noexcept;
        uint8_t isPm()                  const noexcept;

    private:
        DateTime now;
        RTC_DS3231 rtc;

        char the_date[11];
        char the_time[9];
        char the_temp[5];

        uint16_t year;
        uint8_t month;
        uint8_t day;
        uint8_t hour;
        uint8_t display_hour;
        uint8_t minute;
        uint8_t is_pm_p;
};

