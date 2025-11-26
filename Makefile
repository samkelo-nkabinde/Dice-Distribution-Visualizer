CC = gcc
CFLAGS = -O1 -Wall -std=c99 -Wno-missing-braces -I include/
LDFLAGS = -L lib/
LDLIBS = -lm
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

SRC = src/dice_roll.c
OUT = dice_roll.exe

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(LDFLAGS) $(LIBS) $(LDLIBS)

clean:
	del /Q $(OUT)

