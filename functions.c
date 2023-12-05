#include <stdio.h>
#include "functions.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

void affiche(int n, int T[n][n],int*Score){
    printf("Score Actuel : %d\n",*Score);
    for (int i =0; i<n; i++ ){
        for (int y =0; y<n; y++ ) {
            printf("%-7d", T[i][y]);
        }
        printf("\n");
    }
}

void affiche_duo(int n, int T1[n][n], int T2[n][n], int* score){
    printf("Score Actuel ! %d\n", *score);
    for (int i = 0; i < n; i++){
        for (int y = 0; y < n; y++){
            printf("%-7d", T1[i][y]);
        }
        printf("%-7s", "    ");
        for (int m = 0; m < n; m++){
            printf("%-7d", T2[i][m]);
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

void fusion(int n, int Tab[n][n], char sensRotation){
    /*    On prendra r pour de gauche à droite
          l pour de droit à gauche
          u pour de haut en bas
          d pour de bas en haut*/

    switch(sensRotation){

        case 'd':

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
            break;
        case 's':

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

    }}
void creationTab(int n,int T[n][n]){
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            T[i][j]=0;
        }
    }
}

void duo(int n, int T1[n][n], int T2[n][n], int *score){
    int a = 1;
    char dir;
    creationTab(n, T1);
    creationTab(n, T2);
    add_case(n, T1, &score);
    add_case(n, T2, &score);
    affiche_duo(n, T1, T2, &score);
    while (a) {
        printf("dans quel direction voulez vous aller ? (l/r/u/d) ou 'a' pour quitter\n");
        scanf("%c", &dir);
        fflush(stdin);

        if (dir == 'a') { a = 0; }
        else {
            fusion(n, T1, dir);
            fusion(n, T2, dir);
            move(n, T1, dir);
            move(n, T2, dir);
            add_case(n, T1, &score);
            add_case(n, T2, &score);
            affiche_duo(n, T1, T2, &score);
        }
    }
}

void normal(int n, int T1[n][n], int *score){
    int a = 1;
    char dir;
    creationTab(n, T1);
    add_case(n, T1, &score);
    affiche(n, T1, &score);
    while (a) {
        printf("dans quel direction voulez vous aller ? (l/r/u/d) ou 'a' pour quitter");
        scanf("%c", &dir);
        fflush(stdin);
        tolower(dir);
        if (dir == 'a') { a = 0; }
        else {
            fusion(4, T1, dir);
            move(4, T1, dir);
            add_case(n, T1, &score);
            affiche(n, T1, &score);
        }

    }
}

void puzzle(int *score){
    int a = 1;

    char dir;
    FILE* f = fopen("./../puzzleStorage/puzzle1.txt", "r");
    if (f != NULL) {
        char buffer[256];
        fgets(buffer, 256, f);
        strtok(buffer, "|");
        int n = *strtok(NULL, "|") - '0';
        int T1[n][n];
        fgets(buffer, 256, f);

        printf("%d", n);
        for (int i = 0; i < n; i++) {
            if (*strtok(buffer, "|") - '0' == -1) {
                T1[i][0] = -1;
            } else {
                T1[i][0] = *strtok(buffer, "|") - '0';
            }
            printf("%d", T1[i][0]);
            printf("%s", strtok(NULL, "|"));
            for (int y = 1; y < n; y++) {
                printf("Lol");
                printf("%c", *strtok(NULL, "|") - '0');
                if (strtok(NULL, "|") - '0' == -1) {

                    T1[i][y] = -1;
                } else {

                    printf("%d", *strtok(NULL, "|") - '0');
                    T1[i][y] = 0;
                }
            }
            fgets(buffer, 256, f);
        }


        fclose(f);
        affiche(n, T1, &score);
        while (a) {
            printf("dans quel direction voulez vous aller ? (l/r/u/d) ou 'a' pour quitter");
            scanf("%c", &dir);
            fflush(stdin);
            tolower(dir);
            if (dir == 'a') { a = 0; }
            else {
                fusion(4, T1, dir);
                move(4, T1, dir);
                add_case(n, T1, &score);
                affiche(n, T1, &score);
            }

        }
    }
}

void jeu(int n, int mode) {
    int score = 0, T1[n][n], T2[n][n];
    if (mode == 1) {
        normal(n, T1, &score);
    } else if (mode == 2) {
        duo(n, T1, T2, &score);
    } else if (mode == 3){
        puzzle(&score);
    }
}
