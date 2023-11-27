#include <stdio.h>

int main(){
    printf("Open a pipe");

    FILE * gp = _popen("gnuplot -persist","w");

    if(gp){ // if is gnuplot is found
        fprintf(gp,"set term wxt size 640,400\n");
        fprintf(gp,"set title 'Resultat de mesure vs sin(x)'\n");
        fprintf(gp,"set xlabel 'Temps (s)'\n");
        fprintf(gp,"set ylabel 'Valeurs'\n");
        fprintf(gp,"set style data linespoints\n");
        fprintf(gp,"plot 'curve.txt' ,sin(x)\n");
        fflush(gp);
        _pclose(gp);
    }

    return 0;
}