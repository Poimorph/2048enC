#include <stdio.h>
#include "functions.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

void affiche(int n, int T[n][n],int*Score){
    printf("Score Actuel : %d\n",*Score);
    for (int i =0; i<n; i++ ){
        for (int y =0; y<n; y++ ) {
            printf("%-7d", T[i][y]);
        }
        printf("\n");
    }
}
int compare(int value1, int value2){
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

    case 'd':
        printf("deplacement de gauche a droite\n");
      for (int x = 0; x < n; x++){
          for (int y = n-1; y >=0; y--){
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
    case 'q':
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
    case 'z':
        printf("deplacement de bas en haut\n");
        for (int y=0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                for (int j = x + 1; j < n; j++) {
                    if (compare(Tab[x][y], Tab[j][y])) {
                        Tab[x][y] = 2 * Tab[x][y];
                        Tab[j][y] = 0;
                        j = n;
                    } else if (Tab[j][y] != 0) {
                        j = n;
                    }
                }
            }
        }
        }
      break;
    case 's':
        printf("deplacement de haut en bas\n");
        for (int y = 0; y < n; y++){
            for (int x = n-1; x >=0; x--){
                for (int j=x-1;j>=0;j--){
                    if (compare(Tab[x][y], Tab[j][y])){
                        Tab[x][y] += Tab[j][y];
                        Tab[j][y] = 0;
                        j=-1;
                    }
                    else if (Tab[j][x]!=0){
                        j=-1;
                }
            }
        }}
      break;
      default:
          break;
  
}

void move(int n, int T[n][n],char sens){
    int caseLibre[n][2], traker,index;
    switch (sens) {
        case 'd':
            for (int x=0;x<n;x++){
                traker=0;
                index=0;
                for(int y=n-1;y>=0;y--){
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
        case 'q':

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
        case 'z':
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
        case 's':
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
        default:
            break;
    }
}

void jeu(int n, int mode,int T[n][n]){
    int a=1,score=0;
    char dir;
    add_case(n,T,&score);
    affiche(n,T,&score);
    while (a){
        printf("dans quel direction voulez vous aller ? (l/r/u/d) ou 'a' pour quitter");
        scanf("%c",&dir);
        fflush(stdin);
        strlwr(&dir);
        if (dir=='a'){a=0;}
        else{fusion(4,T,dir);
        move(4,T,dir);
        add_case(n,T,&score);
        affiche(n,T,&score);
        }

    }
}
