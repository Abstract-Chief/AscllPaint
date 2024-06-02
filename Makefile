CC=g++
CCFLAGS=-g -Wall

SRC=src/asllpaint.cpp src/color.cpp

build: $(SRC)
	$(CC) $(CCFLAGS) $(SRC) -o build/AsciiPaint -lncurses

parserC: parser/c/reader.c
	gcc $(CCFLAGS) $< -o build/parser -lncurses -lm

parserCPP: parser/cpp/parser.cpp
	$(CC) $(CCFLAGS) $< -o build/parser -lncurses -lm


start: build
	build/AsciiPaint
