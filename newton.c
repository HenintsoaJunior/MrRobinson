#include <stdio.h>
#include <math.h>

float f(float x);
float f_prime(float x);
float Newton(float x0,float eps);
void displayResult(float x0,float eps,float ksi);

int main(){
    printf("trouver un kis tel que f(x)=0");
//Donnee
float a=0.557,b=0.453; //borne d'intervalle
float x0= (a+b)/2;

float eps =1e-6; //precision a atteindre

//traitement
float ksi = Newton(x0,eps);

//resultat
displayResult(x0,eps,ksi);


    return 0;
}
float Newton(float x0, float eps) {
    int N = 0; // Nombre d'itérations
    float x = x0;
    float x1 = x - f(x) / f_prime(x);

    while (fabs(x1 - x) > eps) {
        x = x1;
        x1 = x - f(x) / f_prime(x);
        N++;
    }
    return x;
}

void displayResult(float x0,float eps,float ksi){
    printf("La solution dans [%g]  de ksi= %g\n", x0, ksi);
    printf("\t avec une precision de [%g]\n", eps);
   
}

float f(float x){
    return (x * x * x / 10) + 4 * (x * x / 5) + 5;
}

float f_prime(float x){
    return (3 * x * x / 10) + (8 * x / 5);
}
