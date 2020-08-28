CP = cp
LUA = lua5.3
MKDIR = mkdir -p
RM = rm -rf

CFLAGS = -std=c99 -Iinclude -Wall -Werror
LLIBS = -llua

INSTALL_PATH = /usr/bin

.PHONY: all build clean install test

BUILD_DIR = build
TOCSTR = $(LUA) tocstr.lua

TARGET_SOURCES = $(filter-out src/main.c, $(wildcard src/*.c))
TARGET_OBJECTS = $(addprefix $(BUILD_DIR)/, $(TARGET_SOURCES:.c=.o))
TARGET = $(BUILD_DIR)/ltdd

TEST_SOURCES = $(wildcard test/*.c)
TEST_OBJECTS = $(addprefix $(BUILD_DIR)/, $(TEST_SOURCES:.c=.o))
TEST_TARGET = $(BUILD_DIR)/ltdd_test

TEST_CSTR_LUA = $(wildcard test/lua/*.lua)
TEST_CSTR_SOURCES = $(addprefix $(BUILD_DIR)/, $(TEST_CSTR_LUA:.lua=.c))
TEST_CSTR_OBJECTS = $(TEST_CSTR_SOURCES:.c=.o)

all: $(TARGET)

build:
	$(MKDIR) $(BUILD_DIR)/src
	$(MKDIR) $(BUILD_DIR)/test/lua

clean:
	$(RM) $(BUILD_DIR)

install:
	$(CP) $(TARGET) $(INSTALL_PATH)/$(TARGET)

test: CFLAGS += -g
test: LLIBS += -lcgreen
test: $(TEST_TARGET)

$(TARGET): clean build $(TARGET_OBJECTS) $(BUILD_DIR)/src/main.o
	$(CC) -o $(TARGET) $(TARGET_OBJECTS) $(BUILD_DIR)/src/main.o $(LLIBS)

$(TEST_TARGET): clean build $(TARGET_OBJECTS) $(TEST_OBJECTS) $(TEST_CSTR_OBJECTS)
	$(CC) -o $(TEST_TARGET) $(TARGET_OBJECTS) $(TEST_OBJECTS) $(TEST_CSTR_OBJECTS) $(LLIBS)

$(BUILD_DIR)/src/%.o:
	$(CC) -o $@ $(CFLAGS) -c src/$(basename $(notdir $@)).c

$(BUILD_DIR)/test/lua/%.c:
	$(TOCSTR) \"test/cstr.h\" $(basename $(notdir $@)) /test/lua/$(basename $(notdir $@)).lua $(BUILD_DIR)/test/lua/$(basename $(notdir $@)).c

$(BUILD_DIR)/test/lua/%.o:
	$(CC) -o $@ $(CFLAGS) -c $(BUILD_DIR)/test/lua/$(basename $(notdir $@)).c

$(BUILD_DIR)/test/%.o:
	$(CC) -o $@ $(CFLAGS) -c test/$(basename $(notdir $@)).c
