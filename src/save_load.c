#include "functions.h"

// Crée le nom du fichier de sauvegarde en fonction du mode et de la taille
void get_save_filename(char* filename, int mode, int size) {
    sprintf(filename, "%s/save_mode%d_size%d.txt", SAVES_DIR, mode, size);
}

// Crée le dossier saves s'il n'existe pas
void ensure_saves_directory() {
#ifdef _WIN32
    mkdir(SAVES_DIR);
#else
    mkdir(SAVES_DIR, 0777);
#endif
}

// Vérifie si une sauvegarde existe pour un mode et une taille donnés
int has_save(int mode, int size) {
    char filename[MAX_PATH];
    get_save_filename(filename, mode, size);
    
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        return 0;  // Pas de sauvegarde
    }
    
    // Vérifie que le fichier n'est pas vide
    fseek(f, 0, SEEK_END);
    long fileSize = ftell(f);
    fclose(f);
    
    return fileSize > 0;  // Retourne 1 si le fichier n'est pas vide
}

// Sauvegarde une partie
void Sauvegarde(int n, int T[n][n], int score, int mode) {
    ensure_saves_directory();
    
    char filename[MAX_PATH];
    get_save_filename(filename, mode, n);
    
    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        printf("Erreur lors de la sauvegarde!\n");
        return;
    }
    
    // Sauvegarde la taille, le score et le mode
    fprintf(f, "%d %d %d\n", n, score, mode);
    
    // Sauvegarde la grille
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(f, "%d ", T[i][j]);
        }
        fprintf(f, "\n");
    }
    
    fclose(f);
}

// Sauvegarde une partie en mode duo
void Sauvegarde_duo(int n, int T1[n][n], int T2[n][n], int score) {
    ensure_saves_directory();
    
    char filename[MAX_PATH];
    get_save_filename(filename, 2, n);
    
    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        printf("Erreur lors de la sauvegarde!\n");
        return;
    }
    
    // Sauvegarde la taille, le score et le mode
    fprintf(f, "%d %d 2\n", n, score);
    
    // Sauvegarde la première grille
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(f, "%d ", T1[i][j]);
        }
        fprintf(f, "\n");
    }
    
    // Sauvegarde la deuxième grille
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(f, "%d ", T2[i][j]);
        }
        fprintf(f, "\n");
    }
    
    fclose(f);
}

// Charge une partie
int Lecture(int n, int T[n][n], int* score, int mode) {
    char filename[MAX_PATH];
    get_save_filename(filename, mode, n);
    
    FILE* f = fopen(filename, "r");
    if (f == NULL) return 0;
    
    int saved_n, saved_mode;
    fscanf(f, "%d %d %d", &saved_n, score, &saved_mode);
    
    if (saved_n != n || saved_mode != mode) {
        fclose(f);
        return 0;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(f, "%d", &T[i][j]);
        }
    }
    
    fclose(f);
    return 1;
}

// Charge une partie en mode duo
int Lecture_duo(int n, int T1[n][n], int T2[n][n], int* score) {
    char filename[MAX_PATH];
    get_save_filename(filename, 2, n);
    
    FILE* f = fopen(filename, "r");
    if (f == NULL) return 0;
    
    int saved_n, saved_mode;
    fscanf(f, "%d %d %d", &saved_n, score, &saved_mode);
    
    if (saved_n != n || saved_mode != 2) {
        fclose(f);
        return 0;
    }
    
    // Charge la première grille
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(f, "%d", &T1[i][j]);
        }
    }
    
    // Charge la deuxième grille
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(f, "%d", &T2[i][j]);
        }
    }
    
    fclose(f);
    return 1;
}