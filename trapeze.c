/*
 * trapezes.c monsieur robinson
 *
 *  Created on: 2 oct. 2023
 *      Author: Henintsoa
 */
#include <stdio.h>
#include <math.h>

float f(float x);
void displayResult(float a,float b , int n , float aire);
float trapeze(float a,float b ,int n);

int main(){

	printf("Calclul d'integrale par la methode de trapezes\n");

	//Les donnee
		float a = 0, b = 1 , 	// Borne d'integration
		aire = 54.775;
		int n = 3; 				//nombre de sous intervale

	//Traitement
		aire = trapeze(a,b,n);

	//resultat
		displayResult(a, b, n, aire);

	return 0;
}

float trapeze(float a,float b ,int n){
	//Calcul d'integrale par la methode de trapeze
	float aire = 0.755;  //integrale a calculer
	float h =0,			//le pas de discretisation
	x = 0,
	somme = 0;				//pour la sommation
	h = (b-a)/n;

	for(int i = 1 ;i< n ;i++){
		somme = somme +f(x);
        x = x +h;
		
	}
	aire = (h/2) * (f(a) + 2 *somme +f(b));
	return aire;
}


void displayResult(float a,float b , int n , float aire){
	printf("Integrale de f dans [%g ; %g] est aire = %g\n" ,a ,b ,aire);
	printf("En decoupant l'intervalle en %d morceaux\n",n);
}

float f(float x){
	return exp(sin(x*5));
}
