#include <stdio.h>
#include <stdlib.h>

void gnuplot(float *xd, float *yd, float xmin, float xmax, float ymin, float ymax, int dim);
void getData(int *dim, float **xd, float **yd);
float *newVect(int dim);
float **newMat(int dim);
void problem(char *message);

int main() {
    float *xd, *yd;
    int dim = 0;

    // Récupération des données
    getData(&dim, &xd, &yd);

    // Plot si des données ont été lues
    if (dim > 0) {
        gnuplot(xd, yd, xd[0], xd[dim - 1], yd[0], yd[dim - 1], dim);
    } else {
        printf("Aucune donnée à afficher.\n");
    }

    free(xd);
    free(yd);

    return 0;
}

void gnuplot(float *xd, float *yd, float xmin, float xmax, float ymin, float ymax, int dim) {
    FILE *GP = popen("gnuplot -persist", "w");

    if (GP) {
        // Setup du plot
        fprintf(GP, "set term wxt size 640,400\n");
        fprintf(GP, "set title 'Interpolation'\n");
        fprintf(GP, "set xlabel 'x'\n");
        fprintf(GP, "set ylabel 'y'\n");
        fprintf(GP, "set style data linespoints\n");
        fprintf(GP, "set xrange [%f:%f]\n", xmin, xmax);
        fprintf(GP, "set yrange [%f:%f]\n", ymin, ymax);

        // Données
        fprintf(GP, "$data1 << EDF\n");
        for (int i = 0; i < dim; i++) {
            fprintf(GP, "%f %f\n", xd[i], yd[i]);
        }
        fprintf(GP, "EDF\n");

        // Plot
        fprintf(GP, "plot $data1 using 1:2 w linespoints lc 'black' pointtype 7 t 'linear'\n");

        fflush(GP);
        pclose(GP);
    } else {
        printf("Gnuplot introuvable.\n");
    }
}

void getData(int *dim, float **xd, float **yd) {
    float **M = NULL;
    FILE *pf = fopen("data1.txt", "r");

    if (pf != NULL) {
        fscanf(pf, "%d", dim);
        if (*dim > 0) {
            *xd = (float *)malloc(*dim * sizeof(float));
            *yd = (float *)malloc(*dim * sizeof(float));
            M = newMat(*dim);

            for (int i = 0; i < *dim; ++i) {
                fscanf(pf, "%f %f", &(*xd)[i], &(*yd)[i]);
                // Vous pouvez vérifier la lecture des valeurs ici
                // printf("xd[%d] = %f, yd[%d] = %f\n", i, (*xd)[i], i, (*yd)[i]);
            }
            fclose(pf);
            // libération de la mémoire allouée pour M si nécessaire
        } else {
            printf("Le fichier est vide.\n");
            fclose(pf);
            exit(2);
        }
    } else {
        printf("Fichier introuvable.\n");
        exit(2);
    }
}

float *newVect(int dim) {
    float *v = malloc(sizeof(float) * dim);
    if (v == NULL) {
        problem("Impossible d'allouer le vecteur.");
    }
    return v;
}

float **newMat(int dim) {
    float **mat = malloc(sizeof(float *) * dim);
    if (mat == NULL) {
        problem("Impossible d'allouer la matrice.");
    }
    for (int i = 0; i < dim; ++i) {
        mat[i] = malloc(sizeof(float) * 2); // Supposant que vous travaillez avec des paires de valeurs (x, y)
        if (mat[i] == NULL) {
            problem("Impossible d'allouer une ligne de la matrice.");
        }
    }
    return mat;
}

void problem(char *message) {
    printf("%s\n", message);
    exit(2);
}
