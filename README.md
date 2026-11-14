# Adaptive Load-Balancing Routing (ALBR) for Road Networks

## Problem Statement

A road network is modeled as a weighted graph \(G=(V,E,w)\) where intersections are vertices and bidirectional roads are edges. At each time step \(t\), transport requests \(r_i=(n_i,s_i,d_i)\) arrive with a vehicle count, source, and destination. ALBR distributes vehicles across valid paths from \(s_i\) to \(d_i\) to balance traffic and minimize distance.

## Key Objectives

1. Generate weighted road networks and time-step requests of varying sizes.
2. Implement an algorithm balancing travel distance and network traffic.
3. Track assigned paths, vehicle counts, and road-wise loads per time step.
4. Evaluate performance using max road load, average load, load variance, and total distance.
5. Benchmark against shortest-path and greedy load-balancing routing.
6. Analyze complexity, scalability, runtime, and the trade-off between balancing and distance.

## Proposed Approach: ALBR

ALBR dynamically splits traffic across multiple candidate paths using a cost function that factors in distance and current congestion:

\[c_e = w(e) + \lambda(2L_e + 1)\]

Where \(w(e)\) is road distance, \(L_e\) is current vehicle count, and \(\lambda\) is the load-balancing parameter. It generates up to three candidate paths via repeated Dijkstra searches, updating edge loads and costs incrementally after each vehicle assignment.

## Evaluation Metrics & Comparisons

Performance is measured via **Maximum Road Load**, **Average Road Load**, **Load Variance**, and **Total Travel Distance**, benchmarked against:
1. **Shortest Path Routing (SPR):** Routes all vehicles through the shortest path.
2. **Greedy Load-Balancing Routing (GLBR):** Chooses paths by average current load (using distance as a tie-breaker).
3. **Adaptive Load-Balancing Routing (ALBR):** Dynamically updates path selection using real-time load data.

## Project Structure

```text
Adaptive-Load-Balancing-Routing/
│
├── road_traffic_routing.cpp
├── README.md
├── .gitignore
│
└── output/
    └── sample_output.txt
```

## Compilation and Execution

Requirements: A C++ compiler (GCC or MinGW) and terminal.

1. **Clone the Repository:**
   ```bash
   git clone https://github.com
   ```
2. **Navigate to Directory:**
   ```bash
   cd Adaptive-Load-Balancing-Routing
   ```
3. **Compile Code:**
   ```bash
   g++ road_traffic_routing.cpp -o routing.exe
   ```
4. **Run and Save Output:**
   ```powershell
   .\routing.exe > output\sample_output.txt
   Get-Content output\sample_output.txt
   ```

## Author

**Afra Yasmin**  
Department of Computer Science and Engineering  
Khulna University of Engineering & Technology (KUET), Bangladesh  
GitHub: https://github.com
