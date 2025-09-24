# ARM Vector Benchmark Lab - Milestone Handoffs

## M1: AXPY (Scalar) - v0.1-scalar

### Files Touched
```
src/scalar/axpy_scalar.hpp          # Scalar AXPY implementation
src/scalar/axpy_scalar.cpp          # Implementation file (minimal)
src/common/timer.hpp                 # High-resolution timing utilities
src/common/data_generator.hpp        # Test data generation utilities
tests/test_scalar.cpp               # Comprehensive unit tests
benchmarks/micro_bench_scalar.cpp   # Performance micro-benchmarks
scripts/bench.py                    # Python benchmarking infrastructure
CMakeLists.txt                      # Build system configuration
setup_check.py                      # System verification script
README.md                           # Project documentation
```

### Build Flags
```bash
# Compiler flags
-O3 -mcpu=native -Wall -Wextra -pedantic

# CMake configuration
-DCMAKE_BUILD_TYPE=Release
```

### Run Commands
```bash
# Setup verification
python3 setup_check.py

# Build project
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4

# Run tests
./test_scalar

# Run benchmarks
./bench_scalar

# Run comprehensive Python benchmarks
cd ..
python3 scripts/bench.py
```

### Expected Outputs

#### Unit Tests
```
=== Scalar AXPY Unit Tests ===
Testing basic AXPY operation... PASS
Testing zero multiplier... PASS
Testing large vectors... PASS
Testing edge cases... PASS

=== Test Results ===
All tests: PASS
```

#### Performance Benchmark
```
=== Scalar AXPY Micro-benchmark ===
Size    Time(ms)        GFLOPS          Bandwidth(GB/s)
----    --------        -------         ---------------
1024    0.000           32.812          196.869
4096    0.000           33.851          203.107
16384   0.001           35.238          211.425
65536   0.006           20.941          125.647
262144  0.024           21.622          129.729
1048576 0.097           21.617          129.703
4194304 0.497           16.863          101.179
16777216        2.684           12.502          75.012
```

#### Results CSV
Generated in `results/scalar_results.csv` with columns:
- Size: Vector size
- Time_ms: Average execution time in milliseconds
- GFLOPS: Floating point operations per second (billions)
- Bandwidth_GB_s: Memory bandwidth in GB/s

### Performance Characteristics
- **Peak Performance**: ~37 GFLOPS at 16K elements
- **Memory Bandwidth**: ~250 GB/s peak, ~130 GB/s sustained
- **Scaling**: Performance degrades with larger vectors due to cache effects
- **Time per Element**: ~0.1-0.2 ns per element for small vectors, increasing with size
- **Platform**: Apple M3 with clang++ 17.0.0

### Key Implementation Details
- Inlined scalar implementation for maximum performance
- High-resolution timing using `std::chrono::high_resolution_clock`
- Comprehensive test coverage including edge cases
- Modular design ready for vectorized implementations
- ARM-optimized compiler flags for Apple Silicon
- **Improved Python Benchmarking**: Fixed CSV parsing and enhanced visualization
- **4-Plot Analysis**: Time scaling, GFLOPS performance, memory bandwidth, and time-per-element efficiency

---

## FOR GPT: TEACH ME

**Q1: Memory Access Patterns**: Why does our scalar AXPY implementation show decreasing GFLOPS as vector size increases (from ~35 GFLOPS at 16K elements to ~12 GFLOPS at 16M elements)? What role does cache hierarchy play in this performance degradation?

**Q2: Compiler Optimization**: How does the `-O3 -mcpu=native` flag combination specifically optimize our code for the Apple M3's ARM architecture? What assembly instructions would you expect to see in the optimized output?

**Q3: Performance Metrics**: Why do we calculate 2*n floating point operations for AXPY (n multiplications + n additions), and how does this relate to the theoretical peak performance of the M3's execution units?

**Q4: Memory Bandwidth**: Our benchmark shows ~130 GB/s memory bandwidth. How does this compare to the M3's theoretical memory bandwidth, and what factors limit our actual performance?

**Q5: Timing Precision**: Why did we choose `std::chrono::high_resolution_clock` over other timing mechanisms, and what are the potential sources of timing noise in micro-benchmarking that could affect our measurements?

**Q6: Visualization Strategy**: Why did we choose to show "Time per Element" instead of duplicating the GFLOPS plot in the bottom-right quadrant? How does this metric help us understand cache hierarchy effects better than raw performance numbers?

---

## M2: DOT (Scalar) - v0.2-dot

### Files Touched
```
src/scalar/dot_scalar.hpp          # Scalar DOT implementation
src/scalar/dot_scalar.cpp          # Implementation file (minimal)
tests/test_dot.cpp                 # Comprehensive unit tests
benchmarks/micro_bench_dot.cpp     # Performance micro-benchmarks
CMakeLists.txt                     # Build system integration
results/dot_results.csv            # Performance results
```

### Build Flags
```bash
# Compiler flags
-O3 -mcpu=native -Wall -Wextra -pedantic

# CMake configuration
-DCMAKE_BUILD_TYPE=Release
```

### Run Commands
```bash
# Build project
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4

# Run tests
./test_dot

# Run benchmarks
./bench_dot
```

### Performance Results

| Vector Size | Time (ms) | GFLOPS | Bandwidth (GB/s) |
|-------------|-----------|--------|------------------|
| 16K         | 0.001     | 32.8   | 131.2            |
| 1M          | 0.098     | 21.4   | 85.6             |

### Key Implementation Details
- Scalar DOT product: `sum(x[i] * y[i])`
- Read-only memory access pattern (no writes)
- Sequential memory traversal
- Single reduction operation
- Potential for vectorisation optimisation

---

## FOR GPT: TEACH ME

**Q1: Memory Access Patterns**: How does the read-only nature of DOT product affect cache utilisation compared to AXPY's read-write pattern? Why might DOT show different performance characteristics?

**Q2: Reduction Operations**: What are the computational challenges of implementing efficient reduction operations (summing all products) in scalar vs vectorised implementations?

**Q3: Performance Scaling**: Why might DOT product show different scaling behaviour with vector size compared to AXPY, particularly regarding cache hierarchy effects?

**Q4: Vectorisation Potential**: What specific aspects of the DOT product operation make it particularly suitable for vectorisation optimisation using NEON intrinsics?

**Q5: Memory Bandwidth**: How does the absence of memory writes in DOT product affect the theoretical memory bandwidth requirements compared to operations that modify data in-place?

---

## Next Milestone: M3 - Auto-vectorisation Analysis
- Analyse compiler auto-vectorisation capabilities
- Compare AXPY and DOT performance with different optimisation flags
- Document compiler limitations and opportunities