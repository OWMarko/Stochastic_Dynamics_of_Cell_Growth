FROM python:3.9-slim-bullseye

LABEL maintainer="OWMarko"
LABEL description="Stochastic Cell Growth Engine (C++ & Python)"

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libomp-dev \
    && rm -rf /var/lib/apt/lists/*


RUN pip install --no-cache-dir pandas matplotlib numpy

WORKDIR /app

COPY . .

RUN mkdir -p build && cd build && \
    cmake .. && \
    make

CMD ["/bin/bash", "-c", "./build/cell_sim && python scripts/plot_mass.py && python scripts/plot_yule.py && python scripts/plot_inference.py"]