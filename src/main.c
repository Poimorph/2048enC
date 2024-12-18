#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int main(){
    srand(time(0));
    int n=0, mode;
    while (mode<1||mode>3) { // Si le joueur accepte de jouer on lui demande le mode de jeu qu'il veut
        printf("Veuillez choisir la mode de Jeu \n1 : mode Classique\n2 : mode Duo\n3 : mode Puzzle \n");
        scanf("%d",&mode);
        if (mode<1||mode>3){
            printf("Saisie incorrect, Veuillez resaisir ! \n");
        }
    }
    if(mode!=3){// Si le mode de jeu n'est pas le puzzle alors on lui demande la taille du tableaux.
        while (n<4||n>9) {
            printf("Veuillez choisir la taille du tableau (entre 4 et 9) :");
            scanf("%d", &n);
            if (n < 4 || n > 9) {
                printf("Saisie incorrect, Veuillez resaisir ! \n");
            }
        }
    }
    fflush(stdin);
    jeu(n,mode);
}

