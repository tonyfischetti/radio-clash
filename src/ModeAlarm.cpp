
#include "ModeAlarm.h"


ModeAlarm::ModeAlarm(TickTockClock& _rtc,
                     Sixteen& _sixteen,
                     Alarm& _alarm,
                     Defe& _defe,
                     AudioController& _jefa)
    : rtc                {_rtc},
      sixteen            {_sixteen},
      alarm              {_alarm},
      defe               {_defe},
      jefa               {_jefa},
      set_alarm_time     {0},
      blink_on_p         {true},
      alarm_sounding_p   {false},
      time_alarm_sounded {0},
      reupped_alarm_p    {true} {
}

const char* ModeAlarm::getModeName() const {
    return mode_name;
}

uint8_rc ModeAlarm::tick() {
    if (set_alarm_time &&
        (millis() - set_alarm_time) > SET_ALARM_TIMEOUT)
        set_alarm_time = 0;
    if (isSounding()) {
        /* this is to get around a limitation of DFplayer...          *
         *   without this, if the player is paused, the alarm won't   *
         *   play the alarm song, but the last song played and paused */
        if (((millis() - time_alarm_sounded) > 501) && reupped_alarm_p == 0) {
            reupped_alarm_p = true;
            defe.setVolume(100);
            defe.startAlarm(ALARM_FOLDER, ALARM_TRACK);
        }
        defe.manage();
    }
    if (alarm.isArmed() && !isSounding() &&
        // making sure it doesn't repeat after it's turned off
        (millis() - time_alarm_sounded) > 60000) {
        if (rtc.getMinute() == alarm.getMinute()) {
            if (rtc.getHour() == alarm.getHour()) {
                deebug("mode alarm", "time to sound again");
                return 1;
            }
        }
    }
    return 0;
}

const uint8_rc ModeAlarm::isSounding() const {
    return alarm_sounding_p;
}

void ModeAlarm::soundAlarm() {
    deebug("alarm mode", "SOUNDING ALARM!");
    alarm_sounding_p = true;
    time_alarm_sounded = millis();
    deebug("alarm mode", "   final alarm sounding step");
    defe.startAlarm(ALARM_FOLDER, ALARM_TRACK);
    reupped_alarm_p = false;
}

// TODO TODO TODO TODO: SNOOZE?!

void ModeAlarm::turnOffAlarm() {
    deebug("alarm mode", "turning off alarm");
    // TODO: this
    alarm_sounding_p = false;
    defe.stopAlarm();
}

uint8_rc ModeAlarm::reCw() {
    deebug("alarm mode", "rcCw");
    if (set_alarm_time) {
        deebug("alarm mode", "  while in setting mode");
        set_alarm_time = millis();
        switch (selection_bookmark) {
            case 0:
                if (selected_hour != 12)
                    ++selected_hour;
                else
                    selected_hour = 1;
                break;
            case 1:
                if (selected_minute != 59)
                    ++selected_minute;
                else
                    selected_minute = 0;
                break;
            case 2:
                selected_pm_p = !selected_pm_p;
                break;
            case 3:
                selected_armed_p = !selected_armed_p;
                break;
        }
    }
    return true;
}

uint8_rc ModeAlarm::reCcw() {
    deebug("alarm mode", "rcCcw");
    if (set_alarm_time) {
        deebug("alarm mode", "  while in setting mode");
        set_alarm_time = millis();
        switch (selection_bookmark) {
            case 0:
                if (selected_hour != 1)
                    --selected_hour;
                else
                    selected_hour = 12;
                break;
            case 1:
                if (selected_minute != 0)
                    --selected_minute;
                else
                    selected_minute = 59;
                break;
            case 2:
                selected_pm_p = !selected_pm_p;
                break;
            case 3:
                selected_armed_p = !selected_armed_p;
                break;
        }
    }
    return true;
}

uint8_rc ModeAlarm::rePress() {
    deebug("alarm mode", "rePress()");
    if (isSounding()) {
        deebug("alarm mode", "    sounding but turning off");
        turnOffAlarm();
        return 0;
    }
    if (!set_alarm_time) {
        deebug("alarm mode", "entering alarm set mode");
        set_alarm_time     = millis();
        selected_hour      = alarm.getDisplayHour();
        selected_minute    = alarm.getMinute();
        selected_pm_p      = alarm.isPm();
        selected_armed_p   = alarm.isArmed();
        selection_bookmark = 0;
    }
    else if (selection_bookmark == 0) {
        set_alarm_time = millis();
        ++selection_bookmark;
    }
    else if (selection_bookmark == 1) {
        set_alarm_time = millis();
        ++selection_bookmark;
    }
    else if (selection_bookmark == 2) {
        set_alarm_time = millis();
        ++selection_bookmark;
    }
    else if (selection_bookmark == 3) {

        if (selected_pm_p)
            selected_hour += 12;
        else if (selected_hour == 12)
            selected_hour = 0;
        if (selected_hour == 24)
            selected_hour = 12;
        alarm.setHour(selected_hour);
        alarm.setMinute(selected_minute);
        if (selected_armed_p) {
            alarm.arm();
            deebug("alarm mode", "  just armed alarm");
            deebug("alarm mode", "  alarm: %2d:%02d", selected_hour, selected_minute);
        }
        else {
            alarm.disarm();
            deebug("alarm mode", "  just disarmed alarm");
        }

        deebug("alarm mode", "  about to leave set alarm mode");
        set_alarm_time = 0;
    }
    return 0;
}

uint8_rc ModeAlarm::remOK() {
    deebug("alarm mode", "remOK() is going to masquerade as a rePress");
    return rePress();
}

uint8_rc ModeAlarm::remCircleLeft() {
    deebug("alarm mode", "remCircleLeft() is going to masquerade as a reCcw");
    return reCcw();
}

uint8_rc ModeAlarm::remCircleRight() {
    deebug("alarm mode", "remCircleRight() is going to masquerade as a reCw");
    return reCw();
}

uint8_rc ModeAlarm::display() {
    if (!set_alarm_time) {
        snprintf(sixteen.line0, 17, "Alarm mode               ");
        snprintf(sixteen.line1, 17, "%2d:%02d %s %s           ",
                 alarm.getDisplayHour(),
                 alarm.getMinute(),
                 alarm.isPm() ? "pm" : "am",
                 alarm.isArmed() ? "on" : "off");
    }
    else {
        snprintf(sixteen.line0, 17, "Setting alarm            ");
        snprintf(sixteen.line1, 17, "%2d:%02d %s %s           ",
                 selected_hour,
                 selected_minute,
                 selected_pm_p ? "pm" : "am",
                 selected_armed_p ? "on" : "off");
        if (blink_timer > BLINK_FREQUENCY) {
            if (blink_on_p){
                switch (selection_bookmark) {
                    case 0:
                        sixteen.line1[0] = ' ';
                        sixteen.line1[1] = ' ';
                        break;
                    case 1:
                        sixteen.line1[3] = ' ';
                        sixteen.line1[4] = ' ';
                        break;
                    case 2:
                        sixteen.line1[6] = ' ';
                        sixteen.line1[7] = ' ';
                        break;
                    case 3:
                        sixteen.line1[9]  = ' ';
                        sixteen.line1[10] = ' ';
                        sixteen.line1[11] = ' ';
                        break;

                }
            }
            blink_on_p = !blink_on_p;
            blink_timer = 0;
        }
    }
    if (isSounding()) {
        snprintf(sixteen.line0, 17, "ALARM! ALARM! ALARM! ALARM!");
        snprintf(sixteen.line1, 17, "ALARM! ALARM! ALARM! ALARM!");
    }
    sixteen.update();
    return true;
}

