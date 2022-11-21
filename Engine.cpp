#include <iostream>
#include <windows.h>
#include <stdlib.h>
using namespace std;

struct ScreenSize
{
    int columns;
    int rows;
};

struct Screen
{
    ScreenSize size;
    char * buffer;
};

void Draw(Screen screen, int tick);
void Start(int argc, char *argv[]);

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

int ScreenStringSize(ScreenSize screenSize)
{
    return screenSize.columns * (screenSize.rows+1);
}

char * getScreenBase(ScreenSize screenSize)
{
    // Creating Blank Slate
    int stringSize = ScreenStringSize(screenSize);
    char * screenString = (char *) malloc(stringSize * sizeof(char));
    char * head = screenString;

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

void writeToBase(Screen screen, char * str, int column, int row)
{
    int strLength = strlen(str);
    if (strLength+column > screen.size.columns)
        strLength = screen.size.columns-column;

    
}

void writePixel(Screen screen, char pixel, int x, int y)
{
    char * sBuffer = screen.buffer;
    sBuffer += x + (screen.size.columns+1)*y;
    *sBuffer = pixel;
}

int main(int argc, char *argv[])
{
    Screen screen;
    char * screenBase;

    int tick = 0;

    while (true)
    {
        ScreenSize newScreenSize = getScreenSize();

        if (screen.size.columns != newScreenSize.columns || screen.size.rows != newScreenSize.rows)
        {
            // new Screen size
            screen.size = newScreenSize;
            screen.buffer = (char *) malloc(ScreenStringSize(screen.size));

            free(screenBase);
            screenBase = getScreenBase(newScreenSize);
        }

        strcpy(screen.buffer, screenBase);

        Draw(screen, tick);

        printf(screen.buffer);
        GoToXY(0, 0);

        printf("tick: %d\n", tick);
        GoToXY(0, 0);

        Sleep(1);
        tick++;
    }

    return 0;
}