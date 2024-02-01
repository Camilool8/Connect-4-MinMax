#include "connect4.h"

bool player_color;

// Funciones que encontré en foros de internet para limpiar la consola en Windows (con su API)
// Y en sistemas Unix-like (con ANSI escape codes)
// https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c

#ifdef _WIN32
#include <windows.h>

void clearScreen()
{
    COORD topLeft = {0, 0};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    SetConsoleCursorPosition(console, topLeft);
}

#elif __APPLE__ || __linux__ || __unix__

void clearScreen()
{
    printf("\033[2J\033[H");
}

#endif