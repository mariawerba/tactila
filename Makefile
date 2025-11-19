# Simple Makefile for building the console Tactila tester
# Usage:
#   make        # build the binary
#   make run    # run the binary
#   make clean  # remove build artifacts

CXX := g++
CC := gcc

CXXFLAGS := -std=c++11 -I. -Wall -Wextra
CFLAGS := -Wall -Wextra -I.

# Try to get hidapi flags from pkg-config if available
HID_CFLAGS := $(shell pkg-config --cflags hidapi 2>/dev/null)
HID_LIBS := $(shell pkg-config --libs hidapi 2>/dev/null)

LDFLAGS :=
LDLIBS := -pthread -ludev $(HID_LIBS)

SOURCES := main.cpp halldial.cpp usbhidhandler.cpp
COBJS := hid.o
TARGET := tactila_test

.PHONY: all clean run

all: $(TARGET)

$(COBJS): hid.c
	$(CC) $(CFLAGS) $(HID_CFLAGS) -c hid.c -o hid.o

$(TARGET): $(SOURCES) $(COBJS)
	$(CXX) $(CXXFLAGS) $(HID_CFLAGS) $(SOURCES) $(COBJS) -o $(TARGET) $(LDFLAGS) $(LDLIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(COBJS)
