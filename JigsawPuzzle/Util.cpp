#include "Util.h"

#include <Windows.h>

void setCurRow(const int row) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = 0;
    coord.Y = row;
    SetConsoleCursorPosition(handle, coord);
}
