
#pragma once

#include "deebug.hpp"
#include "common.h"

#include <elapsedMillis.h>
#include <Sixteen.h>
#include "Alarm.h"
#include "TickTockClock.h"
#include "Defe.h"
#include "LBMode.h"
#include "AudioController.h"


class ModeAlarm final : public LBMode {
    public:
        ModeAlarm(TickTockClock&, Sixteen&, Alarm&,
                  Defe&, AudioController&) noexcept;

        const char* getModeName()   const noexcept override;
        uint8_t tick()                    noexcept override;
        uint8_t reCw()                    noexcept override;
        uint8_t reCcw()                   noexcept override;
        uint8_t rePress()                 noexcept override;
        uint8_t remOK()                   noexcept override;
        uint8_t remCircleLeft()           noexcept override;
        uint8_t remCircleRight()          noexcept override;
        uint8_t display()                 noexcept override;

        const uint8_t isSounding() const noexcept;
        void soundAlarm()                noexcept;
        void turnOffAlarm()              noexcept;

        const char* mode_name {"Alarm mode"};

    private:
        TickTockClock& rtc;
        Sixteen& sixteen;
        Alarm& alarm;
        Defe& defe;
        AudioController& jefa;

        elapsedMillis blink_timer;

        uint64_t set_alarm_time;

        const uint32_t SET_ALARM_TIMEOUT {5000};
        const uint16_t BLINK_FREQUENCY    {500};

        uint8_t selected_hour;
        uint8_t selected_minute;
        uint8_t selected_pm_p;
        uint8_t selected_armed_p;

        uint8_t selection_bookmark;
        
        uint8_t blink_on_p;

        uint8_t alarm_sounding_p;
        uint64_t time_alarm_sounded;
        uint8_t reupped_alarm_p;
};

