#include <stdio.h>

#define ERRO_IO -1
#define SUCESSO_IO 1
#define SEPARADOR_VOTOS '|'
#define SEPARADOR_TOTAL '?'
#define NOME_ARQUIVO_VOTOS "dados.tse"

FILE *arq;

int escreverEmArquivo(char valor[]) {
    arq = fopen(NOME_ARQUIVO_VOTOS, "a+b");

    if(arq == NULL){
        return ERRO_IO;
    }

    fprintf(arq, valor);
    fclose(arq);
    return SUCESSO_IO;
}

/*int lerArquivo() {
    arq = fopen(NOME_ARQUIVO_VOTOS, "r+b");

    if(arq == NULL){
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
    fclose(arq);

    return SUCESSO_IO;
}*/

int confirmarVoto(char voto[]) {
    char gravar[4];
    gravar[0] = voto[0];
    gravar[1] = voto[1];
    gravar[2] = SEPARADOR_VOTOS;
    gravar[3] = '\0';
    return escreverEmArquivo(gravar);
}

int verificaNumRegistros() {
    arq = fopen(NOME_ARQUIVO_VOTOS, "r+b");
    int i = 0;
    char ch;

    if(arq == NULL){
        return ERRO_IO;
    }

    while((ch=fgetc(arq))!= EOF) {
        if (ch == SEPARADOR_VOTOS) {
            i++;
        }
    }
    fclose(arq);

    return i;
}

int gravarTotalVotos(int valor) {
    char gravar[20];
    sprintf(gravar, "%d", valor);
    strcat(gravar, "?");
    return escreverEmArquivo(gravar);
}

int verificaTotalVotos() {
    arq = fopen(NOME_ARQUIVO_VOTOS, "r+b");

    if(arq == NULL){
        return ERRO_IO;
    }

    char ch, cNum[20];
    int i = 0;
    while((ch=fgetc(arq))!= EOF && (ch != '?')) {
        cNum[i] = ch;
        i++;
    }
    cNum[i] = '\0';
    fclose(arq);
    return strToInt(cNum);
}

int removerArquivo() {
    return remove(NOME_ARQUIVO_VOTOS);
}
