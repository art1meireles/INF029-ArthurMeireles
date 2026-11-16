#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"

typedef struct {
    int *dados;
    int tamanho;
    int quantidade;
} EstruturaAuxiliar;

EstruturaAuxiliar vetorPrincipal[TAM];

int ehPosicaoValida(int posicao);

void ordenarVetor(int vetor[], int n)
{
    int i, j, chave;

    for (i = 1; i < n; i++)
    {
        chave = vetor[i];
        j = i - 1;

        while (j >= 0 && vetor[j] > chave)
        {
            vetor[j + 1] = vetor[j];
            j--;
        }

        vetor[j + 1] = chave;
    }
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    int retorno = SUCESSO;

    // se posição é um valor válido {entre 1 e 10}
    if (ehPosicaoValida(posicao) != SUCESSO)
        retorno = POSICAO_INVALIDA;
    // a posicao pode já existir estrutura auxiliar
    else if (vetorPrincipal[posicao - 1].dados != NULL)
        retorno = JA_TEM_ESTRUTURA_AUXILIAR;
    // o tamanho nao pode ser menor que 1
    else if (tamanho < 1)
        retorno = TAMANHO_INVALIDO;
    else
    {
        // o tamanho ser muito grande
        int *novo = (int *) malloc(tamanho * sizeof(int));

        if (novo == NULL)
            retorno = SEM_ESPACO_DE_MEMORIA;
        else
        {
            // deu tudo certo, crie
            vetorPrincipal[posicao - 1].dados = novo;
            vetorPrincipal[posicao - 1].tamanho = tamanho;
            vetorPrincipal[posicao - 1].quantidade = 0;
            retorno = SUCESSO;
        }
    }

    return retorno;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    int retorno = 0;

    if (ehPosicaoValida(posicao) != SUCESSO)
        retorno = POSICAO_INVALIDA;
    else
    {
        EstruturaAuxiliar *aux = &vetorPrincipal[posicao - 1];

        // testar se existe a estrutura auxiliar
        if (aux->dados != NULL)
        {
            if (aux->quantidade < aux->tamanho)
            {
                //insere
                aux->dados[aux->quantidade] = valor;
                aux->quantidade++;
                retorno = SUCESSO;
            }
            else
            {
                retorno = SEM_ESPACO;
            }
        }
        else
        {
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }

    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    int retorno = SUCESSO;

    if (ehPosicaoValida(posicao) != SUCESSO)
        retorno = POSICAO_INVALIDA;
    else if (vetorPrincipal[posicao - 1].dados == NULL)
        retorno = SEM_ESTRUTURA_AUXILIAR;
    else if (vetorPrincipal[posicao - 1].quantidade == 0)
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    else
    {
        vetorPrincipal[posicao - 1].quantidade--;
        retorno = SUCESSO;
    }

    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    int retorno = SUCESSO;

    if (ehPosicaoValida(posicao) != SUCESSO)
        retorno = POSICAO_INVALIDA;
    else if (vetorPrincipal[posicao - 1].dados == NULL)
        retorno = SEM_ESTRUTURA_AUXILIAR;
    else if (vetorPrincipal[posicao - 1].quantidade == 0)
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    else
    {
        EstruturaAuxiliar *aux = &vetorPrincipal[posicao - 1];
        int i, encontrada = -1;

        for (i = 0; i < aux->quantidade && encontrada == -1; i++)
        {
            if (aux->dados[i] == valor)
                encontrada = i;
        }

        if (encontrada == -1)
            retorno = NUMERO_INEXISTENTE;
        else
        {
            for (i = encontrada; i < aux->quantidade - 1; i++)
                aux->dados[i] = aux->dados[i + 1];

            aux->quantidade--;
            retorno = SUCESSO;
        }
    }

    return retorno;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 1 || posicao > 10)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int retorno = 0;

    if (ehPosicaoValida(posicao) != SUCESSO)
        retorno = POSICAO_INVALIDA;
    else if (vetorPrincipal[posicao - 1].dados == NULL)
        retorno = SEM_ESTRUTURA_AUXILIAR;
    else
    {
        int i;
        for (i = 0; i < vetorPrincipal[posicao - 1].quantidade; i++)
            vetorAux[i] = vetorPrincipal[posicao - 1].dados[i];

        retorno = SUCESSO;
    }

    return retorno;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int retorno = getDadosEstruturaAuxiliar(posicao, vetorAux);

    if (retorno == SUCESSO)
        ordenarVetor(vetorAux, vetorPrincipal[posicao - 1].quantidade);

    return retorno;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int retorno = 0;
    int i, j, total = 0;

    for (i = 0; i < TAM; i++)
    {
        for (j = 0; j < vetorPrincipal[i].quantidade; j++)
        {
            vetorAux[total] = vetorPrincipal[i].dados[j];
            total++;
        }
    }

    if (total == 0)
        retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    else
        retorno = SUCESSO;

    return retorno;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int retorno = getDadosDeTodasEstruturasAuxiliares(vetorAux);

    if (retorno == SUCESSO)
    {
        int i, total = 0;

        for (i = 0; i < TAM; i++)
            total += vetorPrincipal[i].quantidade;

        ordenarVetor(vetorAux, total);
    }

    return retorno;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    int retorno = 0;

    if (ehPosicaoValida(posicao) != SUCESSO)
        retorno = POSICAO_INVALIDA;
    else if (vetorPrincipal[posicao - 1].dados == NULL)
        retorno = SEM_ESTRUTURA_AUXILIAR;
    else
    {
        EstruturaAuxiliar *aux = &vetorPrincipal[posicao - 1];
        int resultante = aux->tamanho + novoTamanho;

        if (resultante < 1)
            retorno = NOVO_TAMANHO_INVALIDO;
        else
        {
            int *novo = (int *) realloc(aux->dados, resultante * sizeof(int));

            if (novo == NULL)
                retorno = SEM_ESPACO_DE_MEMORIA;
            else
            {
                aux->dados = novo;
                aux->tamanho = resultante;

                if (aux->quantidade > resultante)
                    aux->quantidade = resultante;

                retorno = SUCESSO;
            }
        }
    }

    return retorno;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
    int retorno = 0;

    if (ehPosicaoValida(posicao) != SUCESSO)
        retorno = POSICAO_INVALIDA;
    else if (vetorPrincipal[posicao - 1].dados == NULL)
        retorno = SEM_ESTRUTURA_AUXILIAR;
    else if (vetorPrincipal[posicao - 1].quantidade == 0)
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    else
        retorno = vetorPrincipal[posicao - 1].quantidade;

    return retorno;
}

int getTamanhoEstruturaAuxiliar(int posicao)
{
    int retorno = 0;

    if (ehPosicaoValida(posicao) != SUCESSO)
        retorno = POSICAO_INVALIDA;
    else if (vetorPrincipal[posicao - 1].dados == NULL)
        retorno = SEM_ESTRUTURA_AUXILIAR;
    else
        retorno = vetorPrincipal[posicao - 1].tamanho;

    return retorno;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
    int i, j, total = 0;
    No *cabecote = NULL;

    for (i = 0; i < TAM; i++)
        total += vetorPrincipal[i].quantidade;

    if (total > 0)
    {
        cabecote = (No *) malloc(sizeof(No));

        if (cabecote != NULL)
        {
            No *atual = cabecote;
            int falhou = 0;

            cabecote->conteudo = 0;
            cabecote->prox = NULL;

            for (i = 0; i < TAM && !falhou; i++)
            {
                for (j = 0; j < vetorPrincipal[i].quantidade && !falhou; j++)
                {
                    No *novo = (No *) malloc(sizeof(No));

                    if (novo == NULL)
                        falhou = 1;
                    else
                    {
                        novo->conteudo = vetorPrincipal[i].dados[j];
                        novo->prox = NULL;
                        atual->prox = novo;
                        atual = novo;
                    }
                }
            }

            if (falhou)
                destruirListaEncadeadaComCabecote(&cabecote);
        }
    }

    return cabecote;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    if (inicio != NULL)
    {
        int i = 0;
        No *atual = inicio->prox;

        while (atual != NULL)
        {
            vetorAux[i] = atual->conteudo;
            i++;
            atual = atual->prox;
        }
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    if (inicio != NULL && *inicio != NULL)
    {
        No *atual = *inicio;
        No *proximo;

        while (atual != NULL)
        {
            proximo = atual->prox;
            free(atual);
            atual = proximo;
        }

        *inicio = NULL;
    }
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa

*/

void inicializar()
{
    int i;

    for (i = 0; i < TAM; i++)
    {
        vetorPrincipal[i].dados = NULL;
        vetorPrincipal[i].tamanho = 0;
        vetorPrincipal[i].quantidade = 0;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
    int i;

    for (i = 0; i < TAM; i++)
    {
        if (vetorPrincipal[i].dados != NULL)
        {
            free(vetorPrincipal[i].dados);
            vetorPrincipal[i].dados = NULL;
        }

        vetorPrincipal[i].tamanho = 0;
        vetorPrincipal[i].quantidade = 0;
    }
}

/*
Objetivo: dobrar o valor apontado por x.
*/
void dobrar(int *x)
{
    *x = (*x) * 2;
}