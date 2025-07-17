# Comparação de Performance: Rust vs C - PORTUGUES PT-BR (In the end have a English version)
## Contagem de Números Primos de 1 a 5.000.000

Este projeto contém implementações otimizadas para contar números primos em Rust e C, com duas abordagens diferentes:

### Arquivos do Projeto

1. **Método Tradicional (Teste de Primalidade)**:
   - `primes_rust.rs` - Implementação em Rust
   - `primes_c.c` - Implementação em C

2. **Crivo de Eratóstenes (Mais Eficiente)**:
   - `primes_rust_sieve.rs` - Implementação em Rust
   - `primes_c_sieve.c` - Implementação em C

3. **Scripts de Compilação e Execução**:
   - `Makefile` - Para compilação manual do C

### Como Executar

#### Opção 2: Compilação e Execução Manual

**Para Rust:**
```bash
cargo build --release
.\target\release\primes_rust.exe
.\target\release\primes_rust_sieve.exe
```

**Para C:**
```bash
gcc -O3 -march=native -flto -ffast-math -funroll-loops -o primes_c primes_c.c -lm
gcc -O3 -march=native -flto -ffast-math -funroll-loops -o primes_c_sieve primes_c_sieve.c -lm
.\primes_c.exe
.\primes_c_sieve.exe
```

### Otimizações Implementadas

**Rust:**
- Otimização de release com nível 3
- Link Time Optimization (LTO)
- Codegen units = 1 para máxima otimização
- Panic = abort para reduzir overhead

**C:**
- Otimização -O3
- -march=native para otimizações específicas do processador
- Link Time Optimization (-flto)
- Fast math (-ffast-math)
- Loop unrolling (-funroll-loops)

### Algoritmos

1. **Método Tradicional**: Testa cada número dividindo por todos os ímpares até √n
2. **Crivo de Eratóstenes**: Marca múltiplos de números primos em um array booleano

### Saída Esperada

Ambos os programas exibem:
- Todos os números primos encontrados (um por linha)
- Quantidade total de primos encontrados
- Tempo de execução em segundos

### Notas sobre Performance

O Crivo de Eratóstenes é significativamente mais rápido para grandes intervalos, pois tem complexidade O(n log log n) comparado a O(n√n) do método tradicional.

## Otimizações Implementadas na Versão Melhorada

### Rust - Método Tradicional:
- Algoritmo 6k±1: testa apenas números da forma 6k±1 (reduz testes em ~66%)
- BufWriter para I/O otimizado
- Testa apenas números ímpares após 2
- Aproximação inteira para sqrt
- Inline functions com `#[inline(always)]`
- Compilação com `-C target-cpu=native`

### Rust - Crivo de Eratóstenes:
- Acesso unsafe para eliminar bounds checking
- Otimização para pular números pares
- BufWriter para I/O otimizado
- `get_unchecked()` para acesso direto ao array
- LTO "fat" para máxima otimização
- Overflow-checks desabilitado

### C - Método Tradicional (Otimizado):
- Algoritmo 6k±1: mesma otimização do Rust
- `setvbuf()` com buffer de 64KB para I/O otimizado
- `static inline` para funções
- Testa apenas números ímpares após 2
- Aproximação inteira para sqrt

### C - Crivo de Eratóstenes (Otimizado):
- Marca todos os pares de uma vez com loop otimizado
- `setvbuf()` para I/O otimizado
- `static inline` para funções
- Step otimizado no crivo (pula números pares)
- Processar apenas ímpares na saída

### Flags de Compilação Agressivas:
**Rust:**
- `RUSTFLAGS=-C target-cpu=native -C target-feature=+crt-static`
- `opt-level = 3`, `lto = "fat"`, `overflow-checks = false`

**C:**
- `-O3 -march=native -mtune=native -flto -ffast-math`
- `-funroll-loops -finline-functions -fomit-frame-pointer -DNDEBUG`

## Resultados de Performance

### Resultados Originais:
RUST: 
  - Classico: 15.139 segundos
  - Crivo de Eratóstenes: 15.393 segundos

C: 
  - Clássico: 11.127 segundos
  - Crivo de Eratóstenes: 10.747 segundos


### Rust Tradicional 
Quantidade de números primos encontrados: 348513
Tempo gasto: 1.653 segundos

### Rust: Crivo de Eratóstenes
Quantidade de números primos encontrados: 348513
Tempo gasto: 1.411 segundos


### C Tradicional
Quantidade de números primos encontrados: 348513
Tempo gasto: 1.685 segundos

### C Crivo de Eratóstenes
Quantidade de números primos encontrados: 348513
Tempo gasto: 1.430 segundos

---

# Performance Comparison: Rust vs C (English)
## Prime Number Counting from 1 to 5,000,000

This project contains optimized implementations for counting prime numbers in Rust and C, using two different approaches:

### Project Files

1. **Traditional Method (Primality Testing)**:
   - `primes_rust.rs` - Rust implementation
   - `primes_c.c` - C implementation

2. **Sieve of Eratosthenes (More Efficient)**:
   - `primes_rust_sieve.rs` - Rust implementation
   - `primes_c_sieve.c` - C implementation

3. **Compilation and Execution Scripts**:
   - `Makefile` - For manual C compilation

### How to Run

#### Option 2: Manual Compilation and Execution

**For Rust:**
```bash
$env:RUSTFLAGS="-C target-cpu=native -C target-feature=+crt-static"
cargo build --release
.\target\release\primes_rust.exe
.\target\release\primes_rust_sieve.exe
```

**For C:**
```bash
gcc -O3 -march=native -mtune=native -flto -ffast-math -funroll-loops -finline-functions -fomit-frame-pointer -DNDEBUG -o primes_c_optimized primes_c.c -lm
gcc -O3 -march=native -mtune=native -flto -ffast-math -funroll-loops -finline-functions -fomit-frame-pointer -DNDEBUG -o primes_c_sieve_optimized primes_c_sieve.c -lm
.\primes_c_optimized.exe
.\primes_c_sieve_optimized.exe
```

### Algorithms

1. **Traditional Method**: Tests each number by dividing by all odd numbers up to √n
2. **Sieve of Eratosthenes**: Marks multiples of prime numbers in a boolean array

### Optimizations Implemented in the Improved Version

#### Rust - Traditional Method:
- 6k±1 Algorithm: tests only numbers of the form 6k±1 (reduces tests by ~66%)
- BufWriter for optimized I/O
- Tests only odd numbers after 2
- Integer approximation for sqrt
- Inline functions with `#[inline(always)]`
- Compilation with `-C target-cpu=native`

#### Rust - Sieve of Eratosthenes:
- Unsafe access to eliminate bounds checking
- Optimization to skip even numbers
- BufWriter for optimized I/O
- `get_unchecked()` for direct array access
- "Fat" LTO for maximum optimization
- Overflow-checks disabled

#### C - Traditional Method (Optimized):
- 6k±1 Algorithm: same optimization as Rust
- `setvbuf()` with 64KB buffer for optimized I/O
- `static inline` for functions
- Tests only odd numbers after 2
- Integer approximation for sqrt

#### C - Sieve of Eratosthenes (Optimized):
- Marks all even numbers at once with optimized loop
- `setvbuf()` for optimized I/O
- `static inline` for functions
- Optimized step in sieve (skips even numbers)
- Process only odd numbers in output

### Aggressive Compilation Flags:
**Rust:**
- `RUSTFLAGS=-C target-cpu=native -C target-feature=+crt-static`
- `opt-level = 3`, `lto = "fat"`, `overflow-checks = false`

**C:**
- `-O3 -march=native -mtune=native -flto -ffast-math`
- `-funroll-loops -finline-functions -fomit-frame-pointer -DNDEBUG`

### Performance Results

#### Original Results:
**Rust:**
- Traditional: 15.139 seconds
- Sieve of Eratosthenes: 15.393 seconds

**C:**
- Traditional: 11.127 seconds
- Sieve of Eratosthenes: 10.747 seconds

#### Optimized Results:
**Rust:**
- Traditional: 1.653 seconds (9.2x faster!)
- Sieve of Eratosthenes: 1.411 seconds (10.9x faster!)

**C:**
- Traditional: 1.685 seconds (6.6x faster!)
- Sieve of Eratosthenes: 1.430 seconds (7.5x faster!)

### Key Insights

1. **Massive Performance Gains**: Both languages achieved 6-11x speedup with optimizations
2. **Competitive Performance**: Rust and C now perform almost identically
3. **Sieve Advantage**: The Sieve of Eratosthenes is consistently faster for large ranges
4. **Optimization Effectiveness**: Proper algorithm choice and compiler flags are crucial

### Expected Output

All programs display:
- All prime numbers found (one per line)
- Total count of prime numbers found: 348,513
- Execution time in seconds

**Note**: The term "sieve" refers to the "Sieve of Eratosthenes" algorithm, which works like a sieve/strainer - it eliminates composite numbers, leaving only primes.
