#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "interface.c"

int main() {
    //desenhaTelaCarregamento();
    desenhaMenuPrincipal();

}

void desenhaTelaCarregamento() {
    imprimirLogoTsec(19, 4);
    desenhaRetangulo(25, 14, 30, 2, 0, 0);
    int i;
    for (i=0; i<29; i++) {
        delay(50);
        gotoxy(26 + i, 15);
        printarChar(219, 1);
    }
    limpaTela();
    getch();
}

void desenhaMenuPrincipal() {
    limpaTela();
    desenhaCabecalho(" Sistema de Votação TSEc ");
    desenhaRetangulo(3, 14, 30, 2, 0, 0);
    getch();
}

void desenhaCabecalho(char titulo[]) {
    int i;
    for (i=0; i<5; i++) {
        gotoxy(1,1 + i);
        printarChar(177, 78);
    }
    int tamTitulo = strlen(titulo);
    int posTitulo = (79-tamTitulo)/2;
    gotoxy(posTitulo, 3);
    for (i=0; i<tamTitulo; i++) {
        printf("%c", titulo[i]);
    }
}
