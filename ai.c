#include "ai.h"

// Realiza un movimiento aleatorio para la IA
int random_move(int board[][BOARD_SIZE_VERTICAL], int computer_num)
{
    // Genera un número aleatorio para la columna
    int m = rand() % BOARD_SIZE_HORIZONTAL + 1;
    // Verifica si la columna está llena y genera otro número si es necesario
    while (is_column_full(board, m))
        m = rand() % BOARD_SIZE_HORIZONTAL + 1;
    // Actualiza el tablero con el movimiento de la IA
    update_board(board, m, computer_num);
    return m; // devuelve la columna elegida
}

int best_move(int board[][BOARD_SIZE_VERTICAL], int computer_num)
{
    // Determina el número del jugador oponente
    int player_num = (computer_num == 1) ? 2 : 1;
    // Crea una copia del tablero para usar en la evaluación MinMax
    int minmaxBoard[BOARD_SIZE_HORIZONTAL][BOARD_SIZE_VERTICAL] = {{0}};
    // Representa a la IA y al jugador con valores positivos y negativos respectivamente
    int computer = 1, player = -1;

    // Copia el tablero actual al tablero para MinMax, asignando valores positivos y negativos
    // a las piezas de la IA y del jugador, respectivamente
    for (int i = 0; i < BOARD_SIZE_HORIZONTAL; i++)
    {
        for (int j = 0; j < BOARD_SIZE_VERTICAL; j++)
        {
            if (board[i][j] == computer_num)
                minmaxBoard[i][j] = computer; // Asigna un valor positivo a las piezas de la IA
            if (board[i][j] == player_num)
                minmaxBoard[i][j] = player; // Asigna un valor negativo a las piezas del jugador
        }
    }

    // Inicializa variables para almacenar el mejor movimiento y su puntaje
    int m, score;
    // Ejecuta el algoritmo MinMax para determinar el mejor movimiento para la IA
    MinMax_Ai(1, computer, 4, minmaxBoard, &m, &score); // Usa 1 para buscar una victoria de la IA
    // Actualiza el tablero original con el mejor movimiento encontrado
    update_board(board, m + 1, computer_num);
    // devuelve el mejor movimiento más 1 (debido a la indexación desde 0)
    return m + 1;
}

void MinMax_Ai(int MinMax, int player, int depth, int minmaxBoard[][BOARD_SIZE_VERTICAL], int *m, int *score)
{
    // Inicializa el mejor puntaje y el mejor movimiento
    int best_score = MinMax ? -10000000 : 10000000;
    int best_move = -1, y;

    // Itera sobre todas las columnas posibles del tablero
    for (y = 0; y < BOARD_SIZE_HORIZONTAL; y++)
    {
        // Continúa si la columna está llena
        if (minmaxBoard[y][0] != 0)
            continue;

        // Calcula la fila disponible más baja en la columna
        int r = calcRow(minmaxBoard, y, player);
        // Si no hay filas disponibles, continúa
        if (r == BOARD_SIZE_VERTICAL)
            continue;

        // Calcula el puntaje actual del tablero
        int s = scoring(minmaxBoard);
        // Si el puntaje es el máximo o mínimo, actualiza y sale del bucle
        if (s == (MinMax ? 1000000 : -1000000))
        {
            best_score = s;
            best_move = y;
            minmaxBoard[y][r] = 0;
            break;
        }

        int recurMove, recurScore;
        // Realiza una llamada recursiva si la profundidad es mayor que 1
        if (depth > 1)
            MinMax_Ai(!MinMax, player == 1 ? -1 : 1, depth - 1, minmaxBoard, &recurMove, &recurScore);
        else
        {
            recurMove = -1;
            recurScore = s;
        }

        // Restablece el tablero a su estado original
        minmaxBoard[y][r] = 0;

        // Ajusta el puntaje recursivo basado en la profundidad y el jugador
        if (recurScore == 1000000 || recurScore == -1000000)
            recurScore -= depth * (int)player;

        // Actualiza el mejor puntaje y el mejor movimiento
        if (MinMax)
        {
            if (recurScore >= best_score)
            {
                best_score = recurScore;
                best_move = y;
            }
        }
        else
        {
            if (recurScore <= best_score)
            {
                best_score = recurScore;
                best_move = y;
            }
        }
    }

    // Asigna el mejor movimiento y puntaje a las variables de mejor movimiento y puntaje
    *m = best_move;
    *score = best_score;
}

int calcRow(int board[][BOARD_SIZE_VERTICAL], int col, int player)
{
    int y;
    // Itera de abajo hacia arriba en la columna especificada
    for (y = BOARD_SIZE_VERTICAL - 1; y >= 0; y--)
    {
        // Verifica si la celda actual está vacía (valor 0)
        if (board[col][y] == 0)
        {
            // Asigna el valor del jugador a la celda vacía encontrada
            board[col][y] = player;
            // devuelve el índice de la fila donde se realizó la inserción
            return y;
        }
    }
    // Si no hay celdas vacías en la columna, devuelve el tamaño del tablero en vertical
    // Esto indica que la columna está llena
    return BOARD_SIZE_VERTICAL;
}

int scoring(int scoring[][BOARD_SIZE_VERTICAL])
{
    int count[9] = {0};
    int x, y;

    // Calcular los puntajes de alineación horizontal
    // Recorre cada fila del tablero
    for (y = 0; y < BOARD_SIZE_VERTICAL; y++)
    {
        // Calcula el puntaje inicial para los primeros tres elementos de la fila
        int score = scoring[0][y] + scoring[1][y] + scoring[2][y];
        // Itera sobre los elementos restantes de la fila
        for (x = 3; x < BOARD_SIZE_HORIZONTAL; x++)
        {
            // Actualiza el puntaje y cuenta los puntajes
            score += scoring[x][y];
            count[score + 4]++;
            // Resta el elemento más antiguo del puntaje actual
            score -= scoring[x - 3][y];
        }
    }

    // Calcular los puntajes de alineación vertical
    // Recorre cada columna del tablero
    for (x = 0; x < BOARD_SIZE_HORIZONTAL; x++)
    {
        // Calcula el puntaje inicial para los primeros tres elementos de la columna
        int score = scoring[x][0] + scoring[x][1] + scoring[x][2];
        // Itera sobre los elementos restantes de la columna
        for (y = 3; y < BOARD_SIZE_VERTICAL; y++)
        {
            // Actualiza el puntaje y cuenta los puntajes
            score += scoring[x][y];
            count[score + 4]++;
            // Resta el elemento más antiguo del puntaje actual
            score -= scoring[x][y - 3];
        }
    }

    // Calcular los puntajes de alineación diagonal de abajo izquierda a arriba derecha
    // Recorre las diagonales posibles en esta dirección
    for (y = 0; y < BOARD_SIZE_VERTICAL - 3; y++)
    {
        for (x = 0; x < BOARD_SIZE_HORIZONTAL - 3; x++)
        {
            int score = 0, diX = 0;
            // Suma los valores en la diagonal
            for (diX = 0; diX < 4; diX++)
            {
                score += scoring[x + diX][y + diX];
            }
            count[score + 4]++;
        }
    }

    // Calcular los puntajes de alineación diagonal de arriba izquierda a abajo derecha
    // Recorre las diagonales posibles en esta dirección
    for (y = 3; y < BOARD_SIZE_VERTICAL; y++)
    {
        for (x = 0; x < BOARD_SIZE_HORIZONTAL - 3; x++)
        {
            int score = 0, diX = 0;
            // Suma los valores en la diagonal
            for (diX = 0; diX < 4; diX++)
            {
                score += scoring[x + diX][y - diX];
            }
            count[score + 4]++;
        }
    }

    // Evaluar el resultado final basado en los conteos
    // Si count[0] es diferente de cero, devuelve un valor muy negativo
    if (count[0] != 0)
        return -1000000;
    // Si count[8] es diferente de cero, devuelve un valor muy positivo
    else if (count[8] != 0)
        return 1000000;
    // En otro caso, calcula el puntaje basado en una fórmula específica
    else
        return -count[1] * 5 - count[2] * 2 - count[3] + count[7] * 5 + count[6] * 2 + count[5];
}