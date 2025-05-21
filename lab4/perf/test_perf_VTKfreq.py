#!/usr/bin/env python3
import subprocess
import re
import matplotlib.pyplot as plt
import numpy as np
import time
import os
import sys

# Configuration
EXECUTABLE = "./../build/perf/collision"  # Path to the collision executable
FREQUENCIES = [1, 2, 5, 10, 20, 50, 100, 200]  # Different frequencies to test
RUNS_PER_FREQ = 1  # Number of runs per frequency to get an average
CUTOFF = 2.5  # Default cutoff value
DT = 0.01  # Default time step

# Results storage
results = {freq: [] for freq in FREQUENCIES}
setup_times = {freq: [] for freq in FREQUENCIES}
simulation_times = {freq: [] for freq in FREQUENCIES}

def run_simulation(freq):
    """Run the collision simulation with a specific VTK frequency"""
    print(f"Running with VTK frequency: {freq}")
    
    cmd = [EXECUTABLE, f"--freq={freq}", f"--dt={DT}", f"--cutoff={CUTOFF}"]
    
    try:
        start_time = time.time()
        result = subprocess.run(cmd, capture_output=True, text=True, check=True)
        end_time = time.time()
        
        # Extract timing information from the output
        output = result.stdout
        
        # Parse setup time
        setup_match = re.search(r"Universe creation with \d+ particles took ([0-9.]+) seconds", output)
        setup_time = float(setup_match.group(1)) if setup_match else 0
        
        # Parse simulation time
        sim_match = re.search(r"Simulation.* took ([0-9.]+) seconds", output)
        sim_time = float(sim_match.group(1)) if sim_match else 0
        
        # Calculate total time
        total_time = end_time - start_time
        
        return {
            "total_time": total_time,
            "setup_time": setup_time,
            "simulation_time": sim_time,
            "output": output
        }
    
    except subprocess.CalledProcessError as e:
        print(f"Error running simulation: {e}")
        print(f"Command output: {e.output}")
        return None

# Check if executable exists
if not os.path.exists(EXECUTABLE):
    print(f"Error: Executable {EXECUTABLE} not found")
    sys.exit(1)

# Run simulations
print(f"Testing VTK generation frequency impact on performance")
print(f"Running each frequency {RUNS_PER_FREQ} times for accuracy")

for freq in FREQUENCIES:
    for run in range(RUNS_PER_FREQ):
        print(f"Frequency {freq}: Run {run+1}/{RUNS_PER_FREQ}")
        result = run_simulation(freq)
        
        if result:
            results[freq].append(result["total_time"])
            setup_times[freq].append(result["setup_time"])
            simulation_times[freq].append(result["simulation_time"])
            print(f"  Total: {result['total_time']:.2f}s, Setup: {result['setup_time']:.2f}s, Sim: {result['simulation_time']:.2f}s")
        else:
            print(f"  Run failed.")

# Calculate averages
avg_results = {freq: np.mean(times) for freq, times in results.items() if times}
avg_setup = {freq: np.mean(times) for freq, times in setup_times.items() if times}
avg_sim = {freq: np.mean(times) for freq, times in simulation_times.items() if times}

# Error bars (standard deviation)
err_results = {freq: np.std(times) for freq, times in results.items() if len(times) > 1}
err_sim = {freq: np.std(times) for freq, times in simulation_times.items() if len(times) > 1}

# Create plot
plt.figure(figsize=(12, 8))

# Plot simulation time
freqs = list(avg_sim.keys())
sim_times = list(avg_sim.values())
sim_errors = [err_sim.get(f, 0) for f in freqs]

plt.subplot(2, 1, 1)
plt.errorbar(freqs, sim_times, yerr=sim_errors, fmt='-o', label='Simulation Time', color='blue')
plt.xlabel('VTK Generation Frequency')
plt.ylabel('Time (seconds)')
plt.title('Impact of VTK Generation Frequency on Simulation Performance')
plt.grid(True)
plt.legend()

# Add log scale plot for frequency
plt.subplot(2, 1, 2)
plt.errorbar(freqs, sim_times, yerr=sim_errors, fmt='-o', label='Simulation Time', color='blue')
plt.xscale('log')
plt.xlabel('VTK Generation Frequency (log scale)')
plt.ylabel('Time (seconds)')
plt.title('Performance with Log Scale Frequency')
plt.grid(True)
plt.legend()

plt.tight_layout()
plt.savefig('vtk_frequency_performance.png', dpi=300)
plt.show()

# Print summary
print("\nPerformance Summary:")
print(f"{'Frequency':<10} {'Total Time':<15} {'Setup Time':<15} {'Simulation Time':<15}")
print("-" * 55)
for freq in sorted(avg_results.keys()):
    print(f"{freq:<10} {avg_results[freq]:<15.2f} {avg_setup[freq]:<15.2f} {avg_sim[freq]:<15.2f}")

print(f"\nResults saved to vtk_frequency_performance.png")

# Save CSV data
with open('vtk_frequency_performance.csv', 'w') as f:
    f.write('Frequency,TotalTime,SetupTime,SimulationTime\n')
    for freq in sorted(avg_results.keys()):
        f.write(f"{freq},{avg_results[freq]:.3f},{avg_setup[freq]:.3f},{avg_sim[freq]:.3f}\n")

print(f"Raw data saved to vtk_frequency_performance.csv")