#include <stdio.h>
#include <string.h>
#include <conio.h>

#include "utils.c"
#include "interface.c"
#include "modulovotacao.c"
#include "VotacaoIO.c"

#define INI_VOTACAO 1
#define VER_RESULTADOS 2
#define SAIR 3

#define QTD_CANDIDATOS 6
#define NUM_CANDIDATO_NULO 0
#define NUM_CANDIDATO_AUSENCIA 1

struct ObjetoCandidato {
    int num;
    char nome[50];
    int valido;
    int numVotos;
};

struct ObjetoCandidato candidatos[QTD_CANDIDATOS];

void InicializarCandidatos() {
    struct ObjetoCandidato candidato1;
    candidato1.num = 17;
    strcpy(candidato1.nome, "Maeli Gente");
    candidato1.valido = 1;
    candidato1.numVotos = 0;

    struct ObjetoCandidato candidato2;
    candidato2.num = 22;
    strcpy(candidato2.nome, "Loula do Brasil");
    candidato2.valido = 1;
    candidato2.numVotos = 0;

    struct ObjetoCandidato candidato3;
    candidato3.num = 31;
    strcpy(candidato3.nome, "Lissandra Progresso");
    candidato3.valido = 1;
    candidato3.numVotos = 0;

    struct ObjetoCandidato candidato4;
    candidato4.num = 28;
    strcpy(candidato4.nome, "Maia da Ana");
    candidato4.valido = 1;
    candidato4.numVotos = 0;

    struct ObjetoCandidato candidato5;
    candidato5.num = 0;
    strcpy(candidato5.nome, "Voto Nulo");
    candidato5.valido = 1;
    candidato5.numVotos = 0;

    struct ObjetoCandidato candidato6;
    candidato6.num = 0;
    strcpy(candidato6.nome, "Ausência");
    candidato6.valido = 1;
    candidato6.numVotos = 0;

    candidatos[0] = candidato1;
    candidatos[1] = candidato2;
    candidatos[2] = candidato3;
    candidatos[3] = candidato4;
    candidatos[4] = candidato5;
    candidatos[5] = candidato6;
}

int main() {
    if (1) {
        InicializarCandidatos();
        desenhaTelaCarregamento();
        votosRealizados = verificaNumRegistros();
        qtdEleitores = verificaTotalVotos();
        system("color F0");
        desenhaMenuPrincipal();
    } else {
        votosRealizados = verificaNumRegistros();
        qtdEleitores = verificaTotalVotos();
        printf("%i  %i", votosRealizados, qtdEleitores);
    }
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
        desenhaBotaoMenu(INI_VOTACAO, qtdEleitores > 0 && qtdEleitores > votosRealizados ? "Continuar Votação" : "Iniciar nova votação", opcaoSelecionada, opcaoMenu, pintado);
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
                case VER_RESULTADOS: desenhaResultados(); break;
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

/////////////////////////////////////

void desenhaResultados() {
    desenhaInterface(" Resultados ");
    int qtdResultados = verificaTotalVotos();
    int votos[qtdResultados];

    int i, voto = 0, pular = 1;
    while ((voto = retornaRegistrosLaco()) >= 0) {
        if (pular) {
            pular = 0;
            continue;
        }
        int nulo = 1;
        for (i=0; i<QTD_CANDIDATOS; i++) {
            if (candidatos[i].num == voto) {
                candidatos[i].numVotos++;
                nulo = 0;
                break;
            }
        }
        for (i=0; i<QTD_CANDIDATOS && nulo; i++) {
            if (candidatos[i].num == NUM_CANDIDATO_NULO) {
                candidatos[i].numVotos++;
                nulo = 0;
                break;
            }
        }
    }

    desenhaDivisaoVInterface(50);

    for (i=0; i<QTD_CANDIDATOS; i++) {
        gotoxy(3, 6+(i*3));
        int porcentagem = (candidatos[i].numVotos * 100)/qtdResultados;
        char nome[14];
        put8s(candidatos[i].nome, 13);
        printf("  ");
        printarChar(219, (25*porcentagem)/100);
        printf("(%i%%)", porcentagem);
        gotoxy(3, 6+(i*3)+1);
        printf("- %i Votos", candidatos[i].numVotos);
    }

    getch();
}
