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

void Draw(Screen screen, int tick)
{

    drop* head = droplets;
    for (int i = 0; i < dropCount; i++)
    {
        head->x = (screen.size.columns-2+head->x-1)%(screen.size.columns-2);
        head->y = (screen.size.rows-1+head->y+1)%(screen.size.rows-1);
        writePixel(screen, '/', head->x+1, head->y);
        writePixel(screen, '/', head->x, head->y+1);
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
