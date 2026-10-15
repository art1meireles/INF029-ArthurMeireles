
#include <stdio.h>

#define TAM 10
#define NUM_NAVIOS 5

#define AGUA ' '
#define NAVIO 'N'
#define ACERTO 'O'
#define ERRO 'X'

/* Inicializa a matriz com agua */
void inicializaTabuleiro(char tab[TAM][TAM]) {
    int i, j;

    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tab[i][j] = AGUA;
        }
    }
}

/* Exibe o tabuleiro com os numeros das linhas e colunas */
void listaTabuleiro(char tab[TAM][TAM]) {
    int i, j;

    printf("\n    ");
    for (j = 0; j < TAM; j++) {
        printf(" %d  ", j);
    }

    printf("\n");

    for (i = 0; i < TAM; i++) {
        printf("%2d  ", i);

        for (j = 0; j < TAM; j++) {
            printf("| %c ", tab[i][j]);
        }

        printf("|\n");

        printf("    ");
        for (j = 0; j < TAM; j++) {
            printf("----");
        }
        printf("-\n");
    }
}

/* Define o tamanho de cada navio */
void defineTamanhos(int tamanhos[NUM_NAVIOS]) {
    int i;

    tamanhos[0] = 4;
    tamanhos[1] = 3;
    tamanhos[2] = 1;
    tamanhos[3] = 1;
    tamanhos[4] = 1;

    /* Navios adicionais devem ter tamanho 2 */
    for (i = 5; i < NUM_NAVIOS; i++) {
        tamanhos[i] = 2;
    }
}

/* Posiciona um navio se todas as condicoes forem validas */
int posicionaNavio(
    char tab[TAM][TAM],
    int linha,
    int coluna,
    int tamanho,
    char direcao
) {
    int i;

    /* Verifica se a direcao e valida */
    if (direcao != 'H' && direcao != 'V') {
        return 0;
    }

    /* Verifica os limites do tabuleiro */
    if (linha < 0 || linha >= TAM ||
        coluna < 0 || coluna >= TAM) {
        return 0;
    }

    if (direcao == 'H' && coluna + tamanho > TAM) {
        return 0;
    }

    if (direcao == 'V' && linha + tamanho > TAM) {
        return 0;
    }

    /* Verifica se todas as posicoes estao vazias */
    for (i = 0; i < tamanho; i++) {
        if (direcao == 'H') {
            if (tab[linha][coluna + i] != AGUA) {
                return 0;
            }
        } else {
            if (tab[linha + i][coluna] != AGUA) {
                return 0;
            }
        }
    }

    /* Posiciona o navio */
    for (i = 0; i < tamanho; i++) {
        if (direcao == 'H') {
            tab[linha][coluna + i] = NAVIO;
        } else {
            tab[linha + i][coluna] = NAVIO;
        }
    }

    return 1;
}

/* Solicita o posicionamento de todos os navios */
void posicionaTodosNavios(
    char tab[TAM][TAM],
    int tamanhos[NUM_NAVIOS],
    int jogador
) {
    int i;
    int linha, coluna;
    char direcao;
    int valido;

    for (i = 0; i < NUM_NAVIOS; i++) {
        valido = 0;

        while (valido == 0) {
            printf("\nJogador %d - Navio %d de %d\n",
                   jogador, i + 1, NUM_NAVIOS);

            printf("Tamanho do navio: %d\n", tamanhos[i]);

            printf("Linha inicial (0 a 9): ");
            scanf("%d", &linha);

            printf("Coluna inicial (0 a 9): ");
            scanf("%d", &coluna);

            printf("Direcao (H = horizontal, V = vertical): ");
            scanf(" %c", &direcao);

            if (direcao >= 'a' && direcao <= 'z') {
                direcao = direcao - 'a' + 'A';
            }

            valido = posicionaNavio(
                tab, linha, coluna, tamanhos[i], direcao
            );

            if (valido == 0) {
                printf("\nPosicionamento invalido!\n");
                printf("Verifique os limites e as sobreposicoes.\n");
            }
        }

        printf("\nTabuleiro do jogador %d:\n", jogador);
        listaTabuleiro(tab);
    }
}

/* Executa um disparo. Retorna 1 se o tiro foi valido */
int realizaDisparo(
    char tabAdversario[TAM][TAM],
    char tabAtaques[TAM][TAM],
    int linha,
    int coluna
) {
    /* Verifica se as coordenadas estao dentro do tabuleiro */
    if (linha < 0 || linha >= TAM ||
        coluna < 0 || coluna >= TAM) {
        printf("Coordenadas invalidas!\n");
        return 0;
    }

    /* Impede disparos repetidos */
    if (tabAtaques[linha][coluna] == ACERTO ||
        tabAtaques[linha][coluna] == ERRO) {
        printf("Voce ja atirou nessa posicao!\n");
        return 0;
    }

    /* Verifica se o disparo atingiu um navio */
    if (tabAdversario[linha][coluna] == NAVIO) {
        printf("\nACERTOU um navio!\n");

        tabAdversario[linha][coluna] = ACERTO;
        tabAtaques[linha][coluna] = ACERTO;
    } else {
        printf("\nTIRO NA AGUA!\n");

        tabAdversario[linha][coluna] = ERRO;
        tabAtaques[linha][coluna] = ERRO;
    }

    return 1;
}

/* Verifica se ainda existem navios nao atingidos */
int verificaVitoria(char tab[TAM][TAM]) {
    int i, j;

    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            if (tab[i][j] == NAVIO) {
                return 0;
            }
        }
    }

    return 1;
}

/* Realiza o turno de um jogador */
int turno(
    int jogador,
    char tabProprio[TAM][TAM],
    char tabAtaques[TAM][TAM],
    char tabAdversario[TAM][TAM]
) {
    int linha, coluna;
    int valido = 0;

    while (valido == 0) {
        printf("\n================================\n");
        printf("          JOGADOR %d\n", jogador);
        printf("================================\n");

        printf("\nSeu tabuleiro:\n");
        listaTabuleiro(tabProprio);

        printf("\nSeu tabuleiro de ataques:\n");
        listaTabuleiro(tabAtaques);

        printf("\nEscolha a posicao do disparo:\n");

        printf("Linha (0 a 9): ");
        scanf("%d", &linha);

        printf("Coluna (0 a 9): ");
        scanf("%d", &coluna);

        valido = realizaDisparo(
            tabAdversario, tabAtaques, linha, coluna
        );
    }

    return verificaVitoria(tabAdversario);
}

int main(void) {
    char tabuleiro1[TAM][TAM];
    char tabuleiro2[TAM][TAM];

    char ataques1[TAM][TAM];
    char ataques2[TAM][TAM];

    int tamanhos[NUM_NAVIOS];
    int vencedor = 0;

    /* Inicializa os tabuleiros */
    inicializaTabuleiro(tabuleiro1);
    inicializaTabuleiro(tabuleiro2);
    inicializaTabuleiro(ataques1);
    inicializaTabuleiro(ataques2);

    defineTamanhos(tamanhos);

    /* Posicionamento dos navios */
    printf("================================\n");
    printf("       BATALHA NAVAL\n");
    printf("================================\n");

    printf("\nJogador 1: posicione seus navios.\n");
    posicionaTodosNavios(tabuleiro1, tamanhos, 1);

    printf("\nJogador 2: posicione seus navios.\n");
    posicionaTodosNavios(tabuleiro2, tamanhos, 2);

    /* Alternancia de turnos */
    while (vencedor == 0) {
        printf("\nVez do jogador 1.\n");

        if (turno(1, tabuleiro1, ataques1, tabuleiro2)) {
            vencedor = 1;
        } else {
            printf("\nVez do jogador 2.\n");

            if (turno(2, tabuleiro2, ataques2, tabuleiro1)) {
                vencedor = 2;
            }
        }
    }

    printf("\n================================\n");
    printf("JOGADOR %d VENCEU!\n", vencedor);
    printf("================================\n");

    return 0;
}