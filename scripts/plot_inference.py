import pandas as pd
import matplotlib.pyplot as plt
import os

CSV_FILE = "../data/inference_results.csv"
TRUE_LAMBDA = 2.0

def main():
    if not os.path.exists(CSV_FILE):
        print(f"ERROR: The file '{CSV_FILE}' was not found.")
        print("       Please run the C++ simulation first (./cell_sim).")
        return

    print(f"Loading data from {CSV_FILE}...")
    df = pd.read_csv(CSV_FILE)

    plt.figure(figsize=(10, 6))

    plt.plot(df['n'], df['estimated_lambda'], 
             color='blue', linewidth=1.5, label=r"Estimation $\hat{\lambda}_n$ (C++)")

    plt.axhline(TRUE_LAMBDA, color='red', linestyle='--', linewidth=2, label=r"True Value $\lambda$")

    plt.xlabel("Number of observed divisions ($n$)", fontsize=12)
    plt.ylabel(r"Estimated Value $\hat{\lambda}_n$", fontsize=12)
    plt.title(r"Convergence of the Estimator ($\hat{\lambda}_n = n/T_n$)", fontsize=14)
    plt.legend(fontsize=12)
    plt.grid(True, alpha=0.3)
    
    plt.ylim(TRUE_LAMBDA - 1.0, TRUE_LAMBDA + 1.0)

    print("Displaying plot...")
    plt.show()

if __name__ == "__main__":
    main()