#include <stdio.h>

void inicializarTabuleiro(char tabuleiro[3][3]);
void mostrarTabuleiro(char tabuleiro[3][3]);
int jogadaValida(char tabuleiro[3][3], char linha, int coluna);
void fazerJogada(char tabuleiro[3][3], char linha, int coluna, char simbolo);
int verificarVencedor(char tabuleiro[3][3], char simbolo);
int tabuleiroCheio(char tabuleiro[3][3]);

int main()
{
    char tabuleiro[3][3];
    char linha;
    int coluna;
    int jogador = 1;
    char simbolo;
    int fim = 0;

    inicializarTabuleiro(tabuleiro);

    printf("=== JOGO DA VELHA ===\n");
    printf("Como jogar:\n");
    printf("Cada jogador deve informar linha e coluna.\n");
    printf("Exemplos de jogadas validas:\n");
    printf("A1  B3  C2\n");
    printf("Jogador 1 usa X\n");
    printf("Jogador 2 usa O\n\n");

    while(!fim){

        mostrarTabuleiro(tabuleiro);

        if(jogador == 1)
            simbolo = 'X';
        else
            simbolo = 'O';

        printf("Jogador %d, informe sua jogada: ", jogador);
        scanf(" %c%d", &linha, &coluna);

        if(jogadaValida(tabuleiro, linha, coluna)){

            fazerJogada(tabuleiro, linha, coluna, simbolo);

            if(verificarVencedor(tabuleiro, simbolo)){

                mostrarTabuleiro(tabuleiro);

                printf("Jogador %d venceu!\n", jogador);

                fim = 1;
            }

            else if(tabuleiroCheio(tabuleiro)){

                mostrarTabuleiro(tabuleiro);

                printf("Nao houve ganhador.\n");

                fim = 1;
            }

            else{

                if(jogador == 1)
                    jogador = 2;
                else
                    jogador = 1;
            }
        }

        else{

            printf("Entrada invalida!\n");
            printf("Use valores entre A-C e 1-3.\n");
            printf("Exemplos: A1, B2, C3\n\n");
        }
    }

    return 0;
}

void inicializarTabuleiro(char tabuleiro[3][3])
{
    int i, j;

    for(i = 0; i < 3; i++){

        for(j = 0; j < 3; j++){

            tabuleiro[i][j] = ' ';
        }
    }
}

void mostrarTabuleiro(char tabuleiro[3][3])
{
    printf("\n");

    printf("    1   2   3\n");

    printf("A   %c | %c | %c\n",
           tabuleiro[0][0],
           tabuleiro[0][1],
           tabuleiro[0][2]);

    printf("   ---+---+---\n");

    printf("B   %c | %c | %c\n",
           tabuleiro[1][0],
           tabuleiro[1][1],
           tabuleiro[1][2]);

    printf("   ---+---+---\n");

    printf("C   %c | %c | %c\n",
           tabuleiro[2][0],
           tabuleiro[2][1],
           tabuleiro[2][2]);

    printf("\n");
}

int jogadaValida(char tabuleiro[3][3], char linha, int coluna)
{
    int i, j;

    if(linha >= 'a' && linha <= 'c')
        linha = linha - 32;

    if(linha < 'A' || linha > 'C')
        return 0;

    if(coluna < 1 || coluna > 3)
        return 0;

    i = linha - 'A';
    j = coluna - 1;

    if(tabuleiro[i][j] != ' ')
        return 0;

    return 1;
}

void fazerJogada(char tabuleiro[3][3], char linha, int coluna, char simbolo)
{
    int i, j;

    if(linha >= 'a' && linha <= 'c')
        linha = linha - 32;

    i = linha - 'A';
    j = coluna - 1;

    tabuleiro[i][j] = simbolo;
}

int verificarVencedor(char tabuleiro[3][3], char simbolo)
{
    int i;

    /* linhas */

    for(i = 0; i < 3; i++){

        if(tabuleiro[i][0] == simbolo &&
           tabuleiro[i][1] == simbolo &&
           tabuleiro[i][2] == simbolo)

            return 1;
    }

    /* colunas */

    for(i = 0; i < 3; i++){

        if(tabuleiro[0][i] == simbolo &&
           tabuleiro[1][i] == simbolo &&
           tabuleiro[2][i] == simbolo)

            return 1;
    }

    /* diagonal principal */

    if(tabuleiro[0][0] == simbolo &&
       tabuleiro[1][1] == simbolo &&
       tabuleiro[2][2] == simbolo)

        return 1;

    /* diagonal secundaria */

    if(tabuleiro[0][2] == simbolo &&
       tabuleiro[1][1] == simbolo &&
       tabuleiro[2][0] == simbolo)

        return 1;

    return 0;
}

int tabuleiroCheio(char tabuleiro[3][3])
{
    int i, j;

    for(i = 0; i < 3; i++){

        for(j = 0; j < 3; j++){

            if(tabuleiro[i][j] == ' ')
                return 0;
        }
    }

    return 1;
}