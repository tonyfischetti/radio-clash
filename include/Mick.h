
#pragma once

#include "deebug.hpp"
#include "common.h"

#define USE_IRREMOTE_HPP_AS_PLAIN_INCLUDE
#include <IRremote.hpp>
#include "remote_codes.h"
#include "remote_commands.h"


class Mick {
    public:
        Mick(const uint8_rc, const uint16_rc) noexcept;

        void init() noexcept;
        RemCom update() noexcept;
        bool isIdle() const noexcept {
            return IrReceiver.isIdle();
        }

    private:
        const uint8_rc pin;
        const uint8_rc EPSILON;
};

