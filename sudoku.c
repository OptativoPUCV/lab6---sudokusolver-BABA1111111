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
   for (int i = 0; i < 9; i++){
      int fil[10] = {0};
      for (int j = 0; j < 9; j++){
         int num = n->sudo[i][j];
         if (num != 0){
            if (fil[num] == 1){
               return 0;
            }
            fil[num] = 1;
         }
      }
   }
   
   for (int j = 0; j < 9; j++){
      int col[10] = {0};
      for (int i = 0; i < 9; i++){
         int num = n->sudo[i][j];
         if (num != 0){
            if (col[num] == 1){
               return 0;
            }
            col[num] = 1;
         }
      }
   }
   for (int subFil = 0; subFil < 3; subFil++){
      for (int subCol = 0; subCol < 3; subCol++){
         int sub[10] = {0};

         for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3;j++){
               int num = n->sudo[subFil * 3 + i][subCol * 3 + j];
               if (num != 0){
                  if (sub[num] == 1){
                     return 0;
                  }
                  sub[num] = 1;
               }
            }
         }
      }
   }
   return 1;
}


List* get_adj_nodes(Node* n){
   List* list=createList();

   int fil = -1, col = -1;
   
   for (int i = 0; i < 9 && fil == -1; i++){
      for (int j = 0; j < 9 && col == -1; j++){
         if (n->sudo[i][j] == 0){
            fil = i;
            col = j;
            break;
         }
      }
   }

   if (fil == -1 && col == -1){
      return list;
   }

   for(int num = 1; num <= 9; num++){
      Node* newNode = copy(n);

      newNode->sudo[fil][col] = num;
      if (is_valid(newNode)){
         pushBack(list, newNode);
      }
      else{
         free(newNode);
      }
   }

    return list;
}


int is_final(Node* n){
   for (int i = 0; i < 9; i++){
      for (int j = 0; j < 9; j++){
         if (n->sudo[i][j] == 0){
            return 0;
         }
      }
   }
   
   return 1;
}

Node* DFS(Node* initial, int* cont){
   // Cree un stack S (pila) e inserte el nodo.
   // Mientras el stack S no se encuentre vacío:
   // a) Saque y elimine el primer nodo de S.
   // b) Verifique si corresponde a un estado final, si es así retorne el nodo.
   // c) Obtenga la lista de nodos adyacentes al nodo.
   // d) Agregue los nodos de la lista (uno por uno) al stack S.
   // e) Libere la memoria usada por el nodo.
   // Si terminó de recorre el grafo sin encontrar una solución, retorne NULL.
   // Almacene en la variable cont, la cantidad de iteraciones que realiza el algoritmo.
   // Puede ver un código de ejemplo en las diapos.
   // Recuerde revisar las operaciones del TDA Stack en el archivo list.h.

   Stack* stack = createStack();
   push(stack, initial);
   *cont = 0;

   while(!is_empty(stack)){
      Node* current = top(stack);
      pop(stack);
      (*cont)++;

      if (is_final(current)){
         return current;
      }
      List* adjNodes =  get_adj_nodes(current);
      Node* nodeAdj;

      while((nodeAdj = first(adjNodes)) !=  NULL){
         push(stack, nodeAdj);
         popFront(adjNodes);
      }
      
   }
   
  return NULL;
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