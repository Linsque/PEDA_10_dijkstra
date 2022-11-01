//Rafael Bonfim Zacco

/*
Sua  tarefa  será  construir  um  grafo,  com  20  vértices  cujos  valores  serão  aleatoriamente selecinados em um conjunto de inteiros contendo números inteiros entre 1 e 100. Cada vértice terá um número aleatório de arestas menor ou igual a três. Cada aresta terá um peso definido por um número inteiro positivo aleatoriamente definido entre 1 e 20. Você deverá criar este grafo, armazenando estes vértices  e  arestas  em  uma  tabela  de  adjacências  ou  em  uma  lista  de  adjacências,  nos  dois  caso armazenando o peso definido para cada uma delas. 

Seu  objetivo  será,  usando  o  algoritmo  de  menor  distância  de  Dijkstra,  imprimir  a  lista  de menores  distâncias,  destacando  a  ordem  de  visitação  dos  vértices  entre  um  vertice  inicial  da  sua escolha e todos os outros 19 vértices deste grafo.

Para que este programa possa ser verificado, você deverá imprimir, além da lista de caminhos e do  valor  da  menor  distância  uma  lista  de  pesos  de  cada  aresta  de  cada  um  dos  vértices  segundo  o modelo:  [1,2,  19],  neste  conjunto,  o  primeiro  número  indica  o  vertice  1,  o  segundo  o  vertice  2  e  o terceiro o peso da aresta entre os vértices 1 e 2. 
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void iniciarMatriz(int matriz[][100]){
  for (int i=0 ; i<100 ; i++){
    for (int j=0 ; j<100 ; j++){    
      matriz[i][j] = -1;
    }
  }
}

void criarVerticeMatriz(int matriz[][100],int valor){ 
  while( (matriz[valor][valor] == 0) || (matriz[valor][valor] == 1) ){
    valor = 1 + rand() % 100;
  }
  matriz[valor][valor] = 0;
}

int contarAdjMatriz(int matriz[][100],int valor){
  int soma = 0;

  for (int i=0 ; i<100 ; i++){
    if( (matriz[valor][i] != -1) && (matriz[valor][i] != 0) ){
      soma += 1;
    }
  }
  return soma;
}

bool verificaVerticeMatriz(int matriz[][100],int valor){
  if(matriz[valor][valor] != -1){
    return true;
  }
  
  return false;
}

void criarArestaMatriz(int matriz[][100],int vertice1,int vertice2){
  int distancia;
  
  if(vertice1 != vertice2){
    if( (verificaVerticeMatriz(matriz,vertice1) == true) && (verificaVerticeMatriz(matriz,vertice2) == true) ){
      if( (contarAdjMatriz(matriz,vertice1) < 3) && (contarAdjMatriz(matriz,vertice2) < 3) ){
        distancia = 1 + rand() % 20;
        matriz[vertice1][vertice2] = distancia;
        matriz[vertice2][vertice1] = distancia;
      } 
    } 
  }
}

void imprimirMatriz(int matriz[][100]){
  for (int i=0 ; i<100 ; i++){
    if(matriz[i][i] != -1 ){
      printf("Matriz[%d]",i+1);
      for(int j=0 ; j<100 ; j++){
        if( (matriz[i][j] != -1) && (i!=j) ){
          printf(" -> Matriz[%d] (%d)",j+1,matriz[i][j]);
        }
      }
    printf("\n");
    }
  }
}

void vertices(int matriz[][100],int vertice[]){
  int j = 0;
  
  for (int i=0 ; i<100 ; i++){
    if( (matriz[i][i] == 1) || (matriz[i][i] == 0) ){
      vertice[j] = i;
      j++;
    }
  } 
}

void dijkstra(int matriz[][100]){
  int vertice[20];
  
  int visitado[20];
  int distancia[20];
  int predecessor[20];

  int i;
  int v;
  int p;
  
  vertices(matriz,vertice);

  for(int t=0 ; t<20 ; t++){
    visitado[t] = 0;
    distancia[t] = INT_MAX/2;
    predecessor[t] = -1;
  }

  i = 0;
  distancia[i] = 0;
  predecessor[i] = 0;
  
  bool chave = false;
  while(chave == false){
    v = vertice[i];
    visitado[i] = 1;

    for(int k = 0; k<100; k++){
      p = matriz[v][k];
      if(p != -1 && p != 0){
        for(int l = 0; l< 20; l++){
          if(k == vertice[l] && visitado[l] == 0){
            if(distancia[l] > (distancia[i]+p)){
              distancia[l] = distancia[i]+p;
              predecessor[l] = i; 
            }
          }
        }
      }
    }
    
    i = -1;
    int aux = INT_MAX/2;
    for(int x = 0; x<20; x++){

      if(visitado[x] == 0){
        if(distancia[x] < aux){
          aux = distancia[x];
          i = x;
        }
      }  
    }

    if(aux == INT_MAX/2){ 
      chave = true;
    }  
  }

  printf("\n---- VISITAS ----\n");
  for(int r = 0; r<20; r++){
    if(visitado[r] == 1){
      printf("Visita[%d] = Visitado\n",vertice[r]+1);
    }
    else{
      printf("Visita[%d] = Não Visitado\n",vertice[r]+1);
    }
  }

  printf("\n---- CAMINHOS ----\n");
  for(int r = 0; r<20; r++){
    if(distancia[r] == INT_MAX/2){
       printf("Distancia[%d] = Infinito\n",vertice[r]+1);
    }
    else{
      printf("Distancia[%d] = %d\n",vertice[r]+1,distancia[r]);
    }
  }
  
  printf("\n---- PREDECESSORES ----\n");
  for(int r = 0; r<20; r++){
    if(predecessor[r] == -1){
      printf("Predecessor[%d] = NULL\n",vertice[r]+1);
    }
    else{
      printf("Predecessor[%d] = %d\n",vertice[r]+1,vertice[predecessor[r]]+1);
    }
  }
}

void imprimirArestas(int matriz[][100]){
  for (int i=0 ; i<100 ; i++){
    if(matriz[i][i] != -1 ){
      for(int j=0 ; j<100 ; j++){
        if( (matriz[i][j] != -1) && (i!=j) ){
          printf("[%d,%d,%d]\n",i+1,j+1,matriz[i][j]);
        }
      }
    }
  }
}

int main() {

  int grafo_matriz[100][100];
  int numero_aleatorio1; 
  int numero_aleatorio2;
  int vertices[20];
  
  srand(time(NULL));

  iniciarMatriz(grafo_matriz);

  for(int i=0 ; i<20 ; i++){
    numero_aleatorio1 = rand() % 100;
    criarVerticeMatriz(grafo_matriz,numero_aleatorio1);
    vertices[i] = numero_aleatorio1;
  }

  for(int i=0 ; i<20 ; i++){
    numero_aleatorio1 = rand() % 4;
    for(int j=0 ; j<numero_aleatorio1 ; j++){
      numero_aleatorio2 = 1 + rand() % 20;
      criarArestaMatriz(grafo_matriz,vertices[i],vertices[numero_aleatorio2]);
    }
  }

  printf("\n---- REPRESENTAÇÃO DA MATRIZ ----\n");
  imprimirMatriz(grafo_matriz);

  printf("\n---- LISTA DE PESOS ----\n");
  imprimirArestas(grafo_matriz);
  
  dijkstra(grafo_matriz);

  return 0;
}