# GLOBAL CONFIG

SRCEXT = cpp

CURRENT_DIR = $(CURDIR)
BIN_DIR     = $(CURRENT_DIR)/bin
BUILD_DIR   = $(CURRENT_DIR)/build
OBJ_DIR     = $(CURRENT_DIR)/build
INC_DIR     = $(CURRENT_DIR)/flashing-jacket/src
SRC_DIR     = $(CURRENT_DIR)/flashing-jacket/src

SOURCES  = $(wildcard $(SRC_DIR)/*.$(SRCEXT))
INCLUDES = $(wildcard $(INC_DIR)/*.h)
OBJECTS  = $(SOURCES:$(SRC_DIR)/%.$(SRCEXT)=$(OBJ_DIR)/%.o)




# ARDUINO CONFIG

ARDUINO := arduino

TARGET := flashing-jacket
SKETCH := $(TARGET).ino

PACKAGE := adafruit
ARCH := samd
BOARD := adafruit_feather_m0

PORT := /dev/ttyACM0

FULLBOARD = $(PACKAGE):$(ARCH):$(BOARD)

AFLAGS  = --pref build.path=$(BUILD_DIR)
AFLAGS += --preserve-temp-files
#AFLAGS += -v





# TEST
CC = gcc
CFLAGS = -Wall -ansi
LFLAGS = -lm


TEST_DIR      = $(CURRENT_DIR)/test
TEST_SOURCES  = $(wildcard $(TEST_DIR)/**/*.$(SRCEXT))
TEST_OBJECTS  = $(TEST_SOURCES:%.$(SRCEXT)=$(OBJ_DIR)/%.o)
TEST_INC_DIR  = $(TEST_DIR)




all: $(TARGET)

$(TARGET): 
	mkdir $(BUILD_DIR)
	$(ARDUINO) --verify $(AFLAGS) $(SKETCH_PATH) --board $(FULLBOARD) --port $(PORT)

upload:
	mkdir $(BUILD_DIR)
	$(ARDUINO) --upload $(AFLAGS) $(SKETCH_PATH) --board $(FULLBOARD) --port $(PORT)
	if [ -n "$(MONITOR)" ]; then screen $(PORT) $(MONITOR); fi

test: $(OBJECTS) $(TEST_OBJECTS)
	echo $(TEST_OBJECTS)
	mkdir $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/$@ $^ $(LFLAGS)

$(OBJECTS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(SRCEXT)
	mkdir $(OBJ_DIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INC_DIR)

$(TEST_OBJECTS): $(OBJ_DIR)/%.o: $(TEST_DIR)/%.$(SRCEXT)
	mkdir $(OBJ_DIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INC_DIR) -I$(TEST_INC_DIR)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

rebuild: clean build
