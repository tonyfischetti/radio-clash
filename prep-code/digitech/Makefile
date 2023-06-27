ARDUINO_DIR = /usr/share/arduino
ARDMK_DIR = ~/.arduino-makefile
BOARD_TAG = leonardo
ARCHITECTURE  = avr
MONITOR_PORT  = /dev/ttyACM0
AVRDUDE_CONF = /usr/share/arduino/hardware/tools/avrdude.conf
MONITOR_BAUDRATE = 115200
OPTIMIZATION_LEVEL=s

CPPFLAGS += -DPROFILE
# CPPFLAGS += -DPROFILE -DDEBUG -DWITH_TIME

# ARDUINO_LIBS = Adafruit_NeoPixel elapsedMillis Wire LiquidCrystal_I2C IRremote Adafruit_BusIO SPI RTClib SoftwareSerial DFRobotDFPlayerMini
ARDUINO_LIBS = Adafruit_NeoPixel elapsedMillis Wire LiquidCrystal_I2C IRremote Adafruit_BusIO SPI RTClib SoftwareSerial DFPlayerMini_Fast FireTimer

include $(ARDMK_DIR)/Arduino.mk
