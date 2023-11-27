#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

/*
void Affiche(int n, int T[n][n]){
    system("cls");
    for (int i =0; i<n; i++ ){
        for (int y =0; y<n; y++ ) {
            if (y == 0) {
                printf("\n");
            }
            printf("%d ", T[i][y]);
        }}}

int Compare(int i1, int i2 ){
    if (i1 == i2){
        return i1*2;
    }else {
        return 0;
    }
}
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
        }}}

int PremierCaseLibreDown (int n ,int T[n][n], int i){
    for (int y = n; y>0 ; y -- ){
        if (T[y][i]== 0) {
            return y;
        }}}



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
        for (int y = n ; y>-1; y--){
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

int main() {
   int T[4][4]={0,2,0,0,2,2,0,0,0,0,2,0,2,2,2,0};
    srand( time( NULL ) );

    Affiche(4,T);
    system("pause");

    MoveUp(4,T);
    Affiche(4,T);
    system("pause");
    MoveDown(4,T);
    Affiche(4,T);

    return 0;
}
*/
