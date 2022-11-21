#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string>
using namespace std;

struct ScreenSize
{
    int columns;
    int rows;
};

struct Screen
{
    ScreenSize size;
    char *buffer;
};

void Draw(Screen screen, int tick);

ScreenSize getScreenSize()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    ScreenSize screenSize;
    screenSize.columns = columns;
    screenSize.rows = rows - 1;
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

int ScreenStringSize(ScreenSize screenSize)
{
    return screenSize.columns * (screenSize.rows + 1);
}

char *getScreenBase(ScreenSize screenSize)
{
    // Creating Blank Slate
    int stringSize = ScreenStringSize(screenSize);
    char *screenString = (char *)malloc(stringSize * sizeof(char));
    char *head = screenString;

    // Filling String
    for (int y = 0; y < screenSize.rows; y++)
    {
        for (int x = 0; x < screenSize.columns; x++)
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

void writeToBase(Screen screen, char *str, int column, int row)
{
    int strLength = strlen(str);
    if (strLength + column > screen.size.columns)
        strLength = screen.size.columns - column;

    char *head = screen.buffer;

    head += (screen.size.columns + 1) * row + column;
    for (int i = 0; i < strLength; i++)
    {
        *head = *str;
        head++;
        str++;
    }
}

void writePixel(Screen screen, char pixel, int x, int y)
{
    char *sBuffer = screen.buffer;
    sBuffer += x + (screen.size.columns + 1) * y;
    *sBuffer = pixel;
}

Screen screen;
char *screenBase;
int tick = 0;

ScreenSize newScreenSize = getScreenSize();

void handleTick()
{
    ScreenSize newScreenSize = getScreenSize();

    if (screen.size.columns != newScreenSize.columns || screen.size.rows != newScreenSize.rows)
    {
        // new Screen size
        screen.size = newScreenSize;
        screen.buffer = (char *)malloc(ScreenStringSize(screen.size));

        free(screenBase);
        screenBase = getScreenBase(newScreenSize);
    }

    strcpy(screen.buffer, screenBase);

    Draw(screen, tick);

    // Number
    string tickString = "Tick: " + to_string(tick);
    char *tickS = (char *)malloc(sizeof(char) * strlen(tickString.c_str()));
    strcpy(tickS, tickString.c_str());
    writeToBase(screen, tickS, 0, 0);
    cout << screen.buffer;

    GoToXY(0, 0);

    tick++;
}