#~constants
SRC_DIR=./src
BIN_DIR=./bin
BUILD_DIR=./build
EXEC=game.exe
C=g++
SRCEXTENSION=.cpp
OBJEXTENSION=.cpp.o
CFLAGS=-std=c++17 
C2OFLAGS=-W
O2EXEFLAGS=-lglew32 -lglu32 -lglfw3 -lopengl32
RAW_SRC_FILES_PATH=$(wildcard $(SRC_DIR)/*$(SRCEXTENSION))
SOURCE_FILES=$(RAW_SRC_FILES_PATH:$(SRC_DIR)/%=%)
SRC=$(foreach file, $(SOURCE_FILES), $(SRC_DIR)/$(file))
OBJ=$(foreach file, $(SOURCE_FILES), $(BIN_DIR)/$(file:$(SRCEXTENSION)=$(OBJEXTENSION)))

#~run command arguments parsing into RUN_ARGS
ifneq (,$(filter $(firstword $(MAKECMDGOALS)), run fullauto))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif

#~MAKEFILE

all: $(BIN_DIR)_dir $(BIN_DIR)/$(EXEC)

$(BIN_DIR)/$(EXEC): $(OBJ)
	$(C) $(CFLAGS) -o $@ $^ $(O2EXEFLAGS)

$(BIN_DIR)/%$(OBJEXTENSION): $(SRC_DIR)/%$(SRCEXTENSION) $(SRC_DIR)/%.h
	$(C) $(CFLAGS) -c -o $@ $< $($@) $(C2OFLAGS)

$(BIN_DIR)/%$(OBJEXTENSION): $(SRC_DIR)/%$(SRCEXTENSION)
	$(C) $(CFLAGS) -c -o $@ $< $(C2OFLAGS)

#~UTILS

.PHONY: clean reset build fullauto rbin rbuild run

clean:
	rm -rf $(BIN_DIR)/*$(OBJEXTENSION)

reset:
	rm -rf $(BIN_DIR)
	rm -rf $(BUILD_DIR)

build: all $(BUILD_DIR)_dir
	cp $(BIN_DIR)/*.exe $(BUILD_DIR)
	cp $(BIN_DIR)/*.dll $(BUILD_DIR)
#^remove created files if wanted clean
ifeq (clean,$(firstword $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))))
	rbin
endif

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