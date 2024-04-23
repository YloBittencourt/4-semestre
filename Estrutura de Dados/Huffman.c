#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Estrutura para representar um nó da árvore de Huffman
struct Node {
  char data;
  int freq;
  struct Node *left, *right;
};

// Função para criar um novo nó
struct Node *novoNo(char data, int freq) {
  struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
  temp->left = temp->right = NULL;
  temp->data = data;
  temp->freq = freq;
  return temp;
}

// Função para imprimir códigos binários
void imprimirCodigos(struct Node *raiz, int arr[], int topo) {
  if (raiz->left) {
    arr[topo] = 0;
    imprimirCodigos(raiz->left, arr, topo + 1);
  }

  if (raiz->right) {
    arr[topo] = 1;
    imprimirCodigos(raiz->right, arr, topo + 1);
  }

  if (!(raiz->left) && !(raiz->right)) {
    printf("%c: %d vezes - ", raiz->data, raiz->freq);
    for (int i = 0; i < topo; ++i) {
      printf("%d", arr[i]);
    }
    printf("\n");
  }
}

// Função para codificar a entrada de texto
void codificarTexto(char entrada[], struct Node *raiz, char codigos[][MAX],
                    int arr[], int topo) {
  if (raiz->left) {
    arr[topo] = 0;
    codificarTexto(entrada, raiz->left, codigos, arr, topo + 1);
  }

  if (raiz->right) {
    arr[topo] = 1;
    codificarTexto(entrada, raiz->right, codigos, arr, topo + 1);
  }

  if (!(raiz->left) && !(raiz->right)) {
    int i = 0;
    while (codigos[raiz->data - 'a'][i] != '\0') {
      i++;
    }

    for (int j = 0; j < topo; ++j) {
      codigos[raiz->data - 'a'][i++] = arr[j] == 0 ? '0' : '1';
    }
    codigos[raiz->data - 'a'][i] = '\0';
  }
}

// Função principal para construir a árvore de Huffman
struct Node *construirArvoreHuffman(char data[], int freq[], int tamanho) {
  struct Node *esquerda, *direita, *topo;

  // Cria uma fila de prioridade mínima
  struct Node *minHeap[tamanho];
  int tamanhoFila = tamanho;

  for (int i = 0; i < tamanho; ++i) {
    minHeap[i] = novoNo(data[i], freq[i]);
  }

  while (tamanhoFila > 1) {
    esquerda = minHeap[0];
    direita = minHeap[1];

    // Remove os dois nós mínimos e cria um novo nó interno
    topo = novoNo('$', esquerda->freq + direita->freq);
    topo->left = esquerda;
    topo->right = direita;

    // Adiciona o novo nó à fila de prioridade
    minHeap[0] = topo;
    for (int i = 1; i < tamanhoFila - 1; ++i) {
      minHeap[i] = minHeap[i + 1];
    }

    tamanhoFila--;
  }

  // O nó restante é a raiz da árvore de Huffman
  return minHeap[0];
}

// Função principal
int main() {
  // Solicitar entrada de texto
  char entrada[MAX];
  printf("Digite uma linha de texto (sem acento e sem pontuacao): ");
  scanf("%s", entrada);

  // Calcular a frequência dos caracteres na entrada
  int frequencias[26] = {0};
  for (int i = 0; entrada[i] != '\0'; ++i) {
    frequencias[entrada[i] - 'a']++;
  }

  // Construir a árvore de Huffman
  int tamanho = 0;
  for (int i = 0; i < 26; ++i) {
    if (frequencias[i] > 0) {
      tamanho++;
    }
  }

  char caracteres[tamanho];
  int frequenciasFiltradas[tamanho];
  int indice = 0;

  for (int i = 0; i < 26; ++i) {
    if (frequencias[i] > 0) {
      caracteres[indice] = 'a' + i;
      frequenciasFiltradas[indice] = frequencias[i];
      indice++;
    }
  }

  struct Node *raiz =
      construirArvoreHuffman(caracteres, frequenciasFiltradas, tamanho);

  // Imprimir os códigos binários
  int arr[tamanho], topo = 0;
  imprimirCodigos(raiz, arr, topo);

  // Codificar a entrada de texto
  char codigos[26][MAX];
  for (int i = 0; i < 26; ++i) {
    codigos[i][0] = '\0';
  }

  codificarTexto(entrada, raiz, codigos, arr, topo);

  // Mostrar a entrada de texto codificada
  printf("Entrada de texto codificada: ");
  for (int i = 0; entrada[i] != '\0'; ++i) {
    printf("%s", codigos[entrada[i] - 'a']);
  }
  printf("\n");

  return 0;
}
