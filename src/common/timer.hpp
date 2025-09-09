#pragma once

#include <chrono>
#include <iostream>

/**
 * High-resolution timer for micro-benchmarking
 * Uses std::chrono::high_resolution_clock for maximum precision
 */
class Timer {
private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;
    bool running = false;

public:
    void start() {
        start_time = std::chrono::high_resolution_clock::now();
        running = true;
    }
    
    void stop() {
        end_time = std::chrono::high_resolution_clock::now();
        running = false;
    }
    
    // Get elapsed time in nanoseconds
    long long elapsed_ns() const {
        auto end = running ? std::chrono::high_resolution_clock::now() : end_time;
        return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start_time).count();
    }
    
    // Get elapsed time in milliseconds
    double elapsed_ms() const {
        return elapsed_ns() / 1e6;
    }
    
    // Get elapsed time in seconds
    double elapsed_seconds() const {
        return elapsed_ns() / 1e9;
    }
    
    // Print timing information
    void print(const std::string& operation) const {
        std::cout << operation << ": " << elapsed_ms() << " ms" << std::endl;
    }
};