#include <stdio.h>

static int qtdEleitores = 0;
static int votosRealizados = 0;

struct Candidato {
    int num;
    char nome[50];
    int valido;
};

void iniciarVotacao() {
    if (!(qtdEleitores > 0 && qtdEleitores > votosRealizados)) {
        qtdEleitores = -1;
        votosRealizados = -1;
        removerArquivo();
        pedirNumeroEleitores();
    }
    if (qtdEleitores > 0) {
        votacao();
    }
}

void inicializarCandidatos() {

}

void pedirNumeroEleitores() {
    limpaTela();
    int qtd = 0;
    desenhaInterface("Iniciar nova votação");
    while(!qtd) {
        limparEspaco(1,5,77,18);
        gotoxy(4,7);
        printf("Quantidade de eleitores: ");
        scanf("%i", &qtd);
        fflush(stdin);
    }
    qtdEleitores = qtd;
    gravarTotalVotos(qtdEleitores);
    limpaTela();
}

struct Candidato verificarCandidato(int num) {
    struct Candidato c;
    strcpy(c.nome, "Voto Nulo");
    c.num = num;
    c.valido = 1;
    switch (num) {
        case 17: strcpy(c.nome, "Maeli Gente"); return c;
        case 22: strcpy(c.nome, "Loula do Brasil"); return c;
        case 31: strcpy(c.nome, "Lissandra Progresso"); return c;
        case 38: strcpy(c.nome, "Maia da Ana"); return c;
    }
    c.valido = 0;
    return c;
}


void votacao() {
    char num[] = "xx";
    struct Candidato c;
    while (votosRealizados < qtdEleitores) {
        limpaTela();
        char pressionado;
        desenharTecladoUrna(0);
        desenharBotoesAcao();
        desenharTelaVotacao();
        desenharDetalhesVoto(num, c);
        while(1) {
            pressionado = getch();
            int valido = isCharNumber(pressionado);

            if (valido) {
                if (num[0] == 'x') {
                    num[0] = pressionado;
                } else if (num[1] == 'x') {
                    num[1] = pressionado;
                    c = verificarCandidato(strToInt(num));
                }
                desenharTecladoUrna(pressionado);
            } else {
                if (pressionado == 8) {
                    num[0] = 'x';
                    num[1] = 'x';
                } else if (pressionado == 32) {
                    num[0] = '0';
                    num[1] = '0';
                } else if (pressionado == 13 && num[0] != 'x' && num[1] != 'x') {
                    confirmarVoto(num);
                    desenhaTelaFim();
                    num[0] = 'x';
                    num[1] = 'x';
                    break;
                }
                desenharBotoesAcao();
            }

            delay(100);
            desenharTecladoUrna(0);
            desenharBotoesAcao(0);
            desenharDetalhesVoto(num, c);
        }
    }
}

void desenharTecladoUrna(char pressionado) {
    int i, j, num = 0;
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++) {
            num++;
            desenharBotaoNumerico(49 + (j*10),1 + (i*5),num,pressionado);
        }
    }
}

void desenharBotaoNumerico(int x, int y, int numero, char pressionado) {
    numero = numero + 48;
    char texto[2];
    texto[0] = numero;
    texto[1] = '\0';
    desenhaBotao(x,y,8,4,(numero == pressionado),0,texto);
}

void desenharBotoesAcao(char pressionado) {
    desenhaBotao(49, 16, 13, 2, pressionado == 32, 0, "Branco");
    desenhaBotao(64, 16, 13, 2, pressionado == 8, 0, "Corrige");
    desenhaBotao(49, 19, 28, 4, pressionado == 13, 0, "Confirma");
}

void desenharTelaVotacao() {
    desenhaRetangulo(2,1,45,22,0,0);
    gotoxy(5, 3);
    printf("SEU VOTO PARA PREFEITO");
    gotoxy(5, 8);
    put8s("Número: ", 0);
    desenhaRetangulo(12, 6, 4, 3, 0, 0);
    desenhaRetangulo(17, 6, 4, 3, 0, 0);
    gotoxy(5, 12);
    printf("Nome: ");
    gotoxy(2, 17);
    printarChar(195, 1);
    printarChar(196, 44);
    printarChar(180, 1);
    gotoxy(5, 19);
    printf("Aperte a tecla:");
    gotoxy(10, 20);
    printf("ENTER para CONFIRMAR");
    gotoxy(9, 21);
    printf("APAGAR para CORRIGIR");
}

void desenharDetalhesVoto(char num[], struct Candidato c) {
    gotoxy(14,8);
    if (num[0] != 'x') {
        printf("%c", num[0]);
        gotoxy(19,8);
    } else {
        printf("%c", ' ');
        gotoxy(14,8);
    }

    if (num[1] != 'x') {
        printf("%c", num[1]);
        gotoxy(12, 12);
        put8s(c.nome, 0);
    } else {
        gotoxy(19,8);
        printf("%c", ' ');
        gotoxy(12, 12);
        printarChar(' ', 20);
    }
}

void desenhaTelaFim() {
    votosRealizados = (votosRealizados < 0 ? 1 : votosRealizados + 1);
    limpaTela();
    desenhaRetangulo(2, 1, 75, 22, 0, 0);
    gotoxy(39,10);
    printf("FIM");
    delay(5000);
}
