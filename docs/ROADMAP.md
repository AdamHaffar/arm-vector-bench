# ARM Vector Benchmark Lab - Development Roadmap

## Overview
A comprehensive benchmarking suite for vector operations on Apple Silicon (M3) processors, comparing scalar, auto-vectorized, NEON intrinsics, and Accelerate framework implementations.

## Development Schedule

### Week 0 (Current Week) - Foundation & Baseline
**Goal**: Establish scalar baseline and project infrastructure

- [x] **M1: AXPY (scalar)** - Basic scalar implementation with comprehensive testing
  - Scalar AXPY operation: `y = a * x + y`
  - High-resolution timing utilities
  - Unit tests covering edge cases and correctness
  - Micro-benchmarking suite with GFLOPS/bandwidth metrics
  - CMake build system with ARM optimization flags
  - Python benchmarking infrastructure
  - **Status**: ✅ Complete
  - **Results**: ~21 GFLOPS, ~130 GB/s on M3

### Week 1 - Core Operations & Auto-Vectorization
**Goal**: Expand to core BLAS operations and explore compiler optimizations

- [ ] **M2: DOT (scalar)** - Dot product implementation
  - Scalar dot product: `sum(x[i] * y[i])`
  - Similar testing and benchmarking framework
  - Compare with AXPY performance characteristics

- [ ] **M3: GEMM (naive, tiny sizes)** - Matrix multiplication baseline
  - Naive O(n³) implementation for small matrices
  - Focus on correctness and basic performance
  - Memory access pattern analysis

- [ ] **M4: Auto-vectorization flags & notes** - Compiler optimization exploration
  - Test different compiler flags (-O1, -O2, -O3, -Ofast)
  - Analyze assembly output for vectorization
  - Document compiler capabilities and limitations

### Week 2 - NEON Intrinsics Implementation
**Goal**: Manual vectorization using ARM NEON intrinsics

- [ ] **M5: NEON AXPY (intrinsics)** - Manual vectorization of AXPY
  - ARM NEON intrinsics implementation
  - 128-bit and 256-bit vector operations
  - Proper alignment and memory handling
  - Compare vs scalar and auto-vectorized versions

- [ ] **M6: NEON DOT (lane reductions)** - Vectorized dot product
  - NEON intrinsics with lane reduction operations
  - Masked tail handling for non-multiple-of-4 sizes
  - Performance comparison across implementations

### Week 3 - Analysis & Polish
**Goal**: Comprehensive analysis and project completion

- [ ] **M7: Python sweeps + visualization** - Comprehensive benchmarking
  - Automated size sweeps across all implementations
  - Matplotlib visualization of performance trends
  - Optional Accelerate framework comparison
  - CSV export for further analysis

- [ ] **M8: README polish & results** - Project completion
  - Comprehensive README with results summary
  - "What I learned" section with insights
  - Performance comparison tables
  - Git tags for major milestones
  - Prepare for public release

## Milestone Naming Convention
- Feature branches: `m{n}-{short-name}` (e.g., `m1-axpy-scalar`)
- Commits: Small, incremental changes (1-3 per day max)
- PRs: Squash-merge milestone PRs
- Tags: `v0.{n}-{name}` (e.g., `v0.1-scalar`)

## Success Metrics
- [ ] All implementations pass comprehensive unit tests
- [ ] Performance benchmarks show clear scaling characteristics
- [ ] NEON implementations demonstrate significant speedup over scalar
- [ ] Documentation is complete and professional
- [ ] Code is ready for public release

## Notes
- Focus on Apple M3 optimization (`-mcpu=native`)
- Maintain human-readable, incremental commits
- Each milestone should be independently testable
- Keep performance measurements consistent across implementations