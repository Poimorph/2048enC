#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "functions.h"

int main() {
    srand(time(0));
    int n = 0, mode;
    while (mode < 1 || mode > 3) { // Si le joueur accepte de jouer on lui demande le mode de jeu qu'il veut
        printf("Veuillez choisir la mode de Jeu \n1 : mode Classique\n2 : mode Duo\n3 : mode Puzzle \n");
        scanf("%d", &mode);
        if (mode < 1 || mode > 3) {
            printf("Saisie incorrect, Veuillez resaisir ! \n");
        }
    }
    if (mode != 3) { // Si le mode de jeu n'est pas le puzzle alors on lui demande la taille du tableaux.
        while (n < 4 || n > 9) {
            printf("Veuillez choisir la taille du tableau (entre 4 et 9) :");
            scanf("%d", &n);
            if (n < 4 || n > 9) {
                printf("Saisie incorrect, Veuillez resaisir ! \n");
            }
        }
    } else {
        n = 4;
        printf("Voulez-vous charger un puzzle existant (C) ou en générer un nouveau (N) ? ");
        char choix;
        do {
            scanf(" %c", &choix);
            choix = tolower(choix);
            while (getchar() != '\n');

            if (choix != 'c' && choix != 'n') {
                printf("Veuillez choisir C (charger) ou N (nouveau) : ");
            }
        } while (choix != 'c' && choix != 'n');

        if (choix == 'c') {
            n = 5;
        } else {
            do {
                printf("Entrez la taille du puzzle (entre 4 et 9) : ");
                scanf("%d", &n);
                while (getchar() != '\n');

                if (n < 4 || n > 9) {
                    printf("La taille doit être entre 4 et 9.\n");
                }
            } while (n < 4 || n > 9);
            mode = 4;
        }
    }

    // Calculer la taille de la fenêtre
    int windowWidth = n * (CELL_SIZE + CELL_PADDING) + CELL_PADDING;
    int windowHeight = n * (CELL_SIZE + CELL_PADDING) + CELL_PADDING + 50; // Espace supplémentaire pour le score
    windowWidth = (mode == 2) ? windowWidth * 2 + CELL_SIZE : windowWidth; // Double la largeur pour le mode duo

    // initialisation de SDL
    if (!initSDL(windowWidth, windowHeight)) {
        printf("Échec de l'initialisation de SDL. Sortie...\n");
        return 1;
    }
    fflush(stdin);
    jeu(n, mode);
    cleanupSDL();
}
