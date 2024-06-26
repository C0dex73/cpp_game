#~constants
SRC_DIR=./src
BIN_DIR=./bin
BUILD_DIR=./build
EXEC=app.exe
C=YOUR COMPILER HERE
SRCEXTENSION=YOUR LANGUAGE EXTENSION HERE (e.g. c, cpp)
CFLAGS=
C2OFLAGS=-W
O2EXEFLAGS=
RAW_SRC_FILES_PATH=$(wildcard $(SRC_DIR)/*.$(SRCEXTENSION))
SOURCE_FILES=$(RAW_SRC_FILES_PATH:$(SRC_DIR)/%=%)
SRC=$(foreach file, $(SOURCE_FILES), $(SRC_DIR)/$(file))
OBJ=$(foreach file, $(SOURCE_FILES), $(BIN_DIR)/$(file:.$(SRCEXTENSION)=.o))

#~run command arguments parsing into RUN_ARGS
ifneq (,$(filter $(firstword $(MAKECMDGOALS)), run fullauto))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif

#~MAKEFILE

all: $(BIN_DIR)_dir $(BIN_DIR)/$(EXEC)

$(BIN_DIR)/$(EXEC): $(OBJ)
	$(C) $(CFLAGS) -o $@ $^ $(O2EXEFLAGS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.$(SRCEXTENSION) $(SRC_DIR)/%.h
	$(C) $(CFLAGS) -c -o $@ $< $($@) $(C2OFLAGS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.$(SRCEXTENSION)
	$(C) $(CFLAGS) -c -o $@ $< $(C2OFLAGS)

#~UTILS

.PHONY: clean reset build fullauto rbin rbuild run

clean:
	rm -rf $(BIN_DIR)/*.o

reset:
	rm -rf $(BIN_DIR)
	rm -rf $(BUILD_DIR)

build: all $(BUILD_DIR)_dir
	cp $(BIN_DIR)/*.exe $(BUILD_DIR)

fullauto: build
	$(BUILD_DIR)/$(EXEC) $(RUN_ARGS)

rbin:
	rm -rf $(BIN_DIR)

rbuild:
	rm -rf $(BUILD_DIR)

run: $(BUILD_DIR)/$(EXEC) | build
	$(BUILD_DIR)/$(EXEC) $(RUN_ARGS)

#~DIRECTORIES

$(BUILD_DIR)_dir:
	mkdir $(BUILD_DIR) -p

$(BIN_DIR)_dir :
	mkdir $(BIN_DIR) -p

#~DEBUG
debug:
	@echo There is no debug script written in $(CURDIR)/makefile :: debug