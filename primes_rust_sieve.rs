use std::time::Instant;
use std::io::{self, Write, BufWriter};

fn optimized_sieve(limit: usize) -> Vec<bool> {
    let mut is_prime = vec![true; limit + 1];
    
    unsafe {
        // Usar acesso unsafe para eliminar bounds checking
        let ptr = is_prime.as_mut_ptr();
        
        *ptr.add(0) = false;
        if limit > 0 {
            *ptr.add(1) = false;
        }
        
        // Marcar todos os pares como não-primos (exceto 2)
        if limit >= 4 {
            for i in (4..=limit).step_by(2) {
                *ptr.add(i) = false;
            }
        }
        
        // Crivo otimizado começando com ímpares
        let sqrt_limit = (limit as f64).sqrt() as usize;
        let mut i = 3;
        while i <= sqrt_limit {
            if *ptr.add(i) {
                // Começar em i² e pular números pares
                let mut j = i * i;
                let step = i * 2; // Para pular números pares
                while j <= limit {
                    *ptr.add(j) = false;
                    j += step;
                }
            }
            i += 2;
        }
    }
    
    is_prime
}

fn main() {
    const LIMIT: usize = 5_000_000;
    
    println!("Contando números primos de 1 a {} (usando Crivo de Eratóstenes)...", LIMIT);
    
    let start = Instant::now();
    let is_prime = optimized_sieve(LIMIT);
    
    // Usar BufWriter para I/O otimizado
    let stdout = io::stdout();
    let mut writer = BufWriter::new(stdout.lock());
    
    let mut count = 0;
    
    // Processar 2 separadamente
    if LIMIT >= 2 && is_prime[2] {
        writeln!(writer, "2").unwrap();
        count += 1;
    }
    
    // Processar apenas números ímpares para reduzir iterações
    for n in (3..=LIMIT).step_by(2) {
        if unsafe { *is_prime.get_unchecked(n) } {
            writeln!(writer, "{}", n).unwrap();
            count += 1;
        }
    }
    
    writer.flush().unwrap();
    drop(writer);
    
    let duration = start.elapsed();
    
    println!("\nQuantidade de números primos encontrados: {}", count);
    println!("Tempo gasto: {:.3} segundos", duration.as_secs_f64());
}
