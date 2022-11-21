#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include "Engine.cpp"
using namespace std;

struct drop {
    int x;
    int y;
};

int dropCount = 1;
drop* droplets;

void Draw(Screen screen, int tick)
{

    drop* head = droplets;
    for (int i = 0; i < dropCount; i++)
    {
        head->x = (head->x-1)%screen.size.columns;
        head->y = (head->y+1)%screen.size.rows;
        writePixel(screen, '/', head->x, head->y);
        head++;
    }
}

void Start(ScreenSize size)
{
    droplets = (drop*) malloc(sizeof(drop) * dropCount);
    drop* head = droplets;
    for (int i = 0; i < dropCount; i++)
    {
        head->x = rand()%size.columns;
        head->y = rand()%size.rows;
        head++;
    }
}