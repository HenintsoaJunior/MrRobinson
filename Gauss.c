#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void display_results(int dim, float **A, float *b, float *x);
void gauss(int dim, float **A, float *b, float *x, int *p);
void solveTriangleSup(int dim, float **A, float *b, float *x, int *p);
void getData(int *dim, float ***A, float **b, float **x, int **p);
float *newVect(int dim);
float **newMat(int dim);
void problem(char *message);

int main() {
    printf("Resolution d'une matrice grace a la methode de pivaut de gauss\n");

    int dim = 1;
    float **A = NULL; //adresse de la matrice
    float *b = NULL;  //adresse du vecteur du second Membre
    float *x = NULL;  //adresse du vecteur du solutions
    int *p = NULL;     //pointeur de ligne pour les pivotage

    getData(&dim, &A, &b, &x, &p); //recuperer la dimension de la matrice et le second membre
    printf("tonga");
    ///Traitement
    gauss(dim, A, b, x, p);

    ///Resultat
    display_results(dim, A, b, x);

    return 0;
}

void gauss(int dim, float **A, float *b, float *x, int *p) {
    float rapport;
    for (int k = 0; k < dim - 1; k++) {
        int max = k;
        for (int i = k + 1; i < dim; i++) {
            if (fabs(A[p[i]][k]) > fabs(A[p[max]][k])) {
                max = i;
            }
        }
        if (max != k) {
            int temp = p[k];
            p[k] = p[max];
            p[max] = temp;
        }
        for (int i = k + 1; i < dim; i++) {
            rapport = A[p[i]][k] / A[p[k]][k];
            for (int j = k; j < dim; j++) {
                A[p[i]][j] -= rapport * A[p[k]][j];
            }
            b[p[i]] -= rapport * b[p[k]];
        }
    }

    for (int i = dim - 1; i >= 0; i--) {
        x[i] = b[p[i]];
        for (int j = i + 1; j < dim; j++) {
            x[i] -= A[p[i]][j] * x[j];
        }
        x[i] /= A[p[i]][i];
    }
}

void solveTriangleSup(int dim, float **A, float *b, float *x, int *p) {
    for (int i = dim - 1; i >= 0; i--) {
        x[i] = b[p[i]];
        for (int j = i + 1; j < dim; j++) {
            x[i] -= A[p[i]][j] * x[j];
        }
        x[i] /= A[p[i]][i];
    }
}

void display_results(int dim, float **A, float *b, float *x) {
    printf("Matrice A:\n");
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            printf("%.2f\t", A[i][j]);
        }
        printf("\n");
    }
    printf("Vecteur b:\n");
    for (int i = 0; i < dim; i++) {
        printf("%.2f\n", b[i]);
    }
    printf("Solutions:\n");
    for (int i = 0; i < dim; i++) {
        printf("x[%d] = %.2f\n", i, x[i]);
    }
}

void getData(int *dim, float ***A, float **b, float **x, int **p) {
    float **M = NULL, *v = NULL, *sol = NULL;
    FILE *pf = NULL; // pointeur de fichier
    int *pt = NULL;
    pf = fopen("data.txt", "r");

    if (pf != NULL) {
        fscanf(pf, "%d", dim); // récupère la dimension
        M = newMat(*dim);      // alloue de la place pour la matrice
        v = newVect(*dim);     // alloue de la place pour le vecteur second membre
        sol = newVect(*dim);   // alloue de la place pour les solutions

        for (int i = 0; i < *dim; i++) {
            for (int j = 0; j < *dim; j++) {
                fscanf(pf, "%f", &M[i][j]); // lit les données par ligne pour la matrice
            }
        }
        for (int i = 0; i < *dim; i++) {
            fscanf(pf, "%f", &v[i]); // lit les données pour le vecteur second membre
        }
        fclose(pf);

        // Initialisation du tableau temporaire pt
        pt = malloc(*dim * sizeof(int));
        if (pt == NULL)
            problem("Ne peux pas allouer un matrice");

        for (int i = 0; i < *dim; i++)
            pt[i] = i; // attribue les valeurs à pt, le tableau temporaire

    } else {
        problem("Problem: can't open file\n");
        exit(2);
    }

    *A = M; // assigne la matrice
    *b = v; // assigne le vecteur second membre
    *x = sol; // assigne les solutions
    *p = pt; // assigne le tableau pt à p
}


float *newVect(int dim) {
    float *v = NULL;
    v = malloc(dim * sizeof(float));
    if (v == NULL)
        problem("Ne peux pas allouer un matrice");
    return v;
}

float **newMat(int dim) {
    float **A = NULL;
    A = malloc(dim * sizeof(float *));
    if (A == NULL)
        problem("Ne peux pas allouer un matrice");
    for (int i = 0; i < dim; i++) {
        A[i] = malloc(dim * sizeof(float));
        if (A[i] == NULL)
            problem("Ne peux pas allouer un matrice");
    }
    return A;
}

void problem(char *message) {
    printf("%s\n", message);
    exit(2);
}
