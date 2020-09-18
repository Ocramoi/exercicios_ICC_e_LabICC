#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int fiboI(int n) {
    int f1 = 0, 
        f2 = 1,
        temp;
    
    for (int i = 1; i < n; ++i) {
        temp = f1 + f2;
        f1 = f2;
        f2 = temp;
    }

    return temp;
}

int fiboR(int n) {
    if (n == 0 ||n == 1) return n;

    return fiboR(n - 1) + fiboR(n - 2);
}

int main(int argc, char **argv) {
    int n = atoi(argv[1]);
    FILE *valsRec = fopen("recursivo.dat",  "w+"),
         *valsIter = fopen("iterativo.dat", "w+");
    clock_t init, end;
    double tempo;

    for (int i = 3; i < n + 1; ++i) {
        init = clock();
        fiboR(i);
        end = clock();
        tempo = (double)(end - init)/CLOCKS_PER_SEC;
        fprintf(valsRec, "%d %lf\n", i, tempo);

        init = clock();
        fiboI(i);
        end = clock();
        tempo = (double)(end - init)/CLOCKS_PER_SEC;
        fprintf(valsIter, "%d %lf\n", i, tempo);
    }

    fclose(valsRec); fclose(valsIter);

    return 0;
}