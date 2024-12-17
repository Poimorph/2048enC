#include "functions.h"


void duo(int n, int T1[n][n], int T2[n][n], int *score){
    /* Fonction principale du mode duo*/
    int jouer = 1;
    char dir;
    char rep = 'n';

    // Vérifie s'il existe une sauvegarde pour le mode duo
    if (has_save(2, n)) {
        printf("Une partie en mode duo sauvegardée existe pour cette taille.\n");
        printf("Voulez-vous la continuer ? (O/N) ");
        
        do {
            scanf(" %c", &rep);
            rep = tolower(rep);
            while(getchar() != '\n');  // Vide le buffer
            
            if (rep != 'o' && rep != 'n') {
                printf("Veuillez répondre par O (oui) ou N (non) : ");
            }
        } while (rep != 'o' && rep != 'n');
    }

    // Initialisation en fonction de la réponse
    if (rep == 'o') {
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

    int fusionHappend1, movementHappend1, fusionHappend2, movementHappend2;

    while (jouer) {
        printf("\nDirections: [Z]Haut [S]Bas [D]Droite [Q]Gauche [A]Quitter\nVotre choix: ");
        scanf(" %c", &dir);
        while(getchar() != '\n');
        dir = tolower(dir);

        if (dir == 'a') {
            jouer = 0;
            Sauvegarde_duo(n, T1, T2, *score);  // Sauvegarde avant de quitter
        } else if (strchr("zsdq", dir) != NULL) {
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
        }
    }
}

/**
 * Fonction principale du mode normal du jeu 2048enC.
 * Permet à un joueur de jouer en mode normal avec la possibilité de sauvegarder et reprendre la partie.
 * @param n Taille du tableau de jeu
 * @param T1 Tableau de jeu principal
 * @param score Pointeur vers la variable de score
 */
void normal(int n, int T1[n][n], int* score) {
    int jouer = 1;
    char dir;
    char rep = 'n';
    
    // IMPORTANT : Vérifie d'abord s'il existe une sauvegarde
    if (has_save(1, n)) {
        printf("Une partie sauvegardée existe pour ce mode et cette taille.\n");
        printf("Voulez-vous la continuer ? (O/N) ");
        
        do {
            scanf(" %c", &rep);
            rep = tolower(rep);
            while(getchar() != '\n');  // Vide le buffer
            
            if (rep != 'o' && rep != 'n') {
                printf("Veuillez répondre par O (oui) ou N (non) : ");
            }
        } while (rep != 'o' && rep != 'n');
    }
    
    // Initialisation en fonction de la réponse
    if (rep == 'o') {
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
        add_case(n, T1, score);  // Ajoute deux cases au début
    }
    
    affiche(n, T1, score);
    
    // Boucle principale du jeu
    while (jouer) {
        printf("\nDirections: [Z]Haut [S]Bas [D]Droite [Q]Gauche [A]Quitter\nVotre choix: ");
        scanf(" %c", &dir);
        while(getchar() != '\n');
        dir = tolower(dir);
        
        if (dir == 'a') {
            jouer = 0;
            Sauvegarde(n, T1, *score, 1);
        } else if (strchr("zsdq", dir) != NULL) {
            int moved = move(n, T1, dir);
            int fused = fusion(n, T1, dir);
            
            if (fused) {
                moved = move(n, T1, dir) || moved;
            }
            
            if (moved || fused) {
                add_case(n, T1, score);
            }
            
            affiche(n, T1, score);
        }
    }
}


void puzzle(int *score) {
    char choix;
    printf("Voulez-vous charger un puzzle existant (C) ou en générer un nouveau (N) ? ");
    
    do {
        scanf(" %c", &choix);
        choix = tolower(choix);
        while(getchar() != '\n');
        
        if (choix != 'c' && choix != 'n') {
            printf("Veuillez choisir C (charger) ou N (nouveau) : ");
        }
    } while (choix != 'c' && choix != 'n');
    
    int n;
    int T1[9][9];  // Tableau statique de taille maximale
    
    // Initialiser tout le tableau à 0 avant toute autre opération
    memset(T1, 0, sizeof(T1));
    
    if (choix == 'c') {
        // Charger un puzzle existant
        FILE* f = fopen("Puzzle/puzzleOne.txt", "r");
        if (f == NULL) {
            printf("Erreur: Impossible d'ouvrir le fichier puzzle!\n");
            return;
        }
        
        char buffer[256];
        if (fgets(buffer, sizeof(buffer), f) == NULL) {
            printf("Erreur de lecture du fichier puzzle!\n");
            fclose(f);
            return;
        }
        
        if (sscanf(buffer, "%*s %d", &n) != 1) {
            printf("Erreur: Format de fichier incorrect!\n");
            fclose(f);
            return;
        }
        
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
        // Générer un nouveau puzzle
        do {
            printf("Entrez la taille du puzzle (entre 4 et 9) : ");
            scanf("%d", &n);
            while(getchar() != '\n');
            
            if (n < 4 || n > 9) {
                printf("La taille doit être entre 4 et 9.\n");
            }
        } while (n < 4 || n > 9);
        
        // Le tableau est déjà initialisé à 0 grâce au memset
        
        // Ajouter quelques obstacles (X) aléatoirement
        int nbObstacles = n * n / 6;  // Environ 1/6 des cases seront des obstacles
        for (int i = 0; i < nbObstacles; i++) {
            int x, y;
            do {
                x = rand() % n;
                y = rand() % n;
            } while (T1[x][y] != 0);
            T1[x][y] = -1;  // -1 représente un X
        }
        
        // Ajouter quelques nombres initiaux (uniquement 2 ou 4)
        for (int i = 0; i < 2; i++) {
            add_case(n,T1,score);
        }
    }
    
    char dir;
    int jouer = 1;
    *score = 0;
    
    while (jouer) {
        affiche(n, T1, score);
        
        printf("\nDirections: [Z]Haut [S]Bas [D]Droite [Q]Gauche [A]Quitter\nVotre choix: ");
        scanf(" %c", &dir);
        dir = tolower(dir);
        
        if (dir == 'a') {
            jouer = 0;
        } else if (strchr("zsdq", dir) != NULL) {
            int moved = move(n, T1, dir);
            int fused = fusion(n, T1, dir);
            if (fused) {
                moved = move(n, T1, dir) || moved;
            }
            if (moved || fused) {
                add_case(n, T1, score);
            }
        }
    }
}




void jeu(int n, int mode) {
    int score = 0;
    int T1[n][n], T2[n][n];

    ensure_saves_directory();  // S'assure que le dossier saves existe

    switch(mode) {
        case 1:
            normal(n, T1, &score);
            break;
        case 2:
            duo(n, T1, T2, &score);
            break;
        case 3:
            puzzle(&score);
            break;
        default:
            printf("Mode de jeu invalide\n");
    }
}

