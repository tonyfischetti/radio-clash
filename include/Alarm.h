
#pragma once

#include "deebug.hpp"
#include "common.h"

#include <Sixteen.h>
#include "TickTockClock.h"
#include <RTClib.h>

class Alarm {
    public:
        Alarm()                        noexcept;

        void arm()                     noexcept;
        void disarm()                  noexcept;
        void setHour(uint8_t)          noexcept;
        void setMinute(uint8_t)        noexcept;
        uint8_t getHour()        const noexcept;
        uint8_t getDisplayHour() const noexcept;
        uint8_t getMinute()      const noexcept;
        uint8_t isPm()           const noexcept;
        uint8_t isArmed()        const noexcept;

    private:
        uint8_t is_armed_p;
        uint8_t target_hour;
        uint8_t target_display_hour;
        uint8_t target_minute;
        uint8_t is_pm_p;
};

