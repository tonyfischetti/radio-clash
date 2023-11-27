
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
        void setHour(uint8_rc)          noexcept;
        void setMinute(uint8_rc)        noexcept;
        uint8_rc getHour()        const noexcept;
        uint8_rc getDisplayHour() const noexcept;
        uint8_rc getMinute()      const noexcept;
        uint8_rc isPm()           const noexcept;
        uint8_rc isArmed()        const noexcept;

    private:
        uint8_rc is_armed_p;
        uint8_rc target_hour;
        uint8_rc target_display_hour;
        uint8_rc target_minute;
        uint8_rc is_pm_p;
};

