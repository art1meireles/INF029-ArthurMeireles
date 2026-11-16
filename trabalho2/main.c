#include <stdio.h>
#include <stdlib.h>

#include "trabalho2.h"

#define TAM 10

int getTamanhoEstruturaAuxiliar(int posicao);

int menu();
int lerInteiro(int *valor);
void imprimirVetor(int vetor[], int n);
void inserir();
void listarEstruturas(int ordenado);
void listarTodosOrdenados();
void excluir();
void aumentar();

int lerInteiro(int *valor)
{
    char linha[64];

    if (fgets(linha, sizeof(linha), stdin) == NULL)
        return -1;

    if (sscanf(linha, "%d", valor) == 1)
        return 1;

    return 0;
}

int menu()
{
    int op;
    int leitura;

    printf("\n===== MENU =====\n");
    printf("1 - Inserir elemento\n");
    printf("2 - Listar os números de todas as estruturas\n");
    printf("3 - Listar os números ordenados de cada estrutura\n");
    printf("4 - Listar todos os números de forma ordenada\n");
    printf("5 - Excluir um elemento\n");
    printf("6 - Aumentar o tamanho de uma estrutura auxiliar\n");
    printf("7 - Sair\n");
    printf("Digite a opção desejada: ");

    leitura = lerInteiro(&op);

    if (leitura == -1)
        op = 7;
    else if (leitura == 0)
        op = -1;

    return op;
}

void imprimirVetor(int vetor[], int n)
{
    int i;

    for (i = 0; i < n; i++)
        printf("%d ", vetor[i]);

    printf("\n");
}

void inserir()
{
    int posicao, tamanho, valor, ret;

    printf("Em qual posição deseja inserir (1..10)? ");
    if (lerInteiro(&posicao) != 1)
    {
        printf("Entrada inválida.\n");
        return;
    }

    ret = getQuantidadeElementosEstruturaAuxiliar(posicao);

    if (ret == POSICAO_INVALIDA)
    {
        printf("Posição inválida.\n");
        return;
    }

    if (ret == SEM_ESTRUTURA_AUXILIAR)
    {
        printf("Ainda não existe estrutura auxiliar nessa posição.\n");
        printf("Qual o tamanho total dela (quantidade de inteiros)? ");
        if (lerInteiro(&tamanho) != 1)
        {
            printf("Entrada inválida.\n");
            return;
        }

        ret = criarEstruturaAuxiliar(posicao, tamanho);

        if (ret == TAMANHO_INVALIDO)
            printf("Tamanho inválido: deve ser maior ou igual a 1.\n");
        else if (ret == SEM_ESPACO_DE_MEMORIA)
            printf("Sem espaço de memória para criar a estrutura.\n");
        else if (ret != SUCESSO)
            printf("Não foi possível criar a estrutura auxiliar.\n");

        if (ret != SUCESSO)
            return;

        printf("Estrutura auxiliar criada com tamanho %d.\n", tamanho);
    }

    printf("Número a inserir: ");
    if (lerInteiro(&valor) != 1)
    {
        printf("Entrada inválida.\n");
        return;
    }

    ret = inserirNumeroEmEstrutura(posicao, valor);

    if (ret == SUCESSO)
        printf("Número inserido com sucesso.\n");
    else if (ret == SEM_ESPACO)
        printf("Não há mais espaço nessa estrutura para inserir números.\n");
    else if (ret == SEM_ESTRUTURA_AUXILIAR)
        printf("Não existe estrutura auxiliar nessa posição.\n");
    else if (ret == POSICAO_INVALIDA)
        printf("Posição inválida.\n");
}

void listarEstruturas(int ordenado)
{
    int posicao, tamanho, qtd;
    int *vetorAux;

    for (posicao = 1; posicao <= TAM; posicao++)
    {
        tamanho = getTamanhoEstruturaAuxiliar(posicao);

        if (tamanho == SEM_ESTRUTURA_AUXILIAR)
        {
            printf("Posição %d: sem estrutura auxiliar\n", posicao);
        }
        else
        {
            qtd = getQuantidadeElementosEstruturaAuxiliar(posicao);

            if (qtd == ESTRUTURA_AUXILIAR_VAZIA)
            {
                printf("Posição %d (tamanho %d): vazia\n", posicao, tamanho);
            }
            else
            {
                vetorAux = (int *) malloc(qtd * sizeof(int));

                if (vetorAux == NULL)
                {
                    printf("Posição %d: sem memória para listar\n", posicao);
                }
                else
                {
                    if (ordenado)
                        getDadosOrdenadosEstruturaAuxiliar(posicao, vetorAux);
                    else
                        getDadosEstruturaAuxiliar(posicao, vetorAux);

                    printf("Posição %d (tamanho %d): ", posicao, tamanho);
                    imprimirVetor(vetorAux, qtd);

                    free(vetorAux);
                }
            }
        }
    }
}

void listarTodosOrdenados()
{
    int posicao, qtd, total = 0;
    int *vetorAux;

    for (posicao = 1; posicao <= TAM; posicao++)
    {
        qtd = getQuantidadeElementosEstruturaAuxiliar(posicao);

        if (qtd > 0)
            total += qtd;
    }

    if (total == 0)
    {
        printf("Não há nenhum número cadastrado.\n");
        return;
    }

    vetorAux = (int *) malloc(total * sizeof(int));

    if (vetorAux == NULL)
    {
        printf("Sem memória para listar.\n");
        return;
    }

    if (getDadosOrdenadosDeTodasEstruturasAuxiliares(vetorAux) == SUCESSO)
    {
        printf("Todos os números ordenados: ");
        imprimirVetor(vetorAux, total);
    }

    free(vetorAux);
}

void excluir()
{
    int posicao, valor, ret;

    printf("Em qual posição deseja excluir (1..10)? ");
    if (lerInteiro(&posicao) != 1)
    {
        printf("Entrada inválida.\n");
        return;
    }

    printf("Qual número deseja excluir? ");
    if (lerInteiro(&valor) != 1)
    {
        printf("Entrada inválida.\n");
        return;
    }

    ret = excluirNumeroEspecificoDeEstrutura(posicao, valor);

    if (ret == SUCESSO)
        printf("Número excluído com sucesso.\n");
    else if (ret == POSICAO_INVALIDA)
        printf("Posição inválida.\n");
    else if (ret == SEM_ESTRUTURA_AUXILIAR)
        printf("Não existe estrutura auxiliar nessa posição.\n");
    else if (ret == ESTRUTURA_AUXILIAR_VAZIA)
        printf("A estrutura auxiliar está vazia.\n");
    else if (ret == NUMERO_INEXISTENTE)
        printf("O número %d não existe nessa estrutura.\n", valor);
}

void aumentar()
{
    int posicao, extra, ret;

    printf("Em qual posição deseja aumentar (1..10)? ");
    if (lerInteiro(&posicao) != 1)
    {
        printf("Entrada inválida.\n");
        return;
    }

    printf("Quantas posições extras? ");
    if (lerInteiro(&extra) != 1)
    {
        printf("Entrada inválida.\n");
        return;
    }

    if (extra < 1)
    {
        printf("O tamanho extra deve ser maior ou igual a 1.\n");
        return;
    }

    ret = modificarTamanhoEstruturaAuxiliar(posicao, extra);

    if (ret == SUCESSO)
        printf("Tamanho aumentado com sucesso. Novo tamanho: %d\n", getTamanhoEstruturaAuxiliar(posicao));
    else if (ret == POSICAO_INVALIDA)
        printf("Posição inválida.\n");
    else if (ret == SEM_ESTRUTURA_AUXILIAR)
        printf("Não existe estrutura auxiliar nessa posição.\n");
    else if (ret == SEM_ESPACO_DE_MEMORIA)
        printf("Sem espaço de memória para aumentar a estrutura.\n");
    else if (ret == NOVO_TAMANHO_INVALIDO)
        printf("Novo tamanho inválido.\n");
}

int main()
{
    inicializar();

    int op;
    int sair = 0;

    while (!sair)
    {
        op = menu();

        switch (op)
        {
        case 1:
            inserir();
            break;

        case 2:
            listarEstruturas(0);
            break;

        case 3:
            listarEstruturas(1);
            break;

        case 4:
            listarTodosOrdenados();
            break;

        case 5:
            excluir();
            break;

        case 6:
            aumentar();
            break;

        case 7:
            sair = 1;
            finalizar();
            break;

        default:
            printf("Opção inválida.\n");
        }
    }

    return 0;
}