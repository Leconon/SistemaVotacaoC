#include <stdio.h>

#define ERRO_IO -1
#define SUCESSO_IO 0

FILE *arq;

int escreverEmArquivo(char numero[]) {
    printf("%i", numero);
    arq = fopen("dados.tse", "a+b");

    if(arq ==NULL){
        return ERRO_IO;
    }

    fprintf(arq, numero);
    fprintf(arq, "|");
    fclose(arq);
    return SUCESSO_IO;
}

int lerArquivo() {
    arq = fopen("dados.bat", "r+b");

    if(arq ==NULL){
        return ERRO_IO;
    }

    char ch;
    while((ch=fgetc(arq))!= EOF) {
        if (ch != '|') {
            putchar(ch);
        } else {
            printf("\n");
        }
    }
    return SUCESSO_IO;
}






