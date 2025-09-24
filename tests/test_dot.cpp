#include "scalar/dot_scalar.hpp"
#include "common/data_generator.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

/**
 * Unit tests for scalar DOT product implementation
 * Tests correctness with various data patterns and edge cases
 */

bool test_basic_dot() {
    std::cout << "Testing basic DOT product operation... ";
    
    std::vector<float> x = {1.0f, 2.0f, 3.0f, 4.0f};
    std::vector<float> y = {2.0f, 3.0f, 4.0f, 5.0f};
    
    // Expected result: 1*2 + 2*3 + 3*4 + 4*5 = 2 + 6 + 12 + 20 = 40
    float expected = 40.0f;
    float result = DotScalar::compute(x, y);
    
    bool passed = std::abs(result - expected) < 1e-6f;
    std::cout << (passed ? "PASS" : "FAIL") << std::endl;
    return passed;
}

bool test_zero_vectors() {
    std::cout << "Testing zero vectors... ";
    
    std::vector<float> x = {0.0f, 0.0f, 0.0f};
    std::vector<float> y = {1.0f, 2.0f, 3.0f};
    
    float result = DotScalar::compute(x, y);
    bool passed = std::abs(result) < 1e-6f;
    
    std::cout << (passed ? "PASS" : "FAIL") << std::endl;
    return passed;
}

bool test_orthogonal_vectors() {
    std::cout << "Testing orthogonal vectors... ";
    
    std::vector<float> x = {1.0f, 0.0f};
    std::vector<float> y = {0.0f, 1.0f};
    
    float result = DotScalar::compute(x, y);
    bool passed = std::abs(result) < 1e-6f;
    
    std::cout << (passed ? "PASS" : "FAIL") << std::endl;
    return passed;
}

bool test_large_vectors() {
    std::cout << "Testing large vectors... ";
    
    const size_t n = 10000;
    DataGenerator gen;
    std::vector<float> x = gen.generate_random(n);
    std::vector<float> y = gen.generate_random(n);
    
    // Compute expected result manually
    float expected = 0.0f;
    for (size_t i = 0; i < n; ++i) {
        expected += x[i] * y[i];
    }
    
    float result = DotScalar::compute(x, y);
    bool passed = std::abs(result - expected) < 1e-6f;
    
    std::cout << (passed ? "PASS" : "FAIL") << std::endl;
    return passed;
}

bool test_edge_cases() {
    std::cout << "Testing edge cases... ";
    
    // Test single element
    std::vector<float> x_single = {42.0f};
    std::vector<float> y_single = {2.0f};
    float result_single = DotScalar::compute(x_single, y_single);
    bool single_passed = std::abs(result_single - 84.0f) < 1e-6f;
    
    // Test empty vectors (should work with 0 result)
    std::vector<float> x_empty, y_empty;
    bool empty_passed = false;
    try {
        float result_empty = DotScalar::compute(x_empty, y_empty);
        empty_passed = std::abs(result_empty) < 1e-6f;
    } catch (const std::invalid_argument&) {
        empty_passed = true; // Also acceptable to throw
    }
    
    bool passed = single_passed && empty_passed;
    std::cout << (passed ? "PASS" : "FAIL") << std::endl;
    return passed;
}

int main() {
    std::cout << "=== Scalar DOT Product Unit Tests ===" << std::endl;
    
    bool all_passed = true;
    all_passed &= test_basic_dot();
    all_passed &= test_zero_vectors();
    all_passed &= test_orthogonal_vectors();
    all_passed &= test_large_vectors();
    all_passed &= test_edge_cases();
    
    std::cout << "\n=== Test Results ===" << std::endl;
    std::cout << "All tests: " << (all_passed ? "PASS" : "FAIL") << std::endl;
    
    return all_passed ? 0 : 1;
}