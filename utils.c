#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "utils.h"

void gotoxy(int x, int y) {
    COORD p = { x, y };
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), p );
}

void delay(int milliseconds) {
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}
