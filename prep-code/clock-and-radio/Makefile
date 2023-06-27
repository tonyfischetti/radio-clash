ARDUINO_DIR = /usr/share/arduino
ARDMK_DIR = ~/.arduino-makefile
BOARD_TAG = uno
ARCHITECTURE  = avr
MONITOR_PORT  = /dev/ttyUSB0
AVRDUDE_CONF = /usr/share/arduino/hardware/tools/avrdude.conf
MONITOR_BAUDRATE = 115200
OPTIMIZATION_LEVEL=s

CPPFLAGS += -DPROFILE

ARDUINO_LIBS = Wire RTClib TEA5767 elapsedMillis Adafruit_BusIO SPI Recoder Sixteen LiquidCrystal_I2C

include $(ARDMK_DIR)/Arduino.mk
