HOST_SYSTEM = $(shell uname | cut -f 1 -d_)
SYSTEM ?= $(HOST_SYSTEM)
CC      = g++
CFLAGS  = -c -Wall -std=c++11 -pthread -I/usr/local/include
ifeq ($(SYSTEM),Darwin)
LDFLAGS = -L/usr/local/lib -lpthread -lprotobuf -lgrpc++ -lgrpc\
          -lgrpc++_reflection\
          -ldl
else
LDFLAGS = -L/usr/local/lib -lprotobuf -pthread -lgrpc++ -lgrpc\
		  -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed\
		  -ldl
endif
EXECUTABLE_NAME=serving_client

BIN         =./bin
SOURCE_DIR  =./src
OBJ         =./obj

SOURCE_FILES   =$(wildcard src/*.cc) $(wildcard src/**/*.cc)

EXECUTABLE_FILES = $(EXECUTABLE_NAME:%=$(BIN)/%)
OBJECT_FILES     = $(SOURCE_FILES:%.cc=$(OBJ)/%.o)

build: $(EXECUTABLE_FILES)

clean:
	rm -r -f $(BIN)
	rm -r -f $(OBJ)

.PHONY: build clean

$(EXECUTABLE_FILES): $(OBJECT_FILES)
	@echo Linking $<
	@mkdir -p $(@D)
	@$(CC) $^ $(LDFLAGS) -o $@
	@echo "Build successful!"

$(OBJECT_FILES): $(OBJ)/%.o: %.cc
	@echo Compiling $<
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ $<
