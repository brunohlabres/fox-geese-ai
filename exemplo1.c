#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tabuleiro.h"

#define MAXSTR 512
#define MAXINT 16
#define MAXLIN 7
#define MAXCOL 7
#define MAXTAB 10


int numgansos = 13;

typedef struct tGanso{
  int x;
  int y;
} tGanso;

void tabToMatriz(char tabuleiro[MAXSTR], char matriz[MAXTAB][MAXTAB]){
  int i, j ,k = 0;

  for (i = 0 ; i < MAXTAB ; i++ ){
    for (j = 0; j < MAXTAB; j++){
      matriz[i][j] = tabuleiro[k];
      k++;
    }
  }
}


int getPosXRaposa(char matriz[MAXTAB][MAXTAB]){
  int i,j;

  for (i = 0 ; i < MAXTAB ; i++){
    for (j = 0 ; j < MAXTAB ; j++){
      if (matriz[i][j] == 'r')
        return i;
    }
  }
  return -1;
}

int getPosYRaposa(char matriz[MAXTAB][MAXTAB]){
  int i,j;

  for (i = 0 ; i < MAXTAB ; i++){
    for (j = 0 ; j < MAXTAB ; j++){
      if (matriz[i][j] == 'r')
        return j;
    }
  }
  return -1;
}

void printaPosGansos(tGanso gansos[numgansos]){
  for (int i = 0 ; i < numgansos ; i++){
    printf("Ganso %d: %d %d\n", i, gansos[i].x, gansos[i].y);
  }
}

// dada uma posicao x e y, diz se existe a possibilidade do ganso ser comido
int vaiSerComido(char matriz[MAXTAB][MAXTAB],int x, int y){
  if ((matriz[x][y+1] == 'r') && (matriz[x][y-1] == '-'))
    return 1;
  else if ((matriz[x][y-1] == 'r') && (matriz[x][y+1] == '-'))
    return 1;
  else if ((matriz[x-1][y] == 'r') && (matriz[x+1][y] == '-'))
    return 1;
  else if ((matriz [x+1][y] == 'r') && (matriz[x-1][y] == '-'))
    return 1;
  else
    return 0;
}

int gansoEmPerigo(char matriz[MAXTAB][MAXTAB], tGanso gansos[numgansos]){
  for (int i = 0 ; i < numgansos ; i++){
    if (vaiSerComido(matriz, gansos[i].x, gansos[i].y))
      return i;
  }
  return -1;
}

void jogadaAleatoriaGanso(char matriz[MAXTAB][MAXTAB], char *buf){
  int i,j,g,m,k = 0;
  int jogou = 0;
  int tentativasGansos = 0;
  tGanso gansos[numgansos];

  // guarda a posicao de todos os gansos
  for (i = 0 ; i < MAXTAB ; i++){
    for (j = 0 ; j < MAXTAB ; j++){
      if (matriz[i][j] == 'g'){
        gansos[k].x = i;
        gansos[k].y = j;
        k++;
      }
    }
    numgansos = k;
  }

  if ((g = gansoEmPerigo(matriz,gansos)) != -1){
    i = gansos[g].x;
    j = gansos[g].y;

    if (matriz[i-1][j] == 'r'){ // se a raposa esta acima
      if (matriz[i+1][j-1] == 'g'){ // ache um ganso que possa bloquear a raposa de comer seu colega
        sprintf(buf, "g m %d %d %d %d", i+1, j-1, i+1, j);
      }
      if (matriz[i+2][j] == 'g'){ // ache um ganso que possa bloquear a raposa de comer seu colega
        sprintf(buf, "g m %d %d %d %d", i+2, j, i+1, j);
      }
      if (matriz[i+1][j+1] == 'g'){ // ache um ganso que possa bloquear a raposa de comer seu colega
        sprintf(buf, "g m %d %d %d %d", i+1, j+1, i+1, j);
      }
    }

    else if (matriz[i+1][j] == 'r'){ // se a raposa esta abaixo
      if (matriz[i-1][j-1] == 'g'){ // ache um ganso que possa bloquear a raposa de comer seu colega
        sprintf(buf, "g m %d %d %d %d", i-1, j-1, i-1, j);
      }
      if (matriz[i-2][j] == 'g'){ // ache um ganso que possa bloquear a raposa de comer seu colega
        sprintf(buf, "g m %d %d %d %d", i-2, j, i-1, j);
      }
      if (matriz[i-1][j+1] == 'g'){ // ache um ganso que possa bloquear a raposa de comer seu colega
        sprintf(buf, "g m %d %d %d %d", i-1, j+1, i-1, j);
      }

    }

    else if (matriz[i][j-1] == 'r'){ // se a raposa esta a esquerda
      if (matriz[i-1][j+1] == 'g'){ // ache um ganso que possa bloquear a raposa de comer seu colega
        sprintf(buf, "g m %d %d %d %d", i-1, j+1, i, j+1);
      }
      if (matriz[i][j+2] == 'g'){ // ache um ganso que possa bloquear a raposa de comer seu colega
        sprintf(buf, "g m %d %d %d %d", i, j+2, i, j+1);
      }
      if (matriz[i+1][j+1] == 'g'){ // ache um ganso que possa bloquear a raposa de comer seu colega
        sprintf(buf, "g m %d %d %d %d", i+1, j+1, i, j+1);
      }

    }

    else if (matriz[i][j+1] == 'r'){ // se a raposa esta a direita
      if (matriz[i-1][j-1] == 'g'){ // ache um ganso que possa bloquear a raposa de comer seu colega
        sprintf(buf, "g m %d %d %d %d", i-1, j-1, i, j-1);
      }
      if (matriz[i][j-2] == 'g'){ // ache um ganso que possa bloquear a raposa de comer seu colega
        sprintf(buf, "g m %d %d %d %d", i, j-2, i, j-1);
      }
      if (matriz[i+1][j-1] == 'g'){ // ache um ganso que possa bloquear a raposa de comer seu colega
        sprintf(buf, "g m %d %d %d %d", i+1, j-1, i, j-1);
      }

    }
    else { // se nao tem colega pra salva-lo, o proprio ganso tenta se salvar
      if (matriz[i][j-1] == '-'){ // vai pra esquerda
        sprintf(buf, "g m %d %d %d %d", i, j, i, j-1);
      }
      if (matriz[i][j+1] == '-'){ // vai pra direita
        sprintf(buf, "g m %d %d %d %d", i, j, i, j+1);
      }
      if (matriz[i-1][j] == '-'){ // vai pra cima
        sprintf(buf, "g m %d %d %d %d", i, j, i-1, j);
      }

      if (matriz[i+1][j] == '-'){ // vai pra baixo
        sprintf(buf, "g m %d %d %d %d", i, j, i+1, j);
      }
    }
  }
  else{
    // escolhe um ganso para mover, se ele nao pode ou vai ser comido se mover, tenta o prox
    m = rand() % numgansos; // recebe ganso a ser movido

    // move ganso para baixo, se ele n for ser comido
    while ((tentativasGansos < numgansos) && (!jogou)){
      if ((matriz[gansos[m].x+1][gansos[m].y] == '-') && !vaiSerComido(matriz, gansos[m].x+1, gansos[m].y)){
        sprintf(buf, "g m %d %d %d %d", gansos[m].x, gansos[m].y, gansos[m].x+1, gansos[m].y);
        jogou = 1;
      }
      else{ // testa outro ganso 
        m = (m+1) % numgansos; 
      }
    }

  }
  printaPosGansos(gansos);
  /*
  for (i = 0 ; i < MAXTAB ; i++){
    for (j = 0 ; j < MAXTAB ; j++){
      if (matriz[i][j] == 'g'){
        if ((matriz[i+1][j] == '-') && !jogou){ // come g abaixo
          sprintf(buf, "g m %d %d %d %d\n", i, j, i+1, j);
          jogou = 1;
        }
        else if ((matriz[i][j-1] == '-')){ // come g a esquerda
          sprintf(buf, "g m %d %d %d %d\n", i, j, i, j-1);
          jogou = 1;
        }
        else if ((matriz[i][j+1] == '-') && (j+1 <= MAXTAB)){ // come g a direita
          sprintf(buf, "g m %d %d %d %d\n", i, j, i, j+1);
          jogou = 1;
        }
      }
    }
  }*/
}

void jogadaAleatoriaRaposa(char matriz[MAXTAB][MAXTAB], char *buf){
  int rapX = getPosXRaposa(matriz);
  int rapY = getPosYRaposa(matriz);
  int r;

  if ((matriz[rapX-1][rapY] == 'g') && (matriz[rapX-2][rapY]) == '-'){ // come g acima
    sprintf(buf, "r m %d %d %d %d\n", rapX, rapY, rapX-2, rapY);
  }
  else if ((matriz[rapX+1][rapY] == 'g') && (matriz[rapX+2][rapY]) == '-'){ // come g abaixo
    sprintf(buf, "r m %d %d %d %d\n", rapX, rapY, rapX+2, rapY);
  }
  else if ((matriz[rapX][rapY-1] == 'g') && (matriz[rapX][rapY-2]) == '-'){ // come g a esquerda
    sprintf(buf, "r m %d %d %d %d\n", rapX, rapY, rapX, rapY-2);
  }
  else if ((matriz[rapX][rapY+1] == 'g') && (matriz[rapX][rapY+2]) == '-'){ // come g a direita
    sprintf(buf, "r m %d %d %d %d\n", rapX, rapY, rapX, rapY+2);
  }
  else{

    r = rand() % 4;
    switch(r){
      case 0:
      if ((matriz[rapX-1][rapY] == '-')){ // move para g acima
        sprintf(buf, "r m %d %d %d %d\n", rapX, rapY, rapX-1, rapY);
      }
      break;
      case 1:
      if ((matriz[rapX+1][rapY] == '-')){ // move para g abaixo
        sprintf(buf, "r m %d %d %d %d\n", rapX, rapY, rapX+1, rapY);
      }
      break;
      case 2:
      if ((matriz[rapX][rapY-1] == '-')){ // move para g a esquerda
        sprintf(buf, "r m %d %d %d %d\n", rapX, rapY, rapX, rapY-1);
      }
      break;
      case 3:
      if ((matriz[rapX][rapY+1] == '-')){ // move para g a direita
        sprintf(buf, "r m %d %d %d %d\n", rapX, rapY, rapX, rapY+1);
      }
      break;
    }
  }
}


int main(int argc, char **argv) {
  char buf[MAXSTR];
  char tabuleiro[MAXSTR]; 
  char lado_meu;
  char lado_adv;
  char tipo_mov_adv;
  int num_mov_adv;
  int mov_adv_l[MAXINT];
  int mov_adv_c[MAXINT];
  int i,j;
  char matriz[MAXTAB][MAXTAB];

  // conecta com o controlador do campo
  tabuleiro_conecta(argc, argv);
  srand(time(NULL));

  while(1){
    // recebe o campo inicial e o movimento do adversario
    tabuleiro_recebe(buf);

    // separa os elementos do string recebido
    sscanf(strtok(buf, " \n"), "%c", &lado_meu);
    sscanf(strtok(NULL, " \n"), "%c", &lado_adv);
    sscanf(strtok(NULL, " \n"), "%c", &tipo_mov_adv);
    if(tipo_mov_adv == 'm') {
      num_mov_adv = 2;
      for(i = 0; i < num_mov_adv; i++) {
        sscanf(strtok(NULL, " \n"), "%d", &(mov_adv_l[i]));
        sscanf(strtok(NULL, " \n"), "%d", &(mov_adv_c[i]));
      }
    }
    else if(tipo_mov_adv == 's') {
      sscanf(strtok(NULL, " \n"), "%d", &num_mov_adv);
      for(i = 0; i < num_mov_adv; i++) {
        sscanf(strtok(NULL, " \n"), "%d", &(mov_adv_l[i]));
        sscanf(strtok(NULL, " \n"), "%d", &(mov_adv_c[i]));
      }
    }
    strncpy(tabuleiro, strtok(NULL, "."), MAXSTR);

    // mostra o que recebeu
    printf("%c\n", lado_meu);
    printf("%c %c", lado_adv, tipo_mov_adv);
    if(tipo_mov_adv != 'n') {
      if(tipo_mov_adv == 's') 
        printf(" %d", num_mov_adv);
      for(i = 0; i < num_mov_adv; i++) {
        printf(" %d", mov_adv_l[i]);
        printf(" %d", mov_adv_c[i]);
      }
    }

    tabToMatriz(tabuleiro, matriz);
    printf("\n");
    printf("%s", tabuleiro);

    //tabToMatriz(buf, matriz);

      puts("mat:");
      for (i = 0 ; i < MAXTAB ; i++){
        for (j = 0 ; j < MAXTAB ; j++){
          printf ("%c", matriz[i][j]);
        }
      }
    
    // prepara um string com o movimento
    if(lado_meu == 'r'){
      //sprintf(buf, "r m 5 4 5 3\n");
            jogadaAleatoriaRaposa(matriz,buf);
    }
    else{
      //sprintf(buf, "g m 3 1 4 1\n");
            jogadaAleatoriaGanso(matriz,buf);
    }

    // envia o movimento para o controlador do campo
    printf("Vou jogar: %s", buf);
    tabuleiro_envia(buf);  
  }
}
