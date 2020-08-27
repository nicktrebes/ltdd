CP = cp
LUA = lua5.3
MKDIR = mkdir -p
RM = rm -rf

CFLAGS = -std=c99 -Iinclude -Wall -Werror
LLIBS = -llua

INSTALL_PATH = /usr/bin

.PHONY: all bin clean install test

TARGET_SOURCES = $(filter-out src/main.c, $(wildcard src/*.c))
TARGET_OBJECTS = $(addprefix bin/, $(TARGET_SOURCES:.c=.o))
TARGET = bin/ltdd

TEST_SOURCES = $(wildcard test/*.c)
TEST_OBJECTS = $(addprefix bin/, $(TEST_SOURCES:.c=.o))
TEST_TARGET = bin/ltdd_test

all: TARGET_OBJECTS += bin/main.o
all: $(TARGET)

bin:
	$(MKDIR) bin/src
	$(MKDIR) bin/test

clean:
	$(RM) bin

install:
	$(CP) $(TARGET) $(INSTALL_PATH)/$(TARGET)

test: CFLAGS += -g
test: LLIBS += -lcgreen
test: $(TEST_TARGET)

$(TARGET): clean bin $(TARGET_OBJECTS)
	$(CC) -o $(TARGET) $(TARGET_OJBECTS) $(LLIBS)

$(TEST_TARGET): clean bin $(TARGET_OBJECTS) $(TEST_OBJECTS)
	$(CC) -o $(TEST_TARGET) $(TARGET_OBJECTS) $(TEST_OBJECTS) $(LLIBS)

bin/src/%.o:
	$(CC) -o $@ $(CFLAGS) -c src/$(basename $(notdir $@)).c

bin/test/%.o:
	$(CC) -o $@ $(CFLAGS) -c test/$(basename $(notdir $@)).c
