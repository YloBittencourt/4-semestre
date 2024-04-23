#include <stdio.h>
#include <stdlib.h>

// Estrutura para um n� da fila
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Estrutura para a fila conforme o slide
typedef struct {
    Node* front; //Ponteiro para o primeiro n� da fila
    Node* rear; //Ponteiro para o �ltimo n� da fila
} Queue;

// Fun��o para criar uma nova fila
Queue* criarQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue)); // Aloca mem�ria para a fila
    //Inicializar o ponteiro do in�cio e fim como NULL
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Fun��o para enfileirar um elemento na fila
void enqueue(Queue* queue, int x) {
    Node* novoNode = (Node*)malloc(sizeof(Node)); // Aloca mem�ria para um novo n�
    novoNode->data = x; // Define o valor do n� como x
    novoNode->next = NULL; // Define o pr�ximo n� como NULL, pois ele ser� o �ltimo

  // Se a fila estiver vazia, o novo n� ser� tanto o in�cio quanto o fim
  // Caso contr�rio, atualiza o pr�ximo n� do n� atual (no fim) para o novo n�
    if (queue->rear == NULL) {
        queue->front = novoNode;
        queue->rear = novoNode;
    } else {
        queue->rear->next = novoNode;
        queue->rear = novoNode;
    }
}

// Fun��o para desenfileirar o elemento de maior valor da fila
void dequeue(Queue* queue) {
    if (queue->front == NULL) {
        return; // Se a fila estiver vazia, n�o h� nada para desenfileirar
    }

    int max = queue->front->data; // Inicializa o valor m�ximo com o valor do primeiro n�
    Node* procura = queue->front; // Come�a a partir do primeiro n�
    Node* anterior = NULL; // Ponteiro para o n� anterior
    Node* maxNode = queue->front; // Inicializa o n� com o valor m�ximo
    Node* anteriorMaxNode = NULL; // Ponteiro para o n� anterior ao n� com o valor m�ximo

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

  // Remove o n� com o valor m�ximo da fila
    if (anteriorMaxNode == NULL) {
        queue->front = maxNode->next;
    } else {
        anteriorMaxNode->next = maxNode->next;
    }

    if (maxNode == queue->rear) {
        queue->rear = anteriorMaxNode;
    }

    free(maxNode); // Libera a mem�ria do n� com valor m�ximo
}

// Fun��o para exibir o estado da fila
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

  // Loop para ler opera��es e executar a��es correspondentes
    while (1) {
        printf("\nOpera��o: ");
        scanf(" %c", &op);
        if (op == '-') { // Se a opera��o for '-', vai mostrar o resultado final e encerrar
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
        display(personalizarQueue); // Exibe o estado da fila ap�s cada opera��o
    }

    // Liberar mem�ria da fila
    Node* procura = personalizarQueue->front;
    while (procura != NULL) {
        Node* temp = procura;
        procura = procura->next;
        free(temp);
    }
    free(personalizarQueue);

    return 0;
}


