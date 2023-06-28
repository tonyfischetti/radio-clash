
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

        uint8_t tick()           noexcept;
        uint8_t reCw()           noexcept override;
        uint8_t reCcw()          noexcept override;
        uint8_t rePress()        noexcept override;
        /*
        uint8_t remOK()          noexcept override;
        uint8_t remCircleLeft()  noexcept override;
        uint8_t remCircleRight() noexcept override;
        */
        uint8_t display()        noexcept override;

        const char* mode_name {"Time mode"};


    private:
        TickTockClock& rtc;
        Sixteen& sixteen;

        elapsedMillis blink_timer;

        uint64_t set_time_time;

        const uint32_t SET_TIME_TIMEOUT = 5000;
        const uint16_t BLINK_FREQUENCY = 500;

        uint16_t selected_year;
        uint8_t  selected_month;
        uint8_t  selected_day;
        uint8_t  selected_hour;
        uint8_t  selected_minute;
        uint8_t  selected_pm_p;

        uint8_t selection_bookmark;
        
        uint8_t blink_on_p;
};

