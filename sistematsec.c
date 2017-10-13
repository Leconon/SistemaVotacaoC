#include <stdio.h>
#include <string.h>
#include <conio.h>

#include "utils.c"
#include "interface.c"

#define INI_VOTACAO 1
#define VER_RESULTADOS 2
#define SAIR 3

int main() {
    desenhaTelaCarregamento();
    system("color F0");
    desenhaMenuPrincipal();
    //iniciarVotacao();
    return 0;
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
}

void desenhaMenuPrincipal() {
    limpaTela();
    desenhaInterface(" Sistema de Votação TSEc ");

    int opcaoMenu = 1, opcaoSelecionada = 0, pintado = 0;
    char tecla;

    while (opcaoSelecionada > -1) {
        if (opcaoSelecionada) {
            pintado = 1;
        }
        desenhaBotaoMenu(INI_VOTACAO, "Iniciar Votação", opcaoSelecionada, opcaoMenu, pintado);
        desenhaBotaoMenu(VER_RESULTADOS, "Verificar Resultados", opcaoSelecionada, opcaoMenu, pintado);
        desenhaBotaoMenu(SAIR, "Sair", opcaoSelecionada, opcaoMenu, pintado);
        if (!pintado) {
            tecla = getch();
        }
        if (tecla == 72 && opcaoMenu > 1) {
            opcaoMenu--;
        } else if (tecla == 80 && opcaoMenu < 3) {
            opcaoMenu++;
        } else if (tecla == 13) {
            opcaoSelecionada = opcaoMenu;
        }
        if (pintado) {
            delay(100);
            switch (opcaoSelecionada) {
                case INI_VOTACAO: iniciarVotacao(); break;
                case VER_RESULTADOS: break;
                case SAIR: opcaoSelecionada = -1; break;
            }
            pintado = 0;
            opcaoSelecionada = (opcaoSelecionada == -1) * -1;
            limpaTela();
            desenhaInterface("Sistema de Votação TSEc");
        }
    }
    limpaTela();
}

void desenhaBotaoMenu(int index, char texto[], int opcaoSelecionada, int opcaoMenu, int pintado) {
    desenhaBotao(15, (index * 5) + 1, 49, 4, opcaoSelecionada == index && pintado, opcaoMenu == index, texto);
}


/*
 * O Código abaixo é o módulo de votação, deverá ser separado em um outro arquivo em breve.
 */

static int qtdEleitores = 0;

struct Candidato {
    int num;
    char nome[50];
    int valido;
};

void iniciarVotacao() {
    // Verificar se já existe o arquivo de dados
    pedirNumeroEleitores();
    if (qtdEleitores > 0) {
        votacao();
    }
    getch();
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
    qtdEleitores = 5;
    limpaTela();
}

struct Candidato verificarCandidato(int num) {
    struct Candidato c;
    strcpy(c.nome, "Voto Nulo");
    c.num = num;
    c.valido = 1;
    switch (num) {
        case 17: strcpy(c.nome, "Voto Nulo"); return c;
        case 22: strcpy(c.nome, "Maeli Gente"); return c;
        case 31: strcpy(c.nome, "Lissandra Progresso"); return c;
        case 38: strcpy(c.nome, "Maia da Ana"); return c;
    }
    c.valido = 0;
    return c;
}


void votacao() {
    limpaTela();
    char pressionado;
    desenharTecladoUrna(0);
    desenharBotoesAcao();
    desenharTelaVotacao();
    while(1) {
        pressionado = getch();
        desenharTecladoUrna(pressionado);
        desenharBotoesAcao();
        delay(100);
        desenharTecladoUrna(0);
        desenharBotoesAcao(0);
    }

    struct Candidato c;
    c = verificarCandidato(17);
    puts(c.nome);
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
    put8s("Número: ");
    desenhaRetangulo(12, 6, 3, 3, 0, 0);
    desenhaRetangulo(16, 6, 3, 3, 0, 0);
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
