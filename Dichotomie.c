#include <stdio.h>
#include <math.h>

float f(float x);
void displayResult(float a, float b , float ksi , float eps);

int main(){
	printf("Resolution de f(x)=0 par dichotomie");
//	Donnee	
	float a = 0 , b= 1 , // Les borne de l'intervalle de separation
		ksi = 87,		// la solution a calculer
		eps = 1e-6;		// la precision a atteindre
// 	Traitement
	

//	Resultat

	displayResult(a,b,ksi,esp);
	
	return 0;
}

void displayResult(float a, float b , float ksi , float eps){
	printf("La solution dans [%g; %g] est ksi = %g a epsilon = %g ",a,b,ksi,esp);
}
float f(float x){	
	return x - 2 -log(x);
}

