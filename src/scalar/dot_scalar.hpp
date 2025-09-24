#pragma once

#include <vector>

/**
 * Scalar implementation of DOT product operation: result = sum(x[i] * y[i])
 * This provides the baseline implementation without any vectorisation
 */
class DotScalar {
public:
    // Perform DOT product operation: result = sum(x[i] * y[i])
    // Parameters:
    //   x: first input vector
    //   y: second input vector  
    //   n: number of elements
    // Returns: scalar dot product result
    static float compute(const float* x, const float* y, size_t n) {
        float result = 0.0f;
        for (size_t i = 0; i < n; ++i) {
            result += x[i] * y[i];
        }
        return result;
    }
    
    // Vector version using std::vector
    static float compute(const std::vector<float>& x, const std::vector<float>& y) {
        if (x.size() != y.size()) {
            throw std::invalid_argument("Vector sizes must match");
        }
        return compute(x.data(), y.data(), x.size());
    }
    
    // Get implementation name for reporting
    static const char* name() {
        return "Scalar";
    }
};