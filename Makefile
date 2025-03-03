CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lSDL2 -lSDL2_ttf -lm

SRCS = src/main.c src/game_logic.c src/display.c src/save_load.c src/game_mode.c
OBJS = $(SRCS:.c=.o)
TARGET = 2048


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c functions.h
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	@echo "Suppression des fichiers objets et de l'executable"
	@rm -f $(OBJS) $(TARGET)

mrpropre: clean
	@echo "Suppression des sauvegardes"
	@rm -rf saves/*

re: clean all


.PHONY: clean mrpropre all