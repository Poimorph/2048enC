#include "functions.h"

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

// Constants pour les coleurs et dimensions
#define CELL_SIZE 100
#define CELL_PADDING 10
#define ANIMATION_SPEED 0.1

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
    {240, 255, 229, 255} 
};

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;
Animation animations[81][81];  // taille maximm pour les grilles 9x9



// Initialiser SDL et créer la fenêtre
int initSDL(int n) {
    SDL_SetHint(SDL_HINT_VIDEODRIVER, "x11");
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Échec de l'initialisation de SDL : %s\n", SDL_GetError());
        return 0;
    }

    if (TTF_Init() < 0) {
        printf("Échec de l'initialisation de TTF : %s\n", TTF_GetError());
        return 0;
    }

    int windowWidth = n * (CELL_SIZE + CELL_PADDING) + CELL_PADDING;
    int windowHeight = n * (CELL_SIZE + CELL_PADDING) + CELL_PADDING + 50; // Espace supplémentaire pour le score

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
    int index = 0;
    int temp = value;
    while (temp > 2 && index < sizeof(COLORS)/sizeof(COLORS[0]) - 1) {
        temp /= 2;
        index++;
    }
    return COLORS[index];
}

// Créer une animation pour le mouvement d'une tuile
void createAnimation(int startX, int startY, int endX, int endY, int value) {
    animations[startX][startY].startX = startX * (CELL_SIZE + CELL_PADDING) + CELL_PADDING;
    animations[startX][startY].startY = startY * (CELL_SIZE + CELL_PADDING) + CELL_PADDING;
    animations[startX][startY].endX = endX * (CELL_SIZE + CELL_PADDING) + CELL_PADDING;
    animations[startX][startY].endY = endY * (CELL_SIZE + CELL_PADDING) + CELL_PADDING;
    animations[startX][startY].currentX = animations[startX][startY].startX;
    animations[startX][startY].currentY = animations[startX][startY].startY;
    animations[startX][startY].value = value;
    animations[startX][startY].progress = 0;
    animations[startX][startY].active = 1;
}

// Mettre à jour et afficher les animations
void updateAnimations() {
    for (int i = 0; i < 81; i++) {
        for (int j = 0; j < 81; j++) {
            if (animations[i][j].active) {
                animations[i][j].progress += ANIMATION_SPEED;
                
                if (animations[i][j].progress >= 1.0) {
                    animations[i][j].active = 0;
                } else {
                    animations[i][j].currentX = animations[i][j].startX + 
                        (animations[i][j].endX - animations[i][j].startX) * animations[i][j].progress;
                    animations[i][j].currentY = animations[i][j].startY + 
                        (animations[i][j].endY - animations[i][j].startY) * animations[i][j].progress;
                    
                    // Afficher la tuile animée
                    SDL_Rect tileRect = {
                        animations[i][j].currentX,
                        animations[i][j].currentY,
                        CELL_SIZE,
                        CELL_SIZE
                    };
                    
                    SDL_Color color = getColorForValue(animations[i][j].value);
                    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                    SDL_RenderFillRect(renderer, &tileRect);
                }
            }
        }
    }
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
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText, textColor);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
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
                CELL_SIZE
            };

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
                SDL_Surface* numSurface = TTF_RenderText_Solid(font, numText, textColor);
                SDL_Texture* numTexture = SDL_CreateTextureFromSurface(renderer, numSurface);
                
                SDL_Rect numRect = {
                    cellRect.x + (CELL_SIZE - numSurface->w) / 2,
                    cellRect.y + (CELL_SIZE - numSurface->h) / 2,
                    numSurface->w,
                    numSurface->h
                };
                
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
    
    // Mettre à jour et afficher les animations
    updateAnimations();

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
    int totalWidth = n * (CELL_SIZE + CELL_PADDING) * 2 + CELL_PADDING * 3;
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    SDL_Color textColor = {70, 70, 70, 255};
    char scoreText[32];
    sprintf(scoreText, "Score: %d", *score);
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText, textColor);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
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
                CELL_SIZE
            };

            if (T1[i][j] == -1) {
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);  // Couleur des obstacles
                SDL_RenderFillRect(renderer, &cellRect);
            } else if (T1[i][j] != 0) {
                SDL_Color color = getColorForValue(T1[i][j]);
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                SDL_RenderFillRect(renderer, &cellRect);

                char numText[8];
                sprintf(numText, "%d", T1[i][j]);
                SDL_Surface* numSurface = TTF_RenderText_Solid(font, numText, textColor);
                SDL_Texture* numTexture = SDL_CreateTextureFromSurface(renderer, numSurface);

                SDL_Rect numRect = {
                    cellRect.x + (CELL_SIZE - numSurface->w) / 2,
                    cellRect.y + (CELL_SIZE - numSurface->h) / 2,
                    numSurface->w,
                    numSurface->h
                };

                SDL_RenderCopy(renderer, numTexture, NULL, &numRect);
                SDL_FreeSurface(numSurface);
                SDL_DestroyTexture(numTexture);
            } else {
                SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);  // Couleur des cases vides
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
                CELL_SIZE
            };

            if (T2[i][j] == -1) {
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
                SDL_RenderFillRect(renderer, &cellRect);
            } else if (T2[i][j] != 0) {
                SDL_Color color = getColorForValue(T2[i][j]);
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                SDL_RenderFillRect(renderer, &cellRect);

                char numText[8];
                sprintf(numText, "%d", T2[i][j]);
                SDL_Surface* numSurface = TTF_RenderText_Solid(font, numText, textColor);
                SDL_Texture* numTexture = SDL_CreateTextureFromSurface(renderer, numSurface);

                SDL_Rect numRect = {
                    cellRect.x + (CELL_SIZE - numSurface->w) / 2,
                    cellRect.y + (CELL_SIZE - numSurface->h) / 2,
                    numSurface->w,
                    numSurface->h
                };

                SDL_RenderCopy(renderer, numTexture, NULL, &numRect);
                SDL_FreeSurface(numSurface);
                SDL_DestroyTexture(numTexture);
            } else {
                SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
                SDL_RenderFillRect(renderer, &cellRect);
            }
        }
    }

    // Mettre à jour et rendre les animations pour les deux grilles
    updateAnimations();
    
    SDL_RenderPresent(renderer);
}