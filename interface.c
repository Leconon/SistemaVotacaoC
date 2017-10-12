#include <stdio.h>
#include <string.h>
#include "utils.c"

void limparEspaco(int xInicial, int yInicial, int xFinal, int yFinal) {
    int i, j;

    xInicial--;
    yInicial--;

    gotoxy(xInicial, yInicial);

    for (i=0; i<yFinal; i++) {
        gotoxy(xInicial, yInicial + i);
        for (j=0; j<xFinal; j++) {
            printf(" ");
        }
        if ((xFinal + xInicial < 80) && (i<yFinal-1)) {
            puts("");
        }
    }
}

void limpaTela() {
    system("cls");
}

void desenhaRetangulo(int xInicial, int yInicial, int xFinal, int yFinal, int pintado, int bordaDupla) {
    int i, j;

    xFinal--;
    yFinal--;

    gotoxy(xInicial, yInicial);

    printf("%c", bordaDupla ? 201 : 218);

    for (i=0; i<xFinal; i++) {
        printf("%c", bordaDupla ? 205 : 196);
    }

    printf("%c", bordaDupla ? 187 : 191);

    gotoxy(xInicial, yInicial + 1);

    for (i=0; i<yFinal; i++) {
        printf("%c", bordaDupla ? 186 : 179);
        for (j=0; j<xFinal; j++) {
            if (pintado) {
                printf("%c", 219);
            } else {
                printf(" ");
            }
        }
        printf("%c", bordaDupla ? 186 : 179);
        gotoxy(xInicial, yInicial+i+2);
    }

    printf("%c", bordaDupla ? 200 : 192);

    for (i=0; i<xFinal; i++) {
        printf("%c", bordaDupla ? 205 : 196);
    }

    printf("%c", bordaDupla ? 188 : 217);
}

void desenhaBotao(int xInicial, int yInicial, int xFinal, int yFinal, int pintado, int bordaDupla, char texto[]) {
    desenhaRetangulo(xInicial, yInicial, xFinal, yFinal, pintado, bordaDupla);

    int posY = yInicial + yFinal/2;
    int posX = (xFinal - strlen(texto))/2 + xInicial + 1;

    gotoxy(posX, posY);
    puts(texto);
}

void printarChar(char c, int qtd) {
    int i;
    for (i=0; i<qtd; i++) {
        printf("%c", c);
    }
}

void imprimirLogoTsec(int x, int y) {
    desenhaRetangulo(2, 1, 75, 22, 0, 0);
    gotoxy(x,++y);
    printarChar(219, 9);
    printarChar(' ', 2);
    printarChar(219, 9);
    printarChar(' ', 2);
    printarChar(219, 9);
    gotoxy(x,++y);

    printarChar(' ', 3);
    printarChar(219, 3);
    printarChar(' ', 5);
    printarChar(219, 3);
    printarChar(' ', 8);
    printarChar(219, 3);
    gotoxy(x,++y);

    printarChar(' ', 3);
    printarChar(219, 3);
    printarChar(' ', 5);
    printarChar(219, 3);
    printarChar(' ', 8);
    printarChar(219, 3);
    gotoxy(x,++y);

    printarChar(' ', 3);
    printarChar(219, 3);
    printarChar(' ', 5);
    printarChar(219, 9);
    printarChar(' ', 2);
    printarChar(219, 9);
    printarChar(' ', 2);
    printarChar(219, 8);
    gotoxy(x,++y);

    printarChar(' ', 3);
    printarChar(219, 3);
    printarChar(' ', 11);
    printarChar(219, 3);
    printarChar(' ', 2);
    printarChar(219, 3);
    printarChar(' ', 8);
    printarChar(219, 3);
    gotoxy(x,++y);

    printarChar(' ', 3);
    printarChar(219, 3);
    printarChar(' ', 11);
    printarChar(219, 3);
    printarChar(' ', 2);
    printarChar(219, 3);
    printarChar(' ', 8);
    printarChar(219, 3);
    gotoxy(x,++y);

    printarChar(' ', 3);
    printarChar(219, 3);
    printarChar(' ', 5);
    printarChar(219, 9);
    printarChar(' ', 2);
    printarChar(219, 9);
    printarChar(' ', 2);
    printarChar(219, 8);
}
