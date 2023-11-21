#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


int Score(int n,int T[n][n]){
    int score = 0 ;
    for (int i =0;i<n;i++){
        for (int y =0;y<n;y++){
            score += T[i][y];
        }
    }
    return score;
}

void Affiche(int n, int T[n][n]){
    system("cls");
    printf("Score : %d", Score(n,T));
    for (int i =0; i<n; i++ ){
        for (int y =0; y<n; y++ ) {
            if (y == 0) {
                printf("\n");
            }
            printf("%d ", T[i][y]);
        }}}


void Apparition(int n,int T[n][n]){
    int b,a;
    do{
     a = rand()%n , b = rand()%n ;
    }while (T[a][b] != 0 );

    if ((rand()%5) == 0 ) {
        T[a][b] = 4;
    }else {
        T[a][b] = 2;
    }

}
int PremierCaseLibreUp (int n ,int T[n][n], int i){
    for (int y = 0; y<n ; y++){
        if (T[y][i]== 0) {
            return y;
        }
    }
}
int PremierCaseLibreDown (int n ,int T[n][n], int i){
    for (int y = n-1; y>-1 ; y -- ){
        if (T[y][i]== 0) {
            return y;
        }
    }
}
int PremierCaseLibreLeft (int n ,int T[n][n], int i){
    for (int y = 0; y<n ; y ++ ){
        if (T[i][y]== 0) {
            return y;
        }
    }
}a
int PremierCaseLibreRight (int n ,int T[n][n], int i){
    for (int y = n-1; y > -1 ; y -- ){
        if (T[i][y] == 0) {
            return y;
        }
    }
}

void MoveUp(int n,int T[n][n]){
    for (int i = 0; i<n;i++){
        for (int y =0; y<n; y++){
            if (T[y][i] !=  0 ){
                int Case = PremierCaseLibreUp(n, T,i);
                if (Case < y ){
                    T[Case][i] = T[y][i];
                    T[y][i] = 0 ;
                }
            }
        }
    }
}

void MoveDown(int n,int T[n][n]){
    for (int i = 0; i<n;i++){
        for (int y = n-1 ; y>-1; y--){
            if (T[y][i] !=  0 ){
                int Case = PremierCaseLibreDown(n, T,i);
                if (Case > y ){
                    T[Case][i] = T[y][i];
                    T[y][i] = 0 ;
                }
            }
        }
    }
}
void MoveLeft(int n,int T[n][n]){
    for (int i = 0; i<n;i++){
        for (int y = 0 ; y<n; y++){
            if (T[i][y] !=  0 ){
                int Case = PremierCaseLibreLeft(n, T,i);
                if (Case < y ){
                    T[i][Case] = T[i][y];
                    T[i][y] = 0 ;
                }
            }
        }
    }
}
void MoveRight(int n,int T[n][n]){
    for (int i = 0; i<n;i++){
        for (int y = n-1 ; y>-1; y--){
            if (T[i][y] !=  0 ){
                int Case = PremierCaseLibreRight(n, T,i);
                if (Case > y ){
                    T[i][Case] = T[i][y];
                    T[i][y] = 0 ;
                }
            }
        }
    }
}

void FusionUp(int n, int T[n][n]){
    for( int i=0 ;i<n; i++){
        for (int y = 0; y<n-1;y++){
            if (T[y][i] == T[y+1][i]){
                T[y][i] = T[y][i]*2;
                T[y+1][i] = 0 ;
                MoveUp(n,T);
            }
        }
    }
}
void FusionDown(int n, int T[n][n]){
    for( int i=0 ;i<n; i++){
        for (int y = n-1; y>-1;y--){
            if (T[y][i] == T[y-1][i]){
                T[y][i] = T[y][i]*2;
                T[y-1][i] = 0 ;
                MoveDown(n,T);
            }
        }
    }
}
void FusionLeft(int n, int T[n][n]){
    for( int i=0 ;i<n; i++){
        for (int y = 0; y<n-1;y++){
            if (T[i][y] == T[i][y+1]){
                T[i][y] = T[i][y]*2;
                T[i][y+1] = 0 ;
                MoveLeft(n,T);
            }
        }
    }
}
void FusionRight(int n, int T[n][n]){
    for( int i=0 ;i<n; i++){
        for (int y = n-1; y>-1;y--){
            if (T[i][y] == T[i][y-1]){
                T[i][y] = T[i][y]*2;
                T[i][y-1] = 0 ;
                MoveRight(n,T);
            }
        }
    }
}


void Fini(int n, int T[n][n]){
    
}

int main() {
   int T[4][4]={0,2,0,0,2,2,0,0,0,0,2,0,2,2,2,0};
    srand( time( NULL ) );




    return 0;
}
