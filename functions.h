#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int compare(int, int);
void fusion(int n, int Tab[n][n], char sensRotation);
void affiche(int n, int T[n][n],int* Score);
void move(int n, int T[n][n],char sens);
void add_case(int length,int Tab[length][length], int *score);
void jeu(int n, int mode);
void creationTab(int n,int T[n][n]);
void duo(int n, int T1[n][n], int T2[n][n], int* score);
void normal(int n, int T1[n][n], int* score);
void affiche_duo(int n, int T1[n][n], int T2[n][n], int* score);
void puzzle(int* score);

#endif //FUNCTIONS_H
