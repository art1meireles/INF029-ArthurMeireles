#include <stdio.h>

#define LIMITE 100000

void subnumeros(int numero) {

    int flag[LIMITE] = {0};
    int digitos[5];
    int tam, ini, i, valor;

    for (i = 4; i >= 0; i--) {
        digitos[i] = numero % 10;
        numero = numero / 10;
    }

    for (tam = 1; tam <= 5; tam++) {
        for (ini = 0; ini + tam <= 5; ini++) {

            valor = 0;

            for (i = ini; i < ini + tam; i++)
                valor = valor * 10 + digitos[i];

            flag[valor]++;
        }
    }

    for (valor = 0; valor < LIMITE; valor++) {

        if (flag[valor] == 1)
            printf("%d - 1 vez; ", valor);

        else if (flag[valor] > 1)
            printf("%d - %d vezes; ", valor, flag[valor]);
    }

    printf("\n");
}

int main() {

    int numero;

    printf("Digite um numero de 5 digitos: ");
    scanf("%d", &numero);

    subnumeros(numero);

    return 0;
}