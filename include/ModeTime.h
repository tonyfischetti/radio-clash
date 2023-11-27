
#pragma once

#include "deebug.hpp"
#include "common.h"

#include <elapsedMillis.h>

#include <Sixteen.h>
#include "TickTockClock.h"
#include "LBMode.h"


class ModeTime final : public LBMode {
    public:
        ModeTime(TickTockClock&, Sixteen&) noexcept;

        const char* getModeName() const noexcept override;

        uint8_rc tick()           noexcept;
        uint8_rc reCw()           noexcept override;
        uint8_rc reCcw()          noexcept override;
        uint8_rc rePress()        noexcept override;
        /*
        uint8_rc remOK()          noexcept override;
        uint8_rc remCircleLeft()  noexcept override;
        uint8_rc remCircleRight() noexcept override;
        */
        uint8_rc display()        noexcept override;

        const char* mode_name {"Time mode"};


    private:
        TickTockClock& rtc;
        Sixteen& sixteen;

        elapsedMillis blink_timer;

        uint64_rc set_time_time;

        const uint32_rc SET_TIME_TIMEOUT {5000};
        const uint16_rc BLINK_FREQUENCY  {500};

        uint16_rc selected_year;
        uint8_rc  selected_month;
        uint8_rc  selected_day;
        uint8_rc  selected_hour;
        uint8_rc  selected_minute;
        uint8_rc  selected_pm_p;

        uint8_rc selection_bookmark;
        
        uint8_rc blink_on_p;
};

