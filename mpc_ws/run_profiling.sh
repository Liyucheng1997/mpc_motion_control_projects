#!/bin/bash

# 1. Source workspace
source install/setup.bash

# Clean up old logs
rm -f plot/mpc_execution_times.csv
rm -f plot/allocator_execution_times.csv

# 2. Launch MPC System (Scenario 4: Bump + Cornering)
echo "Starting MPC System (Scenario 4)..."
ros2 launch mpc_car_control mpc_system.launch.py active_suspension_enabled:=true scenario_id:=4 &
LAUNCH_PID=$!

# 3. Run for 15 seconds
echo "Running for 15 seconds..."
sleep 15

# 4. Graceful Shutdown
echo "Stopping nodes to save data..."
# Send SIGINT to specific nodes to trigger destructors
pkill -SIGINT -f mpc_controller_node
pkill -SIGINT -f control_allocator_node

# Wait for CSV saving
echo "Waiting for CSV saving..."
sleep 3

# Kill the launch process and any remaining nodes
echo "Cleaning up..."
kill -SIGINT $LAUNCH_PID
sleep 2
# Force kill if still running
pkill -9 -f mpc_controller_node
pkill -9 -f control_allocator_node
pkill -9 -f mpc_system.launch.py

# 5. Generate Plot
echo "Generating Performance Plot..."
if [ -f plot/mpc_execution_times.csv ]; then
    python3 src/mpc_car_control/scripts/plot_mpc_performance.py
    echo "Done! Check plot/mpc_performance.png"
else
    echo "Error: CSV files not found. Check if nodes saved data correctly."
fi