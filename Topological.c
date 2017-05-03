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
void dfs(graph* G, int vertice, stack* sta);
void push(stack* sta, int value);
int pop(stack* sta);
void topSort(graph* G, stack* sta, int quant_vertice);
void createDepend(graph* G, int dependencias);

//---------------------------------------------------


graph* create_graph(int quant_vertice){
  int i;
  // Alocando o Grafo.
  graph* G = (graph*) calloc(1, sizeof(graph));
  // Alocando o array das visitas.
  G->visited = (int*) calloc(quant_vertice, sizeof(int));
  // Alocando o array de ponteiro para as listas.
  G->Vert = (node**) calloc(quant_vertice, sizeof(node*));
  // inicializando o array de visitas com 0 e o array de ponteiros para os nodes.
  for (i = 0; i < quant_vertice; i ++){
    G->visited[i] = 0;
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


void dfs(graph* G, int vert_inicial, stack* sta){

  G->visited[vert_inicial] = 1;
  node* aux = G->Vert[vert_inicial];

    while (aux != NULL){
      if(G->visited[aux->dado] == 0){
        dfs(G, aux->dado, sta);
      }
      aux = aux->next;
    }

  G->visited[vert_inicial] = 2;
  push(sta, vert_inicial);

};


void topSort(graph* G, stack* sta, int quant_vertice){

  int i, topSort;

  for(i = 0; i < quant_vertice; i ++){
    if (G->visited[i] == 0){
      dfs(G, i, sta);
    }
  }

  for (i = 0; i < sta->quant_no; i ++){
    topSort = pop(sta);
    printf("%d%c", topSort, i < sta->quant_no - 1 ? ' ' : '\n');
  }

}


void createDepend(graph* G, int dependencias){

    int vertice1, vertice2, i;

    for(i=0 ; i < dependencias ; i++){
	    scanf("%d %d",&vertice1, &vertice2);
	    add_vertice(G, vertice1, vertice2);
    }

}


int pop(stack* sta){

  int vertice = sta->top->dado;

  node* n = sta->top;
  sta->top = sta->top->next;

  free(n);

  return vertice;

}



int main(){

  int quant_vertice, dependencias;
  scanf("%d %d", &quant_vertice, &dependencias);

  graph* G = create_graph(quant_vertice);
  stack* sta = create_stack();

  createDepend(G, dependencias);
  topSort(G, sta, quant_vertice);

    return 0;
}
