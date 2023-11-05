#include <stdio.h>
#include <math.h>

float f(float x);
void displayResult(float a, float b, int n, float aire);
float simpson(float a, float b, int n);

int main() {
    printf("Calcul d'integrale par la methode de Simpson\n");

    // Les donnees
    float a = 0, b = 1, // Borne d'integration
        aire = 0.0;
    int n = 3; // nombre de sous-intervalles

    // Traitement
    aire = simpson(a, b, n);

    // Resultat
    displayResult(a, b, n, aire);

    return 0;
}

float simpson(float a, float b, int n) {
    // Calcul d'integrale par la methode de Simpson
    float aire = 0.0; // integrale a calculer
    float h = (b - a) / n;
    float x = a;

    // Calcul de la somme des valeurs de f(x)
    float sum = f(a) + f(b);

    for (int i = 1; i < n; i++) {
        x = a + i * h;
        if (i % 2 == 0) {
            sum += 2 * f(x);
        } else {
            sum += 4 * f(x);
        }
    }

    aire = (h / 3) * sum;
    return aire;
}

void displayResult(float a, float b, int n, float aire) {
    printf("Integrale de f dans [%g ; %g] est aire = %g\n", a, b, aire);
    printf("En decoupant l'intervalle en %d morceaux\n", n);
}

float f(float x) {
    return exp(sin(x * 5));
}
