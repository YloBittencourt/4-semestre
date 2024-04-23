#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da lista (conforme um exemplo do slide)
struct elemento {
    int valor;
    struct elemento *prox;
};
typedef struct elemento No;
typedef struct elemento *Pno;

// Função para criar um novo nó (slide)
Pno criaelemento(int valor) {
    Pno novo;
    novo = (Pno)malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = NULL;
    return novo;
}

// Função para verificar se a lista está vazia (slide)
int vazia(Pno inicio) {
    if (inicio == NULL)
        return 1;
    else
        return 0;
}

// Função para inserir um novo nó no início da lista (slide)
void insereinicio(Pno *inicio, Pno novo) {
    if (vazia(*inicio)) {
        *inicio = novo;
    } else {
        novo->prox = *inicio;
        *inicio = novo;
    }
}

// Função para inserir um novo nó no final da lista (slide)
void inserefim(Pno *inicio, Pno novo) {
    Pno ultimo;
    if (vazia(*inicio)) {
        *inicio = novo;
    } else {
        ultimo = *inicio;
        while (ultimo->prox != NULL)
            ultimo = ultimo->prox;
        ultimo->prox = novo;
    }
}

// Função para exibir a lista (slide)
void mostrarlista(Pno inicio) {
    Pno atual;
    atual = inicio;
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->prox;
    }
    printf("\n");
}

int main() {
    int qnt; //quantidade
    char op; //opção
    int valor; //valor

    while (scanf("%d", &qnt)){ //vai ler a quantidade
        Pno lista = NULL; //iniciar a lista com NULL
        if(qnt == 0) break; //condição de caso for zero parar o programa

        while (qnt) {
            scanf(" %c %d", &op, &valor); //ler a opção de ser primeiro ou ultimo e o valor a ser colocado, na mesma linha
            Pno novo = criaelemento(valor); // chamada da função criarelemento

            if (op == 'P' || op == 'p') { //caso a opção seja primeiro, inserir no inicio
                insereinicio(&lista, novo);
            } else if (op == 'U' || op == 'u') { //caso a opção seja ultimo, inserir no fim
                inserefim(&lista, novo);
            }
            qnt--; //vai diminuindo a quantidade até chegar no zero
        }

        mostrarlista(lista); //chamada da função mostrarlista
    }

    return 0;
}


