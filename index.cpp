#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include "Engine.cpp"
using namespace std;

struct drop {
    int x;
    int y;
};

void Draw(Screen screen, int tick)
{

    writePixel(screen, '0', 10, 0);
}

int main(int argc, char *argv[])
{
    Start();
}