
// TODO TODO: it's a little behind. Can I manipulate __TIME__ to account
//            for the latency betwixt compilation and the installation
//            of the new firmware?


#include <stdint.h>
#include <elapsedMillis.h>
#include <Wire.h>
#include <RTClib.h>
#include <TEA5767N.h>
#include <Recoder.h>
#include <Sixteen.h>



/* -----------------------------------------------------------------------
 * PROGMEM (so we can put it at the bottom)                             */




/* -----------------------------------------------------------------------
 * PIN MACROS                                                           */

#define I2C_COLLECTOR 3
#define RE_CLK       13 
#define RE_DT_LAG    12
#define RE_SW        11



/* -----------------------------------------------------------------------
 * MACROS                                                               */

#define LCD_ADDRESS 0x3F

// milliseconds between polling different sensors
#define UPDATE_DT_EVERY       500
#define UPDATE_TEMP_EVERY  180000
#define UPDATE_LCD_EVERY      500
#define UPDATE_RE_EVERY         5

#define NUM_STATIONS 4
#define ST_WAXQ 104.3
#define ST_WWPR 105.1
#define ST_WQXR 105.9
#define ST_WQHT  97.1



/* -----------------------------------------------------------------------
 * IR REMOTE CODE MACROS                                                */



/* -----------------------------------------------------------------------
 * STRUCTS                                                              */



/* -----------------------------------------------------------------------
 * OTHER TYPEDEFS                                                       */

typedef uint8_t byte;



/* -----------------------------------------------------------------------
 * OBJECT INSTANTIATION                                                 */

Sixteen sixteen(LCD_ADDRESS);
RTC_DS3231 rtc;
TEA5767N radio = TEA5767N();
Recoder recoder(RE_CLK, RE_DT_LAG, RE_SW);



/* -----------------------------------------------------------------------
 * GLOBALS                                                              */

DateTime now;
char the_date[11];
char the_time[9];
char the_temp[5];
char tmp_date[11];

byte current_station_index = 0;

float my_stations[4] = {ST_WAXQ, ST_WWPR, ST_WQXR, ST_WQHT};



/* -----------------------------------------------------------------------
 * TIMERS                                                               */

elapsedMillis dt_timer;
elapsedMillis temp_timer;
elapsedMillis re_timer;
elapsedMillis lcd_timer;



/* -----------------------------------------------------------------------
 * REMOTE MUTATE FUNCTIONS                                             */



/* -----------------------------------------------------------------------
 * HELPER FUNCTIONS                                                     */

void turn_radio_i2c_on() {
    digitalWrite(I2C_COLLECTOR, HIGH);
}

void turn_radio_i2c_off() {
    digitalWrite(I2C_COLLECTOR, LOW);
}

void tune_to_station() {
    turn_radio_i2c_on();
    radio.selectFrequencyMuting(my_stations[current_station_index]);
    turn_radio_i2c_off();
}

void back_a_station() {
    current_station_index = (current_station_index - 1) % NUM_STATIONS;
    tune_to_station();
}

void forward_a_station() {
    current_station_index = (current_station_index + 1) % NUM_STATIONS;
    tune_to_station();
}

void set_date() {
    sprintf(the_date, "%d-%02d-%02d", now.year(), now.month(), now.day());
}

void set_now() {
    now = rtc.now();
}

void set_temp() {
    sprintf(the_temp, "%2ld C", round(rtc.getTemperature()));
}

void set_time() {
    byte display_hour;
    int hour = now.hour();
    char am_or_pm[3] = "pm";
    if (hour >= 12) {
        am_or_pm[0] = 'p';
        display_hour = hour > 12 ? hour - 12 : hour;
    } else if (hour == 0) {
        display_hour = 12;
        am_or_pm[0] = 'a';
    } else {
        display_hour = hour;
        am_or_pm[0] = 'a';
    }
    sprintf(the_time, "%2d:%02d %s", display_hour, now.minute(), am_or_pm);
}

void update_rotary_encoder() {

    /* Serial.println(millis()); */

    uint8_t mres = recoder.readMovement();
    uint8_t bres = recoder.readButton();

    // movement
    switch (mres) {
        case RECODER_CW:
            Serial.println(F("going forward"));
            forward_a_station();
            return;
        case RECODER_CCW:
            Serial.println(F("going back"));
            back_a_station();
            return;
    }

    // button
    switch (bres) {
        case RECODER_PRESS:
            Serial.println(F("sw button press!"));
            break;
        case RECODER_PRESS_AND_HOLD:
            Serial.println(F("pressed _AND_ held"));
            // TODO: show the radio station, instead
            Serial.println(my_stations[current_station_index]);
            break;
    }
}

void update_all_devices(bool force_update_p = false) {

    if (dt_timer > UPDATE_DT_EVERY || force_update_p) {
        set_now();
        set_date();
        set_time();
        dt_timer = 0;
    }
    if (temp_timer > UPDATE_TEMP_EVERY || force_update_p) {
        set_temp();
        temp_timer = 0;
    }
    if (re_timer > UPDATE_RE_EVERY || force_update_p) {
        update_rotary_encoder();
        re_timer = 0;
    }
    if (lcd_timer > UPDATE_LCD_EVERY || force_update_p) {
        snprintf(sixteen.line0, 17, "   %s", the_date);
        snprintf(sixteen.line1, 17, "%s   %s", the_time, the_temp);
        sixteen.update();
        lcd_timer = 0;
    }

}



/* -----------------------------------------------------------------------
 * SETUP AND MAINLOOP                                                  */

void setup() {

    Serial.begin(115200);

    pinMode(I2C_COLLECTOR, OUTPUT);

    if (!rtc.begin()) {
        Serial.println(F("Couldn't find RTC"));
        Serial.flush();
        while (1)
            delay(10);
    }

    /* if (rtc.lostPower()) */
    /*     rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); */
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

    sixteen.init();

    tune_to_station();

    Serial.println("about to finish setup");

    update_all_devices(true);

}


void loop() {

    update_all_devices();

}



/* -----------------------------------------------------------------------
 * PROGMEM things                                                      */


