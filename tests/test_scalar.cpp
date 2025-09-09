#include "scalar/axpy_scalar.hpp"
#include "common/data_generator.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

/**
 * Unit tests for scalar AXPY implementation
 * Tests correctness with various data patterns
 */

bool test_basic_axpy() {
    std::cout << "Testing basic AXPY operation... ";
    
    std::vector<float> x = {1.0f, 2.0f, 3.0f, 4.0f};
    std::vector<float> y = {0.1f, 0.2f, 0.3f, 0.4f};
    float a = 2.0f;
    
    // Expected result: y = 2*[1,2,3,4] + [0.1,0.2,0.3,0.4] = [2.1,4.2,6.3,8.4]
    std::vector<float> expected = {2.1f, 4.2f, 6.3f, 8.4f};
    
    AxpyScalar::compute(a, x, y);
    
    bool passed = true;
    for (size_t i = 0; i < y.size(); ++i) {
        if (std::abs(y[i] - expected[i]) > 1e-6f) {
            passed = false;
            break;
        }
    }
    
    std::cout << (passed ? "PASS" : "FAIL") << std::endl;
    return passed;
}

bool test_zero_multiplier() {
    std::cout << "Testing zero multiplier... ";
    
    std::vector<float> x = {1.0f, 2.0f, 3.0f};
    std::vector<float> y = {0.5f, 1.0f, 1.5f};
    float a = 0.0f;
    
    std::vector<float> original_y = y;
    AxpyScalar::compute(a, x, y);
    
    // With a=0, y should remain unchanged
    bool passed = true;
    for (size_t i = 0; i < y.size(); ++i) {
        if (std::abs(y[i] - original_y[i]) > 1e-6f) {
            passed = false;
            break;
        }
    }
    
    std::cout << (passed ? "PASS" : "FAIL") << std::endl;
    return passed;
}

bool test_large_vectors() {
    std::cout << "Testing large vectors... ";
    
    const size_t n = 10000;
    DataGenerator gen;
    std::vector<float> x = gen.generate_random(n);
    std::vector<float> y = gen.generate_random(n);
    float a = 1.5f;
    
    // Store original y for verification
    std::vector<float> original_y = y;
    
    AxpyScalar::compute(a, x, y);
    
    // Verify: y[i] = a * x[i] + original_y[i]
    bool passed = true;
    for (size_t i = 0; i < n; ++i) {
        float expected = a * x[i] + original_y[i];
        if (std::abs(y[i] - expected) > 1e-6f) {
            passed = false;
            break;
        }
    }
    
    std::cout << (passed ? "PASS" : "FAIL") << std::endl;
    return passed;
}

bool test_edge_cases() {
    std::cout << "Testing edge cases... ";
    
    // Test empty vectors
    std::vector<float> x_empty, y_empty;
    try {
        AxpyScalar::compute(1.0f, x_empty, y_empty);
    } catch (...) {
        std::cout << "FAIL (empty vector handling)" << std::endl;
        return false;
    }
    
    // Test single element
    std::vector<float> x_single = {42.0f};
    std::vector<float> y_single = {1.0f};
    AxpyScalar::compute(2.0f, x_single, y_single);
    
    bool passed = (std::abs(y_single[0] - 85.0f) < 1e-6f);
    std::cout << (passed ? "PASS" : "FAIL") << std::endl;
    return passed;
}

int main() {
    std::cout << "=== Scalar AXPY Unit Tests ===" << std::endl;
    
    bool all_passed = true;
    all_passed &= test_basic_axpy();
    all_passed &= test_zero_multiplier();
    all_passed &= test_large_vectors();
    all_passed &= test_edge_cases();
    
    std::cout << "\n=== Test Results ===" << std::endl;
    std::cout << "All tests: " << (all_passed ? "PASS" : "FAIL") << std::endl;
    
    return all_passed ? 0 : 1;
}