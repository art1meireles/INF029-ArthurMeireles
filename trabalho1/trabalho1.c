// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Arthur Meireles Dos Santos
//  email: arthurmeireles935@gmail.com
//  Matrícula: 20252160011
//  Semestre: 2026.1

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// ################################################

#include <stdio.h>
#include "trabalho1.h" 
#include <stdlib.h>

/*PROTÓTIPOS DE FUNÇÕES AUXILIARES*/

int ValidarData(int dia, int mes, int ano);
int ValidarMes(int mes);
int ValidarAno(int ano);
int eAnoBissexto(int ano);
int VerificarSeMaior(char datainicial[], char datafinal[]);
int CalcTamStr(char str[]);
int CalcRazao10(int num);
int VerificarAcima(char matriz[8][10], char palavra[6], int lin, int col, int indice);
int VerificarAbaixo(char matriz[8][10], char palavra[6], int lin, int col, int indice);
int VerificarEsquerda(char matriz[8][10], char palavra[6], int lin, int col, int indice);
int VerificarDireita(char matriz[8][10], char palavra[6], int lin, int col, int indice);
int VerificarDiagonalSupEsq(char matriz[8][10], char palavra[6], int lin, int col, int indice);
int VerificarDiagonalSupDir(char matriz[8][10], char palavra[6], int lin, int col, int indice);
int VerificarDiagonalInfEsq(char matriz[8][10], char palavra[6], int lin, int col, int indice);
int VerificarDiagonalInfDir(char matriz[8][10], char palavra[6], int lin, int col, int indice);
int ePosicaoValida(int lin, int col);

DiasMesesAnos ChecarDiferenca(
    DiasMesesAnos dma,
    DataQuebrada dqInit,
    DataQuebrada dqFim
);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
    int datavalida;

    DataQuebrada dq = quebraData(data);

    if(!dq.valido)
        datavalida = 0;
    else
        datavalida = ValidarData(dq.iDia, dq.iMes, dq.iAno);

    if(datavalida)
        return 1;
    else
        return 0;
}



/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{
    DiasMesesAnos dma;

    DataQuebrada dqInit = quebraData(datainicial);
    DataQuebrada dqFim = quebraData(datafinal);

    if(q1(datainicial) == 0){
        dma.retorno = 2;
        return dma;
    }

    else if(q1(datafinal) == 0){
        dma.retorno = 3;
        return dma;
    }

    else{

        // verifica se data inicial é maior que a final
        if(VerificarSeMaior(datainicial, datafinal)){
            dma.retorno = 4;
            return dma;
        }

        // calcula diferenças
        dma.qtdAnos = dqFim.iAno - dqInit.iAno;
        dma.qtdMeses = dqFim.iMes - dqInit.iMes;
        dma.qtdDias = dqFim.iDia - dqInit.iDia;

        // ajusta valores negativos
        dma = ChecarDiferenca(dma, dqInit, dqFim);

        // sucesso
        dma.retorno = 1;

        return dma;
    }
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char texto[], char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;
    int i;
    char atual;

    for(i = 0; texto[i] != '\0'; i++){

        atual = texto[i];

        if(isCaseSensitive != 1){

            if(atual >= 'A' && atual <= 'Z')
                atual += ('a' - 'A');

            if(c >= 'A' && c <= 'Z')
                c += ('a' - 'A');
        }

        if(atual == c)
            qtdOcorrencias++;
    }

    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char strTexto[], char strBusca[], int posicoes[30])
{
    int qtdOcorrencias = 0;
    int TAM_TEXT = CalcTamStr(strTexto);
    int TAM_SEARCH = CalcTamStr(strBusca);

    int CharStrNum[TAM_TEXT];
    int CharSearchNum[TAM_SEARCH];

    int iCont, jCont, kCont = 0;

    for(iCont = 0, jCont = 0; strTexto[iCont] != '\0'; iCont++, jCont++){
        if(strTexto[iCont] == -61)
            iCont++;

        CharStrNum[jCont] = strTexto[iCont];
    }

    for(iCont = 0, jCont = 0; strBusca[iCont] != '\0'; iCont++, jCont++){
        if(strBusca[iCont] == -61)
            iCont++;

        CharSearchNum[jCont] = strBusca[iCont];
    }

    for(iCont = 0; iCont <= TAM_TEXT - TAM_SEARCH; iCont++){
        for(jCont = 0; jCont < TAM_SEARCH; jCont++){
            if(CharStrNum[iCont + jCont] != CharSearchNum[jCont]){
                break;
            }
        }

        if(jCont == TAM_SEARCH){
            qtdOcorrencias++;

            posicoes[kCont] = iCont + 1;
            kCont++;

            posicoes[kCont] = iCont + jCont;
            kCont++;

            iCont = iCont + TAM_SEARCH - 1;

        }
    }

    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
    int invertido = 0;

    while(num > 0){

        invertido = invertido * 10;

        invertido = invertido + (num % 10);

        num = num / 10;
    }

    return invertido;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias = 0;
    int Razao10Busca;
    int divisor;

    Razao10Busca = CalcRazao10(numerobusca);
    divisor = Razao10Busca * 10;

    while(numerobase > 0){

        if(numerobase % divisor == numerobusca){
            qtdOcorrencias++;
            numerobase = numerobase / divisor;
        }
        else{
            numerobase = numerobase / 10;
        }
    }

    return qtdOcorrencias;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

 int q7(char matriz[8][10], char palavra[6])
 {
    int achou = 0;
    int iCont, jCont;

    for(iCont = 0; iCont < 8 && !achou; iCont++){
        for(jCont = 0; jCont < 10 && !achou; jCont++){

            if(matriz[iCont][jCont] == palavra[0]){
                achou += VerificarAcima(matriz, palavra, iCont - 1, jCont, 1);
                achou += VerificarAbaixo(matriz, palavra, iCont + 1, jCont, 1);
                achou += VerificarEsquerda(matriz, palavra, iCont, jCont - 1, 1);
                achou += VerificarDireita(matriz, palavra, iCont, jCont + 1, 1);
                achou += VerificarDiagonalSupEsq(matriz, palavra, iCont - 1, jCont - 1, 1);
                achou += VerificarDiagonalSupDir(matriz, palavra, iCont - 1, jCont + 1, 1);
                achou += VerificarDiagonalInfEsq(matriz, palavra, iCont + 1, jCont - 1, 1);
                achou += VerificarDiagonalInfDir(matriz, palavra, iCont + 1, jCont + 1, 1);
            }
        }
    }

    if(achou > 0)
        achou = 1;

    return achou;

 }



DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

dq.iDia = atoi(sDia);
dq.iMes = atoi(sMes);

if(i == 2)
    dq.iAno = atoi(sAno) + 2000;
else
    dq.iAno = atoi(sAno);

dq.valido = 1;
    
  return dq;
}

int ValidarData(int dia, int mes, int ano)
{
    if(dia < 1)
        return 0;

    if(ValidarMes(mes) == 0 || ValidarAno(ano) == 0)
        return 0;

    if(mes == 2){
        if(eAnoBissexto(ano)){
            return (dia < 30);
        }else{
            return (dia < 29);
        }
    }

    if((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30)
        return 0;
    else if(dia > 31)
        return 0;
    else
        return 1;
}

int ValidarMes(int mes)
{
    return (mes > 0 && mes < 13);
}

int ValidarAno(int ano)
{
    if(ano < 0)
        return 0;

    return 1;
}

int eAnoBissexto(int ano)
{
    if(ano % 100 == 0){
        if(ano % 400 == 0)
            return 1;
        else
            return 0;
    }
    else if(ano % 4 == 0)
        return 1;
    else
        return 0;
}

int VerificarSeMaior(char datainicial[], char datafinal[])
{
    DataQuebrada dqInit = quebraData(datainicial);
    DataQuebrada dqFim = quebraData(datafinal);

    if(dqInit.iAno > dqFim.iAno)
        return 1;

    if(dqInit.iAno == dqFim.iAno &&
       dqInit.iMes > dqFim.iMes)
        return 1;

    if(dqInit.iAno == dqFim.iAno &&
       dqInit.iMes == dqFim.iMes &&
       dqInit.iDia > dqFim.iDia)
        return 1;

    return 0;
}

DiasMesesAnos ChecarDiferenca(
    DiasMesesAnos dma,
    DataQuebrada dqInit,
    DataQuebrada dqFim
)
{
    int mesAnterior = dqFim.iMes - 1;
    int anoAnterior = dqFim.iAno;

    if(mesAnterior == 0){
        mesAnterior = 12;
        anoAnterior--;
    }

    // ajusta dias negativos
    if(dma.qtdDias < 0){

        if(mesAnterior == 4 || mesAnterior == 6 ||
           mesAnterior == 9 || mesAnterior == 11)
        {
            dma.qtdDias += 30;
        }

        else if(mesAnterior == 2){

            if(eAnoBissexto(anoAnterior))
                dma.qtdDias += 29;
            else
                dma.qtdDias += 28;
        }

        else{
            dma.qtdDias += 31;
        }

        dma.qtdMeses--;
    }

    // ajusta meses negativos
    if(dma.qtdMeses < 0){
        dma.qtdMeses += 12;
        dma.qtdAnos--;
    }

    return dma;
}

int CalcTamStr(char str[])
{
    int iCont;
    int tamanho = 0;

    for(iCont = 0; str[iCont] != '\0'; iCont++){
        if(str[iCont] == -61)
            iCont++;

        tamanho++;
    }

    return tamanho;
}

int CalcRazao10(int num)
{
    int Razao10 = 1;

    while(num >= 10){
        num = num / 10;
        Razao10 = Razao10 * 10;
    }

    return Razao10;
}

int VerificarAcima(char matriz[8][10], char palavra[6], int lin, int col, int indice)
{
    if(palavra[indice] == '\0')
        return 1;

    if(!ePosicaoValida(lin, col))
        return 0;

    if(matriz[lin][col] != palavra[indice])
        return 0;

    return VerificarAcima(matriz, palavra, lin - 1, col, indice + 1);
}

int VerificarAbaixo(char matriz[8][10], char palavra[6], int lin, int col, int indice)
{
    if(palavra[indice] == '\0')
        return 1;

    if(!ePosicaoValida(lin, col))
        return 0;

    if(matriz[lin][col] != palavra[indice])
        return 0;

    return VerificarAbaixo(matriz, palavra, lin + 1, col, indice + 1);
}

int VerificarEsquerda(char matriz[8][10], char palavra[6], int lin, int col, int indice)
{
    if(palavra[indice] == '\0')
        return 1;

    if(!ePosicaoValida(lin, col))
        return 0;

    if(matriz[lin][col] != palavra[indice])
        return 0;

    return VerificarEsquerda(matriz, palavra, lin, col - 1, indice + 1);
}

int VerificarDireita(char matriz[8][10], char palavra[6], int lin, int col, int indice)
{
    if(palavra[indice] == '\0')
        return 1;

    if(!ePosicaoValida(lin, col))
        return 0;

    if(matriz[lin][col] != palavra[indice])
        return 0;

    return VerificarDireita(matriz, palavra, lin, col + 1, indice + 1);
}

int VerificarDiagonalSupEsq(char matriz[8][10], char palavra[6], int lin, int col, int indice)
{
    if(palavra[indice] == '\0')
        return 1;

    if(!ePosicaoValida(lin, col))
        return 0;

    if(matriz[lin][col] != palavra[indice])
        return 0;

    return VerificarDiagonalSupEsq(matriz, palavra, lin - 1, col - 1, indice + 1);
}

int VerificarDiagonalSupDir(char matriz[8][10], char palavra[6], int lin, int col, int indice)
{
    if(palavra[indice] == '\0')
        return 1;

    if(!ePosicaoValida(lin, col))
        return 0;

    if(matriz[lin][col] != palavra[indice])
        return 0;

    return VerificarDiagonalSupDir(matriz, palavra, lin - 1, col + 1, indice + 1);
}

int VerificarDiagonalInfEsq(char matriz[8][10], char palavra[6], int lin, int col, int indice)
{
    if(palavra[indice] == '\0')
        return 1;

    if(!ePosicaoValida(lin, col))
        return 0;

    if(matriz[lin][col] != palavra[indice])
        return 0;

    return VerificarDiagonalInfEsq(matriz, palavra, lin + 1, col - 1, indice + 1);
}

int VerificarDiagonalInfDir(char matriz[8][10], char palavra[6], int lin, int col, int indice)
{
    if(palavra[indice] == '\0')
        return 1;

    if(!ePosicaoValida(lin, col))
        return 0;

    if(matriz[lin][col] != palavra[indice])
        return 0;

    return VerificarDiagonalInfDir(matriz, palavra, lin + 1, col + 1, indice + 1);
}

int ePosicaoValida(int lin, int col)
{
    if(lin < 0 || lin >= 8)
        return 0;

    if(col < 0 || col >= 10)
        return 0;

    return 1;
}