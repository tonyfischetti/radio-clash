
#ifndef mick_h
#define mick_h

#include "deebug.hpp"
#include "common.h"

#define USE_IRREMOTE_HPP_AS_PLAIN_INCLUDE
#include <IRremote.hpp>
#include "remote_codes.h"
#include "remote_commands.h"


class Mick {
    public:
        Mick(const uint8_t, const uint16_t) noexcept;

        void init() noexcept;
        RemCom update() noexcept;
        bool isIdle() const noexcept {
            return IrReceiver.isIdle();
        }

    private:
        const uint8_t pin;
        const uint8_t EPSILON;
};

#endif
