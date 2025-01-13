#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "functions.h"

int main() {
    srand(time(0));
    int n = 4;
    int mode = 1;

    if (!initSDL(800, 600)) {
        printf("Échec de l'initialisation de SDL. Sortie...\n");
        return 1;
    }

    // Le menu retourne maintenant :
    // 0 pour quitter
    // 1 pour nouvelle partie
    // 2 pour charger une partie existante
    int menu_choice = menu_demarrage(&n, &mode);
    if (menu_choice == 0) {
        cleanupSDL();
        return 0;
    }

    int windowWidth = n * (CELL_SIZE + CELL_PADDING) + CELL_PADDING;
    int windowHeight = n * (CELL_SIZE + CELL_PADDING) + CELL_PADDING + 50;
    windowWidth = (mode == 2) ? windowWidth * 2 + CELL_SIZE : windowWidth;
    SDL_SetWindowSize(window, windowWidth, windowHeight);

    // Passer le choix du menu à la fonction jeu
    jeu(n, mode, menu_choice == 2); // true si on charge une partie existante
    cleanupSDL();
    return 0;
}
