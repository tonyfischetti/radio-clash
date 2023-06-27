
#ifndef alarm_h
#define alarm_h

#include "deebug.hpp"
#include "common.h"

#include <Sixteen.h>
#include "TickTockClock.h"
#include <RTClib.h>

class Alarm {
    public:
        // TODO TODO: it _will_ take more than just the MP3 player
        //              just not now
        Alarm();

        void arm();
        void disarm();
        uint8_t getHour();
        uint8_t getDisplayHour();
        uint8_t getMinute();
        void setHour(uint8_t);
        void setMinute(uint8_t);

        uint8_t isPm();
        uint8_t isArmed();

    private:
        uint8_t is_armed_p;
        uint8_t target_hour;
        uint8_t target_display_hour;
        uint8_t target_minute;
        uint8_t is_pm_p;
};

#endif

