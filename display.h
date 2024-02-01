#ifndef DISPLAY_H
#define DISPLAY_H

#include "connect4.h"

void display_board(int board[][BOARD_SIZE_VERTICAL]);
void update_board(int board[][BOARD_SIZE_VERTICAL], int m, int player_num);

#endif // DISPLAY_H
