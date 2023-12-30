#include <stdio.h>
#include "functions.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

void affiche(int n, int T[n][n],int*Score){
    /* La fonction affiche, print dans la console le terrain de jeu du 2048*/
    printf("Score Actuel : %d\n",*Score);
    for (int i =0; i<n; i++ ){// Nous parcourons le tableaux
        for (int y =0; y<n; y++ ) {
            if (T[i][y] == -1){// Nous avons décidé de la lettre X sera représenté par un -1 dans le tableaux.
                printf("%-7c", 'X');
            } else {
                printf("%-7d", T[i][y]);
            }
        }
        printf("\n");
    }
}

void affiche_duo(int n, int T1[n][n], int T2[n][n], int* score){
    // Meme principe que pour la fonction affiche() seulement ici nous affichons deux tableaux côte à côte
    printf("Score Actuel ! %d\n", *score);
    for (int i = 0; i < n; i++){
        for (int y = 0; y < n; y++){
            printf("%-7d", T1[i][y]);
        }
        printf("%-7s", "    ");
        for (int m = 0; m < n; m++){
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

    while (Tab[y][x] != 0){ // On cherche pour quelles coordonnées X et Y la case peut être ajouté
        x = (rand()%length);
        y = (rand()%length);
    }
    int newValue=(rand()%2+1)*2; // Nous définissons la valeur de la case ajouté
    Tab[y][x] = newValue;
    *score += newValue; // Nous augmentons le score
}

void move(int n, int T[n][n],char sens){
    //Dirige toutes las case non nulles dans la direction souhaité
    int caseLibre[n][2], traker,index;
    switch (sens) {
        case 'd':
            for (int x=0;x<n;x++){
                traker=0;
                index=0;
                for(int y=n-1;y>=0;y--){
                    if (T[x][y] != -1) {
                        if (T[x][y] == 0) {
                            caseLibre[traker][0] = x;
                            caseLibre[traker][1] = y;
                            traker++;
                        } else if (traker != 0) {
                            int i = caseLibre[index][0], j = caseLibre[index][1];
                            T[i][j] = T[x][y];
                            T[x][y] = 0;
                            caseLibre[traker][0] = x;
                            caseLibre[traker][1] = y;
                            traker++;
                            index++;
                        }
                    }
                }
            }
            break;
        case 'q':

            for (int x=0;x<n;x++){
                traker=0;
                index=0;
                for(int y=0;y<n;y++){
                    if (T[x][y] != -1) {
                        if (T[x][y] == 0) {
                            caseLibre[traker][0] = x;
                            caseLibre[traker][1] = y;
                            traker++;
                        } else if (traker != 0) {
                            int i = caseLibre[index][0], j = caseLibre[index][1];
                            T[i][j] = T[x][y];
                            T[x][y] = 0;
                            caseLibre[traker][0] = x;
                            caseLibre[traker][1] = y;
                            traker++;
                            index++;
                        }
                    }
                }
            }
            break;
        case 'z':
            for (int y=0;y<n;y++){
                traker=0;
                index=0;
                for(int x=0;x<n;x++){
                    if (T[x][y] != -1) {
                        if (T[x][y] == 0) {
                            caseLibre[traker][0] = x;
                            caseLibre[traker][1] = y;
                            traker++;
                        } else if (traker != 0) {
                            int i = caseLibre[index][0], j = caseLibre[index][1];
                            T[i][j] = T[x][y];
                            T[x][y] = 0;
                            caseLibre[traker][0] = x;
                            caseLibre[traker][1] = y;
                            traker++;
                            index++;
                        }
                    }
                }
            }

            break;
        case 's':
            for (int y=0;y<n;y++){
                traker=0;
                index=0;
                for(int x=n-1;x>=0;x--){
                    if (T[x][y] != -1) {
                        if (T[x][y] == 0) {
                            caseLibre[traker][0] = x;
                            caseLibre[traker][1] = y;
                            traker++;
                        } else if (traker != 0) {
                            int i = caseLibre[index][0], j = caseLibre[index][1];
                            T[i][j] = T[x][y];
                            T[x][y] = 0;
                            caseLibre[traker][0] = x;
                            caseLibre[traker][1] = y;
                            traker++;
                            index++;
                        }
                    }
                }
            }
            break;
        default:
            break;
    }
}

void fusion(int n, int Tab[n][n], char sensRotation){
    /*    On prendra :
          d pour de gauche à droite
          q pour de droit à gauche
          s pour de haut en bas
          z pour de bas en haut*/

    switch(sensRotation){

        // Le principe du code est le même pour les 4 possibilité du switch

        case 'd':

            for (int x = 0; x < n; x++){
                for (int y = n-1; y >=0; y--){ // Nous parcourons le tableaux de droite à gauche
                    for(int j=y-1;j>=0;j--){
                        if (compare(Tab[x][y], Tab[x][j])){ // J est une variable qui vérifie toujours y-j = 1
                            Tab[x][y] = Tab[x][y]*2;                        //donc nous comparons un élément avec son précéent dans la liste
                            Tab[x][j] = 0;                                  //pour vérifier si ils peuvent être fusionnées
                            j=-1;
                        }
                        else if (Tab[x][j]!=0){ // Si la valeur précédentes à y n'est pas égale à y ni à 0 alors on sort de la boucle.
                            j=-1;
                        }
                    }
                }
            }

            break;
        case 'q':

            for (int x = 0; x < n; x++){
                for (int y = 0; y < n; y++){
                    for(int j=y+1;j<n;j++){
                        if (compare(Tab[x][y], Tab[x][j])){
                            Tab[x][y] += Tab[x][j];
                            Tab[x][j] = 0;
                            j=n;
                        }
                        else if (Tab[x][j]!=0){
                            j=n;
                        }
                    }
                }
            }
            break;
        case 'z':

            for (int y=0; y < n; y++) {
                for (int x = 0; x < n; x++) {
                    for (int j = x + 1; j < n; j++) {
                        if (compare(Tab[x][y], Tab[j][y])) {
                            Tab[x][y] = 2 * Tab[x][y];
                            Tab[j][y] = 0;
                            j = n;
                        } else if (Tab[j][y] != 0) {
                            j = n;
                        }
                    }
                }
            }
            break;
        case 's':

            for (int y = 0; y < n; y++){
                for (int x = n-1; x >=0; x--){
                    for (int j=x-1;j>=0;j--){
                        if (compare(Tab[x][y], Tab[j][y])){
                            Tab[x][y] += Tab[j][y];
                            Tab[j][y] = 0;
                            j=-1;
                        }
                        else if (Tab[j][x]!=0){
                            j=-1;
                        }
                    }
                }}
            break;
        default:
            break;

    }}
void creationTab(int n,int T[n][n]){
    /*Créer un tableaux à double dimensions vide*/
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            T[i][j]=0;
        }
    }
}

void duo(int n, int T1[n][n], int T2[n][n], int *score){
    /* Fonction principale du mode duo*/
    int jouer = 1;
    char direction;
    //Préparation du mode de jeu
    creationTab(n, T1);
    creationTab(n, T2);
    add_case(n, T1, score);
    add_case(n, T2, score);
    affiche_duo(n, T1, T2, score);
    while (jouer) {
        printf("Dans quel direction voulez-vous aller ? (q/d/z/s) ou 'a' pour quitter\n");
        scanf("%c", &direction);// Récupération du choix du joueur
        fflush(stdin);
        tolower(direction);
        if (direction == 'a') {
            jouer = 0; //Si le joueur décide de mettre fin à sa partie
        }
        else {
            fusion(n, T1, direction);// Opération de fusion dans les deux tableaux
            fusion(n, T2, direction);
            move(n, T1, direction);// Opération de mouvement dans les deux tableaux
            move(n, T2, direction);
            add_case(n, T1, score);// Ajout de case aléatoires dans les deux tableaux
            add_case(n, T2, score);
            affiche_duo(n, T1, T2, score);// Affichage des deux tableaux
        }
    }
}

void normal(int n, int T1[n][n], int *score){
    /*Fonction principale du mode normal*/
    int jouer = 1 ;
    char dir;
    char rep= 'd';
    //Tentative de récupération du fichier de sauvegarde
    FILE * fichier = NULL ;
    fichier = fopen("Save.txt", "r");
    fseek(fichier,0, SEEK_END);
    int s = ftell(fichier);
    fclose(fichier);
    if (s != 0) { // Si le fichier de sauveagrde existe
        //fichier = fopen("Save.txt", "r");
        //fclose(fichier);
        while (rep != 'o' && rep != 'n'){// Demande au joueur si il veut reprendre son fichier de sauvegarde.
            printf("Vous avez une partie de sauvegarder, voulez la continuer ?(oui/non)");
            scanf("%c", &rep);
            tolower(rep);
            fflush(stdin);

        }
        if (rep =='o'){
            Lecture(n, T1, score); // Si oui récupérons les données du fichier de sauvegarde et on remplis le tableaux
        }
        else{
            creationTab(n, T1);// Sinon on créer un nouveau tableaux
            printf("%d", n);
            add_case(n, T1, score);
        }
    }else{
        creationTab(n, T1);// SI aucun fichier de sauvarge détécté.
        add_case(n, T1, score);
    }

    affiche(n, T1, score);
    while (jouer) {
        printf("dans quel direction voulez vous aller ? (l/r/u/d) ou 'a' pour quitter");
        scanf("%c", &dir);
        fflush(stdin);
        tolower(dir);
        if (dir == 'a') {
            jouer = 0;
            Sauvegarde(n, T1 , *score );// Sauvegarde du tableaux dans un fichier en cas d'arret.
        }
        else {
            fusion(n, T1, dir);
            move(n, T1, dir);
            add_case(n, T1, score);
            affiche(n, T1, score);
        }

    }
}

void puzzle(int *score){
    /*Fonction principale du mode puzzle */
    int jouer = 1;
    char dir;


    //Ouverture du fichier puzzle.
    FILE* f = fopen("./puzzleOne.txt", "r");

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
        while (jouer) {
            //Similaire à la fonction normal() du programme
            printf("dans quel direction voulez vous aller ? (q/d/z/s) ou 'a' pour quitter");
            scanf("%c", &dir);
            fflush(stdin);
            tolower(dir);
            if (dir == 'a') {
                jouer = 0;
            }
            else {
                fusion(n, T1, dir);
                move(n, T1, dir);
                add_case(n, T1, score);
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

