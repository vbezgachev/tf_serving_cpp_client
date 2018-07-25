CC      = g++
CFLAGS  =-c -Wall -std=gnu++11
LDFLAGS =
EXECUTABLE_NAME=serving_client

BIN         =./bin
SOURCE_DIR  =./src
OBJ         =./obj

SOURCE_FILES   =\
	serving_client.cc

EXECUTABLE_FILES = $(EXECUTABLE_NAME:%=$(BIN)/%)
OBJECT_FILES     = $(SOURCE_FILES:%.cc=$(OBJ)/%.o)

build: $(EXECUTABLE_FILES)

clean:
	rm -r -f $(BIN)

.PHONY: build clean

$(EXECUTABLE_FILES): $(OBJECT_FILES)
	@echo Linking $<
	@mkdir -p $(@D)
	@$(CC) $(LDFLAGS) -o $@ $^
	@echo "Build successful!"

$(OBJECT_FILES): $(OBJ)/%.o: $(SOURCE_DIR)/%.cc
	@echo Compiling $<
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ $<
