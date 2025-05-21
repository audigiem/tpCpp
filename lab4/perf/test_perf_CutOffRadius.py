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
CUTOFF_VALUES = [1.0, 2.0, 3.0, 4.0, 5.0, 10.0, 20.0, 50.0]  # Different cutoff values to test
RUNS_PER_CUTOFF = 1  # Number of runs per cutoff to get an average
VTK_FREQ = 200  # Set high VTK frequency to minimize its impact
DT = 0.01  # Default time step

# Results storage
results = {cutoff: [] for cutoff in CUTOFF_VALUES}
setup_times = {cutoff: [] for cutoff in CUTOFF_VALUES}
simulation_times = {cutoff: [] for cutoff in CUTOFF_VALUES}

def run_simulation(cutoff):
    """Run the collision simulation with a specific cutoff radius"""
    print(f"Running with cutoff radius: {cutoff}")
    
    cmd = [EXECUTABLE, f"--cutoff={cutoff}", f"--dt={DT}", f"--freq={VTK_FREQ}"]
    
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
print(f"Testing cutoff radius impact on performance")
print(f"Running each cutoff {RUNS_PER_CUTOFF} times for accuracy")

for cutoff in CUTOFF_VALUES:
    for run in range(RUNS_PER_CUTOFF):
        print(f"Cutoff {cutoff}: Run {run+1}/{RUNS_PER_CUTOFF}")
        result = run_simulation(cutoff)
        
        if result:
            results[cutoff].append(result["total_time"])
            setup_times[cutoff].append(result["setup_time"])
            simulation_times[cutoff].append(result["simulation_time"])
            print(f"  Total: {result['total_time']:.2f}s, Setup: {result['setup_time']:.2f}s, Sim: {result['simulation_time']:.2f}s")
        else:
            print(f"  Run failed.")

# Calculate averages
avg_results = {cutoff: np.mean(times) for cutoff, times in results.items() if times}
avg_setup = {cutoff: np.mean(times) for cutoff, times in setup_times.items() if times}
avg_sim = {cutoff: np.mean(times) for cutoff, times in simulation_times.items() if times}

# Error bars (standard deviation)
err_results = {cutoff: np.std(times) for cutoff, times in results.items() if len(times) > 1}
err_sim = {cutoff: np.std(times) for cutoff, times in simulation_times.items() if len(times) > 1}

# Create plot
plt.figure(figsize=(12, 8))

# Plot simulation time
cutoffs = list(avg_sim.keys())
sim_times = list(avg_sim.values())
sim_errors = [err_sim.get(c, 0) for c in cutoffs]

# Plot simulation time vs cutoff radius
plt.subplot(2, 1, 1)
plt.errorbar(cutoffs, sim_times, yerr=sim_errors, fmt='-o', label='Simulation Time', color='blue')
plt.xlabel('Cutoff Radius')
plt.ylabel('Time (seconds)')
plt.title('Impact of Cutoff Radius on Simulation Performance')
plt.grid(True)
plt.legend()

# Plot simulation time vs cutoff radius squared (complexity often scales with r²)
plt.subplot(2, 1, 2)
cutoffs_squared = [c*c for c in cutoffs]
plt.errorbar(cutoffs_squared, sim_times, yerr=sim_errors, fmt='-o', label='Simulation Time', color='green')
plt.xlabel('Cutoff Radius Squared (r²)')
plt.ylabel('Time (seconds)')
plt.title('Performance vs. Cutoff Radius Squared')
plt.grid(True)
plt.legend()

plt.tight_layout()
plt.savefig('cutoff_radius_performance.png', dpi=300)
plt.show()

# Print summary
print("\nPerformance Summary:")
print(f"{'Cutoff':<10} {'Total Time':<15} {'Setup Time':<15} {'Simulation Time':<15}")
print("-" * 55)
for cutoff in sorted(avg_results.keys()):
    print(f"{cutoff:<10.2f} {avg_results[cutoff]:<15.2f} {avg_setup[cutoff]:<15.2f} {avg_sim[cutoff]:<15.2f}")

print(f"\nResults saved to cutoff_radius_performance.png")

# Save CSV data
with open('cutoff_radius_performance.csv', 'w') as f:
    f.write('CutoffRadius,TotalTime,SetupTime,SimulationTime\n')
    for cutoff in sorted(avg_results.keys()):
        f.write(f"{cutoff},{avg_results[cutoff]:.3f},{avg_setup[cutoff]:.3f},{avg_sim[cutoff]:.3f}\n")

print(f"Raw data saved to cutoff_radius_performance.csv")