# ARM Vector Benchmark Lab

> 🚧 **Work in Progress** - This project is actively under development. Current status: M2 (DOT Scalar) complete. See [ROADMAP.md](docs/ROADMAP.md) for development timeline.

A focused benchmarking suite for vector operations on Apple Silicon (M3) processors, comparing scalar, auto-vectorised, and NEON intrinsics implementations.

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
./test_dot

# Run benchmarks
./bench_scalar
./bench_dot

# Run comprehensive benchmark suite
cd ..
python3 scripts/bench.py
```

## Project Structure

- `src/`: Implementation source code organised by optimisation technique
- `tests/`: Unit tests for each implementation
- `benchmarks/`: Micro-benchmarks for performance measurement
- `scripts/`: Python scripts for comprehensive benchmarking and visualisation
- `results/`: Generated benchmark results and plots

## Development Status

### Completed Milestones ✅
- **M1: AXPY (Scalar)** - Basic AXPY scalar implementation with comprehensive testing and benchmarking
- **M2: DOT (Scalar)** - Dot product scalar implementation with performance analysis

### Planned Milestones 📋
- **M3: Auto-vectorisation Analysis** - Compiler optimisation exploration
- **M4: NEON AXPY** - Manual NEON intrinsics implementation
- **M5: Results & Analysis** - Comprehensive performance analysis and roofline model

See [ROADMAP.md](docs/ROADMAP.md) for detailed development timeline and [Handoff.md](docs/Handoff.md) for milestone documentation.

## Results

### M1: Scalar AXPY Performance (Apple M3)

| Vector Size | Time (ms) | GFLOPS | Bandwidth (GB/s) | Time/Element (ns) |
|-------------|-----------|--------|------------------|-------------------|
| 1K          | 0.000     | 41.9   | 251.4            | 0.0               |
| 4K          | 0.000     | 36.2   | 217.1            | 0.0               |
| 16K         | 0.001     | 36.8   | 220.6            | 0.1               |
| 64K         | 0.006     | 22.3   | 134.0            | 0.1               |
| 256K        | 0.024     | 21.8   | 131.0            | 0.1               |
| 1M          | 0.098     | 21.4   | 128.3            | 0.1               |
| 4M          | 0.505     | 16.6   | 99.6             | 0.1               |
| 16M         | 2.663     | 12.6   | 75.6             | 0.2               |

**Key Insights:**
- Peak performance: ~37 GFLOPS at 16K elements
- Peak bandwidth: ~250 GB/s for small vectors, ~130 GB/s sustained
- Time per element: ~0.1-0.2 ns, showing excellent cache efficiency
- Performance degrades with larger vectors due to cache hierarchy effects

### M2: Scalar DOT Performance (Apple M3)

| Vector Size | Time (ms) | GFLOPS | Bandwidth (GB/s) | Time/Element (ns) |
|-------------|-----------|--------|------------------|-------------------|
| 16K         | 0.001     | 15.2   | 95.1             | 0.065            |
| 1M          | 0.067     | 14.9   | 93.2             | 0.067            |

**Key Insights:**
- Consistent ~15 GFLOPS performance across sizes
- Read-only memory access pattern (no writes)
- Lower bandwidth requirements compared to AXPY
- Baseline established for vectorised implementation comparison

## Requirements

- macOS with Apple Silicon (M1/M2/M3)
- clang++ (Xcode command line tools)
- cmake 3.16+
- Python 3.7+ with numpy, matplotlib