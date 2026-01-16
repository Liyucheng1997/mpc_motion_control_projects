
import pandas as pd
import numpy as np
import os

CSV_PATH = 'plot/ride_comfort_data.csv'

if not os.path.exists(CSV_PATH):
    print(f"File not found: {CSV_PATH}")
    exit(1)

try:
    df = pd.read_csv(CSV_PATH)
    if 'az' not in df.columns:
        print("Error: 'az' column not found in csv")
        exit(1)

    rms = np.sqrt(np.mean(np.square(df['az'])))
    peak = df['az'].abs().max()
    
    print("-" * 30)
    print(f"File: {CSV_PATH}")
    print(f"Az RMS : {rms:.4f} m/s^2")
    print(f"Az Peak: {peak:.4f} m/s^2")
    print("-" * 30)

except Exception as e:
    print(f"Error: {e}")
