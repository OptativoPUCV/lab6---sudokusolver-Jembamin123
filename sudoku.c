#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){  
  int filas[9][10]={{0}};
  int columnas[9][10]={{0}};
  int submatrices[3][3][10]={{{0}}};
  
  for(int fila = 0; fila < 9; fila++) {
    for(int col = 0; col < 9; col++) {
      int num = n->sudo[fila][col];
      if(num < 1 || num > 9) {
        return 0;
      }
      if(filas[fila][num]==1 || columnas[col][num]==1 || submatrices[fila/3][col/3][num]==1){
        return 0;
      }
      filas[fila][num]=1;
      columnas[col][num]=1;
      submatrices[fila/3][col/3][num]=1;
    }
  }
  return 1;
}



List* get_adj_nodes(Node* n){
  List* list=createList();
  for(int fil=0; fil<9; fil++){
    for(int col=0; col<9; col++){
      if(n->sudo[fil][col] == 0){
        for(int num=1; num<=9; num++){
          Node* adNodo=createNode();
          for(int i=0; i<9; i++){
            for(int j=0; j<9; j++){
              adNodo->sudo[i][j]=n->sudo[i][j];
            }
          }
          adNodo->sudo[fil][col]=num;
          pushBack(list,adNodo);
        }
      }
    }
  }
  return list;
}


int is_final(Node* n){
  for(int fila=0; fila<9; fila++){
    for(int col=0; col<9; col++){
      if(n->sudo[fila][col] == 0){
        return 0;
      }
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){

  if(is_final(initial)){
    return initial;
  }
  
  List* ad=get_adj_nodes(initial);
  Node* resultado=NULL;

  for(Node* adyacente = first(ad); adyacente!=NULL; adyacente=next(ad)){
    if(is_valid(adyacente)){
      resultado = DFS(adyacente, cont);
      if(resultado != NULL){
        break;  
      }
    }
  }
  if(initial==NULL){
    return NULL;
  }
  return resultado;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/