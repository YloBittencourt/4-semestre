#include <stdio.h>
#include <stdlib.h>

// Defini��o da estrutura do n� da lista (conforme um exemplo do slide)
struct elemento {
    int valor;
    struct elemento *prox;
};
typedef struct elemento No;
typedef struct elemento *Pno;

// Fun��o para criar um novo n� (slide)
Pno criaelemento(int valor) {
    Pno novo;
    novo = (Pno)malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = NULL;
    return novo;
}

// Fun��o para verificar se a lista est� vazia (slide)
int vazia(Pno inicio) {
    if (inicio == NULL)
        return 1;
    else
        return 0;
}

// Fun��o para inserir um novo n� no in�cio da lista (slide)
void insereinicio(Pno *inicio, Pno novo) {
    if (vazia(*inicio)) {
        *inicio = novo;
    } else {
        novo->prox = *inicio;
        *inicio = novo;
    }
}

// Fun��o para inserir um novo n� no final da lista (slide)
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

// Fun��o para exibir a lista (slide)
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
    char op; //op��o
    int valor; //valor

    while (scanf("%d", &qnt)){ //vai ler a quantidade
        Pno lista = NULL; //iniciar a lista com NULL
        if(qnt == 0) break; //condi��o de caso for zero parar o programa

        while (qnt) {
            scanf(" %c %d", &op, &valor); //ler a op��o de ser primeiro ou ultimo e o valor a ser colocado, na mesma linha
            Pno novo = criaelemento(valor); // chamada da fun��o criarelemento

            if (op == 'P' || op == 'p') { //caso a op��o seja primeiro, inserir no inicio
                insereinicio(&lista, novo);
            } else if (op == 'U' || op == 'u') { //caso a op��o seja ultimo, inserir no fim
                inserefim(&lista, novo);
            }
            qnt--; //vai diminuindo a quantidade at� chegar no zero
        }

        mostrarlista(lista); //chamada da fun��o mostrarlista
    }

    return 0;
}


