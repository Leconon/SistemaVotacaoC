#include <stdio.h>

#define FIM_ARQUIVO -2
#define ERRO_IO -1
#define SUCESSO_IO 1
#define SEPARADOR_VOTOS '|'
#define SEPARADOR_TOTAL '?'
#define NOME_ARQUIVO_VOTOS "dados.tse"

FILE *arq;
int arquivoAberto = 0;

int escreverEmArquivo(char valor[]) {
    arq = fopen(NOME_ARQUIVO_VOTOS, "a+b");

    if(arq == NULL){
        return ERRO_IO;
    }

    fprintf(arq, valor);
    fclose(arq);
    return SUCESSO_IO;
}

int lerArquivo(int fecharEAbrir) {
    if (fecharEAbrir) {
        arq = fopen(NOME_ARQUIVO_VOTOS, "r+b");
    }

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
}

int retornaRegistrosLaco() {
    if (!arquivoAberto) {
        arq = fopen(NOME_ARQUIVO_VOTOS, "r+b");
        arquivoAberto = 1;
    }

    if (arq == NULL){
        arquivoAberto = 0;
        return ERRO_IO;
    }

    int digitos = 0;
    char ch, cNum[] = "00";
    while((ch=fgetc(arq))!= EOF) {
        if (ch == SEPARADOR_TOTAL || ch == SEPARADOR_VOTOS) {
            cNum[0] = '0';
            cNum[0] = '0';
            continue;
        }
        cNum[digitos++] = ch;
        if (digitos > 1) {
            return strToInt(cNum);
        }
    }

    fclose(arq);
    arquivoAberto = 0;
    return FIM_ARQUIVO;
}

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
