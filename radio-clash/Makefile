
ESP_ROOT = /home/tony/esp32
ESPMK_DIR = ~/.esp-makefile
CHIP = esp32
BOARD = node32s
UPLOAD_PORT  = /dev/ttyUSB0
UPLOAD_SPEED = 600000

SKETCH = $(PWD)/radio-clash.cpp

# The weird build_opt.h errors are from a race condition. but it's worth it
# BUILD_THREADS=1

BUILD_EXTRA_FLAGS += -DDEBUG -DROTARY_REVERSED
# BUILD_EXTRA_FLAGS += -DDF_DEBUG -DDFPLAY_DEBUG_SERIAL=Serial

BUILD_EXTRA_FLAGS += -Wall -fno-exceptions -fno-unwind-tables
# BUILD_EXTRA_FLAGS += -O2

include $(ESPMK_DIR)/makeEspArduino.mk
