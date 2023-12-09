
        fscanf(pf,"%d",dim);//recupere la dimension
        M = newMat(*dim); //alloue de la place pour la matrice
        v = newVect(*dim);//alloue de la place de la second
        sol = newVect(*dim);//alloue de la place pour la solutions

        for(int i=0 ;i<*dim ;i++){
            for(int j=0;j<*dim;j++){
                fscanf(pf,"%f",&M[i][j]); //lit les donnee par ligne
            }
        }
        for(int i=0;i<*dim;i++){
            fscanf(pf,"%f",&v[i]);
        }
		fclose(pf);
		for(int i=0;i<*dim;i++) sol[i]=0;
	}
	
	else{
		problem("Problem: can't open file\n");
		exit(2);
	}
	
	*A=M;
	*b=v;
	*x=sol;

}


float *newVect(int dim){
    float *v = NULL;
    v = malloc(dim*sizeof(float));
    if(v == NULL) problem("Ne peux pas allouer un matrice");
    return v;
}

float **newMat(int dim){
    float** A = NULL;
    A = malloc(dim*sizeof(float*));
    if(A == NULL) problem("Ne peux pas allouer un matrice");
    for(int i=0;i<dim ;i++){
        A[i] = malloc(dim*sizeof(float));
        if(A[i] == NULL) problem("Ne peux pas allouer un matrice");
    }
    return A;
}


void problem(char * message){
    printf("%s\n",message);
    exit(2);
}

float* pivaut_gauss(float **matrice, int N) {
    // Triangularisation de la matrice
    triangularisation(matrice, N);

    // Résolution du système d'équations
    float* solutions = resolution(matrice, N);

    return solutions;
}

void triangularisation(float **matrice, int N) {
    int i, j, k; //Indice
    float pivot,// la valeur de l’élément diagonal
    ratio;//rapport entre un élément de la matrice et le pivot

    for (k = 0; k < N; k++) {
        pivot = matrice[k][k];

        for (i = k + 1; i < N; i++) {
            ratio = matrice[i][k] / pivot;

            for (j = k; j < N + 1; j++) {
                matrice[i][j] -= ratio * matrice[k][j];
            }
        }
    }
}

float* resolution(float **matrice, int N) {
    int i, j; //Indice
    float* solutions = malloc(N * sizeof(float)); //conservation du valeur entre les appels de fonction

    for (i = N - 1; i >= 0; i--) {
        solutions[i] = matrice[i][N];

        for (j = i + 1; j < N; j++) {
            solutions[i] -= matrice[i][j] * solutions[j];
        }

        solutions[i] /= matrice[i][i];
    }

    return solutions;
}

void display_results(float *solutions, int N) {
    printf("Les solutions sont :\n");
    for (int i = 0; i < N; i++) {
        printf("x%d = %.2f\n", i + 1, solutions[i]);
    }
}
