#include "functions.h"


/** Affiche le terrain de jeu du 2048enC dans la console.
     * @param n      : La taille du tableau (assumant que c'est un tableau carré nxn).
     * @param T      : Le tableau bidimensionnel représentant le terrain de jeu.
     * @param Score  : Pointeur vers la variable contenant le score actuel.
     */
void affiche(int n, int T[n][n], int *Score) {
    printf("\033[2J\033[H"); // Clear screen and move cursor to top
    printf("Score Actuel : %d\n\n", *Score);
    
    // Print column numbers
    printf("   ");
    for (int y = 1; y <= n; y++) {
        printf("%-7d", y);
    }
    printf("\n");
    
    // Print horizontal line
    printf("   ");
    for (int y = 0; y < n * 7; y++) {
        printf("-");
    }
    printf("\n");
    
    // Print rows with row numbers
    for (int i = 0; i < n; i++) {
        printf("%-2d|", i+1);
        for (int y = 0; y < n; y++) {
            if (T[i][y] == -1) {
                printf("%-7c", 'X');
            } else if (T[i][y] == 0) {
                printf("%-7c", '.');
            } else {
                printf("%-7d", T[i][y]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

/**
     * Affiche deux tableaux du jeu 2048enC côte à côte dans la console.
     * @param n     : La taille des tableaux (assumant qu'il s'agit de tableaux carrés nxn).
     * @param T1    : Le premier tableau bidimensionnel à afficher.
     * @param T2    : Le deuxième tableau bidimensionnel à afficher.
     * @param score : Pointeur vers la variable contenant le score actuel.
     */
void affiche_duo(int n, int T1[n][n], int T2[n][n], int *score) {
    printf("\033[2J\033[H"); // Clear screen
    printf("Score Actuel : %d\n\n", *score);
    
    // Print column numbers
    printf("   ");
    for (int y = 0; y < n; y++) {
        printf("%-7d", y+1);
    }
    printf("        ");
    for (int y = 0; y < n; y++) {
        printf("%-7d", y+1);
    }
    printf("\n");
    
    // Print horizontal lines
    printf("   ");
    for (int y = 0; y < n * 7; y++) {
        printf("-");
    }
    printf("        ");
    for (int y = 0; y < n * 7; y++) {
        printf("-");
    }
    printf("\n");
    
    // Print both grids side by side
    for (int i = 0; i < n; i++) {
        printf("%-2d|", i+1);
        for (int y = 0; y < n; y++) {
            if (T1[i][y] == 0) {
                printf("%-7c", '.');
            } else {
                printf("%-7d", T1[i][y]);
            }
        }
        printf("    %-2d|", i+1);
        for (int y = 0; y < n; y++) {
            if (T2[i][y] == 0) {
                printf("%-7c", '.');
            } else {
                printf("%-7d", T2[i][y]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

