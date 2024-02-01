#include "game_logic.h"

int print_welcome(void)
{
    char c;
    srand(time(0)); // Inicializa la semilla para la generación de números aleatorios

    printf("-- Bienvenido a Connect4 --\n");
    printf("\n-- De que color quieres ser? Rojo(R) | Amarillo(A): ");
    c = getchar();
    while (getchar() != '\n')
        ;

    if (c == 'R' || c == 'r')
    {
        player_color = true;
    }
    return 1;
}

// Permite al jugador realizar un movimiento
int player_move(int board[][BOARD_SIZE_VERTICAL], int player_num)
{
    int m;

    // Bucle que se repite hasta que el jugador hace un movimiento válido
    while (1)
    {
        printf("\nDigite el numero de columna para colocar su ficha: ");
        // Verifica si la entrada es válida
        if ((scanf("%d", &m) != 1) || (m < 1) || (m > BOARD_SIZE_HORIZONTAL))
        {
            printf("No es un movimiento valido. Indique un numero de columna!\n");
            while (getchar() != '\n')
                ;
            continue;
        }
        // Verifica si la columna está llena
        if (is_column_full(board, m))
        {
            printf("Esa columna esta llena. Intente nuevamente!\n");
            while (getchar() != '\n')
                ;
            continue;
        }
        // Actualiza el tablero con el movimiento del jugador
        update_board(board, m, player_num);
        while (getchar() != '\n')
            ;
        break; // Sale del bucle una vez realizado un movimiento válido
    }
    return m; // devuelve la columna elegida
}

bool check_win_or_tie(int board[][BOARD_SIZE_VERTICAL], int last_move)
{
    int check;
    // Llama a check_winner para determinar si hay un ganador
    check = check_winner(board, last_move);

    // Si check_winner devuelve un valor diferente de 0, hay un ganador
    if (check != 0)
    {
        // Imprime un mensaje indicando el jugador ganador
        printf("-------------------------------------------------------\n");
        printf("- El jugador de ficha '%c' ha ganado!!! Fin del juego -\n", (check == 1) ? 'X' : 'O');
        printf("-------------------------------------------------------\n");
        return true; // devuelve true indicando que hay un ganador
    }
    // Si check_winner devuelve 0, verifica si hay un empate
    else if (check == 0)
    {
        // Determinar si hay mas de una oportunidad de ganar
        if (check_for_multiple_win_opportunities(board, 1))
        {
            printf("----------------------------------------------------------------------\n");
            printf("Has logrado conseguir mas de una oportunidad de ganar!!! Fin del juego\n");
            printf("----------------------------------------------------------------------\n");
            return true;
        }
        if (check_for_multiple_win_opportunities(board, 2))
        {
            printf("------------------------------------------------------------------------------------\n");
            printf("La computadora ha logrado conseguir mas de una oportunidad de ganar... Fin del juego\n");
            printf("------------------------------------------------------------------------------------\n");
            return true;
        }
        // Recorre el tablero para verificar si hay espacios vacíos
        for (int i = 0; i < BOARD_SIZE_VERTICAL; i++)
        {
            for (int j = 0; j < BOARD_SIZE_HORIZONTAL; j++)
            {
                // Si hay un espacio vacío, el juego continúa
                if (board[j][i] == 0)
                    return false;
            }
        }
        // Si no hay espacios vacíos, es un empate
        printf("-----------------------------\n");
        printf("Ha ocurrido un empate!\n");
        printf("-----------------------------\n");
        return true; // devuelve true indicando que hay un empate
    }
    return false;
}

bool is_column_full(int board[][BOARD_SIZE_VERTICAL], int m)
{
    // Recorre la columna para verificar si hay espacios vacíos
    for (int i = 0; i < BOARD_SIZE_VERTICAL; i++)
    {
        if (board[m - 1][i] == 0)
            return false; // Si hay un espacio vacío, la columna no está llena
    }
    return true; // Si no hay espacios vacíos, la columna está llena
}

int check_winner(int board[][BOARD_SIZE_VERTICAL], int last_move)
{
    // Indica la fila del último movimiento
    int r;
    // Encuentra la fila del último movimiento hecho en la ubicación 'last_move'
    for (int i = 0; i < BOARD_SIZE_VERTICAL; i++)
    {
        if (board[last_move - 1][i] != 0)
        {
            r = i;
            break;
        }
    }

    // Verifica horizontalmente
    int temp, count;
    // Recorre el tablero horizontalmente para buscar una línea de 4 fichas iguales
    for (int i = 0; i < 4 + BOARD_SIZE_HORIZONTAL - 7; i++)
    {
        count = 1;
        temp = i;
        for (int j = 0; j < 3; j++)
        {
            // Cuenta las fichas iguales consecutivas en la misma fila
            if (board[temp][r] != 0 && board[temp][r] == board[temp + 1][r])
                count++;
            temp++;
        }
        // Si hay 4 en línea, devuelve el jugador ganador
        if (count == 4)
            return board[last_move - 1][r];
    }

    // Verifica verticalmente
    // Recorre el tablero verticalmente para buscar una línea de 4 fichas iguales
    for (int i = 0; i < 3 + BOARD_SIZE_VERTICAL - 6; i++)
    {
        count = 1;
        temp = i;
        for (int j = 0; j < 3; j++)
        {
            // Cuenta las fichas iguales consecutivas en la misma columna
            if (board[last_move - 1][temp] != 0 && board[last_move - 1][temp] == board[last_move - 1][temp + 1])
                count++;
            temp++;
        }
        // Si hay 4 en línea, devuelve el jugador ganador
        if (count == 4)
            return board[last_move - 1][r];
    }

    // Verifica diagonalmente
    int diX, diY;   // Direcciones para verificar diagonalmente
    int xLim, yLim; // Límites para evitar desbordamiento del tablero
    int stp;        // Punto de inicio para cada verificación diagonal
    // Verifica en ambas direcciones diagonales
    for (int dir = 0; dir < 2; dir++)
    {
        diX = 1;
        diY = (dir == 0) ? -1 : 1; // Cambia la dirección diagonal
        for (int x = 0; x < BOARD_SIZE_HORIZONTAL; x++)
        {
            for (int y = 0; y < BOARD_SIZE_VERTICAL; y++)
            {
                xLim = x + 3 * diX;
                yLim = y + 3 * diY;
                // Verifica que no se salga de los límites del tablero
                if (xLim < BOARD_SIZE_HORIZONTAL && yLim < BOARD_SIZE_VERTICAL && xLim >= 0 && yLim >= 0)
                {
                    stp = board[x][y];
                    // Cuenta las fichas iguales consecutivas en diagonal
                    if (stp != 0 && stp == board[x + diX][y + diY] && stp == board[x + 2 * diX][y + 2 * diY] && stp == board[xLim][yLim])
                        return stp;
                }
            }
        }
    }
    // Devuelve 0 si no hay ganador
    return 0;
}

// Función para verificar oportunidades de ganar horizontalmente para un jugador específico
int check_horizontal_win_opportunities(int board[][BOARD_SIZE_VERTICAL], int player_num)
{
    int count, opportunities = 0; // Inicializa el contador y el total de oportunidades

    // Recorre cada fila del tablero
    for (int y = 0; y < BOARD_SIZE_VERTICAL; y++)
    {
        // Recorre cada columna con un margen de 4 espacios hacia la derecha
        for (int x = 0; x <= BOARD_SIZE_HORIZONTAL - 4; x++)
        {
            count = 0;
            bool validOpportunity = true; // Flag para marcar si la oportunidad es válida

            // Recorre los 4 espacios hacia la derecha desde la posición actual
            for (int dx = 0; dx < 4; dx++)
            {
                if (board[x + dx][y] == player_num) // Si la celda contiene la ficha del jugador
                {
                    count++;
                }
                else if (board[x + dx][y] != 0)
                {
                    validOpportunity = false;
                    break;
                }
                // Verifica si hay espacio vacío sin una ficha debajo
                else if (y < BOARD_SIZE_VERTICAL - 1 && board[x + dx][y + 1] == 0)
                {
                    validOpportunity = false;
                    break;
                }
            }
            // Si se encontraron al menos 3 fichas y la oportunidad es válida
            if (count >= 3 && validOpportunity)
            {
                opportunities++; // Incrementa el total de oportunidades
            }
        }
    }
    return opportunities;
}

// Función para verificar oportunidades de ganar verticalmente para un jugador específico
int check_vertical_win_opportunities(int board[][BOARD_SIZE_VERTICAL], int player_num)
{
    int count, opportunities = 0;

    // Recorre cada columna del tablero
    for (int x = 0; x < BOARD_SIZE_HORIZONTAL; x++)
    {
        // Recorre cada fila con un margen de 4 espacios hacia abajo
        for (int y = 0; y <= BOARD_SIZE_VERTICAL - 4; y++)
        {
            count = 0;

            // Recorre los 4 espacios hacia abajo desde la posición actual
            for (int dy = 0; dy < 4; dy++)
            {
                if (board[x][y + dy] == player_num)
                    count++;
                else if (board[x][y + dy] != 0)
                    break;
            }
            // Si se encontraron al menos 3 fichas consecutivas
            if (count >= 3)
                opportunities++; // Incrementa el total de oportunidades
        }
    }
    return opportunities;
}

// Función para verificar oportunidades de ganar diagonalmente para un jugador específico
int check_diagonal_win_opportunities(int board[][BOARD_SIZE_VERTICAL], int player_num)
{
    int count, opportunities = 0;

    // Verifica diagonales hacia la derecha
    for (int x = 0; x <= BOARD_SIZE_HORIZONTAL - 4; x++)
    {
        for (int y = 0; y <= BOARD_SIZE_VERTICAL - 4; y++)
        {
            count = 0;
            bool validOpportunity = true;

            // Recorre la diagonal hacia la derecha
            for (int d = 0; d < 4; d++)
            {
                if (board[x + d][y + d] == player_num)
                {
                    count++;
                }
                else if (board[x + d][y + d] != 0)
                {
                    validOpportunity = false;
                    break;
                }
                else if (y + d < BOARD_SIZE_VERTICAL - 1 && board[x + d][y + d + 1] == 0)
                {
                    // Si el espacio diagonal está vacío y no hay ficha debajo, no es una oportunidad válida
                    validOpportunity = false;
                    break;
                }
            }
            if (count >= 3 && validOpportunity)
            {
                opportunities++;
            }
        }
    }

    // Verifica diagonales hacia la izquierda
    for (int x = 3; x < BOARD_SIZE_HORIZONTAL; x++)
    {
        for (int y = 0; y <= BOARD_SIZE_VERTICAL - 4; y++)
        {
            count = 0;
            bool validOpportunity = true;

            // Recorre la diagonal hacia la izquierda
            for (int d = 0; d < 4; d++)
            {
                if (board[x - d][y + d] == player_num)
                {
                    count++;
                }
                else if (board[x - d][y + d] != 0)
                {
                    validOpportunity = false;
                    break;
                }
                else if (y + d < BOARD_SIZE_VERTICAL - 1 && board[x - d][y + d + 1] == 0)
                {
                    // Si el espacio diagonal está vacío y no hay ficha debajo, no es una oportunidad válida
                    validOpportunity = false;
                    break;
                }
            }
            if (count >= 3 && validOpportunity)
            {
                opportunities++;
            }
        }
    }

    return opportunities; // Devuelve el número total de oportunidades diagonales encontradas
}

// Función principal para chequear si el jugador tiene múltiples oportunidades de ganar
bool check_for_multiple_win_opportunities(int board[][BOARD_SIZE_VERTICAL], int player_num)
{
    int total_opportunities = 0;

    total_opportunities += check_horizontal_win_opportunities(board, player_num);
    total_opportunities += check_vertical_win_opportunities(board, player_num);
    total_opportunities += check_diagonal_win_opportunities(board, player_num);

    return total_opportunities >= 2;
}
