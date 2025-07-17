#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

static inline bool is_prime(unsigned int n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    // Otimização: usar aproximação inteira para sqrt
    unsigned int sqrt_n = (unsigned int)sqrt(n);
    if (sqrt_n * sqrt_n < n) sqrt_n++;
    
    // Otimização 6k±1: todos os primos > 3 são da forma 6k±1
    for (unsigned int i = 5; i <= sqrt_n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    const unsigned int LIMIT = 5000000;
    
    printf("Contando números primos de 1 a %u...\n", LIMIT);
    
    clock_t start = clock();
    unsigned int count = 0;
    
    // Usar buffer para I/O otimizado
    setvbuf(stdout, NULL, _IOFBF, 65536);
    
    // Caso especial para 2
    if (LIMIT >= 2) {
        printf("2\n");
        count++;
    }
    
    // Testar apenas números ímpares >= 3
    for (unsigned int n = 3; n <= LIMIT; n += 2) {
        if (is_prime(n)) {
            printf("%u\n", n);
            count++;
        }
    }
    
    fflush(stdout);
    
    clock_t end = clock();
    double duration = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("\nQuantidade de números primos encontrados: %u\n", count);
    printf("Tempo gasto: %.3f segundos\n", duration);
    
    return 0;
}
