cmake_minimum_required(VERSION 3.16)
project(ArmVectorBenchmark VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler-specific flags for ARM optimization
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -mcpu=native -Wall -Wextra -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wall -Wextra -pedantic")
else()
    message(WARNING "clang++ recommended for ARM optimization")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wall -Wextra -pedantic")
endif()

# Optional OpenMP support
option(ENABLE_OPENMP "Enable OpenMP parallelization" OFF)
if(ENABLE_OPENMP)
    find_package(OpenMP REQUIRED)
    if(APPLE)
        # On macOS, link with libomp
        find_library(LIBOMP omp)
        if(LIBOMP)
            set(OpenMP_CXX_LIBRARIES ${LIBOMP})
        endif()
    endif()
endif()

# Include directories
include_directories(src)

# Common utilities (header-only library)
add_library(common_utils INTERFACE)
target_include_directories(common_utils INTERFACE src)

# Scalar implementation
add_library(scalar_impl
    src/scalar/axpy_scalar.cpp
    src/scalar/axpy_scalar.hpp
    src/scalar/dot_scalar.cpp
    src/scalar/dot_scalar.hpp
)

# Auto-vectorized implementation (placeholder for v0.2)
# add_library(autovec_impl
#     src/autovec/axpy_autovec.cpp
#     src/autovec/axpy_autovec.hpp
# )

# NEON implementation (placeholder for v0.3)
# add_library(neon_impl
#     src/neon/axpy_neon.cpp
#     src/neon/axpy_neon.hpp
# )

# Accelerate framework implementation (placeholder for v0.4)
# if(APPLE)
#     add_library(accelerate_impl
#         src/accelerate/axpy_accelerate.cpp
#         src/accelerate/axpy_accelerate.hpp
#     )
#     target_link_libraries(accelerate_impl Accelerate)
# endif()

# Test executables
enable_testing()

add_executable(test_scalar tests/test_scalar.cpp)
target_link_libraries(test_scalar scalar_impl common_utils)

add_executable(test_dot tests/test_dot.cpp)
target_link_libraries(test_dot scalar_impl common_utils)

# add_executable(test_autovec tests/test_autovec.cpp)
# target_link_libraries(test_autovec autovec_impl common_utils)

# add_executable(test_neon tests/test_neon.cpp)
# target_link_libraries(test_neon neon_impl common_utils)

# if(APPLE)
#     add_executable(test_accelerate tests/test_accelerate.cpp)
#     target_link_libraries(test_accelerate accelerate_impl common_utils)
# endif()

# Benchmark executables
add_executable(bench_scalar benchmarks/micro_bench_scalar.cpp)
target_link_libraries(bench_scalar scalar_impl common_utils)

add_executable(bench_dot benchmarks/micro_bench_dot.cpp)
target_link_libraries(bench_dot scalar_impl common_utils)

# add_executable(bench_autovec benchmarks/micro_bench_autovec.cpp)
# target_link_libraries(bench_autovec autovec_impl common_utils)

# add_executable(bench_neon benchmarks/micro_bench_neon.cpp)
# target_link_libraries(bench_neon neon_impl common_utils)

# if(APPLE)
#     add_executable(bench_accelerate benchmarks/micro_bench_accelerate.cpp)
#     target_link_libraries(bench_accelerate accelerate_impl common_utils)
# endif()

# Add OpenMP if enabled
if(ENABLE_OPENMP)
    target_link_libraries(scalar_impl OpenMP::OpenMP_CXX)
    # target_link_libraries(autovec_impl OpenMP::OpenMP_CXX)
    # target_link_libraries(neon_impl OpenMP::OpenMP_CXX)
    # if(APPLE)
    #     target_link_libraries(accelerate_impl OpenMP::OpenMP_CXX)
    # endif()
endif()

# Create build directory
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/results)