#include <stdio.h>
#include <math.h>

float f(float x);
float g(float x, float a, float b);
float ptfx(float x, float a, float b, float epsilon);

int main() {
    // Exemple d'utilisation pour résoudre f(x) = 0 avec epsilon = 10^-6
    float a = 1.0;
    float b = 4.0;
    float suppositionInitiale = (a + b) / 2;
    float epsilon = 1e-6; // 10^-6

    float resultat = ptfx(suppositionInitiale, a, b, epsilon);

    printf("Une solution de f(x) = 0 est : %.16f\n", resultat);

    return 0;
}
float f(float x) {
    return x - 2 - logf(x);
}

float g(float x, float a, float b) {
    float lambda = (b - a) / (f(b) - f(a));
    return x - lambda - f(x);
}

float ptfx(float x, float a, float b, float epsilon) {
    float xPrecedent, xCourant;
    xCourant = x;

    do {
        xPrecedent = xCourant;
        xCourant = g(xPrecedent, a, b);
    } while (fabsf(xCourant - xPrecedent) > epsilon);

    return xCourant;
}
