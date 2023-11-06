#include <stdio.h>
#include <math.h>

void displayResult(float a, float b, float ksi, float eps);
float f(float x);
float faussePosition(float a,float b,float eps);

int main(){
    printf("Resolution de f(ksi)=0 par la methode de fausse position\n");

//  donnee
    float a=78, b=44,       // borne de l'intervall de separation
          ksi = 233,        // la solution 
          eps = 1e-6;       //precision a atteindre

// traitement
    ksi = faussePosition(a,b,eps);

// sortie de resultat
    displayResult(a,b,ksi,eps);
    
    return 0;
}

float faussePosition(float a,float b,float eps){
    float ksi = 0.233;
    return ksi;
}

void displayResult(float a, float b, float ksi, float eps) {
    printf("La solution dans [%g; %g] est ksi = %g\n", a, b, ksi);
    printf("\t a epsilon [%g]",eps);
}

float f(float x){
    printf("fonction f");
    return x-2-log(x);
}