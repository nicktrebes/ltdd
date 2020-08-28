CP = cp
LUA = lua5.3
MKDIR = mkdir -p
RM = rm -rf

LUA_LIB = lua5.3
LUA_LIB_PATH = /usr/local/lua5.3/lib

CFLAGS = -std=c99 -Iinclude -Wall -Werror
LLIBS = -L$(LUA_LIB_PATH) -l$(LUA_LIB) -lm -ldl

INSTALL_PATH = /usr/bin

.PHONY: all build clean install src_lua test test_lua

BUILD_DIR = build
TOCSTR = $(LUA) tocstr.lua

TARGET_SOURCES = $(filter-out src/main.c, $(wildcard src/*.c))
TARGET_OBJECTS = $(addprefix $(BUILD_DIR)/, $(TARGET_SOURCES:.c=.o))
TARGET = $(BUILD_DIR)/ltdd

TARGET_CSTR_LUA = $(wildcard src/lua/*.lua)
TARGET_CSTR_SOURCES = $(addprefix $(BUILD_DIR)/, $(TARGET_CSTR_LUA:.lua=.c))
TARGET_CSTR_OBJECTS = $(TARGET_CSTR_SOURCES:.c=.o)

TEST_SOURCES = $(wildcard test/*.c)
TEST_OBJECTS = $(addprefix $(BUILD_DIR)/, $(TEST_SOURCES:.c=.o))
TEST_TARGET = $(BUILD_DIR)/ltdd_test

TEST_CSTR_LUA = $(wildcard test/lua/*.lua)
TEST_CSTR_SOURCES = $(addprefix $(BUILD_DIR)/, $(TEST_CSTR_LUA:.lua=.c))
TEST_CSTR_OBJECTS = $(TEST_CSTR_SOURCES:.c=.o)

all: $(TARGET)

build:
	$(MKDIR) $(BUILD_DIR)/src/lua
	$(MKDIR) $(BUILD_DIR)/test/lua

clean:
	$(RM) $(BUILD_DIR)

install:
	$(CP) $(TARGET) $(INSTALL_PATH)/$(TARGET)

src_lua: $(TARGET_CSTR_SOURCES)

test: CFLAGS += -g
test: LLIBS += -lcgreen
test: $(TEST_TARGET)

test_lua: $(TEST_CSTR_SOURCES)

TARGET_COMBINED = $(TARGET_OBJECTS) $(BUILD_DIR)/src/main.o $(TARGET_CSTR_OBJECTS)

$(TARGET): clean build src_lua $(TARGET_COMBINED)
	$(CC) -o $(TARGET) $(TARGET_COMBINED) $(LLIBS)

TEST_COMBINED = $(TARGET_OBJECTS) $(TEST_OBJECTS) $(TARGET_CSTR_OBJECTS) $(TEST_CSTR_OBJECTS)

$(TEST_TARGET): clean build src_lua test_lua $(TEST_COMBINED)
	$(CC) -o $(TEST_TARGET) $(TEST_COMBINED) $(LLIBS)

$(BUILD_DIR)/src/lua/%.c:
	$(TOCSTR) "<cstr.h>" $(basename $(notdir $@)) src/lua/$(basename $(notdir $@)).lua $(BUILD_DIR)/src/lua/$(basename $(notdir $@)).c

$(BUILD_DIR)/src/lua/%.o:
	$(CC) -o $@ $(CFLAGS) -c $(BUILD_DIR)/src/lua/$(basename $(notdir $@)).c

$(BUILD_DIR)/src/%.o:
	$(CC) -o $@ $(CFLAGS) -c src/$(basename $(notdir $@)).c

$(BUILD_DIR)/test/lua/%.c:
	$(TOCSTR) "<cstr_test.h>" $(basename $(notdir $@)) test/lua/$(basename $(notdir $@)).lua $(BUILD_DIR)/test/lua/$(basename $(notdir $@)).c

$(BUILD_DIR)/test/lua/%.o:
	$(CC) -o $@ $(CFLAGS) -c $(BUILD_DIR)/test/lua/$(basename $(notdir $@)).c

$(BUILD_DIR)/test/%.o:
	$(CC) -o $@ $(CFLAGS) -c test/$(basename $(notdir $@)).c
