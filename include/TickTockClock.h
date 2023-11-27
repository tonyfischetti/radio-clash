
#pragma once

#include "deebug.hpp"
#include "common.h"

#include <RTClib.h>


class TickTockClock {
    public:
        TickTockClock()                       noexcept;
        void init()                           noexcept;
        void update()                         noexcept;
        uint8_rc lostPowerP()                 noexcept;
        void setTime(DateTime)                noexcept;
        char* getDate()                       noexcept;
        char* getTime()                       noexcept;
        char* getTemp()                       noexcept;
        uint16_rc getYear()             const noexcept;
        uint8_rc getMonth()             const noexcept;
        uint8_rc getDay()               const noexcept;
        uint8_rc getHour()              const noexcept;
        uint8_rc getDisplayHour()       const noexcept;
        uint8_rc getMinute()            const noexcept;
        void setDisplayHour(uint8_rc)         noexcept;
        uint8_rc isPm()                 const noexcept;

    private:
        DateTime now;
        RTC_DS3231 rtc;

        char the_date[11];
        char the_time[9];
        char the_temp[5];

        uint16_rc year;
        uint8_rc month;
        uint8_rc day;
        uint8_rc hour;
        uint8_rc display_hour;
        uint8_rc minute;
        uint8_rc is_pm_p;
};

