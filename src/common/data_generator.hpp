#pragma once

#include <vector>
#include <random>
#include <algorithm>

/**
 * Data generator for benchmark testing
 * Creates reproducible test data with various patterns
 */
class DataGenerator {
private:
    std::mt19937 gen;
    std::uniform_real_distribution<float> dist;

public:
    DataGenerator(unsigned int seed = 42) : gen(seed), dist(-1.0f, 1.0f) {}
    
    // Generate random float data
    std::vector<float> generate_random(size_t size) {
        std::vector<float> data(size);
        std::generate(data.begin(), data.end(), [this]() { return dist(gen); });
        return data;
    }
    
    // Generate sequential data (0, 1, 2, ...)
    std::vector<float> generate_sequential(size_t size) {
        std::vector<float> data(size);
        std::iota(data.begin(), data.end(), 0.0f);
        return data;
    }
    
    // Generate constant data
    std::vector<float> generate_constant(size_t size, float value = 1.0f) {
        return std::vector<float>(size, value);
    }
    
    // Generate data with specific pattern for cache analysis
    std::vector<float> generate_strided(size_t size, size_t stride = 1) {
        std::vector<float> data(size);
        for (size_t i = 0; i < size; i += stride) {
            data[i] = static_cast<float>(i);
        }
        return data;
    }
};