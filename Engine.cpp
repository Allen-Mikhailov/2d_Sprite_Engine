#include <iostream>
#include <windows.h>
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

int main(int argc, char *argv[]) 
{
    ScreenSize screenSize = getScreenSize();
    // SetConsoleCursorPosition

    printf("columns: %d\n", screenSize.columns);
    printf("rows: %d\n", screenSize.rows);
    return 0;
}