#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void getData(int *,float ***,float **,float **);
void problem(char *);
float * newVect(int);
float ** newMat(int);
void displayResult(float *,int);
float ** factoriser(int dim,float ** coefficient);
float * setY(int,float **,float *);
float * cholesky(int,float **,float *,float *);

int main(int argc, char const *argv[])
{
// donnee
	int dim = 1;
	float ** coefficient = NULL;
    float * resultat = NULL;
    float * inconnu = NULL;
    float * y = NULL;

    getData(&dim,&coefficient,&resultat,&inconnu);
// Traitement

    coefficient = factoriser(dim,coefficient);
    y = setY(dim,coefficient,resultat);
    inconnu = cholesky(dim,coefficient,y,inconnu);

// Resultat
    displayResult(inconnu,dim);

    // nettoyage des espaces aloues dynamiquement;
    free(inconnu);
    free(resultat);

    for (int i = 0; i < dim; ++i)
        free(coefficient[i]);
    free(coefficient);

	return 0;
}

float * cholesky(int dim,float ** coefficient,float * y,float * inconnu) {
	for (int i = dim - 1; i >= 0; --i)
	{
		float somme = 0;
		for (int j = 0; j < dim ; ++j)
		{
			somme += coefficient[j][i] * inconnu[j];
		}
		inconnu[i] = (1 / coefficient[i][i])*(y[i] - somme);
	}
	return inconnu;
}


float * setY(int dim,float ** coefficient,float * resultat) {
	float * secondMembre = malloc(sizeof(float)*dim);
	for (int i = 0; i < dim; ++i) {
		secondMembre[i] = 0;				// initialisation du vecteur secondMembre
	}

	for (int i = 0; i < dim; ++i)
	{
		float somme = 0;
		for (int j = 0; j < i; ++j) {
			somme += (coefficient[i][j] * secondMembre[j]);
		}
		secondMembre[i] = (1 / coefficient[i][i]) * (resultat[i] - somme); 
	}
	return secondMembre;
}

float ** factoriser(int dim,float ** coefficient) {
	for (int i = 0; i < dim; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			float somme = 0;
			for (int k = 0; k < j; ++k)
			{
				somme += coefficient[i][k]*coefficient[j][k];
			}
			coefficient[i][j] = (1 / coefficient[j][j]) * (coefficient[i][j] - somme);
		}

			float somme = 0;
		for (int k = 0; k < i; ++k)
		{
			somme += pow(coefficient[i][k],2);
		}
		coefficient[i][i] = sqrt(coefficient[i][i] - somme);

		for (int k = i + 1; k < dim; ++k)
		{
			coefficient[i][k] = 0;
		}
	}
	return coefficient;
}

void getData(int * dim,float *** coefficient,float ** resultat,float ** inconnu) {
	// Poinnteurs pour les donnees
    float ** M = NULL, * v = NULL, * sol = NULL;
    FILE * pf = NULL;       //pointeur de fichier

    pf = fopen("./dataColesky/data0.txt","r");
    if (pf != NULL) {
        fscanf(pf,"%d", dim);                       //recupere la dim;
        M = newMat(*dim);                           //allouer la place pour la matrice
        v = newVect(*dim);                          //allouer la place pour le second membre
        sol = newVect(*dim);                         //allouer la place pour la solution
        for (int i = 0; i < *dim; ++i)
            for (int j = 0; j < *dim; ++j)
                fscanf(pf,"%f",&M[i][j]);             //lit les donnes ligne par ligne
        for (int i = 0; i < *dim; ++i)
            fscanf(pf,"%f",&v[i]);
        fclose(pf);
        for (int i = 0; i < *dim; ++i)
            sol[i] = 0;                             //initialise le vecteur solution

    } else {
        problem("can't find file");
        exit(2);
    }

    // Renvoie les adresses des contenus vers main
    *coefficient = M;
    *resultat = v;
    *inconnu = sol;
}

float * newVect(int dim) {
    float * v = NULL;
    v = malloc(sizeof(float) * dim);
    if (v == NULL) problem("ne peut pa allouer le vecteur");
    return v;
}

float ** newMat(int dim) {
    float ** mat = NULL;
    mat = malloc(sizeof(float *) * dim);
    if (mat == NULL) problem("ne peut pas allouer la matrice");
    for (int i = 0; i < dim; ++i) {
        mat[i] = malloc(sizeof(float) * dim);
        if (mat[i] == NULL) problem("ne peut pas allouer une ligne de matrice");
    }

    return mat;
}

void problem(char * message) {
    printf("%s\n", message);
    exit(2);
}

void displayResult(float * response,int dim) {
    printf("Solution trouvee pour le vecteur X:\n");
    for(int i = 0;i < dim; ++i) {
        printf("valeur de l'inconnu n %i = %g\n",i,response[i]);
    }
}
