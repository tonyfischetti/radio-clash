
.DELETE_ON_ERROR:

COMPTYPE  	:= debug

HOME 		:= /home/tony

TTY 		:= /dev/ttyUSB0
BAUDRATE	:= 115200

CC          := $(HOME)/esp32/tools/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc
CXX         := $(HOME)/esp32/tools/xtensa-esp32-elf/bin/xtensa-esp32-elf-g++
AR          := $(HOME)/esp32/tools/xtensa-esp32-elf/bin/xtensa-esp32-elf-ar
PYTHON3 	:= /usr/bin/python3

ESPMAINROOT := $(HOME)/esp32/
INCDIR    	:= include
INCDIRcntrb := contrib/include
SRCDIR    	:= src
SRCDIRcntrb	:= contrib/src
BUILDDIR  	:= build

PARTTOOL 	:= $(ESPMAINROOT)/tools/gen_esp32part.py
ESPTOOL  	:= $(ESPMAINROOT)/tools/esptool.py
ELFSIZE  	:= $(ESPMAINROOT)/tools/xtensa-esp32-elf/bin/xtensa-esp32-elf-size

# --------------------------------------------------------------- #

.PHONY: all clean mrproper dist check test install begin help done verify \
	    size flash monitor createbuilddir

# --------------------------------------------------------------- #

# TODO: should have CFLAGS? -std=gnu99

CXXFLAGS    := -Wall -Os -w -c -MMD
CXXFLAGS    += -std=gnu++17 -ggdb ##### TRY OTHERS
ifeq ($(COMPTYPE), debug)
	CXXFLAGS += -DDEBUG # -fsanitize=address -fsanitize=undefined DCORE_DEBUG_LEVEL=X???
endif

CXXFLAGS    += -DROTARY_REVERSED
CXXFLAGS    += -DMBEDTLS_CONFIG_FILE=\"mbedtls/esp_config.h\"   ###### ?????
CXXFLAGS    += -DHAVE_CONFIG_H -DUNITY_INCLUDE_CONFIG_H -DWITH_POSIX
CXXFLAGS    += -D_GNU_SOURCE -DIDF_VER=\"v4.4.3\" -DESP_PLATFORM
CXXFLAGS    += -D_POSIX_READER_WRITER_LOCKS 
CXXFLAGS    += -DF_CPU=240000000L -DARDUINO=10605 -DARDUINO_Node32s
CXXFLAGS    += -DARDUINO_ARCH_ESP32 -DARDUINO_BOARD=\"Node32s\"
CXXFLAGS    += -DARDUINO_VARIANT=\"node32s\" -DARDUINO_PARTITION_default
CXXFLAGS    += -DESP32 -DCORE_DEBUG_LEVEL=0 -DARDUINO_USB_CDC_ON_BOOT=0

# some (most?) of these don't work
CXXFLAGS    += -fno-exceptions -fno-unwind-tables -Wno-frame-address
CXXFLAGS    += -ffunction-sections -fdata-sections -Wno-error=unused-function
CXXFLAGS    += -Wno-error=unused-variable -Wno-error=deprecated-declarations
CXXFLAGS    += -Wno-unused-parameter -Wno-sign-compare -freorder-blocks
CXXFLAGS    += -Wwrite-strings -fstack-protector -fstrict-volatile-bitfields
CXXFLAGS    += -Wno-error=unused-but-set-variable -fno-jump-tables
CXXFLAGS    += -fno-tree-switch-conversion -fno-rtti -mlongcalls

CXXFLAGSX   := -Wall -Wextra -Werror -Wpedantic -Wshadow
CXXFLAGSX   += -Wconversion -Wsign-conversion -Wunreachable-code
CXXFLAGSX   += -Weffc++ -Wmissing-braces -Wnon-virtual-dtor #-Winline
CXXFLAGSX   += -Wnormalized -Wold-style-cast 
CXXFLAGSX   += -Wreturn-local-addr -Wsuggest-final-types
CXXFLAGSX   += -Wsuggest-override -Wvirtual-inheritance -Wvirtual-move-assign
CXXFLAGSX   += -Wuninitialized -Wswitch-enum -Wswitch


ESPSRCFILESROOT := $(ESPMAINROOT)cores/esp32/
ESPINCSROOT  	:= $(ESPMAINROOT)tools/sdk/esp32/include/
ESPLIBS 	 	:= $(ESPMAINROOT)tools/sdk/esp32/lib \
				   $(ESPMAINROOT)tools/sdk/esp32/ld \
				   $(ESPMAINROOT)tools/sdk/esp32/dio_qspi

# --------------------------------------------------------------- #

ESPINCSBASE     := newlib/platform_include freertos/include \
	freertos/include/esp_additions/freertos freertos/port/xtensa/include \
	freertos/include/esp_additions esp_hw_support/include \
	esp_hw_support/include/soc esp_hw_support/include/soc/esp32 \
	esp_hw_support/port/esp32 esp_hw_support/port/esp32/private_include \
	heap/include log/include lwip/include/apps lwip/include/apps/sntp \
	lwip/lwip/src/include lwip/port/esp32/include lwip/port/esp32/include/arch \
	soc/include soc/esp32 soc/esp32/include hal/esp32/include hal/include \
	hal/platform_port/include esp_rom/include esp_rom/include/esp32 \
	esp_rom/esp32 esp_common/include esp_system/include esp_system/port/soc \
	esp_system/port/public_compat esp32/include xtensa/include \
	xtensa/esp32/include driver/include driver/esp32/include esp_pm/include \
	esp_ringbuf/include efuse/include efuse/esp32/include vfs/include \
	esp_wifi/include esp_event/include esp_netif/include esp_eth/include \
	tcpip_adapter/include esp_phy/include esp_phy/esp32/include \
	esp_ipc/include app_trace/include esp_timer/include mbedtls/port/include \
	mbedtls/mbedtls/include mbedtls/esp_crt_bundle/include app_update/include \
	spi_flash/include bootloader_support/include nvs_flash/include \
	pthread/include esp_gdbstub/include esp_gdbstub/xtensa esp_gdbstub/esp32 \
	espcoredump/include espcoredump/include/port/xtensa wpa_supplicant/include \
	wpa_supplicant/port/include wpa_supplicant/esp_supplicant/include \
	ieee802154/include console asio/asio/asio/include asio/port/include \
	bt/common/osi/include bt/include/esp32/include bt/common/api/include/api \
	bt/common/btc/profile/esp/blufi/include bt/common/btc/profile/esp/include \
	bt/host/bluedroid/api/include/api bt/esp_ble_mesh/mesh_common/include \
	bt/esp_ble_mesh/mesh_common/tinycrypt/include bt/esp_ble_mesh/mesh_core \
	bt/esp_ble_mesh/mesh_core/include bt/esp_ble_mesh/mesh_core/storage \
	bt/esp_ble_mesh/btc/include bt/esp_ble_mesh/mesh_models/common/include \
	bt/esp_ble_mesh/mesh_models/client/include \
	bt/esp_ble_mesh/mesh_models/server/include \
	bt/esp_ble_mesh/api/core/include bt/esp_ble_mesh/api/models/include \
	bt/esp_ble_mesh/api cbor/port/include unity/include unity/unity/src \
	cmock/CMock/src coap/port/include coap/libcoap/include nghttp/port/include \
	nghttp/nghttp2/lib/includes esp-tls esp-tls/esp-tls-crypto \
	esp_adc_cal/include esp_hid/include tcp_transport/include \
	esp_http_client/include esp_http_server/include \
	esp_https_ota/include esp_https_server/include \
	esp_lcd/include esp_lcd/interface protobuf-c/protobuf-c \
	protocomm/include/common protocomm/include/security \
	protocomm/include/transports mdns/include esp_local_ctrl/include \
	sdmmc/include esp_serial_slave_link/include esp_websocket_client/include \
	expat/expat/expat/lib expat/port/include wear_levelling/include \
	fatfs/diskio fatfs/vfs fatfs/src freemodbus/common/include \
	idf_test/include idf_test/include/esp32 jsmn/include json/cJSON \
	libsodium/libsodium/src/libsodium/include libsodium/port_include \
	mqtt/esp-mqtt/include openssl/include perfmon/include spiffs/include \
	ulp/include wifi_provisioning/include rmaker_common/include \
	json_parser/upstream/include json_parser/upstream json_generator/upstream \
	esp_schedule/include esp_rainmaker/include gpio_button/button/include \
	qrcode/include ws2812_led esp_diagnostics/include rtc_store/include \
	esp_insights/include esp-dsp/modules/dotprod/include \
	esp-dsp/modules/support/include esp-dsp/modules/windows/include \
	esp-dsp/modules/windows/hann/include \
	esp-dsp/modules/windows/blackman/include \
	esp-dsp/modules/windows/blackman_harris/include \
	esp-dsp/modules/windows/blackman_nuttall/include \
	esp-dsp/modules/windows/nuttall/include \
	esp-dsp/modules/windows/flat_top/include esp-dsp/modules/iir/include \
	esp-dsp/modules/fir/include esp-dsp/modules/math/include \
	esp-dsp/modules/math/add/include esp-dsp/modules/math/sub/include \
	esp-dsp/modules/math/mul/include esp-dsp/modules/math/addc/include \
	esp-dsp/modules/math/mulc/include esp-dsp/modules/math/sqrt/include \
	esp-dsp/modules/matrix/include esp-dsp/modules/fft/include \
	esp-dsp/modules/dct/include esp-dsp/modules/conv/include \
	esp-dsp/modules/common/include esp-dsp/modules/kalman/ekf/include \
	esp-dsp/modules/kalman/ekf_imu13states/include esp_littlefs/include \
	esp-dl/include esp-dl/include/tool esp-dl/include/typedef \
	esp-dl/include/image esp-dl/include/math esp-dl/include/nn \
	esp-dl/include/layer esp-dl/include/detect esp-dl/include/model_zoo \
	esp-sr/src/include esp-sr/esp-tts/esp_tts_chinese/include \
	esp-sr/include/esp32 esp32-camera/driver/include \
	esp32-camera/conversions/include fb_gfx/include

ESPINCS 		:= $(addprefix $(ESPINCSROOT), $(ESPINCSBASE))
ESPINCS 		+= $(ESPMAINROOT)tools/sdk/esp32/dio_qspi/include
ESPINCS 		+= $(ESPMAINROOT)cores/esp32
ESPINCS 		+= $(ESPMAINROOT)variants/node32s
ESPINCS 		+= $(ESPMAINROOT)libraries/WiFi/src
ESPINCS 		+= $(ESPMAINROOT)libraries/SPI/src
ESPINCS 		+= $(ESPMAINROOT)libraries/Wire/src

CXXFLAGS    	+= -I$(INCDIR) -I$(INCDIRcntrb)
CXXFLAGS    	+= $(addprefix -I, $(ESPINCS))

# ------------------------------------------------------------------------- #

LDFLAGS := -Wl,--Map=build/radio-clash.map \
	-L$(ESPMAINROOT)tools/sdk/esp32/lib -L$(ESPMAINROOT)tools/sdk/esp32/ld \
	-L$(ESPMAINROOT)tools/sdk/esp32/dio_qspi -T esp32.rom.redefined.ld \
	-T memory.ld -T sections.ld -T esp32.rom.ld -T esp32.rom.api.ld \
	-T esp32.rom.libgcc.ld -T esp32.rom.newlib-data.ld -T esp32.rom.syscalls.ld \
	-T esp32.peripherals.ld -mlongcalls -Wno-frame-address -Wl,--cref \
	-Wl,--gc-sections -fno-rtti -fno-lto -Wl,--wrap=esp_log_write \
	-Wl,--wrap=esp_log_writev -Wl,--wrap=log_printf \
	-u ld_include_hli_vectors_bt -u _Z5setupv -u _Z4loopv -u esp_app_desc \
	-u pthread_include_pthread_impl -u pthread_include_pthread_cond_impl \
	-u pthread_include_pthread_local_storage_impl \
	-u pthread_include_pthread_rwlock_impl -u include_esp_phy_override \
	-u ld_include_highint_hdl -u start_app -u start_app_other_cores \
	-u __ubsan_include -Wl,--wrap=longjmp -u __assert_func \
	-u vfs_include_syscalls_impl -Wl,--undefined=uxTopUsedPriority \
	-u app_main -u newlib_include_heap_impl -u newlib_include_syscalls_impl \
	-u newlib_include_pthread_impl -u newlib_include_assert_impl \
	-u __cxa_guard_dummy -DESP32 -DCORE_DEBUG_LEVEL=0 \
	-DARDUINO_USB_CDC_ON_BOOT=0 -DROTARY_REVERSED -Wall -fno-exceptions \
	-fno-unwind-tables -Wl,--start-group $(BUILDDIR)/arduino.ar \
	$(BUILDDIR)/user_obj.ar $(BUILDDIR)/buildinfo.o $(BUILDDIR)/arduino.ar \
	-lesp_ringbuf -lefuse -lesp_ipc -ldriver -lesp_pm -lmbedtls -lapp_update \
	-lbootloader_support -lspi_flash -lnvs_flash -lpthread -lesp_gdbstub \
	-lespcoredump -lesp_phy -lesp_system -lesp_rom -lhal -lvfs -lesp_eth \
	-ltcpip_adapter -lesp_netif -lesp_event -lwpa_supplicant -lesp_wifi \
	-lconsole -llwip -llog -lheap -lsoc -lesp_hw_support -lxtensa -lesp_common \
	-lesp_timer -lfreertos -lnewlib -lcxx -lapp_trace -lasio -lbt -lcbor \
	-lunity -lcmock -lcoap -lnghttp -lesp-tls -lesp_adc_cal -lesp_hid \
	-ltcp_transport -lesp_http_client -lesp_http_server -lesp_https_ota \
	-lesp_https_server -lesp_lcd -lprotobuf-c -lprotocomm -lmdns \
	-lesp_local_ctrl -lsdmmc -lesp_serial_slave_link -lesp_websocket_client \
	-lexpat -lwear_levelling -lfatfs -lfreemodbus -ljsmn -ljson -llibsodium \
	-lmqtt -lopenssl -lperfmon -lspiffs -lulp -lwifi_provisioning \
	-lrmaker_common -ljson_parser -ljson_generator -lesp_schedule \
	-lesp_rainmaker -lgpio_button -lqrcode -lws2812_led -lesp_diagnostics \
	-lrtc_store -lesp_insights -lesp-dsp -lesp-sr -lesp32-camera \
	-lesp_littlefs -lfb_gfx -lasio -lcmock -lunity -lcoap -lesp_lcd \
	-lesp_websocket_client -lexpat -lfreemodbus -ljsmn -llibsodium -lperfmon \
	-lcbor -lesp_diagnostics -lrtc_store -lesp_adc_cal -lesp_hid -lfatfs \
	-lwear_levelling -lopenssl -lesp_rainmaker -lesp_local_ctrl \
	-lesp_https_server -lwifi_provisioning -lprotocomm -lbt -lbtdm_app \
	-lprotobuf-c -lmdns -lrmaker_common -lmqtt -ljson_parser -ljson_generator \
	-lesp_schedule -lqrcode -lcat_face_detect -lhuman_face_detect \
	-lcolor_detect -lmfn -ldl -lmultinet -lesp_audio_processor \
	-lesp_audio_front_end -lwakenet -lesp-sr -lmultinet -lesp_audio_processor \
	-lesp_audio_front_end -lwakenet -ljson -lspiffs -ldl_lib \
	-lc_speech_features -lwakeword_model -lmultinet2_ch -lesp_tts_chinese \
	-lvoice_set_xiaole -lesp_ringbuf -lefuse -lesp_ipc -ldriver -lesp_pm \
	-lmbedtls -lapp_update -lbootloader_support -lspi_flash -lnvs_flash \
	-lpthread -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system -lesp_rom \
	-lhal -lvfs -lesp_eth -ltcpip_adapter -lesp_netif -lesp_event \
	-lwpa_supplicant -lesp_wifi -lconsole -llwip -llog -lheap -lsoc \
	-lesp_hw_support -lxtensa -lesp_common -lesp_timer -lfreertos -lnewlib \
	-lcxx -lapp_trace -lnghttp -lesp-tls -ltcp_transport -lesp_http_client \
	-lesp_http_server -lesp_https_ota -lsdmmc -lesp_serial_slave_link -lulp \
	-lmbedtls_2 -lmbedcrypto -lmbedx509 -lcoexist -lcore -lespnow -lmesh \
	-lnet80211 -lpp -lsmartconfig -lwapi -lesp_ringbuf -lefuse -lesp_ipc \
	-ldriver -lesp_pm -lmbedtls -lapp_update -lbootloader_support -lspi_flash \
	-lnvs_flash -lpthread -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system \
	-lesp_rom -lhal -lvfs -lesp_eth -ltcpip_adapter -lesp_netif -lesp_event \
	-lwpa_supplicant -lesp_wifi -lconsole -llwip -llog -lheap -lsoc \
	-lesp_hw_support -lxtensa -lesp_common -lesp_timer -lfreertos -lnewlib \
	-lcxx -lapp_trace -lnghttp -lesp-tls -ltcp_transport -lesp_http_client \
	-lesp_http_server -lesp_https_ota -lsdmmc -lesp_serial_slave_link -lulp \
	-lmbedtls_2 -lmbedcrypto -lmbedx509 -lcoexist -lcore -lespnow -lmesh \
	-lnet80211 -lpp -lsmartconfig -lwapi -lesp_ringbuf -lefuse -lesp_ipc \
	-ldriver -lesp_pm -lmbedtls -lapp_update -lbootloader_support -lspi_flash \
	-lnvs_flash -lpthread -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system \
	-lesp_rom -lhal -lvfs -lesp_eth -ltcpip_adapter -lesp_netif -lesp_event \
	-lwpa_supplicant -lesp_wifi -lconsole -llwip -llog -lheap -lsoc \
	-lesp_hw_support -lxtensa -lesp_common -lesp_timer -lfreertos -lnewlib \
	-lcxx -lapp_trace -lnghttp -lesp-tls -ltcp_transport -lesp_http_client \
	-lesp_http_server -lesp_https_ota -lsdmmc -lesp_serial_slave_link -lulp \
	-lmbedtls_2 -lmbedcrypto -lmbedx509 -lcoexist -lcore -lespnow -lmesh \
	-lnet80211 -lpp -lsmartconfig -lwapi -lesp_ringbuf -lefuse -lesp_ipc \
	-ldriver -lesp_pm -lmbedtls -lapp_update -lbootloader_support -lspi_flash \
	-lnvs_flash -lpthread -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system \
	-lesp_rom -lhal -lvfs -lesp_eth -ltcpip_adapter -lesp_netif -lesp_event \
	-lwpa_supplicant -lesp_wifi -lconsole -llwip -llog -lheap -lsoc \
	-lesp_hw_support -lxtensa -lesp_common -lesp_timer -lfreertos -lnewlib \
	-lcxx -lapp_trace -lnghttp -lesp-tls -ltcp_transport -lesp_http_client \
	-lesp_http_server -lesp_https_ota -lsdmmc -lesp_serial_slave_link -lulp \
	-lmbedtls_2 -lmbedcrypto -lmbedx509 -lcoexist -lcore -lespnow -lmesh \
	-lnet80211 -lpp -lsmartconfig -lwapi -lesp_ringbuf -lefuse -lesp_ipc \
	-ldriver -lesp_pm -lmbedtls -lapp_update -lbootloader_support -lspi_flash \
	-lnvs_flash -lpthread -lesp_gdbstub -lespcoredump -lesp_phy -lesp_system \
	-lesp_rom -lhal -lvfs -lesp_eth -ltcpip_adapter -lesp_netif -lesp_event \
	-lwpa_supplicant -lesp_wifi -lconsole -llwip -llog -lheap -lsoc \
	-lesp_hw_support -lxtensa -lesp_common -lesp_timer -lfreertos -lnewlib \
	-lcxx -lapp_trace -lnghttp -lesp-tls -ltcp_transport -lesp_http_client \
	-lesp_http_server -lesp_https_ota -lsdmmc -lesp_serial_slave_link -lulp \
	-lmbedtls_2 -lmbedcrypto -lmbedx509 -lcoexist -lcore -lespnow -lmesh \
	-lnet80211 -lpp -lsmartconfig -lwapi -lphy -lrtc -lesp_phy -lphy -lrtc \
	-lesp_phy -lphy -lrtc -lxt_hal -lm -lnewlib -lstdc++ -lpthread -lgcc \
	-lcxx -lapp_trace -lgcov -lapp_trace -lgcov -lc -Wl,--end-group -Wl,-EL
# ------------------------------------------------------------------------- #

vpath %.h   $(INCDIR)
vpath %.hpp $(INCDIR)
vpath %.h   $(INCDIRcntrb)
vpath %.hpp $(INCDIRcntrb)
vpath %.c   $(SRCDIR)
vpath %.c   $(SRCDIRcntrb)
vpath %.cpp $(SRCDIR)
vpath %.cpp $(SRCDIRcntrb)
vpath %.o   $(BUILDDIR)

COS := HWCDC stdlib_noniso esp32-hal-ledc FirmwareMSC esp32-hal-sigmadelta \
	   esp32-hal-rgb-led IPAddress Stream esp32-hal-matrix WMath MD5Builder \
	   esp32-hal-touch cbuf USBMSC esp32-hal-uart esp32-hal-psram \
	   esp32-hal-time esp32-hal-adc esp32-hal-cpu USB Print wiring_shift \
	   WString main firmware_msc_fat esp32-hal-dac cencode cdecode USBCDC \
	   esp32-hal-rmt base64 esp32-hal-spi \
	   esp32-hal-tinyusb esp32-hal-bt Tone esp32-hal-timer Esp IPv6Address \
	   esp32-hal-i2c esp32-hal-misc HardwareSerial esp32-hal-i2c-slave \
	   wiring_pulse esp32-hal-gpio StreamString \
	   Wire SPI WiFi WiFiAP WiFiClient WiFiGeneric WiFiMulti WiFiSTA WiFiScan \
	   WiFiServer WiFiUdp
COREOBJS := $(addsuffix .o, $(addprefix $(BUILDDIR)/, $(COS)))

MOS  := Adafruit_I2CDevice Adafruit_SPIDevice Adafruit_GFX glcdfont \
		Adafruit_LEDBackpack Adafruit_NeoPixel esp esp8266 kendyte_k210 \
		DFPlay VS1053 LiquidCrystal_I2C RTC_DS3231 RTClib Recoder Sixteen Timeout \
		Alarm Amber AudioController Defe Kerl LBMode Mick ModeAlarm ModeLight \
		ModeMP3 ModeTime ModeWebRadio Phos TickTockClock buildinfo radio-clash
OBJS := $(addsuffix .o, $(addprefix $(BUILDDIR)/, $(MOS)))


# --------------------------------------------------------------- #
# --------------------------------------------------------------- #


all: begin createbuilddir $(OBJS) $(BUILDDIR)/arduino.ar \
	 $(BUILDDIR)/user_obj.ar $(BUILDDIR)/radio-clash.elf \
	 $(BUILDDIR)/radio-clash.partitions.bin $(BUILDDIR)/radio-clash.bin \
	 $(BUILDDIR)/radio-clash.bootloader.bin size done

# core objects must be built before downstream objects
$(OBJS): $(COREOBJS)

begin:
	@echo "$$(tput bold)$$(tput setaf 3)Building radio-clash$$(tput sgr0)"
	@printf "\n"

help:
	@echo "P.S. I Love You"

size: $(BUILDDIR)/radio-clash.elf
	@$(ELFSIZE) -A $(BUILDDIR)/radio-clash.elf | perl support/mem_use.pl "^(?:\.iram0\.text|\.iram0\.vectors|\.dram0\.data|\.flash\.text|\.flash\.rodata|)\s+([0-9]+).*" "^(?:\.dram0\.data|\.dram0\.bss|\.noinit)\s+([0-9]+).*"

flash: $(BUILDDIR)/radio-clash.bootloader.bin $(BUILDDIR)/radio-clash.partitions.bin $(BUILDDIR)/radio-clash.bin
	$(ESPTOOL) --chip esp32 --port "/dev/ttyUSB0" --baud 600000 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size 4MB 0x1000 $(BUILDDIR)/radio-clash.bootloader.bin 0x8000 $(BUILDDIR)/radio-clash.partitions.bin 0xe000 $(ESPMAINROOT)/tools/partitions/boot_app0.bin 0x10000 $(BUILDDIR)/radio-clash.bin

monitor:
	$(PYTHON3) -m serial.tools.miniterm --rts=0 --dtr=0 $(TTY) $(BAUDRATE)

createbuilddir:
	@mkdir -p $(BUILDDIR)


COMPINFO 	= $(info [*] compiling		{ $@ })
COMPCMDCXX 	= @$(CXX) -c -o $@ $< $(CXXFLAGS) $(CXXFLAGSX) $(CPPFLAGS)
COMPCMDC 	= @$(CC) -c -o $@ $< $(CXXFLAGS) $(CPPFLAGS)


#################################
##          main code          ##
#################################

MCCOMMON 	 := $(INCDIR)/deebug.hpp $(INCDIR)/common.h
IRDEPS 		 := $(INCDIR)/remote_commands.h $(INCDIR)/remote_codes.h $(INCDIRcntrb)/IRremote.hpp $(INCDIRcntrb)/IRremoteInt.h $(INCDIRcntrb)/digitalWriteFast.h $(INCDIRcntrb)/private/IRTimer.hpp $(INCDIRcntrb)/IRFeedbackLED.hpp $(INCDIRcntrb)/LongUnion.h $(INCDIRcntrb)/IRProtocol.hpp $(INCDIRcntrb)/IRReceive.hpp $(INCDIRcntrb)/IRSend.hpp $(INCDIRcntrb)/ir_BangOlufsen.hpp $(INCDIRcntrb)/ir_BoseWave.hpp $(INCDIRcntrb)/ir_Denon.hpp $(INCDIRcntrb)/ir_JVC.hpp $(INCDIRcntrb)/ir_Kaseikyo.hpp $(INCDIRcntrb)/ir_Lego.hpp $(INCDIRcntrb)/ir_LG.hpp $(INCDIRcntrb)/ir_MagiQuest.hpp $(INCDIRcntrb)/ir_NEC.hpp $(INCDIRcntrb)/ir_RC5_RC6.hpp $(INCDIRcntrb)/ir_Samsung.hpp $(INCDIRcntrb)/ir_Sony.hpp $(INCDIRcntrb)/ir_FAST.hpp $(INCDIRcntrb)/ir_Others.hpp $(INCDIRcntrb)/ir_Pronto.hpp $(INCDIRcntrb)/ir_DistanceWidthProtocol.hpp
ABSTRACTDEPS := $(BUILDDIR)/LBMode.o
TIMEOUTDEPS  := $(BUILDDIR)/Timeout.o
SIXTEENDEPS  := $(BUILDDIR)/Sixteen.o
TIMEDEPS     := $(BUILDDIR)/RTC_DS3231.o $(BUILDDIR)/RTClib.o $(BUILDDIR)/TickTockClock.o
WIFIDEPS 	 := $(INCDIR)/WifiCredential.h $(INCDIR)/WebStation.h $(BUILDDIR)/SPI.o $(BUILDDIR)/WiFi.o build/WiFiClient.o

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/%.h $(MCCOMMON)
	$(COMPINFO)
	$(COMPCMDCXX)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(MCCOMMON)
	$(COMPINFO)
	$(COMPCMDCXX)

$(BUILDDIR)/Alarm.o: 		$(SIXTEENDEPS) $(TIMEDEPS)
$(BUILDDIR)/Amber.o: 		$(BUILDDIR)/Adafruit_LEDBackpack.o $(TIMEDEPS)
$(BUILDDIR)/Defe.o: 		$(BUILDDIR)/DFPlay.o
$(BUILDDIR)/Kerl.o: 		$(WIFIDEPS)
$(BUILDDIR)/LBMode.o: 		$(TIMEOUTDEPS)
$(BUILDDIR)/Mick.o: 		$(IRDEPS)
$(BUILDDIR)/ModeAlarm.o: 	$(INCDIRcntrb)/elapsedMillis.h $(BUILDDIR)/Alarm.o $(TIMEDEPS) $(BUILDDIR)/Defe.o $(BUILDDIR)/AudioController.o
### SKIPPING ModeLight FOR NOW
$(BUILDDIR)/ModeMP3.o: 		$(BUILDDIR)/Defe.o $(BUILDDIR)/AudioController.o
$(BUILDDIR)/ModeTime.o: 	$(INCDIRcntrb)/elapsedMillis.h $(TIMEDEPS)
$(BUILDDIR)/ModeWebRadio.o: $(BUILDDIR)/VS1053.o $(BUILDDIR)/Kerl.o $(INCDIR)/WebStation.h
### SKIPPING Phos FOR NOW
$(BUILDDIR)/TickTockClock.o:$(BUILDDIR)/RTClib.o

$(BUILDDIR)/radio-clash.o: 	$(IRDEPS) $(BUILDDIR)/VS1053.o $(BUILDDIR)/Sixteen.o $(BUILDDIR)/Recoder.o $(BUILDDIR)/Mick.o $(BUILDDIR)/Kerl.o $(BUILDDIR)/TickTockClock.o $(BUILDDIR)/Defe.o $(BUILDDIR)/Alarm.o $(BUILDDIR)/AudioController.o $(BUILDDIR)/Amber.o $(BUILDDIR)/Phos.o $(BUILDDIR)/LBMode.o $(BUILDDIR)/ModeMP3.o $(BUILDDIR)/ModeTime.o $(BUILDDIR)/ModeAlarm.o $(BUILDDIR)/ModeWebRadio.o $(INCDIR)/net_secrets.h $(INCDIR)/web_station_registry.h $(INCDIR)/playlist_names.h

# all modes depend on abstract interface (LBMode), Sixteen, and Timeout
$(BUILDDIR)/ModeLight.o $(BUILDDIR)/ModeWebRadio.o $(BUILDDIR)/ModeAlarm.o $(BUILDDIR)/ModeMP3.o $(BUILDDIR)/ModeTime.o: $(ABSTRACTDEPS) $(TIMEOUTDEPS) $(SIXTEENDEPS)



#################################
## contrib Arduino lib sources ##
#################################

$(BUILDDIR)/%.o: $(SRCDIRcntrb)/%.cpp $(INCDIRcntrb)/%.h
	$(COMPINFO)
	$(COMPCMDCXX)

$(BUILDDIR)/%.o: $(SRCDIRcntrb)/%.cpp
	$(COMPINFO)
	$(COMPCMDCXX)

$(BUILDDIR)/%.o: $(SRCDIRcntrb)/%.c
	$(COMPINFO)
	$(COMPCMDC)

build/Adafruit_LEDBackpack.o: build/Adafruit_GFX.o build/Adafruit_I2CDevice.o
build/Adafruit_GFX.o: build/Adafruit_I2CDevice.o build/Adafruit_SPIDevice.o $(INCDIRcntrb)/gfxfont.h

$(BUILDDIR)/RTC_DS3231.o: $(BUILDDIR)/RTClib.o
$(BUILDDIR)/RTClib.o: build/Adafruit_I2CDevice.o
(BUILDDIR)/VS1053.o: $(INCDIRcntrb)/ConsoleLogger.h $(INCDIRcntrb)/patches/vs1053b-patches.h
$(BUILDDIR)/Sixteen.o: build/LiquidCrystal_I2C.o



#################################
##          ESP sources        ##
#################################

$(BUILDDIR)/%.o: $(ESPSRCFILESROOT)/%.cpp
	$(COMPINFO)
	$(COMPCMDCXX)

$(BUILDDIR)/%.o: $(ESPSRCFILESROOT)/%.c
	$(COMPINFO)
	$(COMPCMDC)

$(BUILDDIR)/%.o: $(ESPSRCFILESROOT)/libb64/%.c
	$(COMPINFO)
	$(COMPCMDC)

$(BUILDDIR)/%.o: $(ESPMAINROOT)/libraries/Wire/src/%.cpp
	$(COMPINFO)
	$(COMPCMDCXX)

$(BUILDDIR)/%.o: $(ESPMAINROOT)/libraries/WiFi/src/%.cpp
	$(COMPINFO)
	$(COMPCMDCXX)

$(BUILDDIR)/%.o: $(ESPMAINROOT)/libraries/SPI/src/%.cpp
	$(COMPINFO)
	$(COMPCMDCXX)



#################################
##       making archives       ##
#################################

$(BUILDDIR)/arduino.ar: $(COREOBJS)
	$(info [*] making core archive	{ $@ })
	@$(AR) cr $@ $^

$(BUILDDIR)/user_obj.ar: $(OBJS)
	$(info [*] making user archive	{ $@ })
	@$(AR) cr $@ $^

$(BUILDDIR)/radio-clash.elf: $(BUILDDIR)/arduino.ar $(BUILDDIR)/user_obj.ar $(BUILDDIR)/buildinfo.o
	$(info [*] linking binary	{ $@ })
	@$(CXX) $(LDFLAGS) -o $@



#################################
##   building final binaries   ##
#################################

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



done:
	@printf '\n'
	@echo "$$(tput bold)$$(tput setaf 2)[•] Build done!$$(tput sgr0)"

clean:
	rm -rf $(BUILDDIR)

