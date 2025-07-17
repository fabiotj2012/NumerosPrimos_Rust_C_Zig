#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

static inline bool* optimized_sieve(unsigned int limit) {
    bool* is_prime = (bool*)malloc((limit + 1) * sizeof(bool));
    
    // Inicializar todos como verdadeiro
    memset(is_prime, true, (limit + 1) * sizeof(bool));
    
    is_prime[0] = false;
    if (limit > 0) {
        is_prime[1] = false;
    }
    
    // Marcar todos os pares como não-primos (exceto 2)
    if (limit >= 4) {
        for (unsigned int i = 4; i <= limit; i += 2) {
            is_prime[i] = false;
        }
    }
    
    // Crivo otimizado começando com ímpares
    unsigned int sqrt_limit = (unsigned int)sqrt(limit);
    for (unsigned int i = 3; i <= sqrt_limit; i += 2) {
        if (is_prime[i]) {
            // Começar em i² e pular números pares
            unsigned int step = i * 2; // Para pular números pares
            for (unsigned int j = i * i; j <= limit; j += step) {
                is_prime[j] = false;
            }
        }
    }
    
    return is_prime;
}

int main() {
    const unsigned int LIMIT = 5000000;
    
    printf("Contando números primos de 1 a %u (usando Crivo de Eratóstenes)...\n", LIMIT);
    
    clock_t start = clock();
    bool* is_prime = optimized_sieve(LIMIT);
    
    // Usar buffer para I/O otimizado
    setvbuf(stdout, NULL, _IOFBF, 65536);
    
    unsigned int count = 0;
    
    // Processar 2 separadamente
    if (LIMIT >= 2 && is_prime[2]) {
        printf("2\n");
        count++;
    }
    
    // Processar apenas números ímpares para reduzir iterações
    for (unsigned int n = 3; n <= LIMIT; n += 2) {
        if (is_prime[n]) {
            printf("%u\n", n);
            count++;
        }
    }
    
    fflush(stdout);
    
    clock_t end = clock();
    double duration = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("\nQuantidade de números primos encontrados: %u\n", count);
    printf("Tempo gasto: %.3f segundos\n", duration);
    
    free(is_prime);
    return 0;
}
