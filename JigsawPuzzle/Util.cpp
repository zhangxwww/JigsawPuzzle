#include "Util.h"

#include <Windows.h>

void clearScreen() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(handle, coord);
}
