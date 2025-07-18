const std = @import("std");

pub fn main() !void {
    const max = 5_000_000;

    var timer = try std.time.Timer.start();

    // Buffer I/O otimizado (equivalente ao BufWriter do Rust)
    var stdout_file = std.io.getStdOut().writer();
    var buf_writer = std.io.bufferedWriter(stdout_file);
    const writer = buf_writer.writer();

    // Allocator otimizado (page_allocator é mais rápido para grandes alocações)
    const allocator = std.heap.page_allocator;

    // Crivo otimizado - só ímpares (economiza 50% memória)
    const sieve_size = (max / 2) + 1;
    const is_prime = try allocator.alloc(bool, sieve_size);
    defer allocator.free(is_prime);

    // Inicialização rápida com memset
    @memset(is_prime, true);

    var count: u32 = 0;

    // 2 é primo especial
    if (max >= 2) {
        count += 1;
        try writer.print("2\n", .{});
    }

    // Crivo ultra-otimizado com técnicas do seu repo
    const sqrt_max = @as(usize, @intFromFloat(@sqrt(@as(f64, @floatFromInt(max))))) + 1;

    var i: usize = 3;
    while (i <= sqrt_max) : (i += 2) {
        const idx = i >> 1; // Bit shift em vez de divisão
        if (is_prime[idx]) {
            // Otimização: começa do quadrado e pula pares
            var j = i * i;
            const step = i << 1; // 2*i via bit shift
            while (j <= max) : (j += step) {
                is_prime[j >> 1] = false;
            }
        }
    }

    // Impressão otimizada com buffer fixo (técnica do C)
    var buffer: [16]u8 = undefined;

    // Loop de saída otimizado
    var n: usize = 3;
    while (n <= max) : (n += 2) {
        const idx = n >> 1;
        if (is_prime[idx]) {
            count += 1;
            // Formatação manual mais rápida que print
            const len = std.fmt.formatIntBuf(&buffer, n, 10, .lower, .{});
            try writer.writeAll(buffer[0..len]);
            try writer.writeByte('\n');
        }
    }

    // Flush do buffer antes do resumo
    try buf_writer.flush();

    const elapsed = timer.read();
    const seconds = @as(f64, @floatFromInt(elapsed)) / 1_000_000_000.0;
    try stdout_file.print("\nResumo:\nTotal de primos encontrados: {d}\nTempo total: {d:.3} segundos\n", .{ count, seconds });
}
