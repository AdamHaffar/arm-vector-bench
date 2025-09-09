# ARM Vector Benchmark Lab

A comprehensive benchmarking suite for vector operations on Apple Silicon (M3) processors, comparing scalar, auto-vectorized, NEON intrinsics, and Accelerate framework implementations.

## Quick Start

```bash
# Check system requirements
python3 setup_check.py

# Build the project
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)

# Run tests
./test_scalar
./test_autovec
./test_neon
./test_accelerate  # macOS only

# Run benchmarks
./bench_scalar
./bench_autovec
./bench_neon
./bench_accelerate  # macOS only

# Run comprehensive benchmark suite
cd ..
python3 scripts/bench.py
```

## Project Structure

- `src/`: Implementation source code organized by optimization technique
- `tests/`: Unit tests for each implementation
- `benchmarks/`: Micro-benchmarks for performance measurement
- `scripts/`: Python scripts for comprehensive benchmarking and visualization
- `results/`: Generated benchmark results and plots

## Milestones

- **v0.1-scalar**: Basic AXPY scalar implementation
- **v0.2-autovec**: Compiler auto-vectorization
- **v0.3-neon**: Manual NEON intrinsics
- **v0.4-compare-accelerate**: Accelerate framework integration
- **v0.5-memory-patterns**: Memory access analysis
- **v0.6-multi-threaded**: OpenMP parallelization
- **v0.7-optimization**: Advanced optimizations
- **v0.8-comprehensive**: Full benchmark suite

## Results

### M1: Scalar AXPY Performance (Apple M3)

| Vector Size | Time (ms) | GFLOPS | Bandwidth (GB/s) |
|-------------|-----------|--------|------------------|
| 1K          | 0.000     | 32.8   | 196.9            |
| 4K          | 0.000     | 33.9   | 203.1            |
| 16K         | 0.001     | 35.2   | 211.4            |
| 64K         | 0.006     | 20.9   | 125.6            |
| 256K        | 0.024     | 21.6   | 129.7            |
| 1M          | 0.097     | 21.6   | 129.7            |
| 4M          | 0.497     | 16.9   | 101.2            |
| 16M         | 2.684     | 12.5   | 75.0             |

**Key Insights:**
- Peak performance: ~35 GFLOPS at 16K elements
- Sustained bandwidth: ~130 GB/s
- Performance degrades with larger vectors due to cache effects
- Baseline established for vectorized implementation comparison

## Requirements

- macOS with Apple Silicon (M1/M2/M3)
- clang++ (Xcode command line tools)
- cmake 3.16+
- Python 3.7+ with numpy, matplotlib