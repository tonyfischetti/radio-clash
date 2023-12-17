
/********** TODO TODO VERY IMPORTANT ***************/

// MAKE UPDATE TIMES DYNAMIC!
//   for example, ModeTime doesn't have to tick nearly as often if
//   not in time _setting_ mode

/********** TODO TODO TODO TODO ***************/

// have the channel up/down change modes

// no way to toggle shuffle, etc... using physical controls?

// check memory usage, too
// make sure there are no leaks

// make a MP3 mode functionality to repeat one song

// make a function in Defe (for the alarm to use)
//   instead of just playing depeche mode for the alarm

/********** TODO TODO TODO TODO ***************/

// you know what? tracks should only be uint8_rc
// the lisp script can skip anything over that
// Or, _at least, it can be a change-able typedef

// should previous_track sometimes restart the current song?
// probably not

// TRASH FOLDER MUST BE GOT RID OF!

// eventually, test with a playlist of one track

// use more `const`s in constructors, etc...


// TODO TODO: add an `uint8_rc isActive()` member function
//            to decide whether to tick it
//            or `uint8_rc isRunning()`

// TODO: oops, it looks like the pot1 and pot2 affect pot0

// TODO TODO: fill in remaining noexcepts

// TODO: generate gamma tables using the compiler/constexpr...
//           ~ 23.02 of "Modern C++ to Impress your Embedded Dev Friends"

// TODO TODO TODO: the whole `suspend`/`engage` thing has to be re-thought

#include <IRremote.hpp>

#include "deebug.hpp"
#include "common.h"

#include <elapsedMillis.h>
#include <VS1053.h>

#include <Sixteen.h>
#include <Recoder.h>

#include "Mick.h"
#include "Kerl.h"
#include "TickTockClock.h"
#include "Defe.h"
#include "Alarm.h"
#include "AudioController.h"
#include "Amber.h"
#include "Phos.h"

#include "LBMode.h"
#include "ModeMP3.h"
#include "ModeTime.h"
#include "ModeAlarm.h"
#include "ModeWebRadio.h"

#include "net_secrets.h"
#include "web_station_registry.h"
#include "playlist_names.h"



/* -----------------------------------------------------------------------
 * PROGMEM (so we can put it at the bottom)                             */



/* -----------------------------------------------------------------------
 * PIN MACROS                                                           */

// HLG ESP32
#define RX      16
#define TX      17
#define IR_PIN  39
#define SDA     21
#define SCL     22
#define POT0    34
#define POT1    35
#define POT2    32
#ifdef ROTARY_REVERSED
#define RE_CLK  25
#define RE_DT   33
#define RE_SW   26
#else
#define RE_CLK  33
#define RE_DT   25
#define RE_SW   26
#endif

// FOR WEB RADIO
#define SCK     18
#define MISO    19
#define MOSI    23
#define VSCS     5
#define VSDCS    0
#define VSDREQ   4
// EN, 5V, and GND, too

#define MUX_CONTROL_A       13
#define MUX_CONTROL_B        0   // TODO TODO TODO
#define BASE_FM_I2C         12

#define NEOPIXEL_PIN        15



/* -----------------------------------------------------------------------
 * MACROS                                                               */

#define CURRENT_MODE M[CMI]



/* -----------------------------------------------------------------------
 * GLOBALS that would have been macros                                  */

// number of milliseconds to wait for buttons, etc. to settle
static constexpr uint16_rc EPSILON_IR {150};

// time-block after mode change
static constexpr uint16_rc EPS_MODE_CHANGE     {2000};

static constexpr uint16_rc MODE_SELECT_TIMEOUT {5000};

static constexpr uint8_rc ADDRESS_I2C_AMBER    {0x70};
static constexpr uint8_rc ADDRESS_I2C_SIXTEEN  {0x3F};

// milliseconds between polling different sensors
static constexpr uint16_rc CHECK_IR_EVERY       {20};
static constexpr uint16_rc CHECK_LCD_EVERY      {50};
static constexpr uint16_rc CHECK_CLOCK_EVERY   {100};
static constexpr uint16_rc CHECK_POT_EVERY     {300};
static constexpr uint16_rc CHECK_RE_EVERY        {5};
static constexpr uint16_rc CHECK_AMBER_EVERY   {500};
static constexpr uint16_rc CHECK_ALARM_EVERY  {1000};
// TODO TODO: what are the consequences of making this
//            more or less frequent?

static constexpr uint8_rc NUM_NEOPIXELS {64};

// TODO: rethink this
// TODO: bad but 2 is unstable
static constexpr uint8_rc ANALOG_DEV_TOLERANCE {4};

// TODO ACHTUNG NtS
static constexpr uint8_rc NUM_MODES      {4};

// TODO: use enum class
static constexpr uint8_rc INDEX_MP3      {0};
static constexpr uint8_rc INDEX_TIME     {1};
static constexpr uint8_rc INDEX_ALARM    {2};
static constexpr uint8_rc INDEX_WEBRADIO {3};


/* -----------------------------------------------------------------------
 * TYPEDEFS                                                             */



/* -----------------------------------------------------------------------
 * OBJECT INSTANTIATION                                                 */

static Recoder           recoder(RE_CLK, RE_DT, RE_SW);
static Sixteen           sixteen(ADDRESS_I2C_SIXTEEN);
static Mick              mick(IR_PIN, EPSILON_IR);
static Kerl              kerl(NUMWIFICREDENTIALS, WIFI_CREDENTIALS);
static TickTockClock     rtc;
static Defe              defe(NUM_PLAYLISTS, playlist_names, playlist_lengths);
static Alarm             spirit76;
static VS1053            vica(VSCS, VSDCS, VSDREQ);
static AudioController   jefa(MUX_CONTROL_A, MUX_CONTROL_B);
static Amber             amber(ADDRESS_I2C_AMBER, rtc);
static Phos              phos(NEOPIXEL_PIN, NUM_NEOPIXELS);

static ModeMP3           mp3_mode(defe, sixteen, jefa);
static ModeTime          time_mode(rtc, sixteen);
static ModeAlarm         alarm_mode(rtc, sixteen, spirit76, defe, jefa);
static ModeWebRadio      webradio_mode(vica, kerl, sixteen, WEB_STATIONS,
                                       NUM_WEBSTATIONS, jefa);


/* -----------------------------------------------------------------------
 * MUTABLE GLOBALS                                                      */

// holds pointers to all available mode objects
static LBMode *M[NUM_MODES] = { &mp3_mode, &time_mode,
                                &alarm_mode, &webradio_mode };

// holds the index of the current active mode
static uint8_rc CMI {INDEX_MP3};

// holds the index of the current mode using the audio
static uint8_rc AMI {CMI};

// holds the index of the mode that may be switched to
static uint8_rc TMI {CMI};

static uint64_rc mode_select_time {0};

static bool lcd_on_p {true};



/* -----------------------------------------------------------------------
 * TIMERS                                                               */

static elapsedMillis ir_timer;
static elapsedMillis lcd_timer;
static elapsedMillis pot_timer;
static elapsedMillis re_timer;
static elapsedMillis defe_timer;
static elapsedMillis amber_timer;
static elapsedMillis alarm_timer;


/* -----------------------------------------------------------------------
 * (SOME) PROTOTYPES                                                    */

uint8_rc analog_changed_sufficiently_p(const uint8_t, const uint8_t,
                                       const uint8_rc) noexcept;

void change_mode(const uint8_rc new_index) noexcept;


/* -----------------------------------------------------------------------
 * SENSOR UPDATE FUNCTIONS                                              */

    /******* DIGITAL *******/

void update_ir() noexcept {
    const RemCom remote_command = mick.update();

    switch (remote_command) {
        case RemCom::volumeup:
            deebug("update_ir", "    volume up");
            CURRENT_MODE->remVolumeUp();
            break;
        case RemCom::volumedown:
            deebug("update_ir", "    volume down");
            CURRENT_MODE->remVolumeDown();
            break;
        case RemCom::rewind:
            deebug("update_ir", "    rewind");
            CURRENT_MODE->remRewind();
            break;
        case RemCom::playpause:
            deebug("update_ir", "    play / pause");
            CURRENT_MODE->remPlayPause();
            break;
        case RemCom::fastforward:
            deebug("update_ir", "    fast forward");
            CURRENT_MODE->remFastForward();
            break;
        case RemCom::circle_left:
            deebug("update_ir", "    circle left");
            CURRENT_MODE->remCircleLeft();
            break;
        case RemCom::circle_rite:
            deebug("update_ir", "    circle right");
            CURRENT_MODE->remCircleRight();
            break;
        case RemCom::circle_up:
            deebug("update_ir", "    circle up");
            if (!mode_select_time)
                TMI = CMI;
            mode_select_time = millis();
            if (TMI == (NUM_MODES-1))
                break;
            ++TMI;
            break;
        case RemCom::circle_down:
            deebug("update_ir", "    circle down");
            if (!mode_select_time)
                TMI = CMI;
            mode_select_time = millis();
            if (TMI == 0)
                break;
            --TMI;
            break;
        case RemCom::ok:
            deebug("update_ir", "    OK");
            if (mode_select_time)
                change_mode(TMI);
            else
                CURRENT_MODE->remOK();
            break;
        case RemCom::source:
            deebug("update_ir", "    source");
            // remSource() is reserved!
            amber.nextBrightness();
            break;
        case RemCom::tv_power:
            deebug("update_ir", "    tv power");
            // remTVPower() is reserved!
            // TODO TODO TODO: move this to sixteen (call toggle)
            lcd_on_p = !lcd_on_p;
            if (!lcd_on_p)
                sixteen.lcd.noBacklight();
            else
                sixteen.lcd.backlight();
            break;
        case RemCom::red_power:
            deebug("update_ir", "    red power");
            // remRedPower() is reserved!
            break;
        case RemCom::back:
            deebug("update_ir", "    back");
            CURRENT_MODE->remBack();
            break;
        case RemCom::home:
            deebug("update_ir", "    home");
            CURRENT_MODE->remHome();
            break;
        case RemCom::asterisk:
            deebug("update_ir", "    asterisk");
            CURRENT_MODE->remAsterisk();
            break;
        case RemCom::channeldown:
            deebug("update_ir", "    channel down");
            CURRENT_MODE->remChannelDown();
            break;
        case RemCom::netflix:
            deebug("update_ir", "    netflix");
            CURRENT_MODE->remNetflix();
            break;
        case RemCom::hulu:
            deebug("update_ir", "    hulu");
            CURRENT_MODE->remHulu();
            break;
        case RemCom::channelup:
            deebug("update_ir", "    channel up");
            CURRENT_MODE->remChannelUp();
            break;
        case RemCom::mute:
            deebug("update_ir", "    mute");
            CURRENT_MODE->remMute();
            break;
    }
}

void update_rotary_encoder() noexcept {
    const REEvent mres { recoder.readMovement() };
    const REEvent bres { recoder.readButton() };
    // movement
    switch (mres) {
        case REEvent::RECODER_CW:
            // TODO (EXPLAIN BETTER) POTENTIALLY OVERRIDES MEMBER FUNCTION
            if (!mode_select_time) {
                deebug("update_rotary...", "passing <clockwise> to current mode");
                CURRENT_MODE->reCw();
            }
            else {
                // in mode select mode
                mode_select_time = millis();
                deebug("update_rotary...", "using <clockwise> to change mode");
                if (TMI == (NUM_MODES-1))
                    return;
                ++TMI;
            }
            return;
        case REEvent::RECODER_CCW:
            // TODO (EXPLAIN BETTER) POTENTIALLY OVERRIDES MEMBER FUNCTION
            if (!mode_select_time) {
                deebug("update_rotary...", "passing <counter-clockwise> to current mode");
                CURRENT_MODE->reCcw();
            }
            else {
                // in mode select mode
                mode_select_time = millis();
                deebug("update_rotary...", "using <counter-clockwise> to change mode");
                if (TMI == 0)
                    return;
                --TMI;
            }
            return;
    }
    // button
    switch (bres) {
        deebug("tmp", "bres: %d", bres);
        case REEvent::RECODER_PRESS:
            // TODO (EXPLAIN BETTER) POTENTIALLY OVERRIDES MEMBER FUNCTION
            if (!mode_select_time)
                CURRENT_MODE->rePress();
            else {
                deebug("update_rotary...", "about to leave mode select mode");
                deebug("update_rotary...", "calling change_mode with index: %d", TMI);
                change_mode(TMI);
            }
            return;
        case REEvent::RECODER_PRESS_AND_HOLD:
            if (!mode_select_time) {
                deebug("update_rotary...", "entering mode selection mode");
                mode_select_time = millis();
                TMI = CMI;
            }
            else
                mode_select_time = millis();
            return;
    }
}


    /******* ANALOG *******/

void update_pot0() noexcept {
    static uint8_rc previous_vol0;
    // TODO: change resolution
    const uint8_rc current_vol0 = map(analogRead(POT0), 0, 4095, 30, 0);
    if (analog_changed_sufficiently_p(previous_vol0, current_vol0,
                                      ANALOG_DEV_TOLERANCE)) {
        deebug("update_pot0", "pot changed sufficiently");
        previous_vol0 = current_vol0;
        // TODO TODO: what about others?!
        defe.setVolume(current_vol0);
        deebug("update_pot0", "  set volume at: %d", current_vol0);
    }
}

void update_pot1() noexcept {
    static uint8_rc previous_vol1;
    // TODO: change resolution
    const uint8_rc current_vol1 = map(analogRead(POT1), 0, 4095, 30, 0);
    if (analog_changed_sufficiently_p(previous_vol1, current_vol1,
                                      ANALOG_DEV_TOLERANCE)) {
        deebug("update_pot1", "pot changed sufficiently");
    }
}

void update_pot2() noexcept {
    static uint8_rc previous_vol2;
    // TODO: change resolution
    const uint8_rc current_vol2 = map(analogRead(POT2), 0, 4095, 30, 0);
    if (analog_changed_sufficiently_p(previous_vol2, current_vol2,
                                      ANALOG_DEV_TOLERANCE)) {
        deebug("update_pot2", "pot changed sufficiently");
    }
}


/* -----------------------------------------------------------------------
 * DISPLAY FUNCTIONS                                                    */

void show_home() noexcept {
    snprintf(sixteen.line0, 17, "   Light Box");
    snprintf(sixteen.line1, 17, "  ------------");
    sixteen.update();
}

void show_mode_select() noexcept {
    snprintf(sixteen.line0, 17, "Mode select:          ");
    snprintf(sixteen.line1, 17, "[%d/%d] %s            ",
             TMI+1,
             NUM_MODES,
             M[TMI]->getModeName());
    sixteen.update();
}


/* -----------------------------------------------------------------------
 * HELPER FUNCTIONS                                                     */

bool ok_to_change_modes_p() {
    static uint64_rc previous;
    const uint64_rc current {millis()};
    if ((current - previous) > EPS_MODE_CHANGE) {
        previous = current;
        return true;
    }
    return false;
}

void change_mode(const uint8_rc new_index) noexcept {
    if (!ok_to_change_modes_p()) {
        deebug("main", "directive to change modes belayed");
        TMI = CMI;
        return;
    }
    deebug("main", "actually changing modes");
    if (M[new_index]->isAudioNeeder() &&
        new_index != AMI) {
        deebug("main", "new one needs audio");
        M[AMI]->suspend();
        AMI = new_index;
    }

    mode_select_time = 0;
    CMI = new_index;
    TMI = CMI;
    CURRENT_MODE->engage();
}

uint8_rc analog_changed_sufficiently_p(const uint8_t previous,
                                       const uint8_t current,
                                       const uint8_rc TOLERANCE =
                                       ANALOG_DEV_TOLERANCE) noexcept {
    if (abs(current - previous) > TOLERANCE)
        return true;
    return false;
}


void update_all_devices(uint8_rc force_update_p=false) noexcept {
    if (ir_timer > CHECK_IR_EVERY || force_update_p) {
        update_ir();
        ir_timer = 0;
    }
    if (lcd_timer > CHECK_LCD_EVERY || force_update_p) {
        if (mode_select_time)
            show_mode_select();
        else {
            if (lcd_on_p)
                CURRENT_MODE->display();
        }
        lcd_timer = 0;
    }
    if (pot_timer > CHECK_POT_EVERY || force_update_p) {
        update_pot0();
        // update_pot1();
        // update_pot2();
        pot_timer = 0;
    }
    // TODO: TRY WITHOUT THIS
    if (re_timer > CHECK_RE_EVERY || force_update_p) {
        update_rotary_encoder();
        re_timer = 0;
    }
    if (amber_timer > CHECK_AMBER_EVERY || force_update_p) {
        amber.update();
        amber_timer = 0;
    }

    mp3_mode.tick();
    time_mode.tick();
    webradio_mode.tick();

    if (amber_timer > CHECK_AMBER_EVERY || force_update_p) {
        if(alarm_mode.tick()) {
            M[AMI]->suspend();
            AMI = INDEX_ALARM;
            mp3_mode.engage();
            change_mode(INDEX_ALARM);
            alarm_mode.soundAlarm();
        }
        alarm_timer = 0;
    }

    // TODO: and how am I gonna make the volume, etc... controls work
    //       for the music (whichever device is playing) when time
    //       mode is on?

    // maybe make a background tasks array (of pointers)
    // and `(mapcar #'tick BACKGROUND_TASK_ARRAY)`

    // see if mode select mode timed out
    if (mode_select_time &&
        (millis() - mode_select_time) > MODE_SELECT_TIMEOUT) {
        deebug("update_all...", "exiting mode select mode");
        mode_select_time = 0;
        TMI = CMI;
    }

}



/* -----------------------------------------------------------------------
 * SETUP AND MAINLOOP                                                   */

void setup() {

    Serial.begin(115200);
    Serial2.begin(9600);

    deebug("setup", "::alice glass:: HI!");

    jefa.init();
    deebug("setup", "jefa started");
    defe.init(Serial2);
    deebug("setup", "defe started");
    sixteen.init();
    deebug("setup", "sixteen started");
    kerl.init();
    deebug("setup", "kerl started");
    mick.init();
    deebug("setup", "ir started");
    rtc.init();
    deebug("setup", "rtc started");
    amber.init();
    deebug("setup", "amber started");
    phos.init();
    deebug("setup", "phos started");

    show_home();
    deebug("setup", "displaying home screen");

    deebug("setup", "current mode: %s", CURRENT_MODE->mode_name);
    // TODO TODO: `engage`/`suspend` thing is whack. re-think
    CURRENT_MODE->engage();
    deebug("setup", "mode engaged");

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    deebug("setup", "leaving setup");

}


void loop() {
    update_all_devices();
}



/* -----------------------------------------------------------------------
 * PROGMEM things                                                       */


