#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


/** Affiche le terrain de jeu du 2048enC dans la console.
     * @param n      : La taille du tableau (assumant que c'est un tableau carré nxn).
     * @param T      : Le tableau bidimensionnel représentant le terrain de jeu.
     * @param Score  : Pointeur vers la variable contenant le score actuel.
     */
void affiche(int n, int T[n][n], int *Score) {




    // Affiche le score actuel
    printf("Score Actuel : %d\n", *Score);

    // Parcours le tableau et affiche chaque élément
    for (int i = 0; i < n; i++) {
        for (int y = 0; y < n; y++) {
            if (T[i][y] == -1) {
                // La lettre X est représentée par -1 dans le tableau
                printf("%-7c", 'X');
            } else {
                // Affiche la valeur du tableau
                printf("%-7d", T[i][y]);
            }
        }
        printf("\n");
    }
}

/**
     * Affiche deux tableaux du jeu 2048enC côte à côte dans la console.
     * @param n     : La taille des tableaux (assumant qu'il s'agit de tableaux carrés nxn).
     * @param T1    : Le premier tableau bidimensionnel à afficher.
     * @param T2    : Le deuxième tableau bidimensionnel à afficher.
     * @param score : Pointeur vers la variable contenant le score actuel.
     */
void affiche_duo(int n, int T1[n][n], int T2[n][n], int *score) {



    // Affiche le score actuel
    printf("Score Actuel ! %d\n", *score);

    // Parcours les deux tableaux et affiche chaque élément côte à côte
    for (int i = 0; i < n; i++) {
        for (int y = 0; y < n; y++) {
            printf("%-7d", T1[i][y]);
        }
        // Ajoute des espaces pour séparer les deux tableaux
        printf("%-7s", "    ");
        for (int m = 0; m < n; m++) {
            printf("%-7d", T2[i][m]);
        }
        printf("\n");
    }
}

int compare(int value1, int value2){
    /* Fonction simple de comparaison de deux valeur */
    if (value1 == value2){
        return 1;
    }
    else {
        return 0;
    }}

void add_case(int length,int Tab[length][length], int *score){
    /* Ajoute une case de valeur compris entre {2, 4}*/

    // On prend des valeurs aléatoires pour les coordonnées X et Y
    int x = (rand()%length);
    int y = (rand()%length);

    while (Tab[y][x] != 0 && y < length && x < length){ // On cherche pour quelles coordonnées X et Y la case peut être ajouté
        x = (rand()%length);
        y = (rand()%length);
    }
    int newValue=(rand()%2+1)*2; // Nous définissons la valeur de la case ajouté
    Tab[y][x] = newValue;
    *score += newValue; // Nous augmentons le score
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

    int caseLibre[n][2], traker=0, index=0; // tableau pour suivre les cases libres, variables de suivi
    int moveHappend=0; //indicateur de mouvement
    switch (sens) {
        case 'd':
            // Déplacement vers la droite
            for (int x = 0; x < n; x++) {
                traker = 0; // initialise le suivi des cases libres
                index = 0; // initialise l'index des cases libres
                for (int y = n - 1; y >= 0; y--) {
                    if (T[x][y] != -1)// verifie que la valeur de la case n'est pas un X du mode Puzzle
                    {
                        if (T[x][y] == 0) {
                            // Stocke la position des cases libres
                            caseLibre[traker][0] = x;
                            caseLibre[traker][1] = y;
                            traker++;
                        } else if (traker != 0) {
                            // Déplace la case non nulle vers la case libre
                            int i = caseLibre[index][0], j = caseLibre[index][1];
                            T[i][j] = T[x][y];
                            T[x][y] = 0;

                            // Met à jour les informations sur les cases libres
                            caseLibre[traker][0] = x;
                            caseLibre[traker][1] = y;
                            traker++;
                            index++;

                            moveHappend=1; // Indique qu'un mouvement a eu lieu
                        }
                    }
                }
            }
            break;
        case 'q':
            // Déplacement vers la gauche
            for (int x = 0; x < n; x++) {
                traker = 0; // initialise le suivi des cases libres
                index = 0; // initialise l'index des cases libres
                for (int y = 0; y < n; y++) {
                    if (T[x][y] != -1)// verifie que la valeur de la case n'est pas un X du mode Puzzle
                    {
                        if (T[x][y] == 0) {
                            // Stocke la position des cases libres
                            caseLibre[traker][0] = x;
                            caseLibre[traker][1] = y;
                            traker++;
                        } else if (traker != 0) {
                            // Déplace la case non nulle vers la case libre
                            int i = caseLibre[index][0], j = caseLibre[index][1];
                            T[i][j] = T[x][y];
                            T[x][y] = 0;

                            // Met à jour les informations sur les cases libres
                            caseLibre[traker][0] = x;
                            caseLibre[traker][1] = y;
                            traker++;
                            index++;

                            moveHappend=1; // Indique qu'un mouvement a eu lieu
                        }
                    }
                    else{
                        index=traker;
                        }
                    }
                }
            break;
        case 'z':
            // Déplacement vers le haut
            for (int y = 0; y < n; y++) {
                traker = 0; // initialise le suivi des cases libres
                index = 0; // initialise l'index des cases libres
                for (int x = 0; x < n; x++) {
                    if (T[x][y] != -1)// verifie que la valeur de la case n'est pas un X du mode Puzzle
                    {
                        if (T[x][y] == 0) {
                            // Stocke la position des cases libres
                            caseLibre[traker][0] = x;
                            caseLibre[traker][1] = y;
                            traker++;
                        } else if (traker != 0) {
                            // Déplace la case non nulle vers la case libre
                            int i = caseLibre[index][0], j = caseLibre[index][1];
                            T[i][j] = T[x][y];
                            T[x][y] = 0;

                            // Met à jour les informations sur les cases libres
                            caseLibre[traker][0] = x;
                            caseLibre[traker][1] = y;
                            traker++;
                            index++;

                            moveHappend=1; // Indique qu'un mouvement a eu lieu
                        }
                    }
                    else{
                        index=traker;
                    }
                }
            }
            break;
        case 's':
            // Déplacement vers le bas
            for (int y = 0; y < n; y++) {
                traker = 0; // initialise le suivi des cases libres
                index = 0; // initialise l'index des cases libres
                for (int x = n - 1; x >= 0; x--) {
                    if (T[x][y] != -1) // verifie que la valeur de la case n'est pas un X du mode Puzzle
                    {
                        if (T[x][y] == 0) {
                            // Stocke la position des cases libres
                            caseLibre[traker][0] = x;
                            caseLibre[traker][1] = y;
                            traker++;
                        } else if (traker != 0) {
                            // Déplace la case non nulle vers la case libre
                            int i = caseLibre[index][0], j = caseLibre[index][1];
                            T[i][j] = T[x][y];
                            T[x][y] = 0;

                            // Met à jour les informations sur les cases libres
                            caseLibre[traker][0] = x;
                            caseLibre[traker][1] = y;
                            traker++;
                            index++;

                            moveHappend=1; // Indique qu'un mouvement a eu lieu
                        }
                    }
                    else{
                        index=traker;
                    }
                }
            }
            break;
        default:
            break;
    }
    return moveHappend;
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
    int fuseHappend=0; // Indicateur de fusion
    switch (sensRotation) {

        // Fusion des éléments en direction de la droite
        case 'd':
            for (int x = 0; x < n; x++) {
                for (int y = n - 1; y >= 0; y--) { // Parcours de droite à gauche
                    for (int j = y - 1; j >= 0; j--) {
                        if (compare(Tab[x][y], Tab[x][j])) {
                            // Fusionne deux éléments identiques
                            Tab[x][y] = Tab[x][y] * 2;
                            Tab[x][j] = 0;
                            if(Tab[x][y]!=0){
                                fuseHappend=1; // Indique qu'une fusion a eu lieu
                            }
                            j = -1; // Sort de la boucle interne
                        } else if (Tab[x][j] != 0) {
                            j = -1; // Sort de la boucle interne
                        }
                    }
                }
            }
            break;

            // Fusion des éléments en direction de la gauche
        case 'q':
            for (int x = 0; x < n; x++) {
                for (int y = 0; y < n; y++) {
                    for (int j = y + 1; j < n; j++) {
                        if (compare(Tab[x][y], Tab[x][j])) {
                            // Fusionne deux éléments identiques
                            Tab[x][y] += Tab[x][j];
                            Tab[x][j] = 0;
                            if(Tab[x][y]!=0){
                                fuseHappend=1; // Indique qu'une fusion a eu lieu
                            }
                            j = n; // Sort de la boucle interne
                        } else if (Tab[x][j] != 0) {
                            j = n; // Sort de la boucle interne
                        }
                    }
                }
            }
            break;

            // Fusion des éléments en direction du haut
        case 'z':
            for (int y = 0; y < n; y++) {
                for (int x = 0; x < n; x++) {
                    for (int j = x + 1; j < n; j++) {
                        if (compare(Tab[x][y], Tab[j][y])) {
                            // Fusionne deux éléments identiques
                            Tab[x][y] = 2 * Tab[x][y];
                            Tab[j][y] = 0;
                            if(Tab[x][y]!=0){
                            fuseHappend=1; // Indique qu'une fusion a eu lieu
                            }
                            j = n; // Sort de la boucle interne
                        } else if (Tab[j][y] != 0) {
                            j = n; // Sort de la boucle interne
                        }
                    }
                }
            }
            break;

            // Fusion des éléments en direction du bas
        case 's':
            for (int y = 0; y < n; y++) {
                for (int x = n - 1; x >= 0; x--) {
                    for (int j = x - 1; j >= 0; j--) {
                        if (compare(Tab[x][y], Tab[j][y])) {
                            // Fusionne deux éléments identiques
                            Tab[x][y] += Tab[j][y];
                            Tab[j][y] = 0;
                            if(Tab[x][y]!=0){
                                fuseHappend=1; // Indique qu'une fusion a eu lieu
                            }
                            j = -1; // Sort de la boucle interne
                        } else if (Tab[j][x] != 0) {
                            j = -1; // Sort de la boucle interne
                        }
                    }
                }
            }
            break;

        default:
            break;
    }
    return fuseHappend;
}
void creationTab(int n,int T[n][n]){
    /*Créer un tableaux à double dimensions vide*/
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            T[i][j]=0;
        }
    }
}
/**
 * Fonction principale du mode duo du jeu 2048enC.
 * Permet à un joueur de jouer sur deux grilles distinctes en parallèle.
 * @param n Taille des tableaux T1 et T2
 * @param T1 Premier tableau de jeu
 * @param T2 Deuxième tableau de jeu
 * @param score Pointeur vers la variable de score
 */
void duo(int n, int T1[n][n], int T2[n][n], int *score){
    /* Fonction principale du mode duo*/

    int jouer = 1;  // Variable de contrôle pour la boucle principale du jeu.
    char direction;  // Variable pour stocker la direction choisie par le joueur.

    // Préparation du mode de jeu
    creationTab(n, T1);  // Initialisation du tableau T1.
    creationTab(n, T2);  // Initialisation du tableau T2.
    add_case(n, T1, score);  // Ajout d'une case aléatoire dans le tableau T1.
    add_case(n, T2, score);  // Ajout d'une case aléatoire dans le tableau T2.
    affiche_duo(n, T1, T2, score);  // Affichage des deux tableaux et du score.

    // Variables pour suivre les événements de fusion et de mouvement :
    int fusionHappend1, movementHappend1, fusionHappend2, movementHappend2;

    // Boucle principale du jeu
    while (jouer) {
        printf("dans quel direction voulez vous aller ? \nZ pour se deplacer vers le haut\nS pour se deplacer vers le bas\nD pour se deplacer vers la droite\nQ pour se deplacer vers la gauche\nA pour quitter\n");
        scanf("%c", &direction);  // Récupération du choix du joueur.
        fflush(stdin);
        direction = tolower(direction);  // Conversion de la direction en minuscule pour simplifier la gestion.

        if (direction == 'a') {
            jouer = 0;  // Si le joueur décide de mettre fin à sa partie.
        }
        else {
            // Opérations de fusion et de mouvement dans les deux tableaux.
            fusionHappend1 = fusion(n, T1, direction);
            fusionHappend2 = fusion(n, T2, direction);
            movementHappend1 = move(n, T1, direction);
            movementHappend2 = move(n, T2, direction);

            // Si une fusion ou un mouvement a eu lieu dans l'un des tableaux, ajoute une nouvelle case aléatoire dans le même tableau.
            if (fusionHappend1 || movementHappend1) {
                add_case(n, T1, score);
            }
            if (fusionHappend2 || movementHappend2) {
                add_case(n, T2, score);
            }

            // Affichage des deux tableaux et du score.
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
void normal(int n, int T1[n][n], int *score) {
    /* Fonction principale du mode normal */

    int jouer = 1;  // Variable de contrôle pour la boucle principale du jeu.
    char dir;       // Variable pour stocker la direction choisie par le joueur.
    char rep = 'd'; // Variable pour la réponse du joueur concernant la reprise de la sauvegarde.

    // Tentative de récupération du fichier de sauvegarde
    FILE * fichier = NULL;
    fichier = fopen("Save.txt", "r");
    fseek(fichier, 0, SEEK_END);
    int s = ftell(fichier);
    fclose(fichier);

    if (s != 0) { // Si le fichier de sauvegarde existe
        while (rep != 'o' && rep != 'n') {
            printf("Vous avez une partie de sauvegarde, voulez la continuer ? (O/N)");
            scanf("%c", &rep);
            rep = tolower(rep);
            fflush(stdin);
        }

        if (rep == 'o') {
            Lecture(n, T1, score); // Reprendre les données du fichier de sauvegarde et remplir le tableau.
        } else {
            creationTab(n, T1); // Créer un nouveau tableau si le joueur ne souhaite pas reprendre la sauvegarde.
            add_case(n, T1, score);
        }
    } else {
        creationTab(n, T1); // Créer un nouveau tableau si aucun fichier de sauvegarde n'est détecté.
        add_case(n, T1, score);
    }

    affiche(n, T1, score); // Afficher le tableau initial.

    int fusionHappend, movementHappend;

    // Boucle principale du jeu
    while (jouer) {
        printf("Dans quelle direction voulez-vous aller ? \nZ pour se deplacer vers le haut\nS pour se deplacer vers le bas\nD pour se deplacer vers la droite\nQ pour se deplacer vers la gauche\nA pour quitter\n");
        scanf("%c", &dir);
        fflush(stdin);
        dir = tolower(dir);

        if (dir == 'a') {
            jouer = 0; // Si le joueur décide de mettre fin à la partie, sauvegarder le tableau dans un fichier.
            Sauvegarde(n, T1, *score);
        } else {
            fusionHappend = fusion(n, T1, dir);
            movementHappend = move(n, T1, dir);

            if (fusionHappend || movementHappend) {
                add_case(n, T1, score); // Ajouter une nouvelle case aléatoire si une fusion ou un mouvement a eu lieu.
            }

            affiche(n, T1, score); // Afficher le tableau après chaque coup.
        }
    }
}


void puzzle(int *score){
    /*Fonction principale du mode puzzle */
    int jouer = 1;
    char dir;


    //Ouverture du fichier puzzle.
    FILE* f = fopen("../Puzzle/puzzleOne.txt", "r");

    if (f != NULL) {
        //Récupération de la taille du tableaux

        char buffer[256];
        fgets(buffer, 256, f);
        strtok(buffer, " ");

        int n = atoi(strtok(NULL, " "));

        int T1[n][n];



        fgets(buffer, 256, f);
        for (int i = 0; i < n; i++) {
            //Récupération de chaque ligne du tableaux
            char * token = strtok(buffer, "|");
            if (atoi(token) == -1) {// La fonction atoi() convertis un char en Int -> ('7' -> 7)
                T1[i][0] = -1;
            } else {
                T1[i][0] = atoi(token);
            }

            for (int y = 1; y < n; y++) {
                // Récupération de chaque colonne du tableaux
                token = strtok(NULL, "|");

                if (atoi(token) == -1) {
                    T1[i][y] = -1;
                } else {
                    T1[i][y] = atoi(token);
                }
            }
            fgets(buffer, 256, f);
        }


        fclose(f);
        affiche(n, T1, score);
        int fusionHappend,movementHappend;
        while (jouer) {
            //Similaire à la fonction normal() du programme
            printf("dans quel direction voulez vous aller ? \nZ pour se deplacer vers le haut\nS pour se deplacer vers le bas\nD pour se deplacer vers la droite\nQ pour se deplacer vers la gauche\nA pour quitter");
            scanf("%c", &dir);
            fflush(stdin);
            dir=tolower(dir);
            if (dir == 'a') {
                jouer = 0;
            }
            else {
                fusionHappend=fusion(n, T1, dir);
                movementHappend=move(n, T1, dir);
                if(fusionHappend||movementHappend){add_case(n, T1, score);}
                affiche(n, T1, score);
            }

        }
    }
}

void Sauvegarde(int n , int T[n][n], int Score ){
    /*Sauvegarde le contenu du tableaux dans un fichier texte*/
    FILE* fichier = NULL;
    fichier = fopen("Save.txt","w" );// Ecriture dans le fichier de sauvegarde/Création du fichier de sauvegarde si il n'existe pas
    fprintf(fichier, "%d ", n );
    for(int i =0; i<n ; i++){
        for (int y = 0 ; y<n ; y++){
            fprintf(fichier, "%d ", T[i][y] );
        }
    }
    fprintf(fichier, "%d", Score );

    fclose(fichier );
}
void Lecture(int n, int T[n][n] , int* Score){
    /*Lis le contenu d'un fichier de sauvegarde pour le transférer dans un tableaux*/
    FILE* fichier = NULL;

    fichier = fopen("Save.txt", "r");

    if (fichier != NULL)
    {
        fscanf(fichier , "%d", &n);
        for (int i = 0 ; i<n ; i++){
            for (int y = 0 ; y<n ; y++){
                fscanf(fichier , "%d", &T[i][y]);
            }
        }
        fscanf(fichier , "%d", Score );
    }
}




void jeu(int n, int mode) {
    //On initialise la library
    /* Prend en paramètre un Integer qui décide du mode de jeu choisis*/

    int score = 0, T1[n][n], T2[n][n];
    if (mode == 1) {
        normal(n, T1, &score);
    } else if (mode == 2) {
        duo(n, T1, T2, &score);
    } else if (mode == 3){
        puzzle(&score);
    }
}

