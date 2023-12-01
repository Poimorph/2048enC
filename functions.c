#include <stdio.h>
#include "functions.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

void affiche(int n, int T[n][n]){
    for (int i =0; i<n; i++ ){
        for (int y =0; y<n; y++ ) {
            printf("  %d  ", T[i][y]);
        }
        printf("\n");
    }
}
int compare(int value1, int value2){
  // Il est important de noter que la variable value 2 doit nécesserement être la case qui serait utiliser pour fusionner avec une case principale.
  if (value1 == value2){
      return 1;
  }
  else {
      return 0;
}}

void add_case(int length,int Tab[length][length], int *score){
  int x = (rand()%length);
  int y = (rand()%length);

  while (Tab[y][x] != 0){
    x = (rand()%length);
    y = (rand()%length);
  }
  int newValue=(rand()%2+1)*2;
  Tab[y][x] = newValue;
  *score += newValue;
}

void fusion(int n, int Tab[n][n], char sensRotation){
  /*    On prendra r pour de gauche à droite
        l pour de droit à gauche
        u pour de haut en bas
        d pour de bas en haut*/

  switch(sensRotation){

    case 'r':
        printf("deplacement de gauche a droite\n");
      for (int x = 0; x < n; x++){
          for (int y = n-2; y >=0; y--){
              for(int j=y-1;j>=0;j--){
              if (compare(Tab[x][y], Tab[x][j])){
                  Tab[x][y] = Tab[x][y]*2;
                  Tab[x][j] = 0;
                  j=-1;}
              else if (Tab[x][j]!=0){
                  j=-1;
              }
              }
          }
      }

      break;
    case 'l':
        printf("deplacement de droite a gauche\n");
        for (int x = 0; x < n; x++){
            for (int y = 0; y < n; y++){
                for(int j=y+1;j<n;j++){
                    if (compare(Tab[x][y], Tab[x][j])){
                        Tab[x][y] += Tab[x][j];
                        Tab[x][j] = 0;
                        j=n;
                    }
                    else if (Tab[x][j]!=0){
                        j=n;
                    }
                }
            }
        }
      break;
    case 'u':
        printf("deplacement de bas en haut\n");
        for (int y=0; y < n; y++){
            for (int x = 0; x < n; x++){
                for(int j=x+1;j<n;j++){
                if (compare(Tab[x][y], Tab[j][y])){
                    Tab[x][y] = Tab[j][y]*2;
                    Tab[j][y] = 0;
                    j=n+1;
                }
                else if (Tab[j][y]!=0){
                    j=n;
                }
            }
        }
        }
      break;
    default:
        printf("deplacement de haut en bas\n");
        for (int y = 0; y < n; y++){
            for (int x = n-1; x >=0; x--){
                for (int j=x-1;j>=0;j--){
                    if (compare(Tab[x][y], Tab[j][y])){
                        Tab[x][y] = Tab[j][y]*2;
                        Tab[j][y] = 0;
                        j=-1;
                    }
                    else if (Tab[j][x]!=0){
                        j=-1;
                }
            }
        
        }
        }
      break;

  }
}}}

void move(int n, int T[n][n],char sens){
    int caseLibre[n][2], traker,index;
    switch (sens) {
        case 'r':
            for (int x=n-1;x>=0;x--){
                traker=0;
                index=0;
                for(int y=0;y<n;y++){
                    if(T[x][y]==0){
                        caseLibre[traker][0]=x;
                        caseLibre[traker][1]=y;
                        traker++;
                    }
                    else if (traker!=0){
                        int i=caseLibre[index][0], j=caseLibre[index][1];
                        T[i][j]=T[x][y];
                        T[x][y]=0;
                        caseLibre[traker][0]=x;
                        caseLibre[traker][1]=y;
                        traker++;
                        index++;
                    }
                }
            }
            break;
        case 'l':

            for (int x=0;x<n;x++){
                traker=0;
                index=0;
                for(int y=0;y<n;y++){
                    if(T[x][y]==0){
                        caseLibre[traker][0]=x;
                        caseLibre[traker][1]=y;
                        traker++;
                    }
                    else if (traker!=0){
                        int i=caseLibre[index][0], j=caseLibre[index][1];
                        T[i][j]=T[x][y];
                        T[x][y]=0;
                        caseLibre[traker][0]=x;
                        caseLibre[traker][1]=y;
                        traker++;
                        index++;
                    }
                }
            }
            break;
        case 'u':
            for (int y=0;y<n;y++){
                traker=0;
                index=0;
                for(int x=0;x<n;x++){
                    if(T[x][y]==0){
                        caseLibre[traker][0]=x;
                        caseLibre[traker][1]=y;
                        traker++;
                    }
                    else if (traker!=0){
                        int i=caseLibre[index][0], j=caseLibre[index][1];
                        T[i][j]=T[x][y];
                        T[x][y]=0;
                        caseLibre[traker][0]=x;
                        caseLibre[traker][1]=y;
                        traker++;
                        index++;
                    }
                }
            }
    
            break;
        case 'd':
            for (int y=0;y<n;y++){
                traker=0;
                index=0;
                for(int x=n-1;x>=0;x--){
                    if(T[x][y]==0){
                        caseLibre[traker][0]=x;
                        caseLibre[traker][1]=y;
                        traker++;
                    }
                    else if (traker!=0){
                        int i=caseLibre[index][0], j=caseLibre[index][1];
                        T[i][j]=T[x][y];
                        T[x][y]=0;
                        caseLibre[traker][0]=x;
                        caseLibre[traker][1]=y;
                        traker++;
                        index++;
                    }
                }
            }
            break;
    }
}
