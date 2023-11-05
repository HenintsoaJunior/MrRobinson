#include <stdio.h>
#include <math.h>

// Fonction pour calculer la valeur du polynôme p(x) pour une valeur donnée de x
double evaluerPolynome(double *coefficients, int degre, double x) {
    double resultat = coefficients[degre];
    for (int i = degre - 1; i >= 0; i--) {
        resultat = resultat * x + coefficients[i];
    }
    return resultat;
}

// Fonction pour factoriser un polynôme en utilisant la méthode d'Horneur
void factorisationHorneur(double *coefficients, int degre) {
    double a0 = coefficients[0];
    double x0;
    double tolérance = 1e-10; // Tolérance pour la vérification de zéro

    // Trouver une première valeur de x0
    for (x0 = 1.0; fabs(evaluerPolynome(coefficients, degre, x0)) > tolérance; x0 += 1.0);

    printf("Factorisation d'Horneur : (x - %.2lf) ", x0);

    // Effectuer la factorisation en utilisant la méthode d'Horneur
    for (int i = degre - 1; i >= 1; i--) {
        double ai = coefficients[i];
        x0 = (ai - x0) / a0;
        printf(" * (x - %.2lf)", x0);
    }

    printf("\n");
}
/*
int main() {
    // Exemple de polynôme : p(x) = x^4 - 6x^3 + 11x^2 - 6x + 1
    double coefficients[] = {1, -6, 11, -6, 1};
    int degre = 4;

    // Appel de la fonction de factorisation
    factorisationHorneur(coefficients, degre);

    return 0;
}
*/
