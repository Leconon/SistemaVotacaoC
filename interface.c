#include <stdio.h>
#include <string.h>
//#include <time.h>

void limparEspaco(int xInicial, int yInicial, int xFinal, int yFinal) {
    int i, j;
    for (i=0; i<yFinal+1; i++) {
        gotoxy(xInicial, yInicial + i);
        for (j=0; j<xFinal+1; j++) {
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

    char bordaH = bordaDupla ? 205 : 196;
    char bordaV = bordaDupla ? 186 : 179;
    char interior = pintado ? 177 : ' ';

    gotoxy(xInicial, yInicial);

    printf("%c", bordaDupla ? 201 : 218);

    for (i=0; i<xFinal; i++) {
        printf("%c", bordaH);
    }

    printf("%c", bordaDupla ? 187 : 191);

    gotoxy(xInicial, yInicial + 1);

    for (i=0; i<yFinal; i++) {
        printf("%c", bordaV);
        for (j=0; j<xFinal; j++) {
            printf("%c", interior);
        }
        printf("%c", bordaV);
        gotoxy(xInicial, yInicial+i+2);
    }

    printf("%c", bordaDupla ? 200 : 192);

    for (i=0; i<xFinal; i++) {
        printf("%c", bordaH);
    }

    printf("%c", bordaDupla ? 188 : 217);
}

void desenhaBotao(int xInicial, int yInicial, int xFinal, int yFinal, int pintado, int bordaDupla, char texto[]) {
    desenhaRetangulo(xInicial, yInicial, xFinal, yFinal, pintado, bordaDupla);

    int posY = yInicial + yFinal/2;
    int posX = (xFinal - strlen(texto))/2 + xInicial + 1;

    gotoxy(posX, posY);
    put8s(texto);
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

void desenhaInterface(char titulo[]) {
    int i, c = 177;
    int tamTitulo = strlen(titulo);
    int posTitulo = (79-tamTitulo)/2;

    desenhaRetangulo(0, 0, 79, 24, 0, 1);
    gotoxy(0, 0);
    gotoxy(0, 4);
    printarChar(204, 1);
    printarChar(205, 78);
    printarChar(185, 1);
    gotoxy(1, 1);

    gotoxy(posTitulo, 2);
    put8s(titulo);
}
