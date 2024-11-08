import os
import re
import matplotlib.pyplot as plt
from collections import defaultdict

# Directory containing result log files
results_dir = "results"

# Initialize a dictionary to store cumulative solving times for each restartint value
cumulative_solving_times_by_restartint = defaultdict(list)

# Regular expression to find the process time and restart value from each log file
time_regex = re.compile(r"total process time since initialization:\s+([\d.]+)\s+seconds")
restart_regex = re.compile(r"_restart(\d+).log")

# Loop through each log file in the results directory
for log_file in os.listdir(results_dir):
    if log_file.endswith(".log"):
        log_path = os.path.join(results_dir, log_file)
        
        # Extract the restartint value from the filename
        restart_match = restart_regex.search(log_file)
        if restart_match:
            restartint = int(restart_match.group(1))
        
            with open(log_path, "r") as file:
                content = file.read()
                match = time_regex.search(content)
                if match:
                    # Extract the process time
                    solving_time = float(match.group(1))
                    
                    # Calculate cumulative solving time
                    if cumulative_solving_times_by_restartint[restartint]:
                        last_time = cumulative_solving_times_by_restartint[restartint][-1]
                        cumulative_solving_time = last_time + solving_time
                    else:
                        cumulative_solving_time = solving_time
                    
                    # Append cumulative solving time to the list for this restartint value
                    cumulative_solving_times_by_restartint[restartint].append(cumulative_solving_time)

# Sort cumulative solving times for each restartint value to plot the cactus plot
for restartint in cumulative_solving_times_by_restartint:
    cumulative_solving_times_by_restartint[restartint].sort()

# Plotting the cactus plot
plt.figure(figsize=(10, 6))
for restartint, cumulative_solving_times in sorted(cumulative_solving_times_by_restartint.items()):
    plt.plot(range(1, len(cumulative_solving_times) + 1), cumulative_solving_times, marker='o', linestyle='-', label=f"restartint={restartint}")

# Customize the plot
plt.xlabel("Instance Index")
plt.ylabel("Cumulative Solving Time (seconds)")
plt.title("Cactus Plot of Cumulative Solving Times for CNF Instances with Different Restart Intervals")
plt.legend(title="Restart Interval")
plt.grid(True)
plt.show()
