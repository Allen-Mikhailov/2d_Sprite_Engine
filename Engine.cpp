#include <iostream>
#include <windows.h>
#include <stdlib.h>
using namespace std;

struct ScreenSize
{
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

char * getScreenBase(ScreenSize screenSize)
{
    // Creating Blank Slate
    int stringSize = screenSize.columns * (screenSize.rows+1);
    char * screenString = (char *) malloc(stringSize * sizeof(char));
    char * head = screenString;

    // Filling String
    for (int y = 0; y < screenSize.rows; y++)
    {
        for (int y = 0; y < screenSize.columns; y++)
        {
            *head = ' ';
            head++;
        }

        *head = '\n';
        head++;
    }
    head--;
    *head = '\0';
    return screenString;
}

string writeToBase(ScreenSize screenSize, string str, int column, int row)
{

}

int main(int argc, char *argv[])
{
    ScreenSize screenSize;
    char * ScreenBase;

    int tick = 0;

    while (true)
    {
        ScreenSize newScreenSize = getScreenSize();

        if (screenSize.columns != newScreenSize.columns || screenSize.rows != newScreenSize.rows)
        {
            // new Screen size
            screenSize = newScreenSize;
            ScreenBase = getScreenBase(screenSize);
        }

        printf(ScreenBase);
        GoToXY(0, 0);
        printf("tick: %d\n", tick);
        GoToXY(0, 0);

        Sleep(1);
        tick++;
    }

    return 0;
}