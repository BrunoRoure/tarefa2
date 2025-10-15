/* ex03_vector.c Exercício 3 — Expressão Vetorial 
a) Versão sequencial. 
b) Paralelização: prism omp-parallel for schedule(static). 
c) Exiba o tempo total de execução para cada edição. */
Compilar:
   gcc -fopenmp -O2 ex03_vector.c -o ex03_vector

Execute:
   export OMP_NUM_THREADS=4
   ./ex03_vector
c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(void) {
    const long N = 1000000L; /* "1 milhão" */
    double *a = (double*)malloc(N * sizeof(double));
    double* x = (double*)malloc(N * sizeof(double));
    double *y = (double*)malloc(N * sizeof(double));
    double *z = (double *)malloc(N * sizeof(double));
    if (!a || !x || !y || !z) return 1;

    /* Set-up the vectors (please consider example: all 1.0) */
    for (long i = 0; i < N; ++i) {
        x[i] = 1.0;
        y[i] = 1.0;
        z[i] = 1.0;
    }

    /* Versão sequencial */
    double t0 = omp_get_wtime();
    for (long i = 0; i < N; ++i) {
        a[i] = x[i] * x[i] + y[i]*y[i]+z[i];
    }
    double t_seq = omp_get_wtime() - t0;

    /* Implementação paralela com schedule(static) */
    double t1 = omp_get_wtime();
    #pragma omp parallel for schedule(static)
    for(long i = 0; i < N; ++i) {
        a[i] = x[i] * x[i] + y[i] * y[i] + z[i];
    }
    t1 = omp_get_wtime() - t1;

    printf("Tempo sequencial: %.6f s\n", t_seq);
    printf("Tempo paralelo (schedule(static)): %.6f s\n", t1);

    free(a);
    free(x);
    free(y);
    free(z);
    return 0;
}