
#include "Mick.h"


Mick::Mick(const uint8_rc _pin, const uint16_rc _epsilon_ir) noexcept
    : pin{_pin}, EPSILON{_epsilon_ir} {
}

void Mick::init() noexcept {
    IrReceiver.begin(pin);
}

RemCom Mick::update() noexcept {
    static uint64_rc previous_ir_signal;
    const uint64_rc current_millis {millis()};

    if (IrReceiver.decode()) {
        IrReceiver.resume();

        const uint8_rc  command  {IrReceiver.decodedIRData.command};
        const uint16_rc address  {IrReceiver.decodedIRData.address};
        const uint8_rc  protocol {IrReceiver.decodedIRData.protocol};

        deebug("mick", "received ir signal...");
        deebug("mick", "  command:  %d", command);
        deebug("mick", "  address:  %d", address);
        deebug("mick", "  protocol: %d", protocol);

        // ensure it's a legal remote
        if (protocol == 8 &&
            (address == VISIO_ADDRESS || address == WD_ADDRESS)) {
            if ((current_millis - previous_ir_signal) > EPSILON) {
                deebug("mick", "  processing signal!");
                previous_ir_signal = current_millis;
                switch (command) {
                    case VOLUMEUP_CODE:
                        return RemCom::volumeup;
                    case VOLUMEDOWN_CODE:
                        if (address == VISIO_ADDRESS)
                            return RemCom::volumedown;
                        else
                            return RemCom::channelup;
                    case REWIND_CODE:
                        return RemCom::rewind;
                    case PLAYPAUSE_CODE:
                        return RemCom::playpause;
                    case FASTFORWARD_CODE:
                        return RemCom::fastforward;
                    case CIRCLE_LEFT_CODE:
                        return RemCom::circle_left;
                    case CIRCLE_RITE_CODE:
                        if (address == WD_ADDRESS)
                            return RemCom::circle_rite;
                        else
                            return RemCom::mute;
                    case CIRCLE_UP_CODE:
                        return RemCom::circle_up;
                    case CIRCLE_DOWN_CODE:
                        return RemCom::circle_down;
                    case SOURCE_CODE:
                        return RemCom::source;
                    case TV_POWER_CODE:
                        // double function
                        if (address == VISIO_ADDRESS)
                            return RemCom::tv_power;
                        else
                            return RemCom::ok;
                    case RED_POWER_CODE:
                        return RemCom::red_power;
                    case BACK_CODE:
                        return RemCom::back;
                    case HOME_CODE:
                        return RemCom::home;
                    case ASTERISK_CODE:
                        return RemCom::asterisk;
                    case CHANNELDOWN_CODE:
                        return RemCom::channeldown;
                    case NETFLIX_CODE:
                        return RemCom::netflix;
                    case HULU_CODE:
                        return RemCom::hulu;
                    default:
                        return RemCom::unknown;
                }
            }
        }
    }
    return RemCom::unknown;
}

