#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Constantes pour les noms de fichiers
#define SAVES_DIR "saves"
#define MAX_PATH 256

// Constants pour les coleurs et dimensions
#define CELL_SIZE 100
#define CELL_PADDING 10
#define ANIMATION_SPEED 0.1
extern SDL_Color COLORS[];

// Structure pour génrer les animations
typedef struct {
    int startX;
    int startY;
    int endX;
    int endY;
    int currentX;
    int currentY;
    int value;
    float progress;
    int active;
} Animation;

// Opérations sur la grille (game_logic.c)
void creationTab(int n, int T[n][n]);
void add_case(int length, int Tab[length][length], int* score);
int move(int n, int T[n][n], char sens);
int fusion(int n, int Tab[n][n], char sensRotation);
int compare(int value1, int value2);

// Affichage (display.c)
int initSDL(int width, int height);
void cleanupSDL();
SDL_Color getColorForValue(int value);
void createAnimation(int startX, int startY, int endX, int endY, int value);
void updateAnimations();
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
void puzzle(int n, int isSave, int* score);

#endif // FUNCTIONS_H
