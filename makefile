# Files needed
FILES=Card.h Card.cpp Game.h Game.cpp Player.h Player.cpp main.cpp

# Executable file name
PROGRAM=a.out

# Compiler to use
CC=g++

# Flags
CFLAGS=-std=c++0x -Wall

$(PROGRAM): $(FILES)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(FILES)
	
# Cleanup: Run: make clean
clean:
	rm $(PROGRAM)