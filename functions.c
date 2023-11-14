#include <stdio.h>
#include "functions.h"
#include <time.h>
#include <stdlib.h>

int compare(int value1, int value2){
  if (value1 == value2){
      return 1;
  } else {
      return 0;

}

void add_case(int Tab[][], int length){
  srand(time(0));

  int x = (rand()%length);
  int y = (rend()%length);

  while (Tab[y][x] != null){
    x = (rand()%length);
    y = (rand()%length);
  }
  Tab[y][x] = 2;
}

