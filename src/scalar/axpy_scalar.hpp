#pragma once

#include <vector>

/**
 * Scalar implementation of AXPY operation: y = a * x + y
 * This is the baseline implementation without any vectorisation
 */
class AxpyScalar {
public:
    // Perform AXPY operation: y = a * x + y
    // Parameters:
    //   a: scalar multiplier
    //   x: input vector
    //   y: input/output vector (modified in place)
    //   n: number of elements
    static void compute(float a, const float* x, float* y, size_t n) {
        for (size_t i = 0; i < n; ++i) {
            y[i] = a * x[i] + y[i];
        }
    }
    
    // Vector version using std::vector
    static void compute(float a, const std::vector<float>& x, std::vector<float>& y) {
        if (x.size() != y.size()) {
            throw std::invalid_argument("Vector sizes must match");
        }
        compute(a, x.data(), y.data(), x.size());
    }
    
    // Get implementation name for reporting
    static const char* name() {
        return "Scalar";
    }
};