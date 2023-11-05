#include <stdio.h>
#include <math.h>

float f(float x);
void displayResult(float a, float b, int n, float aire);
float trap(float a, float b, float eps);
float trapeze(float a, float b, int n);

int main() {
    printf("Calcul d'intégrale par la méthode des trapèzes\n");

    // Données
    float a = 0, b = 1; // Bornes d'intégration
    float tolerance = 1e-6; // Tolerance for the difference between successive results

    // Calcul de l'intégrale avec la fonction trap
    float aire = trap(a, b, tolerance);

    // Resultat
    displayResult(a, b, 0, aire);

    return 0;
}

float trap(float a, float b, float eps) {
    float aire1 = 0, aire2 = 1;
    int n = 4;

    aire1 = trapeze(a, b, 2);
    aire2 = trapeze(a, b, n);

    while (fabs(aire1 - aire2) > eps) {
        n *= 2;
        aire1 = aire2;
        aire2 = trapeze(a, b, n);
    }

    printf("\nNb de sous-intervalles utilise = %d\n", n);
    return aire2;
}

float trapeze(float a, float b, int n) {
    // Calcul d'intégrale par la méthode des trapèzes
    float h = (b - a) / n;
    float somme = 0;

    for (int i = 1; i < n; i++) {
        float x = a + i * h;
        somme += f(x);
    }

    float aire = (h / 2) * (f(a) + 2 * somme + f(b));
    return aire;
}

void displayResult(float a, float b, int n, float aire) {
    printf("Intégrale de f(x) dans [%g ; %g] est égale à %g\n", a, b, aire);
    printf("En découpant l'intervalle en %d morceaux\n", n);
}

float f(float x) {
    return exp(sin(x * 5));
}
