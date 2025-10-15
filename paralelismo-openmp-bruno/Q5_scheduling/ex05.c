/* ex05_scheduling.c Exercício 5 — Agendamento 
a) Execute com schedule(static) assim como com schedule(dynamic, 1000). 
b) Compare os tempos para diferentes números de threads (2, 4, 8). 
c) Impressão da explicação no final do programa. 
Compilar:
   gcc -fopenmp -O2 ex05_scheduling.c -o ex05_scheduling

Exemplo de execução:
   export OMP_NUM_THREADS=4
   ./ex05_scheduling

Recomendo rodar para 2,4,8... vezes e registrar o tempo.*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(void) {
    const long N = 1000000L;
    double *a = (double *) malloc(N * sizeof(double));
    double *x = malloc(N * sizeof(double));
    double *y = (double*)malloc(N * sizeof(double));
    double *z = malloc(N * sizeof(double));
    if (!a || !x || !y || !z) return 1;

    for (long i = 0; i < N; ++i) {
        /* Para tirar proveito aproximado da carga ligeiramente não uniforme: Faça trabalho extra em alguns índices */
        x[i] = 1.0 + (i % 10 == 0 ? 0.000001 : 0.0);
        y[i] = 1.0;
        z[i] = 1.0;
    }

    double t_static_start = omp_get_wtime();
    #pragma omp parallel for schedule(static)
    for(long i = 0; i < N; ++i) {
        /* simples cálculo */
        a[i] = x[i] * x[i] + y[i] * y[i] + z[i] * z[i];
    }
    double t_static = omp_get_wtime() - t_static_start;

    double t_dynamic_start = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic, 1000)
    for(long i = 0; i < N; ++i) {
        a[i] = x[i] * x[i] + y[i] * y[i] + z[i];
    }
    double t_dynamic = omp_get_wtime() - t_dynamic_start;

    printf("Tempo do agendamento estático = %.6f s\n", t_static);
    printf("Tempo do agendamento (dinâmico,1000) = %.6f s\n", t_dynamic);

    printf("\nBreve explicação:\n"
           "- schedule(static): as iterações são divididas em blocos fixos a priori para cada thread antes de realizá-las. \n"
           "  Muito bom se as iterações tiverem custo conhecido. \n"
           "- schedule(dynamic, chunk): os threads pegam blocos de dados logo após completarem o trabalho.\n"
           "  Útil quando o custo por iteração não é uniforme (desbalanceamento de carga) mas com overhead adicional\n"
           "  baseado na coordenação (empilhar/desempilhar de blocos). \n"
           "Recomendação: Se o trabalho é homogêneo → use estático. Dinâmico se o custo das iterações não for constante → dinâmico. \n");

    free(a); free(x); free(y); free(z);
    return 0;
}