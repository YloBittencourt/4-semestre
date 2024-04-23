#include <stdio.h>
#include <stdlib.h>

// Estrutura para um nó da fila
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Estrutura para a fila conforme o slide
typedef struct {
    Node* front; //Ponteiro para o primeiro nó da fila
    Node* rear; //Ponteiro para o último nó da fila
} Queue;

// Função para criar uma nova fila
Queue* criarQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue)); // Aloca memória para a fila
    //Inicializar o ponteiro do início e fim como NULL
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Função para enfileirar um elemento na fila
void enqueue(Queue* queue, int x) {
    Node* novoNode = (Node*)malloc(sizeof(Node)); // Aloca memória para um novo nó
    novoNode->data = x; // Define o valor do nó como x
    novoNode->next = NULL; // Define o próximo nó como NULL, pois ele será o último

  // Se a fila estiver vazia, o novo nó será tanto o início quanto o fim
  // Caso contrário, atualiza o próximo nó do nó atual (no fim) para o novo nó
    if (queue->rear == NULL) {
        queue->front = novoNode;
        queue->rear = novoNode;
    } else {
        queue->rear->next = novoNode;
        queue->rear = novoNode;
    }
}

// Função para desenfileirar o elemento de maior valor da fila
void dequeue(Queue* queue) {
    if (queue->front == NULL) {
        return; // Se a fila estiver vazia, não há nada para desenfileirar
    }

    int max = queue->front->data; // Inicializa o valor máximo com o valor do primeiro nó
    Node* procura = queue->front; // Começa a partir do primeiro nó
    Node* anterior = NULL; // Ponteiro para o nó anterior
    Node* maxNode = queue->front; // Inicializa o nó com o valor máximo
    Node* anteriorMaxNode = NULL; // Ponteiro para o nó anterior ao nó com o valor máximo

  // Percorrer a fila para encontrar o elemento de maior valor
    while (procura != NULL) {
        if (procura->data > max) {
            max = procura->data;
            maxNode = procura;
            anteriorMaxNode = anterior;
        }
        anterior = procura;
        procura = procura->next;
    }

  // Remove o nó com o valor máximo da fila
    if (anteriorMaxNode == NULL) {
        queue->front = maxNode->next;
    } else {
        anteriorMaxNode->next = maxNode->next;
    }

    if (maxNode == queue->rear) {
        queue->rear = anteriorMaxNode;
    }

    free(maxNode); // Libera a memória do nó com valor máximo
}

// Função para exibir o estado da fila
void display(Queue* queue) {
    Node* procura = queue->front;
    while (procura != NULL) {
        printf("%d ", procura->data);
        procura = procura->next;
    }
    printf("\n");
}

int main() {
    Queue* personalizarQueue = criarQueue();
    char op;
    int x;

  // Loop para ler operações e executar ações correspondentes
    while (1) {
        printf("\nOperação: ");
        scanf(" %c", &op);
        if (op == '-') { // Se a operação for '-', vai mostrar o resultado final e encerrar
            printf("Resultado final: ");
            display(personalizarQueue); //Exibe o estado final da fila
            break;
        }
        if (op == 'E'|| op == 'e') {
            scanf("%d", &x);
            enqueue(personalizarQueue, x); // Enfileira o elemento x
        } else if (op == 'D' || op == 'd') {
            dequeue(personalizarQueue);  // Desenfileira o elemento de maior valor
          printf("\n");
        }
        printf("Resultado: ");
        display(personalizarQueue); // Exibe o estado da fila após cada operação
    }

    // Liberar memória da fila
    Node* procura = personalizarQueue->front;
    while (procura != NULL) {
        Node* temp = procura;
        procura = procura->next;
        free(temp);
    }
    free(personalizarQueue);

    return 0;
}


