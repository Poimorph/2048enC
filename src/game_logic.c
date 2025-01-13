
#include "functions.h"

int compare(int value1, int value2) {
    return (value1 == value2 && value1 != 0 && value1 != -1);
}

void add_case(int length, int Tab[length][length], int *score) {
    // Compter les cellules vides
    int empty_count = 0;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            if (Tab[i][j] == 0) {
                empty_count++;
            }
        }
    }

    if (empty_count == 0) return;

    // Choisir une cellule vide aléatoire
    int target = rand() % empty_count;
    int current = 0;

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            if (Tab[i][j] == 0) {
                if (current == target) {
                    Tab[i][j] = (rand() % 2 + 1) * 2; // 2 ou 4
                    *score += Tab[i][j];
                    return;
                }
                current++;
            }
        }
    }
}

/**
 * Déplace les cases non nulles dans la matrice 2D T dans la direction spécifiée.
 * Les cases vides sont utilisées pour déplacer les cases non nulles.
 *
 * @param n Taille de la matrice (n x n).
 * @param T Matrice 2D représentant le jeu.
 * @param sens Direction du déplacement ('d' pour droite, 'q' pour gauche, 'z' pour haut, 's' pour bas).
 * @return Un indicateur de mouvement (1 si au moins une case non nulle est déplacée, 0 sinon).
 */
int move(int n, int T[n][n], char sens) {
    int moved = 0;
    int temp[n][n];

    // Copie temporaire du tableau
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp[i][j] = T[i][j];
        }
    }

    switch (sens) {
        case 'q': // Gauche
            for (int i = 0; i < n; i++) {
                int pos = 0;
                // Premier passage : déplacer tous les nombres vers la gauche
                for (int j = 0; j < n; j++) {
                    if (temp[i][j] != 0 && temp[i][j] != -1) {
                        int val = temp[i][j];
                        temp[i][j] = 0;

                        // Trouve la position la plus à gauche disponible
                        while (pos < n && T[i][pos] == -1) {
                            pos++;
                        }

                        if (pos < n) {
                            temp[i][pos] = val;
                            pos++;
                        }
                    } else if (temp[i][j] == -1) {
                        pos = j + 1;
                    }
                }
            }
            break;

        case 'd': // Droite
            for (int i = 0; i < n; i++) {
                int pos = n - 1;
                // Premier passage : déplacer tous les nombres vers la droite
                for (int j = n - 1; j >= 0; j--) {
                    if (temp[i][j] != 0 && temp[i][j] != -1) {
                        int val = temp[i][j];
                        temp[i][j] = 0;

                        // Trouve la position la plus à droite disponible
                        while (pos >= 0 && T[i][pos] == -1) {
                            pos--;
                        }

                        if (pos >= 0) {
                            temp[i][pos] = val;
                            pos--;
                        }
                    } else if (temp[i][j] == -1) {
                        pos = j - 1;
                    }
                }
            }
            break;

        case 'z': // Haut
            for (int j = 0; j < n; j++) {
                int pos = 0;
                // Premier passage : déplacer tous les nombres vers le haut
                for (int i = 0; i < n; i++) {
                    if (temp[i][j] != 0 && temp[i][j] != -1) {
                        int val = temp[i][j];
                        temp[i][j] = 0;

                        // Trouve la position la plus haute disponible
                        while (pos < n && T[pos][j] == -1) {
                            pos++;
                        }

                        if (pos < n) {
                            temp[pos][j] = val;
                            pos++;
                        }
                    } else if (temp[i][j] == -1) {
                        pos = i + 1;
                    }
                }
            }
            break;

        case 's': // Bas
            for (int j = 0; j < n; j++) {
                int pos = n - 1;
                // Premier passage : déplacer tous les nombres vers le bas
                for (int i = n - 1; i >= 0; i--) {
                    if (temp[i][j] != 0 && temp[i][j] != -1) {
                        int val = temp[i][j];
                        temp[i][j] = 0;

                        // Trouve la position la plus basse disponible
                        while (pos >= 0 && T[pos][j] == -1) {
                            pos--;
                        }

                        if (pos >= 0) {
                            temp[pos][j] = val;
                            pos--;
                        }
                    } else if (temp[i][j] == -1) {
                        pos = i - 1;
                    }
                }
            }
            break;
    }

    // Vérifie si un mouvement a eu lieu et copie le résultat
    // tout en préservant les X
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (T[i][j] == -1) {
                temp[i][j] = -1; // Préserve les X
            } else if (T[i][j] != temp[i][j]) {
                moved = 1;
            }
            T[i][j] = temp[i][j];
        }
    }

    return moved;
}

/**
 * Fusionne les éléments adjacents dans la matrice 2D `Tab` selon la direction spécifiée.
 * La fusion est effectuée en suivant les règles du jeu (2 éléments identiques fusionnent).
 *
 * @param n Taille de la matrice (n x n).
 * @param Tab Matrice 2D représentant le jeu.
 * @param sensRotation Direction de la fusion ('d' pour de gauche à droite, 'q' pour de droit à gauche,
 *                      'z' pour de bas en haut, 's' pour de haut en bas).
 * @return Un indicateur de fusion (1 si au moins une fusion de cases non nulles a eu lieu, 0 sinon).
 */
int fusion(int n, int Tab[n][n], char sensRotation) {
    int fused = 0;

    switch (sensRotation) {
        case 'q': // Gauche
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n - 1; j++) {
                    if (Tab[i][j] > 0) { // Nombre positif uniquement
                        // Cherche le prochain nombre à droite
                        int next = j + 1;
                        while (next < n && Tab[i][next] == 0) {
                            next++;
                        }
                        if (next < n && Tab[i][next] > 0 && Tab[i][j] == Tab[i][next]) {
                            Tab[i][j] *= 2;
                            Tab[i][next] = 0;
                            fused = 1;
                            j = next; // Évite les fusions multiples
                        }
                    }
                }
            }
            break;

        case 'd': // Droite
            for (int i = 0; i < n; i++) {
                for (int j = n - 1; j > 0; j--) {
                    if (Tab[i][j] > 0) { // Nombre positif uniquement
                        // Cherche le prochain nombre à gauche
                        int next = j - 1;
                        while (next >= 0 && Tab[i][next] == 0) {
                            next--;
                        }
                        if (next >= 0 && Tab[i][next] > 0 && Tab[i][j] == Tab[i][next]) {
                            Tab[i][j] *= 2;
                            Tab[i][next] = 0;
                            fused = 1;
                            j = next; // Évite les fusions multiples
                        }
                    }
                }
            }
            break;

        case 'z': // Haut
            for (int j = 0; j < n; j++) {
                for (int i = 0; i < n - 1; i++) {
                    if (Tab[i][j] > 0) { // Nombre positif uniquement
                        // Cherche le prochain nombre en bas
                        int next = i + 1;
                        while (next < n && Tab[next][j] == 0) {
                            next++;
                        }
                        if (next < n && Tab[next][j] > 0 && Tab[i][j] == Tab[next][j]) {
                            Tab[i][j] *= 2;
                            Tab[next][j] = 0;
                            fused = 1;
                            i = next; // Évite les fusions multiples
                        }
                    }
                }
            }
            break;

        case 's': // Bas
            for (int j = 0; j < n; j++) {
                for (int i = n - 1; i > 0; i--) {
                    if (Tab[i][j] > 0) { // Nombre positif uniquement
                        // Cherche le prochain nombre en haut
                        int next = i - 1;
                        while (next >= 0 && Tab[next][j] == 0) {
                            next--;
                        }
                        if (next >= 0 && Tab[next][j] > 0 && Tab[i][j] == Tab[next][j]) {
                            Tab[i][j] *= 2;
                            Tab[next][j] = 0;
                            fused = 1;
                            i = next; // Évite les fusions multiples
                        }
                    }
                }
            }
            break;
    }

    return fused;
}

// Vérifie si des mouvements sont encore possibles
int isGameOver(int n, int T[n][n]) {
    // Vérifie s'il y a des cases vides
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (T[i][j] == 0) return 0; // Il reste des cases vides
        }
    }

    // Vérifie s'il y a des fusions possibles horizontalement
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (T[i][j] == T[i][j + 1] && T[i][j] != -1) return 0;
        }
    }

    // Vérifie s'il y a des fusions possibles verticalement
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n; j++) {
            if (T[i][j] == T[i + 1][j] && T[i][j] != -1) return 0;
        }
    }

    return 1; // Aucun mouvement possible
}

void creationTab(int n, int T[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            T[i][j] = 0;
        }
    }
}
