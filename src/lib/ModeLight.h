
#ifndef modelight_h
#define modelight_h

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

        uint8_t engage()  noexcept override;
        uint8_t suspend() noexcept override;
        uint8_t tick()    noexcept override;
        uint8_t display() noexcept override;

        const char* mode_name {"Light Mode"};

    private:
        Phos& phos;
        Sixteen& sixteen;

        // uint64_t playlist_select_time;
        // const uint16_t PLAYLIST_SELECT_TIMEOUT {5000};
        //
        // uint8_t playlist_select_index;
};

#endif
