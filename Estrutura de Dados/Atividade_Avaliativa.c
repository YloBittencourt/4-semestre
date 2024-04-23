#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct elemento {
    int valor;
    struct elemento* prox;
};
typedef struct elemento No;
typedef struct elemento* Pno;

/* Função para criar um novo nó com o valor especificado */
Pno criaElemento(int valor) {
    Pno novo;
    novo = (Pno)malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = NULL;
    return novo;
}

/* Função para empilhar um valor na pilha */
void push(Pno* inicio, int valor) {
    Pno novo = criaElemento(valor);
    novo->prox = *inicio;
    *inicio = novo;
}

/* Função para desempilhar um valor da pilha */
int pop(Pno* inicio) {
    if (*inicio == NULL) {
        printf("Erro: Pilha vazia\n");
        exit(1);
    }
    Pno temp = *inicio;
    *inicio = (*inicio)->prox;
    int value = temp->valor;
    free(temp);
    return value;
}

int main() {
    int N;
    while (1) {
        scanf("%d", &N);
        if (N == 0) {
            break; // Encerra o programa quando N for 0
        }

        Pno stack = NULL; // Inicializa a pilha

        for (int i = 0; i < N; i++) {
            char instruction[10];
            scanf("%s", instruction);

            if (strcmp(instruction, "BIPUSH") == 0) {
                int value;
                scanf("%d", &value);
                push(&stack, value); // Empilha o valor K
            } else if (strcmp(instruction, "IADD") == 0) {
                int a = pop(&stack);
                int b = pop(&stack);
                push(&stack, a + b); // Remove dois valores da pilha e empilha sua soma
            } else if (strcmp(instruction, "ISUB") == 0) {
                int a = pop(&stack);
                int b = pop(&stack);
                push(&stack, b - a); // Remove dois valores da pilha e empilha a subtração do primeiro pelo segundo
            } else if (strcmp(instruction, "IMUL") == 0) {
                int a = pop(&stack);
                int b = pop(&stack);
                push(&stack, a * b); // Remove dois valores da pilha e empilha o produto
            }
        }

        printf("%d\n", pop(&stack)); // Imprime o valor no topo da pilha após a execução das instruções
    }

    return 0;
}

