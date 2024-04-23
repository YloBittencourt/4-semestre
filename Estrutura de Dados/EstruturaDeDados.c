#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defini��o da estrutura do n� da lista (conforme um exemplo do slide) - lista encadeada simples
struct elemento {
  int valor;
  struct elemento *prox;
};
typedef struct elemento No;
typedef struct elemento *Pno;

// Fun��o para criar um novo n� (slide)
Pno criaElemento(int valor) {
  Pno novo;
  novo = (Pno)malloc(sizeof(No));
  novo->valor = valor;
  novo->prox = NULL;
  return novo;
}

int vazia(Pno inicio) {
    if (inicio == NULL)
        return 1; // Retorna 1 se a pilha estiver vazia
    else
        return 0; // Retorna 0 se a pilha n�o estiver vazia
}


//Fun��o para empilhar um item na lista (slide)
void push(Pno *inicio, int valor) {
  Pno novo = criaElemento(valor); //chamada da fun��o criaElemento
  novo->prox = *inicio;
  *inicio = novo;
}

//Fun��o para desempilhar um item na lista (slide)
int pop(Pno *inicio) {
    if (vazia(*inicio)) {
        printf("Erro: Pilha vazia\n");
        exit(1);
    }
  Pno temp = *inicio;
  *inicio = (*inicio)->prox;
  int valor = temp->valor;
  free(temp);
  return valor;
}

int main() {
  int n;
  while (1) {
    scanf("%d", &n); //Ler a quantidade da sequ�ncia
    if (n == 0) {
      break; // Encerra o programa quando N for 0
    }

    Pno pilha = NULL; // Inicializando a pilha

    for (int i = 0; i < n; i++) {
      char op[10]; //a opera��o a ser feita (BIPUSH)
      scanf("%s", op);

      if (strcmp(op, "BIPUSH") == 0) { //Caso por BIPUSH
        int valor;
        scanf("%d", &valor); //ler o valor ap�s o BIPUSH
        push(&pilha, valor); //chamada da fun��o push
      } else if (strcmp(op, "IADD") == 0) { //Caso for IADD
        int a = pop(&pilha); //chamada da fun��o pop
        int b = pop(&pilha); //chamada da fun��o pop
        push(&pilha, a + b); //soma dos dois itens
      } else if (strcmp(op, "ISUB") == 0) { //caso for ISUB
        int a = pop(&pilha); //chamada da fun��o pop
        int b = pop(&pilha); //chamada da fun��o pop
        push(&pilha, a - b); //subtra��o de dois itens
      } else if (strcmp(op, "IMUL") == 0) { //caso for IMUL
        int a = pop(&pilha);
        int b = pop(&pilha);
        push(&pilha, a * b); //multiplica��o dos dois itens
      }
    }

    printf("%d\n", pop(&pilha)); //printar o valor final
  }

  return 0;
}
