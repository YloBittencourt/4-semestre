#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um nó da árvore (parecido com o slide, adicionei cpf e nome)
typedef struct No {
  int cpf;
  char nome[100];
  struct No *esquerda;
  struct No *direita;
} No;

// Função para criar um novo nó (const no nome para impedir que o conteúdo seja alterado dentro da função)
No *criarNo(int cpf, const char *nome) {
  // Aloca memória para o novo nó
  No *novoNo = (No *)malloc(sizeof(No));
  // Define os valores do nó com base nos parâmetros
  novoNo->cpf = cpf;
  int i = 0;
  // Copia o nome para o nó, caractere por caractere
  while (nome[i] != '\0' && i < 99) {
    novoNo->nome[i] = nome[i];
    i++;
  }
  novoNo->nome[i] = '\0';
  // Inicializa os ponteiros esquerda e direita como NULL
  novoNo->esquerda = novoNo->direita = NULL;
  // Retorna o novo nó
  return novoNo;
}

// Função para inserir um nó na árvore
No *inserir(No *raiz, int cpf, const char *nome) {
  if (raiz == NULL) {
    return criarNo(cpf, nome);
  }
  // Decide se o novo nó vai para a esquerda ou direita (se for menor vai para a esquerda, se for maior, direita)
  if (cpf < raiz->cpf) {
    raiz->esquerda = inserir(raiz->esquerda, cpf, nome);
  } else if (cpf > raiz->cpf) {
    raiz->direita = inserir(raiz->direita, cpf, nome);
  }
  return raiz;
}

// Função para buscar um nó na árvore e imprimir o nome e o nível
int buscar(No *raiz, int cpf, int nivel) {
  if (raiz == NULL) {
    return -1; 
  }
  // Se o CPF for igual ao CPF do nó atual, imprime o nome e retorna o nível conforme pedido
  if (cpf == raiz->cpf) {
    printf("%s %d\n", raiz->nome, nivel);
    return nivel;
  }
  // Decide se a busca continua na subárvore esquerda ou direita(dependendo se for menor(esquerda) ou maior(direita) da raiz)
  if (cpf < raiz->cpf) {
    return buscar(raiz->esquerda, cpf, nivel + 1);
  } else {
    return buscar(raiz->direita, cpf, nivel + 1);
  }
}

// Função para liberar a memória alocada para a árvore
void liberarArvore(No *raiz) {
  if (raiz != NULL) {
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
  }
}

int main() {
  int N;
  int cpf;
  char nome[100], op;
  int nivel;
  
  scanf("%d", &N);

  No *raiz = NULL;

  // Loop para processar cada ação
  for (int i = 0; i < N; i++) {
    // Leitura da operação, CPF e, se for uma inserção, o nome
    scanf(" %c %d", &op, &cpf);
    if (op == 'I') { //se a opção for para inserir:
      scanf("%s", nome);
      raiz = inserir(raiz, cpf, nome);
    } else if (op == 'B') {
      // Se for uma busca, chama a função de busca e imprime o resultado
      nivel = buscar(raiz, cpf, 1);
      // A função de busca sempre retorna o nível
    }
  }
  // Libera a memória
  liberarArvore(raiz);

  return 0;
}
/*
No slide da questão o exemplo de saida tem o n = 5 porém tem 7 iterações, no exemplo com n = 5 ele vai ler:
5
I 12345
Jacqueline
I 2345
Olivia
I 56789
Maju
B 12345
B 56789

E vai sair:
Jacqueline 1
Maju 2

Para o exemplo pedido no slide o nivel de iterações tem que ser 7, ou seja, N = 7
*/