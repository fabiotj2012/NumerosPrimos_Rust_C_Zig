use std::time::Instant;
use std::io::{self, Write, BufWriter};

#[inline(always)]
fn is_prime(n: u32) -> bool {
    if n < 2 {
        return false;
    }
    if n == 2 || n == 3 {
        return true;
    }
    if n % 2 == 0 || n % 3 == 0 {
        return false;
    }
    
    // Otimização: usar aproximação inteira para sqrt
    let mut sqrt_n = (n as f64).sqrt() as u32;
    if sqrt_n * sqrt_n < n {
        sqrt_n += 1;
    }
    
    // Otimização 6k±1: todos os primos > 3 são da forma 6k±1
    let mut i = 5;
    while i <= sqrt_n {
        if n % i == 0 || n % (i + 2) == 0 {
            return false;
        }
        i += 6;
    }
    true
}

fn main() {
    const LIMIT: u32 = 5_000_000;
    
    println!("Contando números primos de 1 a {}...", LIMIT);
    
    let start = Instant::now();
    let mut count = 0;
    
    // Usar BufWriter para reduzir overhead de I/O
    let stdout = io::stdout();
    let mut writer = BufWriter::new(stdout.lock());
    
    // Casos especiais
    if LIMIT >= 2 {
        writeln!(writer, "2").unwrap();
        count += 1;
    }
    
    // Testar apenas números ímpares >= 3
    for n in (3..=LIMIT).step_by(2) {
        if is_prime(n) {
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
