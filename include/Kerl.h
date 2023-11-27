
#pragma once

#include "deebug.hpp"
#include "common.h"

#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>

#include "WifiCredential.h"
#include "WebStation.h"


static constexpr uint16_t KERL_CONNECTION_TIMEOUT {60000};


class Kerl {
    public:
        Kerl(const uint8_t, const WifiCredential*)              noexcept;
        void init()                                             noexcept;
        uint8_t connectWebKeepAlive()                           noexcept;
        uint8_t connectToAnyNetwork()                           noexcept;
        void disconnect()                                       noexcept;
        uint8_t connectClientKeepAlive(const WebStation*)       noexcept;

        WiFiClient client;

    private:
        const WifiCredential* WIFI_CREDENTIALS;
        const uint8_t num_wifi_credentials;
        uint8_t connected_p;
        uint8_t using_index;
};

