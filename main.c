#include <stdio.h>

void menu (){
    int x;
    printf("Selecione um algoritmo: ");
    printf("1 - Algoritmo 1\n"); // Todo: Implementar algoritmo 1

    printf("Digite a opção desejada: ");
    scanf("%d", &x);
    switch (x) {
        case 1:
            printf("Algoritmo 1 selecionado.\n");
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }
}

int main() {
    int x;
    printf("Digite um número: ");
    scanf("%d", &x);
    printf("O número digitado foi: %d\n", x);
    return 0;
}