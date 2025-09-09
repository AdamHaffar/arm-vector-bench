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
- **Peak Performance**: ~35 GFLOPS at 16K elements
- **Memory Bandwidth**: ~130 GB/s sustained
- **Scaling**: Performance degrades with larger vectors due to cache effects
- **Platform**: Apple M3 with clang++ 17.0.0

### Key Implementation Details
- Inlined scalar implementation for maximum performance
- High-resolution timing using `std::chrono::high_resolution_clock`
- Comprehensive test coverage including edge cases
- Modular design ready for vectorized implementations
- ARM-optimized compiler flags for Apple Silicon

---

## FOR GPT: TEACH ME

**Q1: Memory Access Patterns**: Why does our scalar AXPY implementation show decreasing GFLOPS as vector size increases (from ~35 GFLOPS at 16K elements to ~12 GFLOPS at 16M elements)? What role does cache hierarchy play in this performance degradation?

**Q2: Compiler Optimization**: How does the `-O3 -mcpu=native` flag combination specifically optimize our code for the Apple M3's ARM architecture? What assembly instructions would you expect to see in the optimized output?

**Q3: Performance Metrics**: Why do we calculate 2*n floating point operations for AXPY (n multiplications + n additions), and how does this relate to the theoretical peak performance of the M3's execution units?

**Q4: Memory Bandwidth**: Our benchmark shows ~130 GB/s memory bandwidth. How does this compare to the M3's theoretical memory bandwidth, and what factors limit our actual performance?

**Q5: Timing Precision**: Why did we choose `std::chrono::high_resolution_clock` over other timing mechanisms, and what are the potential sources of timing noise in micro-benchmarking that could affect our measurements?

---

## Next Milestone: M2 - DOT (Scalar)
- Implement scalar dot product operation
- Similar testing and benchmarking framework
- Compare performance characteristics with AXPY
- Expected to show different memory access patterns