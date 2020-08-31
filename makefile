CP = cp
LUA = lua5.3
MKDIR = mkdir -p
RM = rm -rf

LUA_LIB = lua5.3
LUA_LIB_PATH = /usr/local/lua5.3/lib

CFLAGS = -std=c99 -Iinclude -I/usr/local/lua5.3/include -Wall -Werror
LLIBS = -L$(LUA_LIB_PATH) -l$(LUA_LIB) -lm -ldl

INSTALL_PATH = /usr/bin

.PHONY: all build clean install test

BUILD_DIR = build

TARGET_SOURCES = $(filter-out src/main.c, $(wildcard src/*.c))
TARGET_OBJECTS = $(addprefix $(BUILD_DIR)/, $(TARGET_SOURCES:.c=.o))
TARGET = $(BUILD_DIR)/ltdd

TEST_SOURCES = $(wildcard test/*.c)
TEST_OBJECTS = $(addprefix $(BUILD_DIR)/, $(TEST_SOURCES:.c=.o))
TEST_TARGET = $(BUILD_DIR)/ltdd_test

all: $(TARGET)

build:
	$(MKDIR) $(BUILD_DIR)/src/lua
	$(MKDIR) $(BUILD_DIR)/test/lua

clean:
	$(RM) $(BUILD_DIR)

install:
	$(CP) $(TARGET) $(INSTALL_PATH)/$(TARGET)

test: CFLAGS += -g
test: $(TEST_TARGET)

TARGET_COMBINED = $(TARGET_OBJECTS) $(BUILD_DIR)/src/main.o

$(TARGET): clean build $(TARGET_COMBINED)
	$(CC) -o $(TARGET) $(TARGET_COMBINED) $(LLIBS)

TEST_COMBINED = $(TARGET_OBJECTS) $(TEST_OBJECTS)

$(TEST_TARGET): clean build $(TEST_COMBINED)
	$(CC) -o $(TEST_TARGET) $(TEST_COMBINED) $(LLIBS) -lcgreen

$(BUILD_DIR)/src/%.o:
	$(CC) -o $@ $(CFLAGS) -c src/$(basename $(notdir $@)).c

$(BUILD_DIR)/test/%.o:
	$(CC) -o $@ $(CFLAGS) -c test/$(basename $(notdir $@)).c
