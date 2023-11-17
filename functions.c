#include <stdio.h>
#include "functions.h"
#include <time.h>
#include <stdlib.h>

int compare(int value1, int value2){
  // Il est important de noter que la variable value 2 doit nécesserement être la case qui serait utiliser pour fusionner avec une case principale.
  if (value1 == value2){
      return 1;
  } else if (value1 == 0 && value2 != 0){
      return -1;
  }else {
      return 0;
}

void add_case(int Tab[][], int length, int *score){

  int x = (rand()%length);
  int y = (rend()%length);

  while (Tab[y][x] != null){
    x = (rand()%length);
    y = (rand()%length);
  }
  Tab[y][x] = 2;
  *score += 2;
}

void Fusion(int n, int Tab[n][n], char sensRotation){
  //On prendra l pour de gauche à droite
  //r pour de droit à gauche
  //d pour de haut en bas
  //u pour de bas en haut

  switch(sensRotation){

    case 'l':

      for (int x = 0; x < n; x++){
          for (int y = 0; y < n; y++){
              if (compare(Tab[(n-1)-x][(n-1)-y], Tab[(n-1)-x][(n-2)-y])){
                  Tab[(n-1)-x][(n-1)-y] = Tab[(n-1)-x][(n-1)-y]*2;
                  Tab[(n-1)-x][(n-2)-y] = 0;

              }
          }
      }

      break;
    case 'r':
        for (int x = 0; x < n; x++){
            for (int y = 0; y < n; y++){
                if (compare(Tab[x][y], Tab[x][y+1])){
                    Tab[x][y] = Tab[x][y+1]*2;
                    Tab[x][y+1] = 0;

                }
            }
        }
      break;
    case 'd':
        for (int x = 0; x < n; x++){
            for (int y = 0; y < n; y++){
                if (compare(Tab[x][y], Tab[x+1][y])){
                    Tab[x][y] = Tab[x+1][y]*2;
                    Tab[x+1][y] = 0;

                }
            }
        }
      break;
    case 'u':
        for (int x = 0; x < n; x++){
            for (int y = 0; y < n; y++){
                if (compare(Tab[(n-1)-x][y], Tab[(n-2)-x][y+1])){
                    Tab[(n-1)-x][y] = Tab[(n-2)-x][y]*2;
                    Tab[(n-2)-x][y] = 0;

                }
            }
        }
      break;


  }

}

}
