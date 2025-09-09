#include "scalar/axpy_scalar.hpp"
#include "common/data_generator.hpp"
#include "common/timer.hpp"
#include <iostream>
#include <vector>
#include <iomanip>

/**
 * Micro-benchmark for scalar AXPY implementation
 * Measures performance across different vector sizes
 */

struct BenchmarkResult {
    size_t size;
    double time_ms;
    double gflops;
    double bandwidth_gb_s;
};

BenchmarkResult benchmark_axpy(size_t n, int iterations = 1000) {
    DataGenerator gen;
    std::vector<float> x = gen.generate_random(n);
    std::vector<float> y = gen.generate_random(n);
    float a = 1.5f;
    
    Timer timer;
    
    // Warmup
    for (int i = 0; i < 10; ++i) {
        AxpyScalar::compute(a, x, y);
    }
    
    // Actual benchmark
    timer.start();
    for (int i = 0; i < iterations; ++i) {
        AxpyScalar::compute(a, x, y);
    }
    timer.stop();
    
    double total_time_ms = timer.elapsed_ms();
    double avg_time_ms = total_time_ms / iterations;
    
    // Calculate performance metrics
    // AXPY performs: 2*n floating point operations (n multiplications + n additions)
    // and 3*n memory accesses (n reads from x, n reads from y, n writes to y)
    double flops = 2.0 * n * iterations;
    double gflops = (flops / 1e9) / (total_time_ms / 1000.0);
    
    // Memory bandwidth: 3*n*sizeof(float) bytes per iteration
    double bytes_per_iteration = 3.0 * n * sizeof(float);
    double total_bytes = bytes_per_iteration * iterations;
    double bandwidth_gb_s = (total_bytes / 1e9) / (total_time_ms / 1000.0);
    
    return {n, avg_time_ms, gflops, bandwidth_gb_s};
}

void run_size_sweep() {
    std::cout << "=== Scalar AXPY Micro-benchmark ===" << std::endl;
    std::cout << "Size\tTime(ms)\tGFLOPS\t\tBandwidth(GB/s)" << std::endl;
    std::cout << "----\t--------\t-------\t\t---------------" << std::endl;
    
    // Test different vector sizes
    std::vector<size_t> sizes = {
        1024,      // 4KB
        4096,      // 16KB
        16384,     // 64KB
        65536,     // 256KB
        262144,    // 1MB
        1048576,   // 4MB
        4194304,   // 16MB
        16777216   // 64MB
    };
    
    for (size_t size : sizes) {
        BenchmarkResult result = benchmark_axpy(size);
        
        std::cout << std::fixed << std::setprecision(3);
        std::cout << size << "\t"
                  << result.time_ms << "\t\t"
                  << result.gflops << "\t\t"
                  << result.bandwidth_gb_s << std::endl;
    }
}

void run_detailed_analysis(size_t size = 1048576) {
    std::cout << "\n=== Detailed Analysis (size=" << size << ") ===" << std::endl;
    
    DataGenerator gen;
    std::vector<float> x = gen.generate_random(size);
    std::vector<float> y = gen.generate_random(size);
    float a = 1.5f;
    
    Timer timer;
    const int iterations = 1000;
    
    // Measure single iteration
    timer.start();
    AxpyScalar::compute(a, x, y);
    timer.stop();
    double single_time_ms = timer.elapsed_ms();
    
    // Measure multiple iterations
    timer.start();
    for (int i = 0; i < iterations; ++i) {
        AxpyScalar::compute(a, x, y);
    }
    timer.stop();
    double total_time_ms = timer.elapsed_ms();
    double avg_time_ms = total_time_ms / iterations;
    
    std::cout << "Single iteration time: " << single_time_ms << " ms" << std::endl;
    std::cout << "Average time (" << iterations << " iterations): " << avg_time_ms << " ms" << std::endl;
    std::cout << "Time per element: " << (avg_time_ms * 1000) / size << " ns" << std::endl;
    
    // Performance metrics
    double flops = 2.0 * size;
    double gflops = (flops / 1e9) / (avg_time_ms / 1000.0);
    double bytes = 3.0 * size * sizeof(float);
    double bandwidth_gb_s = (bytes / 1e9) / (avg_time_ms / 1000.0);
    
    std::cout << "Performance: " << gflops << " GFLOPS" << std::endl;
    std::cout << "Memory bandwidth: " << bandwidth_gb_s << " GB/s" << std::endl;
}

int main() {
    run_size_sweep();
    run_detailed_analysis();
    
    std::cout << "\n=== Benchmark Complete ===" << std::endl;
    return 0;
}