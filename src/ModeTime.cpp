
#include "ModeTime.h"


ModeTime::ModeTime(TickTockClock& _rtc, Sixteen& _sixteen)
    : rtc           {_rtc},
      sixteen       {_sixteen},
      set_time_time {0},
      blink_on_p    {true} {
}

const char* ModeTime::getModeName() const {
    return mode_name;
}

uint8_t ModeTime::tick() {
    rtc.update();
    if (set_time_time &&
        (millis() - set_time_time) > SET_TIME_TIMEOUT)
        set_time_time = 0;
    return true;
}

uint8_t ModeTime::reCw() {
    deebug("time mode", "rcCw");
    if (set_time_time) {
        deebug("time mode", "  while in setting mode");
        set_time_time = millis();
        switch (selection_bookmark) {
            case 0:
                ++selected_year;
                break;
            case 1:
                ++selected_month;
                break;
            case 2:
                ++selected_day;
                break;
            case 3:
                if (selected_hour != 12)
                    ++selected_hour;
                else
                    selected_hour = 1;
                break;
            case 4:
                if (selected_minute != 59)
                    ++selected_minute;
                else
                    selected_minute = 0;
                break;
            case 5:
                selected_pm_p = !selected_pm_p;
                break;
        }
    }
    return true;
}

uint8_t ModeTime::reCcw() {
    deebug("time mode", "rcCcw");
    if (set_time_time) {
        deebug("time mode", "  while in setting mode");
        set_time_time = millis();
        switch (selection_bookmark) {
            case 0:
                --selected_year;
                break;
            case 1:
                --selected_month;
                break;
            case 2:
                --selected_day;
                break;
            case 3:
                if (selected_hour != 1)
                    --selected_hour;
                else
                    selected_hour = 12;
                break;
            case 4:
                if (selected_minute != 0)
                    --selected_minute;
                else
                    selected_minute = 59;
                break;
            case 5:
                selected_pm_p = !selected_pm_p;
                break;
        }
    }
    return true;
}

// TODO TODO: can this be made more efficient?
uint8_t ModeTime::rePress() {
    deebug("time mode", "pressed");
    if (!set_time_time) {
        deebug("mp3 mode", "  entering time set mode");
        set_time_time      = millis();
        selected_year      = rtc.getYear();
        selected_month     = rtc.getMonth();
        selected_day       = rtc.getDay();
        selected_year      = rtc.getYear();
        selected_hour      = rtc.getDisplayHour();
        selected_minute    = rtc.getMinute();
        selected_pm_p      = rtc.isPm();
        selection_bookmark = 0;
    }
    // is it cool that this is unbounded?
    else if (selection_bookmark == 0) {
        deebug("time mode", "  setting year");
        set_time_time = millis();
        ++selection_bookmark;
    }
    else if (selection_bookmark == 1) {
        deebug("time mode", "  setting month");
        set_time_time = millis();
        ++selection_bookmark;
    }
    else if (selection_bookmark == 2) {
        deebug("time mode", "  setting day");
        set_time_time = millis();
        ++selection_bookmark;
    }
    else if (selection_bookmark == 3) {
        deebug("time mode", "  setting hour");
        set_time_time = millis();
        ++selection_bookmark;
    }
    else if (selection_bookmark == 4) {
        deebug("time mode", "  setting minute");
        set_time_time = millis();
        ++selection_bookmark;
    }
    else if (selection_bookmark == 5) {
        deebug("time mode", "  setting am or pm");
        set_time_time = millis();
        if (selected_pm_p)
            selected_hour += 12;
        else if (selected_hour == 12)
            selected_hour = 0;
        if (selected_hour == 24)
            selected_hour = 12;

        rtc.setTime(DateTime(selected_year, selected_month, selected_day,
                     selected_hour, selected_minute, 0));

        deebug("time mode", "  about to leave set time mode");
        set_time_time = 0;
    }
    return 0;
}

/*
uint8_t ModeTime::remOK() {
    deebug("time mode", "remOK() is going to masquerade as a rePress");
    return rePress();
}

uint8_t ModeTime::remCircleLeft() {
    deebug("time mode", "remCircleLeft() is going to masquerade as a reCcw");
    return reCcw();
}

uint8_t ModeTime::remCircleRight() {
    deebug("time mode", "remCircleRight() is going to masquerade as a reCw");
    return reCw();
}
*/

uint8_t ModeTime::display() {
    if (!set_time_time) {
        snprintf(sixteen.line0, 17, "   %s        ", rtc.getDate());
        snprintf(sixteen.line1, 17, " %s  %s      ", rtc.getTime(),
                 rtc.getTemp());
    }
    // HERE
    else {
        snprintf(sixteen.line0, 17, "SET   %d-%02d-%02d",
                                     selected_year,
                                     selected_month,
                                     selected_day);

        snprintf(sixteen.line1, 17, " %2d:%02d %s",
                                     selected_hour,
                                     selected_minute,
                                     selected_pm_p ? "pm" : "am");
        if (blink_timer > BLINK_FREQUENCY) {
            if (blink_on_p){
                switch (selection_bookmark) {
                    // year
                    case 0:
                        sixteen.line0[6] = ' ';
                        sixteen.line0[7] = ' ';
                        sixteen.line0[8] = ' ';
                        sixteen.line0[9] = ' ';
                        sixteen.update();
                        break;
                    // month
                    case 1:
                        sixteen.line0[11] = ' ';
                        sixteen.line0[12] = ' ';
                        break;
                    // day
                    case 2:
                        sixteen.line0[14] = ' ';
                        sixteen.line0[15] = ' ';
                        break;
                    //hour
                    case 3:
                        sixteen.line1[1]  = ' ';
                        sixteen.line1[2]  = ' ';
                        break;
                    // minute
                    case 4:
                        sixteen.line1[4]  = ' ';
                        sixteen.line1[5]  = ' ';
                        break;
                    // pm or am
                    case 5:
                        sixteen.line1[7]  = ' ';
                        sixteen.line1[8]  = ' ';
                        break;
                }
            }
            blink_on_p = !blink_on_p;
            blink_timer = 0;
        }
    }
    sixteen.update();
    return true;
}





