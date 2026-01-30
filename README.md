# Stochastic Dynamics of Cell Growth (C++ Engine)

![Language](https://img.shields.io/badge/C%2B%2B-17-blue)
![Build](https://img.shields.io/badge/build-passing-brightgreen)
![License](https://img.shields.io/badge/license-MIT-green)

**Simulation of cell population dynamics using Continuous-Time Markov Chains (CTMC).**

## Context & Academic Integrity

This project is based on a **Master 1 coursework on Monte Carlo Methods & Markov Chains** (Université Nice Côte d'Azur).

While the original academic project was prototyped in Python to validate some theorems, **this repository contains an exclusive C++ re-implementation**.
To comply with academic integrity policies and copyright regulations regarding university assignments, the original Python source code and Jupyter Notebooks are **not included**.

This repository serves as a portfolio piece demonstrating:
1.  **C++ Software Engineering:** Translating mathematical models into performant, compiled code.
2.  **HPC Concepts:** Memory management and stochastic simulation optimization.

## Overview

This engine simulates the **Yule Process** and validates the **Inspection Paradox** in cell biology (the bias where observed cells are systematically larger/older than newborn cells).

Unlike the naive Python prototype, this C++ version is designed to handle large-scale populations ($N > 10^5$ cells) efficiently by optimizing memory allocation and random number generation.

### Key Features
* **Core Logic:** Gillespie Algorithm (Minimum Lemma) implemented in **C++17**.
* **Performance:** Uses `std::vector` and `<random>` (Mersenne Twister) for high-throughput simulation.
* **Output:** Generates raw CSV data for external analysis.

## Project Structure

```text
.
├── src/                # C++ source files (Core simulation engine)
├── include/            # C++ header files
├── tests/              # Unit tests (GoogleTest or Assertions)
├── data/               # Output directory for simulation logs
├── CMakeLists.txt      # Build system configuration
└── README.md           # Documentation