#include "display.h"

//  Mostrar el tablero de juego en la consola
void display_board(int board[][BOARD_SIZE_VERTICAL])
{
    printf("\n");

    // Itera sobre cada fila del tablero
    for (int i = 0; i < BOARD_SIZE_VERTICAL; i++)
    {
        // Imprime la línea superior de cada celda del tablero
        for (int j = 0; j < BOARD_SIZE_HORIZONTAL; j++)
        {
            printf("+---");
        }
        printf("+\n");

        // Imprime el contenido de cada celda del tablero
        for (int k = 0; k < BOARD_SIZE_HORIZONTAL; k++)
        {
            printf("| ");
            // Determina si la celda contiene la ficha del jugador 1, jugador 2, o está vacía
            if (board[k][i] == 1)
            {
                if (player_color)
                    printf(RED "X " RESET);
                else
                    printf(YELLOW "X " RESET);
            }
            else if (board[k][i] == 2)
            {
                if (player_color)
                    printf(YELLOW "O " RESET);
                else
                    printf(RED "O " RESET);
            }
            else
                printf("  ");
        }
        printf("|\n");
    }

    // Imprime la línea inferior de la última fila del tablero
    for (int i = 0; i < BOARD_SIZE_HORIZONTAL; i++)
    {
        printf("+---");
    }
    printf("+\n");

    // Imprime los números de las columnas debajo del tablero para referencia del jugador
    for (int i = 0; i < BOARD_SIZE_HORIZONTAL; i++)
    {
        printf("  %d ", i + 1);
    }
    printf(" \n\n");
}

// Actualiza el tablero con el movimiento del jugador
void update_board(int board[][BOARD_SIZE_VERTICAL], int m, int player_num)
{
    int animation_speed = (rand() % (1000 - 500 + 1)) + 500;

    // Encuentra la fila más baja disponible en la columna seleccionada
    int target_row;
    for (target_row = BOARD_SIZE_VERTICAL - 1; target_row >= 0; target_row--)
    {
        if (board[m - 1][target_row] == 0)
            break;
    }

    // Anima la ficha cayendo
    for (int current_row = 0; current_row <= target_row; current_row++)
    {
        board[m - 1][current_row] = player_num;
        clearScreen();                  // Limpia la consola para simular la animación
        display_board(board);           // Muestra el tablero con la ficha en la posición actual
        clearScreen();                  // Limpia la consola para simular la animación
        usleep(animation_speed * 1000); // Pausa la ejecución para simular la caída de la ficha

        if (current_row < target_row)
            board[m - 1][current_row] = 0; // Elimina la ficha de la posición actual si no es la final
    }
}