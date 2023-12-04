#include <stdio.h>

#define N 3 //Definition d'une constante

void display_results(float solutions[N]);
void triangularisation(float matrice[N][N + 1]);
float* resolution(float matrice[N][N + 1]);
float* pivaut_gauss(float matrice[N][N + 1]);
int main() {
printf("Resolution d'une matrice grace a la methode de pivaut de gauss\n");

///Donnee
    float matrice[N][N + 1] = {
        {4, 8, 12, 4},
        {2, 8, 13, 5},
        {2, 9, 18, 11}
    };
///Traitement
    float* solutions = pivaut_gauss(matrice);

 ///Resultat

    display_results(solutions);

    return 0;
}


float* pivaut_gauss(float matrice[N][N + 1]) {
    // Triangularisation de la matrice
    triangularisation(matrice);

    // Résolution du système d'équations
    float* solutions = resolution(matrice);

    return solutions;
}

void triangularisation(float matrice[N][N + 1]) {
    int i, j, k; //Indice
    float pivot,// la valeur de l’élément diagonal
    ratio;//rapport entre un élément de la matrice et le pivot

    for (k = 0; k < N; k++) {
        pivot = matrice[k][k];

        for (i = k + 1; i < N; i++) {
            ratio = matrice[i][k] / pivot;

            for (j = k; j < N + 1; j++) {
                matrice[i][j] -= ratio * matrice[k][j];
            }
        }
    }
}

float* resolution(float matrice[N][N + 1]) {
    int i, j; //Indice
    static float solutions[N]; //conservation du valeur entre les appels de fonction

    for (i = N - 1; i >= 0; i--) {
        solutions[i] = matrice[i][N];

        for (j = i + 1; j < N; j++) {
            solutions[i] -= matrice[i][j] * solutions[j];
        }

        solutions[i] /= matrice[i][i];
    }

    return solutions;
}

void display_results(float solutions[N]) {
    printf("Les solutions sont :\n");
    for (int i = 0; i < N; i++) {
        printf("x%d = %.2f\n", i + 1, solutions[i]);
    }
}
