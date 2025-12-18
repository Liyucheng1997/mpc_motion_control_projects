import matplotlib.pyplot as plt
import csv
import os
import statistics

def read_execution_times(log_path):
    execution_times = []
    if not os.path.exists(log_path):
        print(f"Warning: Log file not found at {log_path}")
        return execution_times

    try:
        with open(log_path, 'r') as f:
            reader = csv.reader(f)
            header = next(reader, None) # Skip header
            if header and "Execution Time (ms)" not in header[0]:
                 print(f"Warning: Header in {log_path} might be different, proceeding anyway")
            
            for row in reader:
                if row:
                    try:
                        execution_times.append(float(row[0]))
                    except ValueError:
                        continue
    except Exception as e:
        print(f"Error reading CSV {log_path}: {e}")
    
    return execution_times

def plot_performance():
    log_dir = '/home/yucheng/mpc_motion_control_projects/mpc_ws/plot'
    mpc_log_path = os.path.join(log_dir, 'mpc_execution_times.csv')
    allocator_log_path = os.path.join(log_dir, 'allocator_execution_times.csv')
    output_path = os.path.join(log_dir, 'mpc_performance.png')

    mpc_times = read_execution_times(mpc_log_path)
    allocator_times = read_execution_times(allocator_log_path)

    if not mpc_times and not allocator_times:
        print("Error: No data found in any CSV")
        return

    plt.figure(figsize=(12, 8))

    # Plot MPC Times
    if mpc_times:
        plt.subplot(2, 1, 1)
        plt.plot(mpc_times, label='MPC Execution Time', color='b')
        mean_val = statistics.mean(mpc_times)
        max_val = max(mpc_times)
        plt.axhline(y=mean_val, color='r', linestyle='--', label=f'Mean: {mean_val:.2f} ms')
        plt.axhline(y=20.0, color='k', linestyle=':', label='20ms Limit (50Hz)')
        plt.title('MPC Controller Execution Time')
        plt.ylabel('Time (ms)')
        plt.legend()
        plt.grid(True)
        
        print(f"MPC Statistics:")
        print(f"  Mean: {mean_val:.2f} ms")
        print(f"  Max:  {max_val:.2f} ms")
        print(f"  Min:  {min(mpc_times):.2f} ms")
        print(f"  Std:  {statistics.stdev(mpc_times) if len(mpc_times) > 1 else 0.0:.2f} ms")

    # Plot Allocator Times
    if allocator_times:
        plt.subplot(2, 1, 2)
        plt.plot(allocator_times, label='Allocator Execution Time', color='g')
        mean_val = statistics.mean(allocator_times)
        max_val = max(allocator_times)
        plt.axhline(y=mean_val, color='r', linestyle='--', label=f'Mean: {mean_val:.2f} ms')
        plt.axhline(y=20.0, color='k', linestyle=':', label='20ms Limit (50Hz)')
        plt.title('Control Allocator Execution Time')
        plt.xlabel('Cycle')
        plt.ylabel('Time (ms)')
        plt.legend()
        plt.grid(True)

        print(f"Allocator Statistics:")
        print(f"  Mean: {mean_val:.2f} ms")
        print(f"  Max:  {max_val:.2f} ms")
        print(f"  Min:  {min(allocator_times):.2f} ms")
        print(f"  Std:  {statistics.stdev(allocator_times) if len(allocator_times) > 1 else 0.0:.2f} ms")

    plt.tight_layout()
    plt.savefig(output_path)
    print(f"Performance plot saved to {output_path}")

if __name__ == "__main__":
    plot_performance()
