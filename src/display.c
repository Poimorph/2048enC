#include "functions.h"

// couleurs pour les differentes valeurs (2,4,8,16,32,64,128,256,512,1024,2048)
SDL_Color COLORS[] = {
    {255, 229, 229, 255},
    {229, 255, 229, 255},
    {229, 229, 255, 255},
    {255, 229, 255, 255},
    {255, 255, 229, 255},
    {229, 255, 255, 255},
    {255, 240, 229, 255},
    {240, 229, 255, 255},
    {229, 255, 240, 255},
    {255, 229, 240, 255},
    {240, 255, 229, 255}};

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;

void displayGameOver(int score) {
    // Obtenir les dimensions réelles de la fenêtre
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    // Créer un overlay semi-transparent sur toute la fenêtre
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_Rect overlay = {0, 0, windowWidth, windowHeight};
    SDL_RenderFillRect(renderer, &overlay);

    // Augmenter la taille de la police pour le "Game Over"
    TTF_Font *gameOverFont = TTF_OpenFont("resources/font.ttf", 48);
    TTF_Font *normalFont = TTF_OpenFont("resources/font.ttf", 24);

    if (!gameOverFont || !normalFont) {
        printf("Erreur de chargement des polices: %s\n", TTF_GetError());
        return;
    }

    SDL_Color textColor = {255, 255, 255, 255};

    // Texte "Game Over" avec la grande police
    SDL_Surface *gameOverSurface = TTF_RenderText_Solid(gameOverFont, "Game Over!", textColor);
    SDL_Texture *gameOverTexture = SDL_CreateTextureFromSurface(renderer, gameOverSurface);

    SDL_Rect gameOverRect = {
        (windowWidth - gameOverSurface->w) / 2,
        (windowHeight - gameOverSurface->h) / 3, // Positionné au tiers supérieur
        gameOverSurface->w,
        gameOverSurface->h};

    // Score avec la police normale
    char scoreText[32];
    sprintf(scoreText, "Score Final: %d", score);
    SDL_Surface *scoreSurface = TTF_RenderText_Solid(normalFont, scoreText, textColor);
    SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

    SDL_Rect scoreRect = {
        (windowWidth - scoreSurface->w) / 2,
        gameOverRect.y + gameOverRect.h + 30, // 30 pixels sous le Game Over
        scoreSurface->w,
        scoreSurface->h};

    // Message pour quitter avec la police normale
    SDL_Surface *quitSurface = TTF_RenderText_Solid(normalFont, "Appuyez sur 'A' pour quitter", textColor);
    SDL_Texture *quitTexture = SDL_CreateTextureFromSurface(renderer, quitSurface);

    SDL_Rect quitRect = {
        (windowWidth - quitSurface->w) / 2,
        scoreRect.y + scoreRect.h + 30, // 30 pixels sous le score
        quitSurface->w,
        quitSurface->h};

    // Rendre tous les textes
    SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    SDL_RenderCopy(renderer, quitTexture, NULL, &quitRect);

    SDL_RenderPresent(renderer);

    // Nettoyer les ressources
    SDL_FreeSurface(gameOverSurface);
    SDL_DestroyTexture(gameOverTexture);
    SDL_FreeSurface(scoreSurface);
    SDL_DestroyTexture(scoreTexture);
    SDL_FreeSurface(quitSurface);
    SDL_DestroyTexture(quitTexture);
    TTF_CloseFont(gameOverFont);
    TTF_CloseFont(normalFont);
}

void draw_choice_buttons(const char *title, const char *button1_text, const char *button2_text) {
    SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
    SDL_RenderClear(renderer);

    // Afficher le titre
    SDL_Color textColor = {70, 70, 70, 255};
    SDL_Surface *titleSurface = TTF_RenderText_Solid(font, title, textColor);
    SDL_Texture *titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);

    SDL_Rect titleRect = {
        (800 - titleSurface->w) / 2,
        100,
        titleSurface->w,
        titleSurface->h};

    SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
    SDL_FreeSurface(titleSurface);
    SDL_DestroyTexture(titleTexture);

    // Créer les deux boutons
    Button buttons[] = {
        {{(800 - BUTTON_WIDTH) / 2, 250, BUTTON_WIDTH, BUTTON_HEIGHT}, (char *)button1_text, 1},
        {{(800 - BUTTON_WIDTH) / 2, 350, BUTTON_WIDTH, BUTTON_HEIGHT}, (char *)button2_text, 2}};

    // Dessiner les boutons
    for (int i = 0; i < 2; i++) {
        draw_button(renderer, buttons[i], font);
    }

    SDL_RenderPresent(renderer);
}

void draw_button(SDL_Renderer *renderer, Button button, TTF_Font *font) {
    // Couleur de fond du bouton

    SDL_SetRenderDrawColor(renderer, 200, 200, 255, 255);

    SDL_RenderFillRect(renderer, &button.rect);

    // Bordure du bouton
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderDrawRect(renderer, &button.rect);

    // Texte du bouton
    SDL_Color textColor = {70, 70, 70, 255};
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, button.text, textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect = {
        button.rect.x + (button.rect.w - textSurface->w) / 2,
        button.rect.y + (button.rect.h - textSurface->h) / 2,
        textSurface->w,
        textSurface->h};

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

int show_load_new_choice(int mode, int size) {
    SDL_Event event;
    int running = 1;
    int has_saved_game = has_save(mode, size);

    // Si aucune sauvegarde n'existe, retourner directement nouvelle partie
    if (!has_saved_game && mode != 3) {
        return 0; // 0 pour nouvelle partie
    }

    const char *title;
    const char *button1_text;
    const char *button2_text;

    if (mode == 3) {
        title = "Choisissez votre option:";
        button1_text = "Charger un puzzle";
        button2_text = "Générer un nouveau puzzle";
    } else {
        title = "Une sauvegarde existe. Que souhaitez-vous faire ?";
        button1_text = "Charger la partie";
        button2_text = "Nouvelle partie";
    }

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return -1; // Code spécial pour quitter
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                // Vérifier les clics sur les boutons
                SDL_Rect button1 = {(800 - BUTTON_WIDTH) / 2, 250, BUTTON_WIDTH, BUTTON_HEIGHT};
                SDL_Rect button2 = {(800 - BUTTON_WIDTH) / 2, 350, BUTTON_WIDTH, BUTTON_HEIGHT};

                if (mouseX >= button1.x && mouseX <= button1.x + button1.w &&
                    mouseY >= button1.y && mouseY <= button1.y + button1.h) {
                    return 1; // Charger partie/puzzle
                }

                if (mouseX >= button2.x && mouseX <= button2.x + button2.w &&
                    mouseY >= button2.y && mouseY <= button2.y + button2.h) {
                    return 0; // Nouvelle partie/générer puzzle
                }
            }
        }

        draw_choice_buttons(title, button1_text, button2_text);
        SDL_Delay(10);
    }

    return -1;
}

void show_size_selector(SDL_Renderer *renderer, TTF_Font *font) {
    int buttonSpacing = 20;
    int buttonWidth = 50;
    int buttonHeight = 50;
    int totalWidth = (6 * buttonWidth) + (5 * buttonSpacing);
    int startX = (800 - totalWidth) / 2;
    int startY = 300;

    SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
    SDL_RenderClear(renderer);

    // Afficher le texte "Choisissez la taille de la grille :"
    SDL_Color textColor = {70, 70, 70, 255};
    SDL_Surface *titleSurface = TTF_RenderText_Solid(font, "Choisissez la taille de la grille:", textColor);
    SDL_Texture *titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);

    SDL_Rect titleRect = {
        (800 - titleSurface->w) / 2,
        200,
        titleSurface->w,
        titleSurface->h};

    SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
    SDL_FreeSurface(titleSurface);
    SDL_DestroyTexture(titleTexture);

    // Dessiner les boutons de taille
    for (int i = 4; i <= 9; i++) {
        SDL_Rect buttonRect = {
            startX + ((i - 4) * (buttonWidth + buttonSpacing)),
            startY,
            buttonWidth,
            buttonHeight};

        SDL_SetRenderDrawColor(renderer, 200, 200, 255, 255);
        SDL_RenderFillRect(renderer, &buttonRect);

        char sizeText[3];
        sprintf(sizeText, "%d", i);
        SDL_Surface *numSurface = TTF_RenderText_Solid(font, sizeText, textColor);
        SDL_Texture *numTexture = SDL_CreateTextureFromSurface(renderer, numSurface);

        SDL_Rect numRect = {
            buttonRect.x + (buttonWidth - numSurface->w) / 2,
            buttonRect.y + (buttonHeight - numSurface->h) / 2,
            numSurface->w,
            numSurface->h};

        SDL_RenderCopy(renderer, numTexture, NULL, &numRect);
        SDL_FreeSurface(numSurface);
        SDL_DestroyTexture(numTexture);
    }

    SDL_RenderPresent(renderer);
}

int menu_demarrage(int *n, int *mode) {
    int window_width = 800;
    int window_height = 600;
    SDL_SetWindowSize(window, window_width, window_height);

    Button buttons[] = {
        {{(window_width - BUTTON_WIDTH) / 2, 150, BUTTON_WIDTH, BUTTON_HEIGHT}, "Mode Classique", 1},
        {{(window_width - BUTTON_WIDTH) / 2, 250, BUTTON_WIDTH, BUTTON_HEIGHT}, "Mode Duo", 2},
        {{(window_width - BUTTON_WIDTH) / 2, 350, BUTTON_WIDTH, BUTTON_HEIGHT}, "Mode Puzzle", 3}};

    int size_selection = 0;
    SDL_Event event;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return 0;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                if (!size_selection) {
                    // Vérifier si un bouton de mode est cliqué
                    for (int i = 0; i < 3; i++) {
                        if (mouseX >= buttons[i].rect.x &&
                            mouseX <= buttons[i].rect.x + buttons[i].rect.w &&
                            mouseY >= buttons[i].rect.y &&
                            mouseY <= buttons[i].rect.y + buttons[i].rect.h) {
                            *mode = buttons[i].mode;
                            if (*mode != 3) {
                                size_selection = 1; // Passer à la sélection de taille
                            } else {
                                // Pour le mode puzzle, aller directement au choix charger/générer
                                int choice = show_load_new_choice(*mode, 4);
                                if (choice == -1)
                                    return 0;      // Quitter
                                *n = 5;            // Taille par défaut pour le puzzle
                                return choice + 1; // Retourner 2 pour charger, 1 pour nouveau
                            }
                            break;
                        }
                    }
                } else {
                    // Vérifier si une taille est cliquée
                    int buttonSpacing = 20;
                    int buttonWidth = 50;
                    int totalWidth = (6 * buttonWidth) + (5 * buttonSpacing);
                    int startX = (window_width - totalWidth) / 2;
                    int startY = 300;

                    for (int i = 4; i <= 9; i++) {
                        SDL_Rect sizeRect = {
                            startX + ((i - 4) * (buttonWidth + buttonSpacing)),
                            startY,
                            buttonWidth,
                            BUTTON_HEIGHT};

                        if (mouseX >= sizeRect.x &&
                            mouseX <= sizeRect.x + sizeRect.w &&
                            mouseY >= sizeRect.y &&
                            mouseY <= sizeRect.y + sizeRect.h) {
                            *n = i;
                            // Montrer l'écran de choix charger/nouvelle partie
                            int choice = show_load_new_choice(*mode, *n);
                            if (choice == -1)
                                return 0;      // Quitter
                            return choice + 1; // Retourner 2 pour charger, 1 pour nouveau
                        }
                    }
                }
            }
        }

        // Affichage
        SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
        SDL_RenderClear(renderer);

        if (!size_selection) {
            // Afficher le titre
            SDL_Color textColor = {70, 70, 70, 255};
            SDL_Surface *titleSurface = TTF_RenderText_Solid(font, "2048 - Choisissez votre mode de jeu", textColor);
            SDL_Texture *titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);

            SDL_Rect titleRect = {
                (window_width - titleSurface->w) / 2,
                50,
                titleSurface->w,
                titleSurface->h};

            SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
            SDL_FreeSurface(titleSurface);
            SDL_DestroyTexture(titleTexture);

            // Afficher les boutons de mode
            for (int i = 0; i < 3; i++) {
                draw_button(renderer, buttons[i], font);
            }
        } else {
            show_size_selector(renderer, font);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    return 1;
}

// Initialiser SDL et créer la fenêtre
int initSDL(int windowWidth, int windowHeight) {
    SDL_SetHint(SDL_HINT_VIDEODRIVER, "x11");
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Échec de l'initialisation de SDL : %s\n", SDL_GetError());
        return 0;
    }

    if (TTF_Init() < 0) {
        printf("Échec de l'initialisation de TTF : %s\n", TTF_GetError());
        return 0;
    }

    window = SDL_CreateWindow("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Échec de la création de la fenêtre : %s\n", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer) {
        printf("Échec de la création du renderer : %s\n", SDL_GetError());
        return 0;
    }

    font = TTF_OpenFont("resources/font.ttf", 24);
    if (!font) {
        printf("Échec du chargement de la police : %s\n", TTF_GetError());
        return 0;
    }

    return 1;
}

// Libérer les ressources SDL
void cleanupSDL() {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

// Obtenir la couleur pour une valeur spécifique
SDL_Color getColorForValue(int value) {
    unsigned int index = 0;
    int temp = value;
    while (temp > 2 && index < sizeof(COLORS) / sizeof(COLORS[0]) - 1) {
        temp /= 2;
        index++;
    }
    return COLORS[index];
}

/** Affiche le terrain de jeu du 2048enC dans la console.
 * @param n      : La taille du tableau (assumant que c'est un tableau carré nxn).
 * @param T      : Le tableau bidimensionnel représentant le terrain de jeu.
 * @param Score  : Pointeur vers la variable contenant le score actuel.
 */
void affiche(int n, int T[n][n], int *Score) {
    SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
    SDL_RenderClear(renderer);

    // Afficher le score
    char scoreText[32];
    sprintf(scoreText, "Score: %d", *Score);
    SDL_Color textColor = {70, 70, 70, 255};
    SDL_Surface *scoreSurface = TTF_RenderText_Solid(font, scoreText, textColor);
    SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_Rect scoreRect = {10, 10, scoreSurface->w, scoreSurface->h};
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    SDL_FreeSurface(scoreSurface);
    SDL_DestroyTexture(scoreTexture);

    // Dessiner la grille
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            SDL_Rect cellRect = {
                j * (CELL_SIZE + CELL_PADDING) + CELL_PADDING,
                i * (CELL_SIZE + CELL_PADDING) + CELL_PADDING + 50,
                CELL_SIZE,
                CELL_SIZE};

            if (T[i][j] == -1) {
                // Couleur pour l'obstacle
                SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
                SDL_RenderFillRect(renderer, &cellRect);

                // Ajouter un contour pour distinguer
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
                SDL_RenderDrawRect(renderer, &cellRect);
            } else if (T[i][j] != 0) {
                // Dessiner la tuile
                SDL_Color color = getColorForValue(T[i][j]);
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                SDL_RenderFillRect(renderer, &cellRect);

                // Dessiner le numéro
                char numText[8];
                sprintf(numText, "%d", T[i][j]);
                SDL_Surface *numSurface = TTF_RenderText_Solid(font, numText, textColor);
                SDL_Texture *numTexture = SDL_CreateTextureFromSurface(renderer, numSurface);

                SDL_Rect numRect = {
                    cellRect.x + (CELL_SIZE - numSurface->w) / 2,
                    cellRect.y + (CELL_SIZE - numSurface->h) / 2,
                    numSurface->w,
                    numSurface->h};

                SDL_RenderCopy(renderer, numTexture, NULL, &numRect);
                SDL_FreeSurface(numSurface);
                SDL_DestroyTexture(numTexture);
            } else {
                // Dessiner la case vide
                SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
                SDL_RenderFillRect(renderer, &cellRect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

/**
 * Affiche deux tableaux du jeu 2048enC côte à côte dans la console.
 * @param n     : La taille des tableaux (assumant qu'il s'agit de tableaux carrés nxn).
 * @param T1    : Le premier tableau bidimensionnel à afficher.
 * @param T2    : Le deuxième tableau bidimensionnel à afficher.
 * @param score : Pointeur vers la variable contenant le score actuel.
 */
void affiche_duo(int n, int T1[n][n], int T2[n][n], int *score) {
    SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
    SDL_RenderClear(renderer);

    // Calculer les dimensions pour l'écran divisé
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    SDL_Color textColor = {70, 70, 70, 255};
    char scoreText[32];
    sprintf(scoreText, "Score: %d", *score);
    SDL_Surface *scoreSurface = TTF_RenderText_Solid(font, scoreText, textColor);
    SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_Rect scoreRect = {10, 10, scoreSurface->w, scoreSurface->h};
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    SDL_FreeSurface(scoreSurface);
    SDL_DestroyTexture(scoreTexture);

    // Dessiner la première grille
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            SDL_Rect cellRect = {
                j * (CELL_SIZE + CELL_PADDING) + CELL_PADDING,
                i * (CELL_SIZE + CELL_PADDING) + CELL_PADDING + 50,
                CELL_SIZE,
                CELL_SIZE};

            if (T1[i][j] == -1) {
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Couleur des obstacles
                SDL_RenderFillRect(renderer, &cellRect);
            } else if (T1[i][j] != 0) {
                SDL_Color color = getColorForValue(T1[i][j]);
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                SDL_RenderFillRect(renderer, &cellRect);

                char numText[8];
                sprintf(numText, "%d", T1[i][j]);
                SDL_Surface *numSurface = TTF_RenderText_Solid(font, numText, textColor);
                SDL_Texture *numTexture = SDL_CreateTextureFromSurface(renderer, numSurface);

                SDL_Rect numRect = {
                    cellRect.x + (CELL_SIZE - numSurface->w) / 2,
                    cellRect.y + (CELL_SIZE - numSurface->h) / 2,
                    numSurface->w,
                    numSurface->h};

                SDL_RenderCopy(renderer, numTexture, NULL, &numRect);
                SDL_FreeSurface(numSurface);
                SDL_DestroyTexture(numTexture);
            } else {
                SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255); // Couleur des cases vides
                SDL_RenderFillRect(renderer, &cellRect);
            }
        }
    }

    // Dessiner la deuxième grille
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            SDL_Rect cellRect = {
                (n + 1) * (CELL_SIZE + CELL_PADDING) + j * (CELL_SIZE + CELL_PADDING) + CELL_PADDING,
                i * (CELL_SIZE + CELL_PADDING) + CELL_PADDING + 50,
                CELL_SIZE,
                CELL_SIZE};

            if (T2[i][j] == -1) {
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
                SDL_RenderFillRect(renderer, &cellRect);
            } else if (T2[i][j] != 0) {
                SDL_Color color = getColorForValue(T2[i][j]);
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                SDL_RenderFillRect(renderer, &cellRect);

                char numText[8];
                sprintf(numText, "%d", T2[i][j]);
                SDL_Surface *numSurface = TTF_RenderText_Solid(font, numText, textColor);
                SDL_Texture *numTexture = SDL_CreateTextureFromSurface(renderer, numSurface);

                SDL_Rect numRect = {
                    cellRect.x + (CELL_SIZE - numSurface->w) / 2,
                    cellRect.y + (CELL_SIZE - numSurface->h) / 2,
                    numSurface->w,
                    numSurface->h};

                SDL_RenderCopy(renderer, numTexture, NULL, &numRect);
                SDL_FreeSurface(numSurface);
                SDL_DestroyTexture(numTexture);
            } else {
                SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
                SDL_RenderFillRect(renderer, &cellRect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}
