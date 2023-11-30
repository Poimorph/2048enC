#include <stdio.h>
#include "functions.h"
#include <stdlib.h>

int main(){
    int T[4][4]={0,8,0,0,
                 2,2,0,4,
                 0,2,2,0,
                 2,16,2,0};
    affiche(4,T);
    system("pause");
    fusion(4,T,'l');
    affiche(4,T);
    printf("\n");
    move(4,T,'l');
    affiche(4,T);
    system("pause");
    fusion(4,T,'r');
    affiche(4,T);
    printf("\n");
    move(4,T,'r');
    affiche(4,T);
    system("pause");
    fusion(4,T,'u');
    affiche(4,T);
    printf("\n");
    move(4,T,'u');
    affiche(4,T);
    system("pause");
    fusion(4,T,'d');
    affiche(4,T);
    printf("\n");
    move(4,T,'d');
    affiche(4,T);}
