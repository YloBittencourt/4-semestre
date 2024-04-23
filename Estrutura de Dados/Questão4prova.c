#include <stdio.h>
#include <stdlib.h>
// Estruturas e funções (slide)
struct elemento {
  int valor;
  struct elemento *prox;
};

typedef struct elemento No;
typedef struct elemento *Pno;

/* Percorre e imprime a lista. Recebe o início da lista */
void mostrarLista(Pno inicio) {
  Pno atual = inicio;
  do {
    printf("%d ", atual->valor);
    atual = atual->prox;
  } while (atual != inicio);
  printf("\n");
}

/* Recebe dados (valor) e retorna um elemento com esse dado */
Pno criaElemento(int valor) {
  Pno novo;
  novo = (Pno)malloc(sizeof(No));

  novo->valor = valor;
  novo->prox = NULL;

  return novo;
}

/* Verifica se a lista está vazia. Se estiver, retorna 1; caso contrário, retorna 0. */
int vazia(Pno inicio) {
  if (inicio == NULL)
    return 1;
  else
    return 0;
}

/* Função para inserir um nó no início da lista, mantendo a propriedade circular*/
void insereInicio(Pno *inicio, Pno *novo) {
  Pno ultimo = *inicio;

  if (vazia(*inicio)) {
    *inicio = *novo;
    (*inicio)->prox = *inicio; // mantêm a propriedade circular
  } else {
    (*novo)->prox = *inicio;

    // Encontra o último elemento
    while (ultimo->prox != *inicio)
      ultimo = ultimo->prox;

    *inicio = *novo;
    ultimo->prox = *novo; // mantêm a propriedade circular
  }
}
//Função para deslocar o no conforme a posição desejada
Pno deslocar(Pno inicio, int i) {
  if (vazia(inicio) || inicio->prox == inicio) {
    return inicio;
  }

  Pno atual = inicio;
  Pno anterior = NULL;
//Como o primeiro elemento deve ser representado pela posição 0, criei uma condição caso i seja igual a zero para não haver bug
  if (i == 0) {
    Pno primeiro = inicio;
    Pno segundo = inicio->prox;

    while (atual->prox != inicio) {
      atual = atual->prox; // vai até o último
    }

    inicio = segundo;      // o primeiro passa a ser o segundo
    atual->prox = segundo; // o último aponta para o segundo
    primeiro->prox = segundo->prox; // o primeiro aponta para o próximo do segundo
    segundo->prox = primeiro; // o segundo aponta para o primeiro

    return inicio;
  } else {
    int contador = 0;
    while (contador < i) {
      anterior = atual;
      atual = atual->prox;
      contador++; // vai incrementando até o contador ser igual à posição desejada para sair da condição
    }

    Pno proximo = atual->prox;

    if (proximo != inicio) {
      // Se o próximo nó não for o início, troque o nó atual com o próximo nó
      if (anterior != NULL) {
        anterior->prox = proximo;
      }
      atual->prox = proximo->prox;
      proximo->prox = atual;
    } else {
      // A posição i é a última, a lista então permanece a mesma, pois não tem posição a frente
    }

    return inicio;
  }
}


int main() {
  Pno inicio = NULL;

  // Inserir alguns elementos na lista (exemplo a lista da prova), mas funciona com 2,3 ou n elementos, pode remover 1 ou 2 dessas opções para testar
  Pno novo1 = criaElemento(22);
  Pno novo2 = criaElemento(21);
  Pno novo3 = criaElemento(20);
  Pno novo4 = criaElemento(10);

  // Chamar a função para inserir no início da lista
  insereInicio(&inicio, &novo1);
  insereInicio(&inicio, &novo2);
  insereInicio(&inicio, &novo3);
  insereInicio(&inicio, &novo4);

  // Mostrar a lista original primeiro
  printf("Lista original: ");
  mostrarLista(inicio);

  int posicao; // Nova variável para saber a posição que foi desejada a ser trocada
  printf("Posição para mover: ");
  scanf("%d", &posicao);
  inicio = deslocar(inicio, posicao);

  printf("Lista após mover o nó da posição %d para frente: ", posicao);
  mostrarLista(inicio); // mostrar a lista após a mudança

  return 0;
}
//Deve-se deslocar a posição para frente, e não o apontamento do ponteiro (->proximo ou ->anterior), pelo o que entendi, então caso a posição for a última a lista permanece inalterada
//Posição 0 = primeiro elemento : 10 20 21 22 -> 20 10 21 22 (o primeiro passa a ser o segundo)
//Posição 1 = segundo elemento : 10 20 21 22 -> 10 21 20 22 (o segundo para a ser o terceiro)
//Posição 2 = terceiro elemento: 10 20 21 22 -> 10 20 22 21 (o terceiro passa a ser o quarto)
//Posição 3 = quarto elemento: 10 20 21 22 -> 10 20 21 22 (inalterada)