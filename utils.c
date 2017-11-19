#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string.h>

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

void put8s(char texto[]) {
    int i;
    for (i=0; i<strlen(texto); i++) {
        //printf("    %i ", texto[i]);
        switch (texto[i]) {
            case -25: printf("%c", 135); break;
            case -29: printf("%c", 198); break;
            case -31: printf("%c", 160); break;
            case -11: printf("%c", 228); break;
            case -6: printf("%c", 163); break;
            default: printf("%c", texto[i]);
        }
    }
}

int charToInt(char num) {
    return num > 47 && num < 58 ? num - 48 : 0;
}

int strToInt(char num[]) {
    int i, dez = 1, retorno = 0;
    for (i=strlen(num)-1; i>=0; i--) {
        if (num[i] > 47 && num[i] < 58) {
            retorno += charToInt(num[i]) * dez;
            dez *= 10;
        }
    }
    return retorno;
}

/*char* intToStr(int num) {
    int i,j;
    int pow = 10;
    int numCasas = 1;
    int resto = 0;
    while ((num/pow) > 0) {
        pow *= 10;
        numCasas++;
    }

    char* texto[numCasas];

    for (i=0; i<numCasas; i++) {
        int ordem = 1;
        for (j=numCasas-i-1; j>0; j--) {
            ordem *= 10;
        }
        int digito = num/ordem;
        num -= digito * ordem;
        texto[i] = digito + 48;
    }
    char* retorno = (char*) texto;
    return retorno;
}*/

int isCharNumber(char num) {
    char i;
    for (i='0'; i<='9'; i++) {
        if (num == i) {
            return 1;
        }
    }
    return 0;
}

int isNumber(char num[]) {
    int i;
    for (i=0; i<strlen(num); i++) {
        if (!isCharNumber(num[i])) {
            return 0;
        }
    }
    return 1;
}
