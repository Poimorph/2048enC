#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// Opérations sur la grille (game_logic.c)

// Constantes pour les noms de fichiers
#define SAVES_DIR "saves"
#define MAX_PATH 256

void creationTab(int n, int T[n][n]);
void add_case(int length, int Tab[length][length], int *score);
int move(int n, int T[n][n], char sens);
int fusion(int n, int Tab[n][n], char sensRotation);
int compare(int value1, int value2);

// Affichage (display.c)
void affiche(int n, int T[n][n], int* Score);
void affiche_duo(int n, int T1[n][n], int T2[n][n], int* score);

// Sauvegarde et chargement (save_load.c)
void Sauvegarde(int n, int T[n][n], int score, int mode);
void Sauvegarde_duo(int n, int T1[n][n], int T2[n][n], int score);
int Lecture(int n, int T[n][n], int* score, int mode);
int Lecture_duo(int n, int T1[n][n], int T2[n][n], int* score);
int has_save(int mode, int size);
void ensure_saves_directory();
void get_save_filename(char* filename, int mode, int size);

// Modes de jeu (game_mode.c)
void jeu(int n, int mode); 
void normal(int n, int T1[n][n], int* score);
void duo(int n, int T1[n][n], int T2[n][n], int* score);
void puzzle(int* score);


#endif //FUNCTIONS_H
