/* ex04_time_per_thread.c Exercício 4 — Tempo por thread adaptado de ex03_vector.c 
a) Você deve exibir o tempo total de execução do programa. 
b) Grave o tempo que cada thread leva. 
c) Indique quantos threads foram usados para fazer o cálculo. 
Compilar:
   gcc -fopenmp -O2 ex04_time_per_thread.c -o ex04_time_per_thread

Execute:
   export OMP_NUM_THREADS=4
   ./ex04_time_per_thread */

   #include <stdio.h>
   #include <stdlib.h> 
   #include <omp.h> 
   int main(void) { 
    const long N = 1000000L; 
    double *a = (double *)malloc(N * sizeof(double));
    double *x = (double*) malloc(N * sizeof(double)); 
    double *y = (double *) malloc(N * sizeof(double)); 
    double *z = (double*) malloc(N * sizeof(double)); 
    if (!a || !x || !y || !z) return 1; 
    
    for (long i = 0; i < N; ++i) { 
        x[i] = 1.0; y[i] = 1.0; z[i] = 1.0; 
        /*coordenadas e métrica, começam a partir do espaço plano*/ 
    } 
    
    double t_total_start = omp_get_wtime(); 
    /* Vamos medir o tempo por thread usando um vetor para salvar os tempos locais. Primeiro, determinamos o número máximo de threads e reservamos um 
    vetor para eles. */ 
    int max_threads = omp_get_max_threads(); 
    double *thread_time = (double*)malloc(max_threads * sizeof(double)); 
    for(int i = 0; i < max_threads; ++i) thread_time[i] = 0.0; 
    /* Seção paralela: cada thread medirá seu próprio tempo de trabalho. */ #pragma omp parallel { 
        int tid = omp_get_thread_num(); double t0 = omp_get_wtime(); 
        #pragma omp for schedule(static) 
        for (long i = 0; i < N; ++i) { 
            a[i] = x[i] * x[i] + y[i] * y[i] + z[i];
         } 
         double t1 = omp_get_wtime(); 
         thread_time[tid] = t1 - t0; 
         /* Cada thread pode imprimir seu tempo: protegemos qualquer escrita com crítico para saída limpa. */ #pragma omp critical { 
            printf("Tempo gasto pelo thread %d = %.6f s\n", tid, thread_time[tid]); 
        } 
    } /* fim paralelo */ 
    double t_total = omp_get_wtime() - t_total_start; 
    printf("Tempo total = %.6f s\n", t_total); 
    /* Calcule quantos threads realmente escreveram tempos (>0) */ int threads_used = 0; 
    for (int i = 0; i < max_threads; ++i) 
    if (thread_time[i] > 0.0) threads_used++; 
    printf("Threads usados no cálculo = %d\n", threads_used); 
    free(thread_time); free(a); free(x); free(y); free(z); 
    
    return 0; 
}