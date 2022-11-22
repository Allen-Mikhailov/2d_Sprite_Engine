#include <iostream>
#include <windows.h>
#include <cmath>
#include <stdlib.h>
#include "../../src/Engine.cpp"
using namespace std;

char* IntialScreen;
ScreenSize initialSize;

double _time = 250;
int tickLength = 10;
double speed;

double borderRange = .5;

double xScale = 0.2;

void Draw(Screen screen, int tick)
{
    double cx = initialSize.columns/2.0;
    double cy = initialSize.rows/2.0;

    char * initialScreenHead = IntialScreen;
    char* screenHead = screen.buffer;

    double place = tick*speed;

    for (int y = 0; y < initialSize.rows; y++)
    {
        for (int x = 0; x < initialSize.columns; x++)
        {
            double distance = sqrt((x-cx)*(x-cx)*xScale + (y-cy)*(y-cy));
            if (abs(distance - place) < borderRange)
                *screenHead = '0';
            else if (distance < place)
                *screenHead = ' ';
            else
                *screenHead = *initialScreenHead;
            screenHead++;
            initialScreenHead++;
        }
        screenHead++;
        initialScreenHead++;
    }
}

int main()
{
    ScreenSize size = getScreenSize();
    initialSize = size;

    // Reading Initial input
    HANDLE     hStdOut      = GetStdHandle( STD_OUTPUT_HANDLE );
    PCHAR_INFO buffer       = new CHAR_INFO[ size.rows * (size.columns+1) ];
    COORD      buffer_size  = { (short)(size.columns+1), (short)size.rows };
    COORD      buffer_index = { 0, 0 }; 
    SMALL_RECT read_rect    = { 0, 0, (short)( (size.columns+1) - 1), (short)( size.rows - 1) };

    // GoToXY(0, 0);
    ReadConsoleOutput(  hStdOut, buffer, buffer_size, buffer_index, &read_rect );

    // Converting buffer to char*
    IntialScreen = (char*) malloc(sizeof(char) * size.rows * (size.columns+1));
    char * head = IntialScreen;
    for (int i = 0; i < size.rows * (size.columns+1); i++)
    {
        *head = buffer[i].Char.AsciiChar;
        head++;
    }

    double maxDistance = sqrt(size.columns*size.columns*xScale/4 + size.rows*size.rows/4)+borderRange+1;
    int ticks = ceil(_time/tickLength);
    speed = maxDistance/ticks;
    for (int i = 0; i < ticks; i++)
    {
        handleTick();
        Sleep(10);
    }

    // Making sure everything is clear
    GoToXY(0, 0);
    printf(getScreenBase(size));
    GoToXY(0, 0);
}