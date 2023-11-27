
#pragma once

// these are the actual codes the remote uses
// but, because there are identical codes for some
// buttons, there's a second step

static constexpr uint8_rc  VISIO_ADDRESS        {4};
static constexpr uint16_rc WD_ADDRESS       {31108};

static constexpr uint8_rc TV_POWER_CODE         {8};      // VISIO
static constexpr uint8_rc SOURCE_CODE          {47};
static constexpr uint8_rc RED_POWER_CODE       {18};
static constexpr uint8_rc BACK_CODE            {27};
static constexpr uint8_rc HOME_CODE             {6};
static constexpr uint8_rc CIRCLE_LEFT_CODE      {7};
static constexpr uint8_rc CIRCLE_RITE_CODE      {9};      // WD
static constexpr uint8_rc CIRCLE_UP_CODE        {5};
static constexpr uint8_rc CIRCLE_DOWN_CODE      {0};
static constexpr uint8_rc OK_CODE               {8};      // WD
static constexpr uint8_rc ASTERISK_CODE        {26};
static constexpr uint8_rc REWIND_CODE          {31};
static constexpr uint8_rc PLAYPAUSE_CODE       {10};
static constexpr uint8_rc FASTFORWARD_CODE     {30};
static constexpr uint8_rc VOLUMEUP_CODE         {2};
static constexpr uint8_rc VOLUMEDOWN_CODE       {3};      // VISIO
static constexpr uint8_rc MUTE_CODE             {9};      // VISIO
static constexpr uint8_rc CHANNELUP_CODE        {3};      // WD
static constexpr uint8_rc CHANNELDOWN_CODE     {76};
static constexpr uint8_rc NETFLIX_CODE         {24};
static constexpr uint8_rc HULU_CODE            {14};

