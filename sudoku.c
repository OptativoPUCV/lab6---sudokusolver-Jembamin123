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

iint is_valid(Node* n, int fila, int col, int num) {
    // Verifica si el número num en la fila, columna y submatriz es válido
    int fil[10] = {0};
    int col[10] = {0};
    int submatriz[10] = {0};
    
    for (int i = 0; i < 9; i++) {
        // Verifica la fila
        if (n->sudo[fila][i] != 0) {
            if (fil[n->sudo[fila][i]] == 1) {
                return 0;
            }
            fil[n->sudo[fila][i]] = 1;
        }
        
        // Verifica la columna
        if (n->sudo[i][col] != 0) {
            if (col[n->sudo[i][col]] == 1) {
                return 0;
            }
            col[n->sudo[i][col]] = 1;
        }
        
        // Verifica la submatriz
        int subfila = 3 * (fila / 3) + i / 3;
        int subcol = 3 * (col / 3) + i % 3;
        if (n->sudo[subfila][subcol] != 0) {
            if (submatriz[n->sudo[subfila][subcol]] == 1) {
                return 0;
            }
            submatriz[n->sudo[subfila][subcol]] = 1;
        }
    }
    
    return 1;
}



List* get_adj_nodes(Node* n){
  List* list = createList();
  
  for(int fil=0; fil<9; fil++){
    for(int col=0; col<9; col++){
      if(n->sudo[fil][col] == 0){
        for(int num=1; num<=9; num++){
          Node* adj_node=copy(n);
          adj_node->sudo[fil][col]=num;
          if(is_valid(adj_node)){
            pushBack(list, adj_node);
          } 
          else{
            free(adj_node);
          }
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
/*
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
  */
  return 0;
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