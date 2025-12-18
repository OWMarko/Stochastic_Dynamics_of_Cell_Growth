FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

COPY scripts/requirements.txt /app/scripts/requirements.txt
RUN pip3 install -r /app/scripts/requirements.txt

WORKDIR /app
COPY . .


RUN mkdir build && cd build && \
    cmake .. && \
    make

CMD ["/bin/bash", "-c", "./build/growth_sim && python3 scripts/visualize_results.py"]
