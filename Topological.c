/*
 * Topological.c
 *
 *  Created on: 9 de abr de 2017
 *      Author: Wagner
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Graph graph;
typedef struct Node node;
typedef struct Stack stack;


struct Stack {
  node* top;
  int quant_no;
};

struct Node {
  int dado;
  node* next;
};

struct Graph {
  int *visited;
  node **Vert;
};

// Funções~

graph* create_graph(int quant_vertice);
node* create_node(int value_vertice);
void add_vertice(graph* G, int vertice1, int vertice2);
void bfs(graph* G, int vertice, stack* sta);
void push(stack* sta, int value);

//---------------------------------------------------


graph* create_graph(int quant_vertice){
  int i;
  // Alocando o Grafo.
  graph* G = (graph*) calloc(quant_vertice, sizeof(graph));
  // Alocando o array das visitas.
  G->visited = (int*) calloc(quant_vertice, sizeof(int));
  // Alocando o array de ponteiro para as listas.
  G->Vert = (node**) calloc(quant_vertice, sizeof(node*));
  // inicializando o array de visitas com 0 e o array de ponteiros para os nodes.
  for (i = 0; i < quant_vertice; i ++){
    G->visited[i] = 0;
    G->Vert[i] = NULL;
    G->Vert[i] = NULL;
  }
  //Retornando o grafo com lista de adjacência.
  return G;
}

node* create_node(int value){
  // Alocando um nó que vai ser o futuro vertice.
  node* n = (node*) calloc(1, sizeof(node));
  // setando os valores da struct no.
  n->dado = value;
  n->next = NULL;

  return n;
}


stack* create_stack(){
  //Alocando a stack.
  stack* sta = (stack*) calloc(1, sizeof(stack));
  sta->top = NULL;
  sta->quant_no = 0;
  return sta;
}

void add_vertice(graph* G, int vertice1, int vertice2){
  // criando o vertice2.
  node* n = create_node(vertice2);
  int i;
  if(G->Vert[vertice1] == NULL){

    G->Vert[vertice1] = n;

  } else {

    node* aux = G->Vert[vertice1];
    for( ; aux->next != NULL ; aux = aux->next){
    }
    aux->next = n;
  }

}

void push(stack* sta, int value){
  node* no = create_node(value);
  if (!sta->quant_no){
    sta->top = no;
  } else {
    no->next = sta->top;
    sta->top = no;
  }
  sta->quant_no ++;
}


void print_stack(stack* sta){
  if(sta->quant_no){
    node* aux = sta->top;
    for (; aux != NULL ; aux = aux->next){
      printf("Topological order: %d\n", aux->dado);
    }
  }
}

int membro_stack(stack* sta, int value){


    node* aux = sta->top;
    if(sta->top == NULL){
      return 1;
    }

    for (; aux != NULL ; aux = aux->next){
      if (aux->dado == value){
        return 0;
      }
    }

    return 1;
}


void bfs(graph* G, int vert_inicial, stack* sta){

  G->visited[vert_inicial] = 1;
  node* aux = G->Vert[vert_inicial];
    while (aux != NULL){
      if(G->visited[aux->dado] != 1){
        bfs(G, aux->dado, sta);
      }
      aux = aux->next;
    }
  G->visited[vert_inicial] = 2;
  if(aux == NULL && membro_stack(sta, vert_inicial)){
    push(sta, vert_inicial);
  }

};


int main(){

  int quant_vertice, i, vertice1, vertice2;
  scanf("%d", &quant_vertice);

  graph* G = create_graph(quant_vertice);
  stack* sta = create_stack();

  for(i=0 ; i<quant_vertice ; i++){
	  scanf("%d %d",&vertice1, &vertice2);
	  add_vertice(G, vertice1, vertice2);
  }

  for(i = 0; i < quant_vertice; i ++){
    if (G->visited[i] == 0){
      bfs(G, i, sta);
    }
  }
  print_stack(sta);

  return 0;
}
