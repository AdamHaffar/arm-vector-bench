# ARM Vector Benchmark Lab - Development Roadmap

## Overview
A focused benchmarking suite for vector operations on Apple Silicon (M3) processors, comparing scalar, auto-vectorised, and NEON intrinsics implementations.

## Development Schedule

### Week 0 (Current Week) - Foundation & Baseline
**Goal**: Establish scalar baseline and project infrastructure

- [x] **M1: AXPY (scalar)** - Basic scalar implementation with comprehensive testing
  - Scalar AXPY operation: `y = a * x + y`
  - High-resolution timing utilities
  - Unit tests covering edge cases and correctness
  - Micro-benchmarking suite with GFLOPS/bandwidth metrics
  - CMake build system with ARM optimisation flags
  - Python benchmarking infrastructure
  - **Status**: ✅ Complete
  - **Results**: ~21 GFLOPS, ~130 GB/s on M3

### Week 1 - Core Operations & Auto-vectorisation
**Goal**: Expand to core BLAS operations and explore compiler optimisations

- [x] **M2: DOT (scalar)** - Dot product implementation
  - Scalar dot product: `sum(x[i] * y[i])`
  - Similar testing and benchmarking framework
  - Compare with AXPY performance characteristics
  - **Status**: ✅ Complete
  - **Results**: ~15 GFLOPS, ~95 GB/s on M3

- [ ] **M3: Auto-vectorisation analysis** - Compiler optimisation exploration
  - Test different compiler flags (-O1, -O2, -O3, -Ofast)
  - Analyse assembly output for vectorisation
  - Document compiler capabilities and limitations
  - Compare AXPY and DOT performance with different flags

### Week 2 - NEON Intrinsics Implementation
**Goal**: Manual vectorisation using ARM NEON intrinsics

- [ ] **M4: NEON AXPY (intrinsics)** - Manual vectorisation of AXPY
  - ARM NEON intrinsics implementation
  - 128-bit vector operations with proper alignment
  - Masked tail handling for non-multiple-of-4 sizes
  - Compare vs scalar and auto-vectorised versions

### Week 3 - Analysis & Polish
**Goal**: Comprehensive analysis and project completion

- [ ] **M5: Results + roofline write-up + plots** - Project completion
  - Comprehensive performance analysis and visualisation
  - Roofline model analysis for M3 architecture
  - Final performance comparison tables
  - Git tags for major milestones
  - Prepare for public release

## Success Metrics
- [x] Scalar implementations pass comprehensive unit tests
- [x] Performance benchmarks show clear scaling characteristics
- [ ] Auto-vectorisation analysis reveals compiler capabilities
- [ ] NEON implementations demonstrate significant speedup over scalar
- [ ] Documentation is complete and professional

