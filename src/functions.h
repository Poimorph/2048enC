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
#define MENU_CELL_SIZE 50
#define MENU_PADDING 10
#define BUTTON_HEIGHT 60
#define BUTTON_WIDTH 200

extern SDL_Color COLORS[];

// structure pour les boutons
typedef struct {
    SDL_Rect rect;
    char* text;
    int mode;
} Button;

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

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;

// Opérations sur la grille (game_logic.c)
void creationTab(int n, int T[n][n]);
void add_case(int length, int Tab[length][length], int* score);
int move(int n, int T[n][n], char sens);
int fusion(int n, int Tab[n][n], char sensRotation);
int compare(int value1, int value2);
int isGameOver(int n, int T[n][n]);

// Affichage (display.c)
int initSDL(int width, int height);
void cleanupSDL();
SDL_Color getColorForValue(int value);
void createAnimation(int startX, int startY, int endX, int endY, int value);
void updateAnimations();
void affiche(int n, int T[n][n], int* Score);
void affiche_duo(int n, int T1[n][n], int T2[n][n], int* score);
void draw_button(SDL_Renderer* renderer, Button button, TTF_Font* font, int is_selected);
void show_size_selector(SDL_Renderer* renderer, TTF_Font* font, int* selected_size);
int menu_demarrage(int* n, int* mode);
void displayGameOver(int score);

// Sauvegarde et chargement (save_load.c)
void Sauvegarde(int n, int T[n][n], int score, int mode);
void Sauvegarde_duo(int n, int T1[n][n], int T2[n][n], int score);
int Lecture(int n, int T[n][n], int* score, int mode);
int Lecture_duo(int n, int T1[n][n], int T2[n][n], int* score);
int has_save(int mode, int size);
void ensure_saves_directory();
void get_save_filename(char* filename, int mode, int size);

// Modes de jeu (game_mode.c)
void jeu(int n, int mode, int isSave);
void normal(int n, int T1[n][n], int* score, int isSave);
void duo(int n, int T1[n][n], int T2[n][n], int* score, int isSave);
void puzzle(int n, int isSave, int* score);

#endif // FUNCTIONS_H
