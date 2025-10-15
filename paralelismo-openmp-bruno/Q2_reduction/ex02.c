/* ex02_reduction.c Exercício 2—Atomismo paralelismo de um loop for trivial a) Gere um vetor de 100 elementos v cujos componentes são todos iguais a 1. 
b) Usando um loop for, some todos eles. 
c) Repita o loop com #pragma omp parallel for reduction(+:sum). 
d) Verifique os resultados e dê uma razão pela qual a diretiva de redução é necessária. */
Comando de compilação:
   gcc -fopenmp -O2 ex02_reduction.c -o ex02_reduction

Execute:
   ./ex02_reduction

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(void) {
    const int N = 100;
    int *v = malloc(N * sizeof(int));
    if (!v) return 1;

    /* (a) Inicializar todos os valores para 1. */
    for (int i = 0; i < N; ++i) v[i] = 1;

    /* (b) Soma sequencial */
    long sum_seq = 0;
    for(int i = 0; i < N; ++i) sum_seq += v[i];

    /* (c) Eles foram projetados para ser a soma paralela errada sem redução, para mostrar o problema:
       => Se fizer do_sum_parallel += v[i] dentro de um for paralelo sem proteção, teremos concorrência e obteremos uma resposta errada. */
    long sum_paral_err = 0;
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        /* A linha abaixo não é segura (condição de corrida) se descomentada. */
        /* sum_paral_err += v[i]; */
    }

    /* (c) Soma paralela correta com redução */
    long sum_parallel = 0;
    #pragma omp parallel for reduction(+:sum_parallel)
    for (int i = 0; i < N; ++i) {
        sum_parallel += v[i];
    }

    printf("Soma sequencial = %ld\n", sum_seq);
    printf("Soma paralela (com redução) = %ld\n",sum_parallel);
    printf("Dica: a redução faz uma cópia privada da variável para cada thread,\n"
           "performs the local sum on each thread, and finally combines (reduces) the\n"
           "partial values atomically/safely to get the final output. \n");

    free(v);
    return 0;
}