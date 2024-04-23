#include <stdio.h>
#include <stdlib.h>

//Criando o struct dos amigos
struct elemento{
    int val;
    struct elemento *prox;
    struct elemento *ant;
};

//Declarando o protótipo da função de criar lista
struct elemento *criaLista(struct elemento *inicio_lista, int x);
//Declarando o protótipo da função de remover da lista
struct elemento *removeDaLista(struct elemento *inicio_lista,int x,int y);
int main(void){

    int n;
    struct elemento *inicio_lista = NULL;

    scanf("%d",&n);

   //Verifico se o número dos casos de testes é diferente de 0 
    while(n!=0){

    int x,y;

    //Lendo o número de amigos e o número de saltos
    scanf("%d %d",&x,&y);
    //Verifico se o número de amigos é diferente de 0
    if(x!=1){

      //Chamando a função
     inicio_lista = criaLista(inicio_lista,x);
     inicio_lista = removeDaLista(inicio_lista,x,y);
     printf("%d\n",inicio_lista->val);
     free(inicio_lista);    
    } else{

        printf("%d\n",x);     
    }

    n--;
  }
    return 0;

}

struct elemento *criaLista(struct elemento *inicio_lista, int x){

    struct elemento *novo = (struct elemento*) malloc(sizeof(struct elemento));
    novo->val = 1;
    novo->prox = NULL;
    novo->ant = NULL;
    inicio_lista = novo;

    for(int i = 2;i<=x;i++){

        novo->prox = (struct elemento*) malloc(sizeof(struct elemento));
        novo->prox->ant = novo;
        novo = novo->prox;
        novo->val = i;
        novo->prox = NULL;
    }

    inicio_lista->ant = novo;
    novo->prox = inicio_lista;

    return inicio_lista;
}

struct elemento *removeDaLista(struct elemento *inicio_lista,int x, int y){


    int i = 1;
    struct elemento *aux = inicio_lista;
    struct elemento *aux2 = NULL;

    while(x!=1){

      while(i!=y){

        i++;
        aux = aux->prox;
    }

    aux->prox->ant = aux->ant;
    aux->ant->prox = aux->prox;
    aux2 = aux;
    aux = aux->prox;
    free(aux2);
    i = 1;
    x--;
    }

    //aux->prox = NULL;
   // aux->ant = NULL;

  return aux;

}
