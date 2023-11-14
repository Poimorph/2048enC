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

void add_case(int Tab[][], int length){

  int x = (rand()%length);
  int y = (rend()%length);

  while (Tab[y][x] != null){
    x = (rand()%length);
    y = (rand()%length);
  }
  Tab[y][x] = 2;
}



int modifiy_value_position(int Tab[4][4], char sensRotation){
  //On prendra l pour de gauche à droite
  //r pour de droit à gauche
  //d pour de haut en bas
  //u pour de bas en haut
  int retenue;
  switch(sensRotation){

    case 'l':
      for (int i = Tab.length-1; i > 1; i--){
        for (int y = Tab[0].length-1; y > 1; y++){
          retenue = 1;
          while (Tab[i][y-retenue] == 0 || y - retenue >= 0){
            retenue += 1;
          } 
          if (compare(Tab[i][y], Tab[i][y-retenue]){
            Tab[i][y] = Tab[i][y] * Tab[i][y-retenue];
            Tab[i][y-retenue] = null;
          } else if (compare(Tab[i][y], Tab[i][y-retenue])){
            Tab[i][y-1] = Tab[i][y-retenue];
            Tab[i][y-retenue] = null;
        }
      }
      break;
    case 'r':
      break;
    case 'd':
      break;
    case 'u':
      break;

  }
  
}
