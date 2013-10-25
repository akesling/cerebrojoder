OPTIONS=-Ofast -Wall -std=c++11 -pedantic
SOURCE_DIR=src
BIN_DIR=bin
CC=g++
SUFFIX=.cpp

% :: $(SOURCE_DIR)/%$(SUFFIX) $(BIN_DIR)
	$(CC) $(OPTIONS) $< -o $(BIN_DIR)/$@

$(BIN_DIR) :
	mkdir -p $(BIN_DIR)

clean :
	rm bin/*
	rmdir bin
