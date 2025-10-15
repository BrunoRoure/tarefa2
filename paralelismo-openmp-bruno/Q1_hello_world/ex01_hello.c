/* ex01_hello.c Exercício 1: "Hello World" em paralelo 
a- Substitua o código que você escreveu no exercício acima pela sua própria versão do aplicativo pi paralelo incluindo o Código C A.2 usando #pragma omp
 parallel. Depois teste e verifique se a sua nova versão está correta; mantenha todos os espaços em branco e chaves, implemente igual ao item A. 
 b- Todos os threads deverão imprimir uma mensagem com seu número (omp_get_thread_num()) e o número total de threads (omp_get_num_threads()). 
 c- Certifique-se de que o programa é executado com 4 threads. 
 
 Instruções de compilação:
   gcc -fopenmp -O2 ex01_hello.c -o ex01_hello

Execução (duas opções):
1- Configuração via variável de ambiente:
   export OMP_NUM_THREADS=4
   ./ex01_hello
2- Ou configure programaticamente:
   ./ex01_hello

Saída esperada:
Mensagens de cada thread com ID e número de threads (ordem das linhas pode variar). */


#include <stdio.h>
#include <omp.h>  
int main(void) { 
    /* Um programa para definir 4 threads dentro do programa. */ omp_set_num_threads(4); 
    
    /* #pragma omp parallel estabelece uma região paralela. O bloco seguinte é sempre executado em paralelo entre todos os threads. 
    */ #pragma omp parallel { 
        /* Cada thread obtém seu ID e o número total de threads. 
        omp_get_thread_num(): retorna um inteiro [0..num_threads-1]. 
        omp_get_num_threads(): retorna o número de threads usados na região atual. */ 
        int tid = omp_get_thread_num(); 
        int nthreads = omp_get_num_threads(); 
        
        /* Imprimimos uma mensagem que identifica o thread. */ 
        printf("Olá do thread %d de %d\n", tid, nthreads); } 
        /*! fim do par */ /* fim da região paralela */ 
        
        return 0;
    }