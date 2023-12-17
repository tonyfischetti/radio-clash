
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
        uint8_rc tick()                   noexcept override;
        uint8_rc reCw()                   noexcept override;
        uint8_rc reCcw()                  noexcept override;
        uint8_rc rePress()                noexcept override;
        uint8_rc remOK()                  noexcept override;
        uint8_rc remCircleLeft()          noexcept override;
        uint8_rc remCircleRight()         noexcept override;
        uint8_rc display()                noexcept override;

        uint8_rc isSounding()       const noexcept;
        void soundAlarm()                 noexcept;
        void turnOffAlarm()               noexcept;

        const char* mode_name {"Alarm mode"};

    private:
        TickTockClock& rtc;
        Sixteen& sixteen;
        Alarm& alarm;
        Defe& defe;
        AudioController& jefa;

        uint8_rc blink_on_p;
        uint8_rc alarm_sounding_p;
        uint64_rc time_alarm_sounded;
        uint8_rc reupped_alarm_p;
        Timeout set_alarm_TMO;

        elapsedMillis blink_timer;

        const uint32_rc SET_ALARM_TIMEOUT {5000};
        const uint16_rc BLINK_FREQUENCY    {500};


        uint8_rc selected_hour;
        uint8_rc selected_minute;
        uint8_rc selected_pm_p;
        uint8_rc selected_armed_p;

        uint8_rc selection_bookmark;
        

};

