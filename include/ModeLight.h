
#pragma once

#include "deebug.hpp"
#include "common.h"

#include "Phos.h"
#include <Sixteen.h>
#include "LBMode.h"



class ModeLight final : public LBMode {
    public:
        ModeLight(Phos&, Sixteen&) noexcept;

        const char* getModeName()  const noexcept override;
        const bool isAudioNeeder() const noexcept override;

        uint8_rc engage()  noexcept override;
        uint8_rc suspend() noexcept override;
        uint8_rc tick()    noexcept override;
        uint8_rc display() noexcept override;

        const char* mode_name {"Light Mode"};

    private:
        Phos& phos;
        Sixteen& sixteen;

        // uint64_rc playlist_select_time;
        // const uint16_rc PLAYLIST_SELECT_TIMEOUT {5000};
        //
        // uint8_rc playlist_select_index;
};

