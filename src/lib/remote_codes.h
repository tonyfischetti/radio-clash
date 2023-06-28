
#pragma once

// these are the actual codes the remote uses
// but, because there are identical codes for some
// buttons, there's a second step

static constexpr uint8_t  VISIO_ADDRESS        {4};
static constexpr uint16_t WD_ADDRESS       {31108};

static constexpr uint8_t TV_POWER_CODE         {8};      // VISIO
static constexpr uint8_t SOURCE_CODE          {47};
static constexpr uint8_t RED_POWER_CODE       {18};
static constexpr uint8_t BACK_CODE            {27};
static constexpr uint8_t HOME_CODE             {6};
static constexpr uint8_t CIRCLE_LEFT_CODE      {7};
static constexpr uint8_t CIRCLE_RITE_CODE      {9};      // WD
static constexpr uint8_t CIRCLE_UP_CODE        {5};
static constexpr uint8_t CIRCLE_DOWN_CODE      {0};
static constexpr uint8_t OK_CODE               {8};      // WD
static constexpr uint8_t ASTERISK_CODE        {26};
static constexpr uint8_t REWIND_CODE          {31};
static constexpr uint8_t PLAYPAUSE_CODE       {10};
static constexpr uint8_t FASTFORWARD_CODE     {30};
static constexpr uint8_t VOLUMEUP_CODE         {2};
static constexpr uint8_t VOLUMEDOWN_CODE       {3};      // VISIO
static constexpr uint8_t MUTE_CODE             {9};      // VISIO
static constexpr uint8_t CHANNELUP_CODE        {3};      // WD
static constexpr uint8_t CHANNELDOWN_CODE     {76};
static constexpr uint8_t NETFLIX_CODE         {24};
static constexpr uint8_t HULU_CODE            {14};

