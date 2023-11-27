
.DELETE_ON_ERROR:

# COMPTYPE  := debug

OS          := $(shell uname -s)
ARCH        := $(shell uname -m)

INCDIR    	:= include
INCDIRcntrb := contrib/include
SRCDIR    	:= src
SRCDIRcntrb := contrib/src
BUILDDIR  	:= build

ESPMAINROOT     := /home/tony/esp32/
ESPSRCFILESROOT := $(ESPMAINROOT)cores/esp32/
ESPINCSROOT  	:= $(ESPMAINROOT)tools/sdk/esp32/include/
ESPLIBS 	 	:= $(ESPMAINROOT)tools/sdk/esp32/lib \
				   $(ESPMAINROOT)tools/sdk/esp32/ld \
				   $(ESPMAINROOT)tools/sdk/esp32/dio_qspi

ESPINCSBASE     := newlib/platform_include freertos/include
ESPINCSBASE     += freertos/include/esp_additions/freertos
ESPINCSBASE     += freertos/include/esp_additions/freertos
ESPINCSBASE     += freertos/port/xtensa/include
ESPINCSBASE     += freertos/include/esp_additions esp_hw_support/include
ESPINCSBASE     += esp_hw_support/include/soc esp_hw_support/include/soc/esp32
ESPINCSBASE     += esp_hw_support/port/esp32
ESPINCSBASE     += esp_hw_support/port/esp32/private_include heap/include
ESPINCSBASE     += log/include lwip/include/apps lwip/include/apps/sntp
ESPINCSBASE     += lwip/lwip/src/include lwip/port/esp32/include
ESPINCSBASE     += lwip/port/esp32/include/arch soc/include
ESPINCSBASE     += soc/esp32 soc/esp32/include hal/esp32/include
ESPINCSBASE     += hal/include hal/platform_port/include esp_rom/include
ESPINCSBASE     += esp_rom/include/esp32 esp_rom/esp32 esp_common/include
ESPINCSBASE     += esp_system/include esp_system/port/soc
ESPINCSBASE     += esp_system/port/public_compat esp32/include xtensa/include
ESPINCSBASE     += xtensa/esp32/include driver/include driver/esp32/include
ESPINCSBASE     += esp_pm/include esp_ringbuf/include efuse/include
ESPINCSBASE     += efuse/esp32/include vfs/include esp_wifi/include
ESPINCSBASE     += esp_event/include esp_netif/include esp_eth/include
ESPINCSBASE     += tcpip_adapter/include esp_phy/include esp_phy/esp32/include
ESPINCSBASE     += esp_ipc/include app_trace/include esp_timer/include
ESPINCSBASE     += mbedtls/port/include mbedtls/mbedtls/include
ESPINCSBASE     += mbedtls/esp_crt_bundle/include app_update/include
ESPINCSBASE     += spi_flash/include bootloader_support/include
ESPINCSBASE     += nvs_flash/include pthread/include esp_gdbstub/include
ESPINCSBASE     += esp_gdbstub/xtensa esp_gdbstub/esp32 espcoredump/include
ESPINCSBASE     += espcoredump/include/port/xtensa wpa_supplicant/include
ESPINCSBASE     += wpa_supplicant/port/include
ESPINCSBASE     += wpa_supplicant/esp_supplicant/include ieee802154/include
ESPINCSBASE     += console asio/asio/asio/include asio/port/include
ESPINCSBASE     += bt/common/osi/include bt/include/esp32/include
ESPINCSBASE     += bt/common/api/include/api
ESPINCSBASE     += bt/common/btc/profile/esp/blufi/include
ESPINCSBASE     += bt/common/btc/profile/esp/include
ESPINCSBASE     += bt/host/bluedroid/api/include/api
ESPINCSBASE     += bt/esp_ble_mesh/mesh_common/include
ESPINCSBASE     += bt/esp_ble_mesh/mesh_common/tinycrypt/include
ESPINCSBASE     += bt/esp_ble_mesh/mesh_core
ESPINCSBASE     += bt/esp_ble_mesh/mesh_core/include
ESPINCSBASE     += bt/esp_ble_mesh/mesh_core/storage
ESPINCSBASE     += bt/esp_ble_mesh/btc/include
ESPINCSBASE     += bt/esp_ble_mesh/mesh_models/common/include
ESPINCSBASE     += bt/esp_ble_mesh/mesh_models/client/include
ESPINCSBASE     += bt/esp_ble_mesh/mesh_models/server/include
ESPINCSBASE     += bt/esp_ble_mesh/api/core/include
ESPINCSBASE     += bt/esp_ble_mesh/api/models/include
ESPINCSBASE     += bt/esp_ble_mesh/api cbor/port/include unity/include
ESPINCSBASE     += unity/unity/src cmock/CMock/src
ESPINCSBASE     += coap/port/include coap/libcoap/include nghttp/port/include
ESPINCSBASE     += nghttp/nghttp2/lib/includes esp-tls esp-tls/esp-tls-crypto
ESPINCSBASE     += esp_adc_cal/include esp_hid/include tcp_transport/include
ESPINCSBASE     += esp_http_client/include esp_http_server/include
ESPINCSBASE     += esp_https_ota/include esp_https_server/include
ESPINCSBASE     += esp_lcd/include esp_lcd/interface protobuf-c/protobuf-c
ESPINCSBASE     += protocomm/include/common protocomm/include/security
ESPINCSBASE     += protocomm/include/transports mdns/include
ESPINCSBASE     += esp_local_ctrl/include sdmmc/include
ESPINCSBASE     += esp_serial_slave_link/include esp_websocket_client/include
ESPINCSBASE     += expat/expat/expat/lib expat/port/include
ESPINCSBASE     += wear_levelling/include fatfs/diskio fatfs/vfs fatfs/src
ESPINCSBASE     += freemodbus/common/include idf_test/include
ESPINCSBASE     += idf_test/include/esp32 jsmn/include json/cJSON
ESPINCSBASE     += libsodium/libsodium/src/libsodium/include
ESPINCSBASE     += libsodium/port_include mqtt/esp-mqtt/include
ESPINCSBASE     += openssl/include perfmon/include spiffs/include
ESPINCSBASE     += ulp/include wifi_provisioning/include rmaker_common/include
ESPINCSBASE     += json_parser/upstream/include json_parser/upstream
ESPINCSBASE     += json_generator/upstream esp_schedule/include
ESPINCSBASE     += esp_rainmaker/include gpio_button/button/include
ESPINCSBASE     += qrcode/include ws2812_led esp_diagnostics/include
ESPINCSBASE     += rtc_store/include esp_insights/include
ESPINCSBASE     += esp-dsp/modules/dotprod/include
ESPINCSBASE     += esp-dsp/modules/support/include
ESPINCSBASE     += esp-dsp/modules/windows/include
ESPINCSBASE     += esp-dsp/modules/windows/hann/include
ESPINCSBASE     += esp-dsp/modules/windows/blackman/include
ESPINCSBASE     += esp-dsp/modules/windows/blackman_harris/include
ESPINCSBASE     += esp-dsp/modules/windows/blackman_nuttall/include
ESPINCSBASE     += esp-dsp/modules/windows/nuttall/include
ESPINCSBASE     += esp-dsp/modules/windows/flat_top/include
ESPINCSBASE     += esp-dsp/modules/iir/include
ESPINCSBASE     += esp-dsp/modules/fir/include
ESPINCSBASE     += esp-dsp/modules/math/include
ESPINCSBASE     += esp-dsp/modules/math/add/include
ESPINCSBASE     += esp-dsp/modules/math/sub/include
ESPINCSBASE     += esp-dsp/modules/math/mul/include
ESPINCSBASE     += esp-dsp/modules/math/addc/include
ESPINCSBASE     += esp-dsp/modules/math/mulc/include
ESPINCSBASE     += esp-dsp/modules/math/sqrt/include
ESPINCSBASE     += esp-dsp/modules/matrix/include
ESPINCSBASE     += esp-dsp/modules/fft/include
ESPINCSBASE     += esp-dsp/modules/dct/include
ESPINCSBASE     += esp-dsp/modules/conv/include
ESPINCSBASE     += esp-dsp/modules/common/include
ESPINCSBASE     += esp-dsp/modules/kalman/ekf/include
ESPINCSBASE     += esp-dsp/modules/kalman/ekf_imu13states/include
ESPINCSBASE     += esp_littlefs/include esp-dl/include esp-dl/include/tool
ESPINCSBASE     += esp-dl/include/typedef esp-dl/include/image
ESPINCSBASE     += esp-dl/include/math esp-dl/include/nn esp-dl/include/layer
ESPINCSBASE     += esp-dl/include/detect esp-dl/include/model_zoo
ESPINCSBASE     += esp-sr/src/include esp-sr/esp-tts/esp_tts_chinese/include
ESPINCSBASE     += esp-sr/include/esp32 esp32-camera/driver/include
ESPINCSBASE     += esp32-camera/conversions/include fb_gfx/include
ESPINCSBASE     += esp32-camera/conversions/include fb_gfx/include

ESPINCS 		:= $(addprefix $(ESPINCSROOT), $(ESPINCSBASE))
ESPINCS 		+= $(ESPMAINROOT)tools/sdk/esp32/dio_qspi/include
ESPINCS 		+= $(ESPMAINROOT)cores/esp32
ESPINCS 		+= $(ESPMAINROOT)variants/node32s
ESPINCS 		+= $(ESPMAINROOT)libraries/WiFi/src
ESPINCS 		+= $(ESPMAINROOT)libraries/SPI/src
ESPINCS 		+= $(ESPMAINROOT)libraries/Wire/src





CC          := /home/tony/esp32/tools/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc
CXX         := /home/tony/esp32/tools/xtensa-esp32-elf/bin/xtensa-esp32-elf-g++
AR          := /home/tony/esp32/tools/xtensa-esp32-elf/bin/xtensa-esp32-elf-ar
PYTHON3 	:= /usr/bin/python3

# TODO: should have CFLAGS? -std=gnu99

CXXFLAGS    := -Wall -Os -w -c -MMD
CXXFLAGS    += -std=gnu++17 -ggdb ##### TRY OTHERS
CXXFLAGS    += -DDEBUG #!!!!!!!!!!

CXXFLAGS    += -DROTARY_REVERSED
CXXFLAGS    += -DMBEDTLS_CONFIG_FILE=\"mbedtls/esp_config.h\"   ###### ?????
CXXFLAGS    += -DHAVE_CONFIG_H -DUNITY_INCLUDE_CONFIG_H -DWITH_POSIX
CXXFLAGS    += -D_GNU_SOURCE -DIDF_VER=\"v4.4.3\" -DESP_PLATFORM
CXXFLAGS    += -D_POSIX_READER_WRITER_LOCKS 
CXXFLAGS    += -DF_CPU=240000000L -DARDUINO=10605 -DARDUINO_Node32s
CXXFLAGS    += -DARDUINO_ARCH_ESP32 -DARDUINO_BOARD=\"Node32s\"
CXXFLAGS    += -DARDUINO_VARIANT=\"node32s\" -DARDUINO_PARTITION_default
CXXFLAGS    += -DESP32 -DCORE_DEBUG_LEVEL=0 -DARDUINO_USB_CDC_ON_BOOT=0

CXXFLAGS    += -fno-exceptions -fno-unwind-tables -Wno-frame-address
CXXFLAGS    += -ffunction-sections -fdata-sections -Wno-error=unused-function
CXXFLAGS    += -Wno-error=unused-variable -Wno-error=deprecated-declarations
CXXFLAGS    += -Wno-unused-parameter -Wno-sign-compare -freorder-blocks
CXXFLAGS    += -Wwrite-strings -fstack-protector -fstrict-volatile-bitfields
CXXFLAGS    += -Wno-error=unused-but-set-variable -fno-jump-tables
CXXFLAGS    += -fno-tree-switch-conversion -fno-rtti -mlongcalls

CXXFLAGS    += -I$(INCDIR) -I$(INCDIRcntrb)
CXXFLAGS    += $(addprefix -I, $(ESPINCS))

LDFLAGS     := -Wl,--Map=build/radio-clash.map \
			   -L$(ESPMAINROOT)tools/sdk/esp32/lib \
			   -L$(ESPMAINROOT)tools/sdk/esp32/ld \
			   -L$(ESPMAINROOT)tools/sdk/esp32/dio_qspi \
			   -T esp32.rom.redefined.ld -T memory.ld -T sections.ld \
			   -T esp32.rom.ld -T esp32.rom.api.ld -T esp32.rom.libgcc.ld \
			   -T esp32.rom.newlib-data.ld -T esp32.rom.syscalls.ld \
			   -T esp32.peripherals.ld -mlongcalls -Wno-frame-address \
			   -Wl,--cref -Wl,--gc-sections -fno-rtti -fno-lto \
			   -Wl,--wrap=esp_log_write -Wl,--wrap=esp_log_writev \
			   -Wl,--wrap=log_printf -u ld_include_hli_vectors_bt \
			   -u _Z5setupv -u _Z4loopv -u esp_app_desc \
			   -u pthread_include_pthread_impl \
			   -u pthread_include_pthread_cond_impl \
			   -u pthread_include_pthread_local_storage_impl \
			   -u pthread_include_pthread_rwlock_impl \
			   -u include_esp_phy_override \
			   -u ld_include_highint_hdl -u start_app -u start_app_other_cores \
			   -u __ubsan_include -Wl,--wrap=longjmp -u __assert_func \
			   -u vfs_include_syscalls_impl -Wl,--undefined=uxTopUsedPriority \
			   -u app_main -u newlib_include_heap_impl \
			   -u newlib_include_syscalls_impl -u newlib_include_pthread_impl \
			   -u newlib_include_assert_impl -u __cxa_guard_dummy -DESP32 \
			   -DCORE_DEBUG_LEVEL=0 -DARDUINO_USB_CDC_ON_BOOT=0 \
			   -DROTARY_REVERSED -Wall -fno-exceptions -fno-unwind-tables \
			   -Wl,--start-group $(BUILDDIR)/arduino.ar \
			   $(BUILDDIR)/user_obj.ar $(BUILDDIR)/buildinfo.o \
			   $(BUILDDIR)/arduino.ar -lesp_ringbuf -lefuse -lesp_ipc \
			   -ldriver -lesp_pm -lmbedtls -lapp_update -lbootloader_support \
			   -lspi_flash -lnvs_flash -lpthread -lesp_gdbstub -lespcoredump \
			   -lesp_phy -lesp_system -lesp_rom -lhal -lvfs -lesp_eth \
			   -ltcpip_adapter -lesp_netif -lesp_event -lwpa_supplicant \
			   -lesp_wifi -lconsole -llwip -llog -lheap -lsoc -lesp_hw_support \
			   -lxtensa -lesp_common -lesp_timer -lfreertos -lnewlib -lcxx \
			   -lapp_trace -lasio -lbt -lcbor -lunity -lcmock -lcoap -lnghttp \
			   -lesp-tls -lesp_adc_cal -lesp_hid -ltcp_transport -lesp_http_client \
			   -lesp_http_server -lesp_https_ota -lesp_https_server -lesp_lcd \
			   -lprotobuf-c -lprotocomm -lmdns -lesp_local_ctrl -lsdmmc \
			   -lesp_serial_slave_link -lesp_websocket_client -lexpat \
			   -lwear_levelling -lfatfs -lfreemodbus -ljsmn -ljson -llibsodium \
			   -lmqtt -lopenssl -lperfmon -lspiffs -lulp -lwifi_provisioning \
			   -lrmaker_common -ljson_parser -ljson_generator -lesp_schedule \
			   -lesp_rainmaker -lgpio_button -lqrcode -lws2812_led \
			   -lesp_diagnostics -lrtc_store -lesp_insights -lesp-dsp -lesp-sr \
			   -lesp32-camera -lesp_littlefs -lfb_gfx -lasio -lcmock -lunity \
			   -lcoap -lesp_lcd -lesp_websocket_client -lexpat -lfreemodbus \
			   -ljsmn -llibsodium -lperfmon -lcbor -lesp_diagnostics -lrtc_store \
			   -lesp_adc_cal -lesp_hid -lfatfs -lwear_levelling -lopenssl \
			   -lesp_rainmaker -lesp_local_ctrl -lesp_https_server \
			   -lwifi_provisioning -lprotocomm -lbt -lbtdm_app -lprotobuf-c \
			   -lmdns -lrmaker_common -lmqtt -ljson_parser -ljson_generator \
			   -lesp_schedule -lqrcode -lcat_face_detect -lhuman_face_detect \
			   -lcolor_detect -lmfn -ldl -lmultinet -lesp_audio_processor \
			   -lesp_audio_front_end -lwakenet -lesp-sr -lmultinet \
			   -lesp_audio_processor -lesp_audio_front_end -lwakenet -ljson \
			   -lspiffs -ldl_lib -lc_speech_features -lwakeword_model \
			   -lmultinet2_ch -lesp_tts_chinese -lvoice_set_xiaole \
			   -lesp_ringbuf -lefuse -lesp_ipc -ldriver -lesp_pm -lmbedtls \
			   -lapp_update -lbootloader_support -lspi_flash -lnvs_flash \
			   -lpthread -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system \
			   -lesp_rom -lhal -lvfs -lesp_eth -ltcpip_adapter -lesp_netif \
			   -lesp_event -lwpa_supplicant -lesp_wifi -lconsole -llwip -llog \
			   -lheap -lsoc -lesp_hw_support -lxtensa -lesp_common -lesp_timer \
			   -lfreertos -lnewlib -lcxx -lapp_trace -lnghttp -lesp-tls \
			   -ltcp_transport -lesp_http_client -lesp_http_server \
			   -lesp_https_ota -lsdmmc -lesp_serial_slave_link -lulp -lmbedtls_2 \
			   -lmbedcrypto -lmbedx509 -lcoexist -lcore -lespnow -lmesh \
			   -lnet80211 -lpp -lsmartconfig -lwapi -lesp_ringbuf -lefuse \
			   -lesp_ipc -ldriver -lesp_pm -lmbedtls -lapp_update \
			   -lbootloader_support -lspi_flash -lnvs_flash -lpthread \
			   -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system -lesp_rom \
			   -lhal -lvfs -lesp_eth -ltcpip_adapter -lesp_netif -lesp_event \
			   -lwpa_supplicant -lesp_wifi -lconsole -llwip -llog -lheap \
			   -lsoc -lesp_hw_support -lxtensa -lesp_common -lesp_timer \
			   -lfreertos -lnewlib -lcxx -lapp_trace -lnghttp -lesp-tls \
			   -ltcp_transport -lesp_http_client -lesp_http_server \
			   -lesp_https_ota -lsdmmc -lesp_serial_slave_link -lulp \
			   -lmbedtls_2 -lmbedcrypto -lmbedx509 -lcoexist -lcore -lespnow \
			   -lmesh -lnet80211 -lpp -lsmartconfig -lwapi -lesp_ringbuf -lefuse \
			   -lesp_ipc -ldriver -lesp_pm -lmbedtls -lapp_update \
			   -lbootloader_support -lspi_flash -lnvs_flash -lpthread \
			   -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system -lesp_rom \
			   -lhal -lvfs -lesp_eth -ltcpip_adapter -lesp_netif -lesp_event \
			   -lwpa_supplicant -lesp_wifi -lconsole -llwip -llog -lheap -lsoc \
			   -lesp_hw_support -lxtensa -lesp_common -lesp_timer -lfreertos \
			   -lnewlib -lcxx -lapp_trace -lnghttp -lesp-tls -ltcp_transport \
			   -lesp_http_client -lesp_http_server -lesp_https_ota -lsdmmc \
			   -lesp_serial_slave_link -lulp -lmbedtls_2 -lmbedcrypto -lmbedx509 \
			   -lcoexist -lcore -lespnow -lmesh -lnet80211 -lpp -lsmartconfig \
			   -lwapi -lesp_ringbuf -lefuse -lesp_ipc -ldriver -lesp_pm -lmbedtls \
			   -lapp_update -lbootloader_support -lspi_flash -lnvs_flash -lpthread \
			   -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system -lesp_rom -lhal \
			   -lvfs -lesp_eth -ltcpip_adapter -lesp_netif -lesp_event \
			   -lwpa_supplicant -lesp_wifi -lconsole -llwip -llog -lheap -lsoc \
			   -lesp_hw_support -lxtensa -lesp_common -lesp_timer -lfreertos \
			   -lnewlib -lcxx -lapp_trace -lnghttp -lesp-tls -ltcp_transport \
			   -lesp_http_client -lesp_http_server -lesp_https_ota -lsdmmc \
			   -lesp_serial_slave_link -lulp -lmbedtls_2 -lmbedcrypto -lmbedx509 \
			   -lcoexist -lcore -lespnow -lmesh -lnet80211 -lpp -lsmartconfig \
			   -lwapi -lesp_ringbuf -lefuse -lesp_ipc -ldriver -lesp_pm -lmbedtls \
			   -lapp_update -lbootloader_support -lspi_flash -lnvs_flash -lpthread \
			   -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system -lesp_rom -lhal \
			   -lvfs -lesp_eth -ltcpip_adapter -lesp_netif -lesp_event \
			   -lwpa_supplicant -lesp_wifi -lconsole -llwip -llog -lheap -lsoc \
			   -lesp_hw_support -lxtensa -lesp_common -lesp_timer -lfreertos \
			   -lnewlib -lcxx -lapp_trace -lnghttp -lesp-tls -ltcp_transport \
			   -lesp_http_client -lesp_http_server -lesp_https_ota -lsdmmc \
			   -lesp_serial_slave_link -lulp -lmbedtls_2 -lmbedcrypto -lmbedx509 \
			   -lcoexist -lcore -lespnow -lmesh -lnet80211 -lpp -lsmartconfig \
			   -lwapi -lphy -lrtc -lesp_phy -lphy -lrtc -lesp_phy -lphy -lrtc \
			   -lxt_hal -lm -lnewlib -lstdc++ -lpthread -lgcc -lcxx -lapp_trace \
			   -lgcov -lapp_trace -lgcov -lc -Wl,--end-group -Wl,-EL

PARTTOOL := $(ESPMAINROOT)/tools/gen_esp32part.py
ESPTOOL  := $(ESPMAINROOT)/tools/esptool.py
ELFSIZE  := $(ESPMAINROOT)/tools/xtensa-esp32-elf/bin/xtensa-esp32-elf-size

# CXXFLAGS  := -std=c++2b -O2 -I. -Wall -Wextra -Werror -Wpedantic -Wshadow
# CXXFLAGS  += -Wconversion -Wsign-conversion -Wunreachable-code
# CXXFLAGS  += -Weffc++ -Wmissing-braces -Wnon-virtual-dtor #-Winline
# CXXFLAGS  += -Wnormalized -Wold-style-cast -Wrange-loop-construct
# CXXFLAGS  += -Wreturn-local-addr -Wredundant-move -Wsuggest-final-types
# CXXFLAGS  += -Wsuggest-override -Wvirtual-inheritance -Wvirtual-move-assign
# CXXFLAGS  += -Wuninitialized -Wswitch-enum -Wswitch
# ifeq ($(COMPTYPE), debug)
# 	CXXFLAGS += -fsanitize=address -fsanitize=undefined
# endif
# CXXFLAGS  += -DSAYBYE
# CXXFLAGS  += -I$(INCDIR)
# CPPFLAGS  :=
# LDFLAGS   :=
# LDLIBS    := -lsystemd -lfmt

SRCS      := $(wildcard $(SRCDIR)/*.cpp $(SRCDIR)/*.c)
SRCSctrib := $(wildcard $(SRCDIResp)/*.cpp $(SRCDIResp)/*.c)
OBJS      := $(notdir $(patsubst %.cpp, %.o, $(SRCS)))
OBJS      := $(notdir $(patsubst %.c, %.o, $(SRCS)))
OBJSesp   := $(notdir $(patsubst %.cpp, %.o, $(SRCSesp)))
OBJSesp   := $(notdir $(patsubst %.c, %.o, $(SRCSesp)))
DESTOBJS  := $(addprefix $(BUILDDIR)/, $(OBJS))
DEPS      := $(wildcard $(INCDIR)/*.h $(INCDIR)/*.hpp)
DEPSesp   := $(wildcard $(INCDIResp)/*.h)


vpath %.h   $(INCDIR)
vpath %.h   $(INCDIRcntrb)
vpath %.hpp $(INCDIR)
vpath %.hpp $(INCDIRcntrb)
vpath %.c   $(SRCDIR)
vpath %.c   $(SRCDIRcntrb)
vpath %.cpp $(SRCDIR)
vpath %.cpp $(SRCDIRcntrb)
vpath %.o   $(BUILDDIR)

.PHONY: all clean mrproper dist check test install begin help done verify \
	    size flash monitor

COREOBJS := $(BUILDDIR)/HWCDC.o $(BUILDDIR)/stdlib_noniso.o
COREOBJS += $(BUILDDIR)/esp32-hal-ledc.o $(BUILDDIR)/FirmwareMSC.o
COREOBJS += $(BUILDDIR)/esp32-hal-sigmadelta.o $(BUILDDIR)/esp32-hal-rgb-led.o
COREOBJS += $(BUILDDIR)/IPAddress.o $(BUILDDIR)/Stream.o
COREOBJS += $(BUILDDIR)/esp32-hal-matrix.o $(BUILDDIR)/WMath.o
COREOBJS += $(BUILDDIR)/MD5Builder.o $(BUILDDIR)/esp32-hal-touch.o
COREOBJS += $(BUILDDIR)/cbuf.o $(BUILDDIR)/USBMSC.o
COREOBJS += $(BUILDDIR)/esp32-hal-uart.o $(BUILDDIR)/esp32-hal-psram.o
COREOBJS += $(BUILDDIR)/esp32-hal-time.o $(BUILDDIR)/esp32-hal-adc.o
COREOBJS += $(BUILDDIR)/esp32-hal-cpu.o $(BUILDDIR)/USB.o $(BUILDDIR)/Print.o
COREOBJS += $(BUILDDIR)/wiring_shift.o $(BUILDDIR)/WString.o $(BUILDDIR)/main.o
COREOBJS += $(BUILDDIR)/firmware_msc_fat.o $(BUILDDIR)/esp32-hal-dac.o
COREOBJS += $(BUILDDIR)/cencode.o $(BUILDDIR)/cdecode.o $(BUILDDIR)/USBCDC.o
COREOBJS += $(BUILDDIR)/esp32-hal-rmt.o $(BUILDDIR)/base64.o
COREOBJS += $(BUILDDIR)/esp32-hal-spi.o $(BUILDDIR)/FunctionalInterrupt.o
COREOBJS += $(BUILDDIR)/esp32-hal-tinyusb.o $(BUILDDIR)/esp32-hal-bt.o
COREOBJS += $(BUILDDIR)/Tone.o $(BUILDDIR)/esp32-hal-timer.o
COREOBJS += $(BUILDDIR)/Esp.o $(BUILDDIR)/IPv6Address.o
COREOBJS += $(BUILDDIR)/esp32-hal-i2c.o $(BUILDDIR)/esp32-hal-misc.o
COREOBJS += $(BUILDDIR)/HardwareSerial.o $(BUILDDIR)/esp32-hal-i2c-slave.o
COREOBJS += $(BUILDDIR)/wiring_pulse.o $(BUILDDIR)/esp32-hal-gpio.o
COREOBJS += $(BUILDDIR)/StreamString.o

OBJS := $(BUILDDIR)/HWCDC.o $(BUILDDIR)/FirmwareMSC.o
OBJS += $(BUILDDIR)/IPAddress.o $(BUILDDIR)/Stream.o $(BUILDDIR)/WMath.o
OBJS += $(BUILDDIR)/MD5Builder.o $(BUILDDIR)/cbuf.o $(BUILDDIR)/USBMSC.o
OBJS += $(BUILDDIR)/USB.o $(BUILDDIR)/Print.o $(BUILDDIR)/WString.o
OBJS += $(BUILDDIR)/FunctionalInterrupt.o $(BUILDDIR)/Tone.o $(BUILDDIR)/USBCDC.o
OBJS += $(BUILDDIR)/IPv6Address.o $(BUILDDIR)/StreamString.o
OBJS += $(BUILDDIR)/HardwareSerial.o $(BUILDDIR)/base64.o $(BUILDDIR)/Esp.o
OBJS += $(BUILDDIR)/main.o $(BUILDDIR)/Wire.o $(BUILDDIR)/SPI.o
OBJS += $(BUILDDIR)/WiFi.o $(BUILDDIR)/WiFiAP.o $(BUILDDIR)/WiFiClient.o
OBJS += $(BUILDDIR)/WiFiGeneric.o $(BUILDDIR)/WiFiMulti.o $(BUILDDIR)/WiFiSTA.o
OBJS += $(BUILDDIR)/WiFiScan.o $(BUILDDIR)/WiFiScan.o $(BUILDDIR)/WiFiServer.o
OBJS += $(BUILDDIR)/WiFiUdp.o $(BUILDDIR)/Adafruit_BusIO_Register.o
OBJS += $(BUILDDIR)/Adafruit_I2CDevice.o $(BUILDDIR)/Adafruit_SPIDevice.o
OBJS += $(BUILDDIR)/Adafruit_GFX.o $(BUILDDIR)/Adafruit_GrayOLED.o
OBJS += $(BUILDDIR)/Adafruit_SPITFT.o $(BUILDDIR)/glcdfont.o
OBJS += $(BUILDDIR)/Adafruit_LEDBackpack.o $(BUILDDIR)/Adafruit_NeoPixel.o
OBJS += $(BUILDDIR)/esp.o $(BUILDDIR)/esp8266.o $(BUILDDIR)/kendyte_k210.o
OBJS += $(BUILDDIR)/DFPlay.o $(BUILDDIR)/VS1053.o $(BUILDDIR)/LiquidCrystal_I2C.o
OBJS += $(BUILDDIR)/RTC_DS1307.o $(BUILDDIR)/RTC_DS3231.o
OBJS += $(BUILDDIR)/RTC_Micros.o $(BUILDDIR)/RTC_Millis.o
OBJS += $(BUILDDIR)/RTC_PCF8523.o $(BUILDDIR)/RTC_PCF8563.o
OBJS += $(BUILDDIR)/RTClib.o $(BUILDDIR)/Recoder.o $(BUILDDIR)/Sixteen.o
OBJS += $(BUILDDIR)/Alarm.o $(BUILDDIR)/Amber.o $(BUILDDIR)/AudioController.o
OBJS += $(BUILDDIR)/Defe.o $(BUILDDIR)/Kerl.o $(BUILDDIR)/LBMode.o
OBJS += $(BUILDDIR)/Mick.o $(BUILDDIR)/ModeAlarm.o $(BUILDDIR)/ModeLight.o
OBJS += $(BUILDDIR)/ModeMP3.o $(BUILDDIR)/ModeTime.o $(BUILDDIR)/ModeWebRadio.o
OBJS += $(BUILDDIR)/Phos.o $(BUILDDIR)/TickTockClock.o
OBJS += $(BUILDDIR)/buildinfo.o
OBJS += $(BUILDDIR)/radio-clash.o


## !! DON'T NEED ALL OF THESE
all: begin $(COREOBJS) $(OBJS) $(BUILDDIR)/arduino.ar $(BUILDDIR)/user_obj.ar \
	 $(BUILDDIR)/radio-clash.elf $(BUILDDIR)/radio-clash.partitions.bin \
	 $(BUILDDIR)/radio-clash.bin \
	 $(BUILDDIR)/radio-clash.bootloader.bin \
	 size \
	 done




begin:
	@echo "$$(tput bold)$$(tput setaf 3)Building radio-clash$$(tput sgr0)"
	@printf "\n"

help:
	@echo "P.S. I Love You"


$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(BUILDDIR)
	$(info [*] compiling		{ $@ })
	@$(CXX) -c -o $@ $< $(CXXFLAGS) $(CPPFLAGS)


# contrib Arduino lib sources
#     do DEPS
$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(BUILDDIR)
	$(info [*] compiling		{ $@ })
	@$(CXX) -c -o $@ $< $(CXXFLAGS) $(CPPFLAGS)

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(BUILDDIR)
	$(info [*] compiling		{ $@ })
	@$(CC) -c -o $@ $< $(CXXFLAGS) $(CPPFLAGS)

# ESP sources
$(BUILDDIR)/%.o: $(ESPSRCFILESROOT)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(info [*] compiling		{ $@ })
	@$(CXX) -c -o $@ $< $(CXXFLAGS) $(CPPFLAGS)

$(BUILDDIR)/%.o: $(ESPSRCFILESROOT)/%.c
	@mkdir -p $(BUILDDIR)
	$(info [*] compiling		{ $@ })
	@$(CC) -c -o $@ $< $(CXXFLAGS) $(CPPFLAGS)

$(BUILDDIR)/%.o: $(ESPSRCFILESROOT)/libb64/%.c
	@mkdir -p $(BUILDDIR)
	$(info [*] compiling		{ $@ })
	@$(CC) -c -o $@ $< $(CXXFLAGS) $(CPPFLAGS)

$(BUILDDIR)/%.o: $(ESPMAINROOT)/libraries/Wire/src/%.cpp
	@mkdir -p $(BUILDDIR)
	$(info [*] compiling		{ $@ })
	@$(CXX) -c -o $@ $< $(CXXFLAGS) $(CPPFLAGS)

$(BUILDDIR)/%.o: $(ESPMAINROOT)/libraries/WiFi/src/%.cpp
	@mkdir -p $(BUILDDIR)
	$(info [*] compiling		{ $@ })
	@$(CXX) -c -o $@ $< $(CXXFLAGS) $(CPPFLAGS)

$(BUILDDIR)/%.o: $(ESPMAINROOT)/libraries/SPI/src/%.cpp
	@mkdir -p $(BUILDDIR)
	$(info [*] compiling		{ $@ })
	@$(CXX) -c -o $@ $< $(CXXFLAGS) $(CPPFLAGS)



$(BUILDDIR)/arduino.ar: $(COREOBJS)
	$(info [*] making core archive	{ $@ })
	@$(AR) cr $@ $^

$(BUILDDIR)/user_obj.ar: $(OBJS)
	$(info [*] making user archive	{ $@ })
	@$(AR) cr $@ $^

$(BUILDDIR)/radio-clash.elf: $(BUILDDIR)/arduino.ar $(BUILDDIR)/user_obj.ar $(BUILDDIR)/buildinfo.o
	$(info [*] linking binary	{ $@ })
	@$(CXX) $(LDFLAGS) -o $@

$(BUILDDIR)/radio-clash.partitions.bin: $(BUILDDIR)/radio-clash.elf
	$(info [*] building partitions	{ $@ })
	@$(PYTHON3) $(PARTTOOL) -q $(ESPMAINROOT)/tools/partitions/default.csv $@

$(BUILDDIR)/radio-clash.bin: $(BUILDDIR)/radio-clash.elf
	$(info [*] create final binary	{ $@ })
	@$(PYTNON3) $(ESPTOOL) --chip esp32 elf2image --flash_mode "dio" --flash_freq "80m" --flash_size "4MB" --elf-sha256-offset 0xb0 -o $@ $^ > /dev/null

$(BUILDDIR)/radio-clash.bootloader.bin:
	$(info [*] building bootloader	{ $@ })
	@cp $(ESPMAINROOT)/tools/partitions/default.csv $(BUILDDIR)/partitions.csv
	@$(PYTHON3) $(ESPTOOL) --chip esp32 elf2image --flash_mode dio --flash_freq 80m --flash_size 4MB -o $(BUILDDIR)/radio-clash.bootloader.bin $(ESPMAINROOT)/tools/sdk/esp32/bin/bootloader_dio_80m.elf


size: $(BUILDDIR)/radio-clash.elf
	@$(ELFSIZE) -A $(BUILDDIR)/radio-clash.elf | perl support/mem_use.pl "^(?:\.iram0\.text|\.iram0\.vectors|\.dram0\.data|\.flash\.text|\.flash\.rodata|)\s+([0-9]+).*" "^(?:\.dram0\.data|\.dram0\.bss|\.noinit)\s+([0-9]+).*"

flash: $(BUILDDIR)/radio-clash.bootloader.bin $(BUILDDIR)/radio-clash.partitions.bin $(BUILDDIR)/radio-clash.bin
	$(ESPTOOL) --chip esp32 --port "/dev/ttyUSB0" --baud 600000 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size 4MB 0x1000 $(BUILDDIR)/radio-clash.bootloader.bin 0x8000 $(BUILDDIR)/radio-clash.partitions.bin 0xe000 $(ESPMAINROOT)/tools/partitions/boot_app0.bin 0x10000 $(BUILDDIR)/radio-clash.bin

# TODO: parameterize /dev/ttyUSB0 and BAUDRATE
monitor:
	$(PYTHON3) -m serial.tools.miniterm --rts=0 --dtr=0 /dev/ttyUSB0 115200




done:
	@printf '\n'
	@echo "$$(tput bold)$$(tput setaf 2)[•] Build done!$$(tput sgr0)"

clean:
	rm -rf $(BUILDDIR)

