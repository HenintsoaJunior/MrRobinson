#include <stdio.h>
#include <math.h>

void displayResult(float a, float b, float ksi, float eps);
float f(float x);
float faussePosition(float a, float b, float eps);

int main() {
    printf("Resolution de f(ksi)=0 par la methode de fausse position\n");

    // Données
    float a = 0.1, b = 1, // Borne de l'intervalle de séparation
          ksi = 0,         // La solution
          eps = 1e-6;      // Précision à atteindre

    // Traitement
    ksi = faussePosition(a, b, eps);

    // Sortie de résultat
    displayResult(a, b, ksi, eps);

    return 0;
}


float faussePosition(float a, float b, float eps) {
    float ksi = 0;
    float f_a = f(a);         // Valeur de la fonction f en a
    float f_b = f(b);         // Valeur de la fonction f en b

    while (fabs(b - a) >= eps) {
        ksi = (a * f_b - b * f_a) / (f_b - f_a);
        float f_ksi = f(ksi); // Valeur de la fonction f en ksi

        if (f_ksi == 0.0) {
            // La solution exacte a été trouvée
            break;
        } else if (f_a * f_ksi < 0) {
            b = ksi;
            f_b = f_ksi;
        } else {
            a = ksi;
            f_a = f_ksi;
        }
    }

    return ksi;
}

void displayResult(float a, float b, float ksi, float eps) {
    printf("La solution dans [%g; %g] est ksi = %g\n", a, b, ksi);
    printf("\t avec une precision de [%g]\n", eps);
}

float f(float x) {
    return x - 2 - log(x);
}
