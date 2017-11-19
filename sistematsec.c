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

int main() {
    if (1) {
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
    limpaTela();
    puts("votacao");
    getch();
}
