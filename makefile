#~CONSTANTS
SRC_DIR=./src
BIN_DIR=./bin
BUILD_DIR=./build
EXEC=cdxg.exe
TEST_EXEC=test.exe
TEST_SUBEXT=.test
C=g++
SRCEXTENSION=.cpp
OBJEXTENSION=.cpp.o
INCLUDE=include
CFLAGS=-std=c++17 -I./include
C2OFLAGS=-W
ADDITIONALOBJFILES=lib/glad.o
O2EXEFLAGS=-lglew32 -lglu32 -lglfw3 -lopengl32 

#~PROCESSED VAR
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

$(BIN_DIR)/$(EXEC): $(OBJ)
	$(C) $(CFLAGS) -o $@ $^ $(ADDITIONALOBJFILES) $(O2EXEFLAGS)

$(BIN_DIR)/%$(OBJEXTENSION): $(SRC_DIR)/%$(SRCEXTENSION) $(SRC_DIR)/$(INCLUDE)/%.h
	$(C) $(CFLAGS) -c -o $@ $< $($@) $(C2OFLAGS)

$(BIN_DIR)/%$(OBJEXTENSION): $(SRC_DIR)/%$(SRCEXTENSION)
	$(C) $(CFLAGS) -c -o $@ $< $(C2OFLAGS)

$(BIN_DIR)/$(TEST_EXEC): $(TEST_OBJ)
	$(C) $(CFLAGS) -o $@ $^ $(ADDITIONALOBJFILES) $(O2EXEFLAGS)

$(BIN_DIR)/%$(TEST_SUBEXT)$(OBJEXTENSION) : $(SRC_DIR)/%$(TEST_SUBEXT)$(SRCEXTENSION) $(SRC_DIR)/$(INCLUDE)/%$(TEST_SUBEXT).h
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
	cp $(BIN_DIR)/*.exe $(BUILD_DIR)
	set -- *.dll \
    ; if [ -e "$$1" ]; then \
        cp $(BIN_DIR)/*.dll $(BUILD_DIR); \
    fi
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

test: $(BIN_DIR)_dir $(BIN_DIR)/$(TEST_EXEC)
	$(BIN_DIR)/$(TEST_EXEC) $(RUN_ARGS)

#~DIRECTORIES

$(BUILD_DIR)_dir:
	mkdir $(BUILD_DIR) -p

$(BIN_DIR)_dir :
	mkdir $(BIN_DIR) -p

#~EXPLICIT DEPENDENCIES

$(SRC_DIR)/displayable.cpp.o : $(SRC_DIR)/$(INCLUDE)/shaders.h

#~DEBUG
debug:
	@echo There is no debug script written in $(CURDIR)/makefile :: debug