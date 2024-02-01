#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "connect4.h"

int print_welcome(void);
int player_move(int board[][BOARD_SIZE_VERTICAL], int player_num);
bool check_win_or_tie(int board[][BOARD_SIZE_VERTICAL], int last_move);
bool is_column_full(int board[][BOARD_SIZE_VERTICAL], int m);
int check_winner(int board[][BOARD_SIZE_VERTICAL], int last_move);
int check_horizontal_win_opportunities(int board[][BOARD_SIZE_VERTICAL], int player_num);
int check_vertical_win_opportunities(int board[][BOARD_SIZE_VERTICAL], int player_num);
int check_diagonal_win_opportunities(int board[][BOARD_SIZE_VERTICAL], int player_num);
bool check_for_multiple_win_opportunities(int board[][BOARD_SIZE_VERTICAL], int player_num);
#endif // GAME_LOGIC_H
