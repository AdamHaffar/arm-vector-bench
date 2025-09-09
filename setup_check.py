#!/usr/bin/env python3
"""
Setup verification script for ARM Vector Benchmark Lab
Checks for required tools and displays system information
"""

import subprocess
import sys
import platform

def run_command(cmd):
    """Run command and return output, None if failed"""
    try:
        result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
        return result.stdout.strip() if result.returncode == 0 else None
    except:
        return None

def check_system():
    """Check system requirements"""
    print("=== ARM Vector Benchmark Lab - Setup Check ===\n")
    
    # System info
    print(f"Platform: {platform.system()} {platform.release()}")
    print(f"Architecture: {platform.machine()}")
    print(f"Python: {sys.version.split()[0]}")
    
    # CPU info
    cpu_info = run_command("sysctl -n machdep.cpu.brand_string")
    if cpu_info:
        print(f"CPU: {cpu_info}")
    
    # Check for clang++
    clang_version = run_command("clang++ --version")
    if clang_version:
        print(f"\n✓ clang++ found:")
        print(f"  {clang_version.split(chr(10))[0]}")
    else:
        print("\n✗ clang++ not found - please install Xcode command line tools")
        return False
    
    # Check for cmake
    cmake_version = run_command("cmake --version")
    if cmake_version:
        print(f"\n✓ cmake found:")
        print(f"  {cmake_version.split(chr(10))[0]}")
    else:
        print("\n✗ cmake not found - please install via brew: brew install cmake")
        return False
    
    # Check for Python packages
    try:
        import numpy
        print(f"\n✓ numpy {numpy.__version__}")
    except ImportError:
        print("\n✗ numpy not found - install with: pip install numpy")
        return False
    
    try:
        import matplotlib
        print(f"✓ matplotlib {matplotlib.__version__}")
    except ImportError:
        print("✗ matplotlib not found - install with: pip install matplotlib")
        return False
    
    print("\n=== Setup Complete ===")
    return True

if __name__ == "__main__":
    success = check_system()
    sys.exit(0 if success else 1)