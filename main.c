#include <stdio.h>
#include "functions.h"
#include <stdlib.h>

int main(){
    char rep='d';
    jeu(5,0);
    /*while (rep!='o' && rep!='n'){
        printf("Voulez-vous jouer ? (oui/non)");
        scanf("%c",&rep);
        fflush(stdin);
        if(rep!='o' && rep!='n'){
            printf("Saisie incorrect, Veuillez resaisir ! \n");
        }
    }
    if (rep=='o'){
        int n=0, mode;
        while (mode<1||mode>3) {
            printf("Veuillez choisir la mode de Jeu \n1 : mode Classique\n2 : mode Duo\n3 : mode Puzzle ");
            scanf("%d",&mode);
            if (mode<1||mode>3){
                printf("Saisie incorrect, Veuillez resaisir ! \n");
            }
        }
        if(mode!=3){
        while (n<4||n>9) {
        printf("Veuillez choisir la taille du tableau (entre 4 et 9) :");
        scanf("%d",&n);
        if (n<4||n>9){
            printf("Saisie incorrect, Veuillez resaisir ! \n");
        }
    }}
        fflush(stdin);
        jeu(n,mode);
    }*/
}
