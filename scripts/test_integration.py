import sys
import os
import pandas as pd

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python test_integration.py <csv_file>")
        sys.exit(1)

    filename = sys.argv[1]

    if not os.path.exists(filename):
        print(f"ERROR: File {filename} not found.")
        sys.exit(1)

    try:
        df = pd.read_csv(filename)
        if df.empty:
            raise ValueError("CSV file is empty")
        print(f"SUCCESS: CSV parsed successfully with {len(df)} rows.")
    except Exception as e:
        print(f"ERROR: Failed to parse CSV: {e}")
        sys.exit(1)