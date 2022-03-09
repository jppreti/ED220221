#include <stdio.h>
#include <stdlib.h>

int main() {
    int number = 10;
    int *numberP = &number;
    printf("Valor da variável number: %d\n",number);
    printf("Endereço da variável number: %p\n",&number);
    printf("Valor da variável numberP: %p\n",numberP);
    printf("Valor apontado por numberP: %d\n\n",*numberP);

    printf("Mudando o valor de number de forma indireta\n\n");
    *numberP = 15;
    printf("Valor da variável number: %d\n",number);

    numberP++;
    printf("Valor da variável numberP: %p\n", numberP);
    printf("Valor no endereço apontado: %d\n", *numberP);

    float *pi = (float *) malloc(sizeof(float));
    printf("Valor da variável pi: %p\n", pi);
    *pi=3.1415;
    printf("Valor no endereço apontado: %f\n", *pi);
    free(pi);
    printf("Valor da variável pi: %p\n", pi);
    printf("Valor da variável apontada: %f\n", *pi);
    *pi = 0;
    pi = NULL;

    int *numbers = (int *) malloc(sizeof(int) * 3);
    *(numbers+0) = 1;
    *(numbers+1) = 2;
    *(numbers+2) = 3;
    
    for (int i = 0; i < 3; i++)
        printf("numbers[%d] = %d\n",i,numbers[i]);
    
    for (int i = 0; i < 3; i++)
        printf("*(numbers+%d) = %d\n",i,*(numbers+i));
    
    int *aux = numbers;
    for (int i = 0; i < 3; i++) {
        printf("aux = %d\n",*aux);
        aux++;
    }

    printf("Término do programa");

    return EXIT_SUCCESS;
}
