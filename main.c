#include "connect4.h"

int main()
{
  int board[BOARD_SIZE_HORIZONTAL][BOARD_SIZE_VERTICAL] = {{0}};
  int player_num, computer_num;
  int last_move;

  player_num = print_welcome();
  if (player_num == 1)
    computer_num = 2;
  else
    computer_num = 1;

  if (player_num == 1)
  {
    display_board(board);
    last_move = player_move(board, player_num);
    display_board(board);
  }

  while (1)
  {
    last_move = random_move(board, computer_num);
    display_board(board);
    printf("La computadora jugó en la columna: %d\n", last_move);

    if (check_win_or_tie(board, last_move))
      return 0;

    last_move = player_move(board, player_num);
    display_board(board);

    if (check_win_or_tie(board, last_move))
      return 0;
  }
}
