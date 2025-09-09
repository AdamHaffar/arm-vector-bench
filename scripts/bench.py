#!/usr/bin/env python3
"""
Comprehensive benchmarking script for ARM Vector Benchmark Lab
Runs size sweeps, generates CSV output, and creates visualizations
"""

import subprocess
import csv
import os
import sys
import matplotlib.pyplot as plt
import numpy as np
from pathlib import Path

class BenchmarkRunner:
    def __init__(self, build_dir="build"):
        self.build_dir = Path(build_dir)
        self.results_dir = Path("results")
        self.results_dir.mkdir(exist_ok=True)
        
    def run_benchmark(self, executable_name, output_file):
        """Run a benchmark executable and capture output"""
        executable_path = self.build_dir / executable_name
        
        if not executable_path.exists():
            print(f"Warning: {executable_path} not found, skipping...")
            return None
            
        try:
            result = subprocess.run(
                [str(executable_path)], 
                capture_output=True, 
                text=True
            )
            
            if result.returncode != 0:
                print(f"Error running {executable_name}: {result.stderr}")
                return None
                
            # Parse output and save to CSV
            self.parse_and_save_output(result.stdout, output_file)
            return result.stdout
            
        except Exception as e:
            print(f"Exception running {executable_name}: {e}")
            return None
    
    def parse_and_save_output(self, output, output_file):
        """Parse benchmark output and save to CSV"""
        lines = output.strip().split('\n')
        
        # Find the data table (skip headers)
        data_lines = []
        in_table = False
        
        for line in lines:
            if "Size" in line and "Time(ms)" in line:
                in_table = True
                continue
            elif "----" in line and "--------" in line:
                continue  # Skip separator line
            elif in_table and line.strip() and not line.startswith("==="):
                data_lines.append(line)
            elif line.startswith("==="):
                in_table = False
        
        # Parse and save data
        with open(self.results_dir / output_file, 'w', newline='') as csvfile:
            writer = csv.writer(csvfile)
            writer.writerow(['Size', 'Time_ms', 'GFLOPS', 'Bandwidth_GB_s'])
            
            for line in data_lines:
                if line.strip():
                    # Split by whitespace and filter out empty strings
                    parts = [p for p in line.split() if p]
                    if len(parts) >= 4:
                        try:
                            size = int(parts[0])
                            time_ms = float(parts[1])
                            gflops = float(parts[2])
                            bandwidth = float(parts[3])
                            writer.writerow([size, time_ms, gflops, bandwidth])
                        except ValueError:
                            continue
    
    def run_all_benchmarks(self):
        """Run all available benchmarks"""
        benchmarks = [
            ("bench_scalar", "scalar_results.csv"),
            ("bench_autovec", "autovec_results.csv"),
            ("bench_neon", "neon_results.csv"),
            ("bench_accelerate", "accelerate_results.csv")
        ]
        
        results = {}
        for executable, output_file in benchmarks:
            print(f"Running {executable}...")
            output = self.run_benchmark(executable, output_file)
            if output:
                results[executable] = output
                print(f"  Results saved to {output_file}")
            else:
                print(f"  Skipped {executable}")
        
        return results
    
    def create_plots(self):
        """Create performance comparison plots"""
        try:
            # Load data
            data = {}
            for csv_file in self.results_dir.glob("*_results.csv"):
                impl_name = csv_file.stem.replace("_results", "")
                data[impl_name] = np.genfromtxt(csv_file, delimiter=',', skip_header=1)
            
            if not data:
                print("No data files found for plotting")
                return
            
            # Create performance comparison plot
            plt.figure(figsize=(12, 8))
            
            # Plot 1: Time vs Size
            plt.subplot(2, 2, 1)
            for impl_name, impl_data in data.items():
                if impl_data.size > 0:
                    sizes = impl_data[:, 0]
                    times = impl_data[:, 1]
                    plt.loglog(sizes, times, 'o-', label=impl_name, linewidth=2)
            
            plt.xlabel('Vector Size')
            plt.ylabel('Time (ms)')
            plt.title('Execution Time vs Vector Size')
            plt.legend()
            plt.grid(True, alpha=0.3)
            
            # Plot 2: GFLOPS vs Size
            plt.subplot(2, 2, 2)
            for impl_name, impl_data in data.items():
                if impl_data.size > 0:
                    sizes = impl_data[:, 0]
                    gflops = impl_data[:, 2]
                    plt.semilogx(sizes, gflops, 'o-', label=impl_name, linewidth=2)
            
            plt.xlabel('Vector Size')
            plt.ylabel('GFLOPS')
            plt.title('Performance vs Vector Size')
            plt.legend()
            plt.grid(True, alpha=0.3)
            
            # Plot 3: Bandwidth vs Size
            plt.subplot(2, 2, 3)
            for impl_name, impl_data in data.items():
                if impl_data.size > 0:
                    sizes = impl_data[:, 0]
                    bandwidth = impl_data[:, 3]
                    plt.semilogx(sizes, bandwidth, 'o-', label=impl_name, linewidth=2)
            
            plt.xlabel('Vector Size')
            plt.ylabel('Bandwidth (GB/s)')
            plt.title('Memory Bandwidth vs Vector Size')
            plt.legend()
            plt.grid(True, alpha=0.3)
            
            # Plot 4: Speedup comparison
            plt.subplot(2, 2, 4)
            if 'scalar' in data and len(data) > 1:
                scalar_data = data['scalar']
                for impl_name, impl_data in data.items():
                    if impl_name != 'scalar' and impl_data.size > 0:
                        sizes = impl_data[:, 0]
                        scalar_times = np.interp(sizes, scalar_data[:, 0], scalar_data[:, 1])
                        impl_times = impl_data[:, 1]
                        speedup = scalar_times / impl_times
                        plt.semilogx(sizes, speedup, 'o-', label=f'{impl_name} vs scalar', linewidth=2)
                
                plt.xlabel('Vector Size')
                plt.ylabel('Speedup')
                plt.title('Speedup vs Scalar Implementation')
                plt.legend()
                plt.grid(True, alpha=0.3)
            else:
                # Only scalar data available - show time per element instead
                if 'scalar' in data and data['scalar'].size > 0:
                    scalar_data = data['scalar']
                    sizes = scalar_data[:, 0]
                    times = scalar_data[:, 1]
                    time_per_element = (times * 1000) / sizes  # Convert to nanoseconds per element
                    plt.semilogx(sizes, time_per_element, 'o-', color='red', linewidth=2, label='Time per Element')
                    plt.xlabel('Vector Size')
                    plt.ylabel('Time per Element (ns)')
                    plt.title('Time per Element vs Vector Size')
                    plt.legend()
                    plt.grid(True, alpha=0.3)
                else:
                    plt.text(0.5, 0.5, 'No data available\nfor speedup comparison', 
                            ha='center', va='center', transform=plt.gca().transAxes)
                    plt.title('Speedup vs Scalar Implementation')
            
            plt.tight_layout()
            plt.savefig(self.results_dir / 'performance_comparison.png', dpi=300, bbox_inches='tight')
            plt.show()
            
            print(f"Plots saved to {self.results_dir / 'performance_comparison.png'}")
            
        except Exception as e:
            print(f"Error creating plots: {e}")

def main():
    print("=== ARM Vector Benchmark Lab - Comprehensive Benchmarking ===")
    
    # Check if build directory exists
    if not Path("build").exists():
        print("Build directory not found. Please run 'mkdir build && cd build && cmake .. && make' first.")
        return 1
    
    runner = BenchmarkRunner()
    
    # Run all benchmarks
    results = runner.run_all_benchmarks()
    
    if not results:
        print("No benchmarks were successfully run.")
        return 1
    
    # Create visualizations
    runner.create_plots()
    
    print("\n=== Benchmarking Complete ===")
    print(f"Results saved in: {runner.results_dir}")
    
    return 0

if __name__ == "__main__":
    sys.exit(main())