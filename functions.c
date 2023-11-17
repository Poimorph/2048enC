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



}
