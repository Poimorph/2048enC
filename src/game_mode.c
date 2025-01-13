#include "functions.h"

char handle_input(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_z:
            case SDLK_UP:
                return 'z';
            case SDLK_s:
            case SDLK_DOWN:
                return 's';
            case SDLK_d:
            case SDLK_RIGHT:
                return 'd';
            case SDLK_q:
            case SDLK_LEFT:
                return 'q';
            case SDLK_a:
            case SDLK_ESCAPE:
                return 'a';
            default:
                return '\0';
        }
    }
    return '\0';
}

/**
 * Fonction principale du mode normal du jeu 2048enC.
 * Permet à un joueur de jouer en mode normal avec la possibilité de sauvegarder et reprendre la partie.
 * @param n Taille du tableau de jeu
 * @param T1 Tableau de jeu principal
 * @param score Pointeur vers la variable de score
 */
void normal(int n, int T1[n][n], int* score, int isSave) {
    int jouer = 1;
    char dir;
    SDL_Event event;

    // Initialisation en fonction de la réponse
    if (isSave) {
        if (!Lecture(n, T1, score, 1)) {
            printf("Erreur de chargement. Démarrage d'une nouvelle partie.\n");
            creationTab(n, T1);
            *score = 0;
            add_case(n, T1, score);
        }
    } else {
        creationTab(n, T1);
        *score = 0;
        add_case(n, T1, score);
        add_case(n, T1, score); // Ajoute deux cases au début
    }

    affiche(n, T1, score);

    int gameOverDisplayed = 0;

    // Boucle principale du jeu
    while (jouer) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                jouer = 0;
                if (gameOverDisplayed == 0) {
                    Sauvegarde(n, T1, *score, 1);
                } else {
                    if (isSave) {
                        char filename[MAX_PATH];
                        get_save_filename(filename, 1, n);
                        remove(filename);
                    }
                }

                break;
            }
            dir = handle_input(event);
            if (dir != '\0') {
                if (dir == 'a') {
                    jouer = 0;
                    if (gameOverDisplayed == 0) {
                        Sauvegarde(n, T1, *score, 1);
                    } else {
                        if (isSave) {
                            char filename[MAX_PATH];
                            get_save_filename(filename, 1, n);
                            remove(filename);
                        }
                    }
                } else {
                    int moved = move(n, T1, dir);
                    int fused = fusion(n, T1, dir);

                    if (fused) {
                        moved = move(n, T1, dir) || moved;
                    }

                    if (moved || fused) {
                        add_case(n, T1, score);
                    }

                    affiche(n, T1, score);

                    // Vérifier si le jeu est terminé
                    if (isGameOver(n, T1)) {
                        gameOverDisplayed = 1;
                        displayGameOver(*score);
                    }
                }
            }
        }
        SDL_Delay(10);
    }
}

void duo(int n, int T1[n][n], int T2[n][n], int* score, int isSave) {
    /* Fonction principale du mode duo*/
    int jouer = 1;
    char dir;
    SDL_Event event;

    // Initialisation en fonction de la réponse
    if (isSave) {
        if (!Lecture_duo(n, T1, T2, score)) {
            printf("Erreur de chargement. Démarrage d'une nouvelle partie.\n");
            creationTab(n, T1);
            creationTab(n, T2);
            *score = 0;
            add_case(n, T1, score);
            add_case(n, T2, score);
        }
    } else {
        // Nouvelle partie
        creationTab(n, T1);
        creationTab(n, T2);
        *score = 0;
        add_case(n, T1, score);
        add_case(n, T2, score);
    }

    affiche_duo(n, T1, T2, score);

    int fusionHappend1, movementHappend1, fusionHappend2, movementHappend2, gameOverDisplayed = 0;

    while (jouer) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                jouer = 0;
                if (gameOverDisplayed == 0) {
                    Sauvegarde_duo(n, T1, T2, *score);
                } else {
                    if (isSave) {
                        char filename[MAX_PATH];
                        get_save_filename(filename, 2, n);
                        remove(filename);
                    }
                }
                break;
            }

            dir = handle_input(event);
            if (dir != '\0') {
                if (dir == 'a') {
                    jouer = 0;
                    if (gameOverDisplayed == 0) {
                        Sauvegarde_duo(n, T1, T2, *score);
                    } else {
                        if (isSave) {
                            char filename[MAX_PATH];
                            get_save_filename(filename, 2, n);
                            remove(filename);
                        }
                    }
                } else {
                    // Premier tableau
                    fusionHappend1 = fusion(n, T1, dir);
                    movementHappend1 = move(n, T1, dir);

                    if (fusionHappend1) {
                        movementHappend1 = move(n, T1, dir) || movementHappend1;
                    }

                    // Deuxième tableau
                    fusionHappend2 = fusion(n, T2, dir);
                    movementHappend2 = move(n, T2, dir);

                    if (fusionHappend2) {
                        movementHappend2 = move(n, T2, dir) || movementHappend2;
                    }

                    // Ajoute de nouvelles cases si nécessaire
                    if (fusionHappend1 || movementHappend1) {
                        add_case(n, T1, score);
                    }
                    if (fusionHappend2 || movementHappend2) {
                        add_case(n, T2, score);
                    }

                    affiche_duo(n, T1, T2, score);

                    // Vérifier si le jeu est terminé
                    if (isGameOver(n, T1) && isGameOver(n, T2)) {
                        gameOverDisplayed = 1;
                        displayGameOver(*score);
                    }
                }
            }
        }
        SDL_Delay(10);
    }
}

void puzzle(int n, int isSave, int* score) {
    int T1[n][n]; // Allocation dynamique

    // Initialiser tout le tableau à 0 avant toute autre opération
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            T1[i][j] = 0;
        }
    }

    if (isSave == 1) {
        // Charger un puzzle existant
        FILE* f = fopen("Puzzle/puzzleOne.txt", "r");
        if (f == NULL) {
            printf("Erreur: Impossible d'ouvrir le fichier puzzle!\n");
            return;
        }

        char buffer[256];

        // Lire le puzzle depuis le fichier
        for (int i = 0; i < n; i++) {
            if (fgets(buffer, sizeof(buffer), f) == NULL) {
                printf("Erreur de lecture du fichier puzzle!\n");
                fclose(f);
                return;
            }

            char* token = strtok(buffer, "|");
            for (int j = 0; j < n && token != NULL; j++) {
                T1[i][j] = (strcmp(token, "X") == 0) ? -1 : atoi(token);
                token = strtok(NULL, "|");
            }
        }
        fclose(f);
    } else {
        // Ajouter quelques obstacles (X) aléatoirement
        int nbObstacles = n * n / 6; // Environ 1/6 des cases seront des obstacles
        for (int i = 0; i < nbObstacles; i++) {
            int x, y;
            do {
                x = rand() % n;
                y = rand() % n;
            } while (T1[x][y] != 0);
            T1[x][y] = -1; // -1 représente un X
        }

        // Ajouter quelques nombres initiaux (uniquement 2 ou 4)
        for (int i = 0; i < 2; i++) {
            add_case(n, T1, score);
        }
    }

    affiche(n, T1, score);

    char dir;
    int jouer = 1;
    *score = 0;
    SDL_Event event;

    while (jouer) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                jouer = 0;
                break;
            }

            dir = handle_input(event);
            if (dir != '\0') {
                if (dir == 'a') {
                    jouer = 0;
                } else {
                    int moved = move(n, T1, dir);
                    int fused = fusion(n, T1, dir);
                    if (fused) {
                        moved = move(n, T1, dir) || moved;
                    }
                    if (moved || fused) {
                        add_case(n, T1, score);
                    }
                    affiche(n, T1, score);

                    // Vérifier si le jeu est terminé
                    if (isGameOver(n, T1)) {
                        displayGameOver(*score);
                    }
                }
            }
        }

        SDL_Delay(10);
    }
}

void jeu(int n, int mode, int charger) {
    int score = 0;
    int T1[n][n], T2[n][n];

    ensure_saves_directory(); // S'assure que le dossier saves existe

    switch (mode) {
        case 1:
            normal(n, T1, &score, charger);
            break;
        case 2:
            duo(n, T1, T2, &score, charger);
            break;
        case 3:
            puzzle(n, charger, &score);
            break;
        default:
            printf("Mode de jeu invalide\n");
    }
}
