/*
 * Phi.c
 *
 *  Created on: 25 sept. 2023
 *      Author: Henintsoa
 */
#include <stdio.h>
#include <math.h>

float interation(int n){
	float phi = (sqrt(5)-1)/2;
	float result = 1;

	for(int k=1 ; k<=n ;k++){
		result = pow(phi ,k * phi);
	}
	return result;
}


float recurance(int n){
	float phi = (sqrt(5)-1)/2;
	float phi_k_moins_1 = 1;
	float phi_k = phi;

	for(int k=2; k<=n ;k++){
		float phi_k_plus_1 = phi_k_moins_1 - phi_k;
		phi_k_moins_1 = phi_k;
		phi_k = phi_k_plus_1;
	}
	return phi_k;
}
/*
int main(){
	int n = 50;
	float result = interation(n);
	printf("phi^%d = %.16f\n",n,result);
	return 0;
}
*/
