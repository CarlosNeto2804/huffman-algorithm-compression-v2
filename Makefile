CC = g++

CFLAGS = -O3
CFLAGS += -Wall -pedantic -std=c++11
CFLAGS += -Wno-unused-function
CFLAGS += -I $(INCLUDES_DIR)


INCLUDES_DIR = $(CURDIR)/include
SRC_DIR = $(CURDIR)/src
BIN_DIR = $(CURDIR)/bin
DATA_DIR = $(CURDIR)/data
EXEC = main.o

SRC = $(wildcard $(SRC_DIR)/*.cpp)

COMPRESS_COMMAND = c
DECOMPRESS_COMMAND = d
INPUT=input.txt
OUTPUT=output.hff

all: all-debug all-release

compress: all-release run-compress

decompress: all-release run-decompress

make-dirs:
	mkdir -p $(BIN_DIR)

all-release: make-dirs
	$(CC) $(CFLAGS) -D NDEBUG $(SRC) -o $(BIN_DIR)/$(EXEC)

all-debug: make-dirs
	$(CC) $(CFLAGS) $(SRC) -o $(BIN_DIR)/$(EXEC)

clean:
	@rm -f $(BIN_DIR)/$(EXEC)

run-compress:
	$(BIN_DIR)/$(EXEC) $(COMPRESS_COMMAND) $(DATA_DIR)/$(INPUT) $(DATA_DIR)/$(OUTPUT) 

run-decompress:
	$(BIN_DIR)/$(EXEC) $(DECOMPRESS_COMMAND) $(DATA_DIR)/$(OUTPUT) $(DATA_DIR)/$(INPUT) 