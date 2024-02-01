#ifndef AI_H
#define AI_H

#include "connect4.h"

int random_move(int board[][BOARD_SIZE_VERTICAL], int computer_num);
int best_move(int board[][BOARD_SIZE_VERTICAL], int computer_num);
void MinMax_Ai(int MinMax, int player, int depth, int minmaxBoard[][BOARD_SIZE_VERTICAL], int *m, int *score);
int calcRow(int board[][BOARD_SIZE_VERTICAL], int col, int player);
int scoring(int score[][BOARD_SIZE_VERTICAL]);

#endif // AI_H
