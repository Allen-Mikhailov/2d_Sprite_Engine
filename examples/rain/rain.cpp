#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include "../../src/Engine.cpp"
using namespace std;

struct drop {
    int x;
    int y;
};

int dropCount = 25;
drop* droplets;

int absMod(int value, int mode)
{
    return (mode+value)%mode;
}

void Draw(Screen screen, int tick)
{
    ScreenSize size = screen.size;
    drop* head = droplets;
    for (int i = 0; i < dropCount; i++)
    {
        // Movement
        head->x = absMod(head->x-1, size.columns-2);
        head->y = absMod(head->y+1, size.rows-1);

        //Drawing
        writePixel(screen, '/', absMod(head->x+1, size.columns-2), head->y);
        writePixel(screen, '/', head->x, absMod(head->y+1, size.rows-1));
        head++;
    }
}

int main()
{
    ScreenSize size = getScreenSize();

    droplets = (drop*) malloc(sizeof(drop) * dropCount);
    drop* head = droplets;
    for (int i = 0; i < dropCount; i++)
    {
        head->x = rand()%size.columns;
        head->y = rand()%size.rows;
        head++;
    }

    while(true)
    {
        handleTick();
        Sleep(150);
    }
}
