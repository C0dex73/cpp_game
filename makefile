#~CONSTANTS
SRC_DIR=./src
BIN_DIR=./bin
BUILD_DIR=./build
EXEC=cdxg
TEST_EXEC=test
TEST_SUBEXT=.test
C=g++
SRCEXTENSION=.cc
OBJEXTENSION=.cc.o
INCLUDE=./include
HEADEREXTENSION=.hh
SHADER_DIR=./assets
SHADER_EXTENSION=.glsl
BUILD_CFLAGS=
DEBUG_CFLAGS=
BUILD_FLAGS=-s
DEBUG_FLAGS=
CFLAGS=-Wall -std=c++20 -I./include -g
C2OFLAGS=-W
ADDITIONALOBJFILES=lib/glad.o bin/rawShaders.o
O2EXEFLAGS=-lglfw -lGL

#~PROCESSED VAR
SHADER_FILES=$(wildcard $(SHADER_DIR)/*$(SHADER_EXTENSION))
RAW_SRC_FILES_PATH=$(wildcard $(SRC_DIR)/*$(SRCEXTENSION))
SOURCE_FILES=$(foreach file, $(RAW_SRC_FILES_PATH:$(SRC_DIR)/%=%), $(if $(findstring $(TEST_SUBEXT),$(file)),,$(file)))
SRC=$(foreach file, $(SOURCE_FILES), $(SRC_DIR)/$(file))
OBJ=$(foreach file, $(SOURCE_FILES), $(BIN_DIR)/$(file:$(SRCEXTENSION)=$(OBJEXTENSION)))
TEST_FILES=$(foreach file, $(RAW_SRC_FILES_PATH:$(SRC_DIR)/%=%), $(if $(findstring $(TEST_SUBEXT),$(file)),$(file)))
TEST_SRC=$(foreach file, $(TEST_FILES), $(SRC_DIR)/$(file))
TEST_OBJ=$(foreach file, $(TEST_FILES), $(BIN_DIR)/$(file:$(SRCEXTENSION)=$(OBJEXTENSION)))

#^ run command arguments parsing into RUN_ARGS
ifneq (,$(filter $(firstword $(MAKECMDGOALS)), run fullauto))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif

#~MAKEFILE

all: $(BIN_DIR)_dir $(BIN_DIR)/$(EXEC) $(BIN_DIR)/$(TEST_EXEC)

$(BIN_DIR)/$(EXEC): $(OBJ) $(ADDITIONALOBJFILES)
	$(C) $(DEBUG_CFLAGS) $(CFLAGS) -o $@ $^ $(O2EXEFLAGS) $(DEBUG_FLAGS)

$(BIN_DIR)/%$(OBJEXTENSION): $(SRC_DIR)/%$(SRCEXTENSION) $(INCLUDE)/%$(HEADEREXTENSION)
	$(C) $(CFLAGS) $(DEBUG_CFLAGS) -c -o $@ $< $($@) $(C2OFLAGS)

$(BIN_DIR)/%$(OBJEXTENSION): $(SRC_DIR)/%$(SRCEXTENSION)
	$(C) $(CFLAGS) $(DEBUG_CFLAGS) -c -o $@ $< $(C2OFLAGS)

$(BIN_DIR)/$(TEST_EXEC): $(TEST_OBJ) $(ADDITIONALOBJFILES)
	$(C) $(CFLAGS) -o $@ $^ $(O2EXEFLAGS)

$(BIN_DIR)/%$(TEST_SUBEXT)$(OBJEXTENSION): $(SRC_DIR)/%$(TEST_SUBEXT)$(SRCEXTENSION) $(SRC_DIR)/$(INCLUDE)/%$(HEADEREXTENSION)
	$(C) $(CFLAGS) -c -o $@ $< $($@) $(C2OFLAGS)

$(BIN_DIR)/%$(TEST_SUBEXT)$(OBJEXTENSION): $(SRC_DIR)/%$(TEST_SUBEXT)$(SRCEXTENSION)
	$(C) $(CFLAGS) -c -o $@ $< $(C2OFLAGS)

#~UTILS

.PHONY: clean reset build fullauto rbin rbuild run

clean:
	rm -rf $(BIN_DIR)/*$(OBJEXTENSION)

reset:
	rm -rf $(BIN_DIR)
	rm -rf $(BUILD_DIR)

build: $(BIN_DIR)_dir $(BUILD_DIR)_dir $(BIN_DIR)/$(EXEC)
	$(C) $(BUILD_CFLAGS) $(CFLAGS) -o $(BUILD_DIR)/$(EXEC) $(OBJ) $(ADDITIONALOBJFILES) $(O2EXEFLAGS) $(BUILD_FLAGS)
	set -- *.dll \
    ; if [ -e "$$1" ]; then \
        cp $(BIN_DIR)/*.dll $(BUILD_DIR); \
    fi
#^remove created files if wanted clean
ifeq (clean,$(firstword $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))))
	rbin
endif

fullauto: build
	$(BIN_DIR)/$(EXEC) $(RUN_ARGS)

rbin:
	rm -rf $(BIN_DIR)

rbuild:
	rm -rf $(BUILD_DIR)

run: $(BUILD_DIR)/$(EXEC) | build
	$(BUILD_DIR)/$(EXEC) $(RUN_ARGS)

test: $(BIN_DIR)_dir $(BIN_DIR)/$(TEST_EXEC)
	$(BIN_DIR)/$(TEST_EXEC) $(RUN_ARGS)

shaders: bin/rawShaders.o

glad: lib/glad.o

#~DIRECTORIES

$(BUILD_DIR)_dir:
	mkdir $(BUILD_DIR) -p

$(BIN_DIR)_dir :
	mkdir $(BIN_DIR) -p

#~EXPLICIT DEPENDENCIES

bin/rawShaders.o: $(BIN_DIR)_dir $(SHADER_FILES)
	ld -r -b binary -o bin/rawShaders.o $(SHADER_FILES)

#TODO : find a way to automate this for all libs
#^ NB : this is done to prevent .o file errors due to specific system dependencies.
lib/glad.o: lib/glad.c
	g++ -c -o lib/glad.o lib/glad.c

src/displayable.cc : include/displayable.hh

#~DEBUG
debug:
	@echo There is no debug script written in $(CURDIR)/makefile :: debug