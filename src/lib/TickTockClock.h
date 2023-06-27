

#include <stdint.h>
#include <Arduino.h>

#include <RTClib.h>

#ifndef ticktockclock_h
#define ticktockclock_h


class TickTockClock {
    public:
        TickTockClock();
        void init();
        void update();
        uint8_t lostPowerP();
        void setTime(DateTime);
        char* getDate();
        char* getTime();
        char* getTemp();
        uint16_t getYear();
        uint8_t getMonth();
        uint8_t getDay();
        uint8_t getHour();
        uint8_t getDisplayHour();
        uint8_t getMinute();
        void setDisplayHour(uint8_t);

        uint8_t isPm();

    private:
        DateTime now;
        RTC_DS3231 rtc;

        char the_date[11];
        char the_time[9];
        char the_temp[5];

        // TODO NOW: YEAR, MONTH, and DAY!!!!
        uint16_t year;
        uint8_t month;
        uint8_t day;
        uint8_t hour;
        uint8_t display_hour;
        uint8_t minute;
        uint8_t is_pm_p;
};

#endif

