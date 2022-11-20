#include <iostream>
#include <windows.h>
#include <stdlib.h> 
using namespace std;

struct ScreenSize {
    int columns;
    int rows;
};

ScreenSize getScreenSize()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    ScreenSize screenSize;
    screenSize.columns = columns;
    screenSize.rows = rows;
    return screenSize;
}

void GoToXY(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, coord);
}

int main(int argc, char *argv[]) 
{
    ScreenSize screenSize = getScreenSize();

    int tick = 0;

    while (true)
    {
        ScreenSize screenSize = getScreenSize();
        GoToXY(0, 0);

        // Creating Blank Slate
        string line = "";

        printf("tick: %d\n", tick);

        Sleep(1);
        tick++;
    }

    return 0;
}