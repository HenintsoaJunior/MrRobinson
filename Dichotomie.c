#include <stdio.h>
#include <math.h>

float f(float x);
void displayResult(float a, float b, float ksi, float eps);
float dichotomie(float a, float b, float eps);

int main() {
    printf("Resolution de f(x)=0 par dichotomie\n");

    float a = 0, b = 1, ksi, eps = 1e-6;

    ksi = dichotomie(a, b, eps);

    displayResult(a, b, ksi, eps);

    return 0;
}

void displayResult(float a, float b, float ksi, float eps) {
    printf("La solution dans [%g; %g] est ksi = %g a epsilon = %g\n", a, b, ksi, eps);
}

float f(float x) {
    return x - 2 - log(x);
}

float dichotomie(float a, float b, float eps) {
    float x;
    while ((b - a) >= eps) {
        x = (a + b) / 2;

        if (f(x) == 0.0) {
            return x;
        } else if (f(a) * f(x) < 0) {
            b = x;
        } else {
            a = x;
        }
    }
    return (a + b) / 2;
}
