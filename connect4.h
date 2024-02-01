#ifndef CONNECT4_H
#define CONNECT4_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#define BOARD_SIZE_HORIZONTAL 7
#define BOARD_SIZE_VERTICAL 6
#define RED "\x1B[31m"
#define YELLOW "\x1B[33m"
#define RESET "\x1B[0m"

#include "display.h"
#include "game_logic.h"
#include "ai.h"

extern bool player_color;
extern void clearScreen();

#endif // CONNECT4_H