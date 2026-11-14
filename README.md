# Adaptive Load-Balancing Routing (ALBR) for Road Networks

## Problem Statement

Consider a large road network represented by a connected, undirected, weighted graph $G = (V, E, w)$, where vertices represent intersections, edges represent bidirectional roads, and edge weights represent distances. Assume that all intersections and vehicles are of the same type.

At each discrete time step $t$, a set of transportation requests arrives. Each request $r_i = (n_i, s_i, d_i)$ specifies the number of vehicles, source intersection, and destination intersection.

The objective is to distribute the vehicles of each request among one or more valid paths from $s_i$ to $d_i$ such that traffic load is balanced across the road network while minimizing total travel distance.

## Objectives

1. Generate connected, weighted road networks of varying sizes and corresponding transportation requests across multiple time steps.
2. Design and implement an efficient algorithm that assigns vehicles to paths while considering both traffic load balancing and travel distance.
3. Report the assigned paths, vehicle distributions, and road-wise traffic loads for each time step.
4. Evaluate the algorithm using maximum road load, average road load, load variance, and total travel distance.
5. Compare the proposed algorithm against shortest-path routing and greedy load-balancing routing using the same generated instances.
6. Analyze the computational complexity, running time, scalability, and trade-off between traffic balancing and travel distance.

## Proposed Approach: ALBR

**Adaptive Load-Balancing Routing (ALBR)** dynamically distributes vehicles across candidate paths by considering both road distance and current traffic load.

The algorithm uses a dynamic edge cost:

$$
c_e = w(e) + \lambda(2L_e + 1)
$$

Where:

- $w(e)$ = original distance of road $e$.
- $L_e$ = current number of vehicles assigned to road $e$.
- $\lambda$ = load-balancing parameter.

The algorithm generates up to three candidate paths for each request using repeated Dijkstra-based searches. Vehicles are assigned individually, and road loads and candidate-path costs are updated after every assignment.

This allows multiple paths to be used for a single transportation request.

## Evaluation Metrics

The proposed algorithm is evaluated using the following metrics:

- **Maximum Road Load:** Maximum number of vehicles on any road.
- **Average Road Load:** Average number of vehicles across all roads.
- **Load Variance:** Measures how evenly vehicles are distributed across the road network.
- **Total Travel Distance:** Sum of the travel distances of all assigned vehicles.

## Comparison Algorithms

The proposed ALBR algorithm is compared against:

1. **Shortest Path Routing (SPR):** Assigns all vehicles of a request to its shortest-distance path.
2. **Greedy Load-Balancing Routing (GLBR):** Selects a candidate path based on its average current road load, using shorter distance as a tie-breaker.
3. **Adaptive Load-Balancing Routing (ALBR):** Dynamically selects paths using distance and updated traffic-load information.

All algorithms are evaluated using the same generated road networks and transportation requests.

## Problem Structure

```text
Road-Traffic-Routing-Algorithm/
│
├── road_traffic_routing.cpp
├── README.md
├── .gitignore
│
└── output/
    └── sample_output.txt
```

## Compilation and Execution

### Requirements

- C++ compiler (GCC or MinGW)
- Terminal or PowerShell

### 1. Clone the Repository

```bash
git clone https://github.com/afrayasmin/Road-Traffic-Routing-Algorithm.git
```

### 2. Navigate to the Problem Directory

```bash
cd Road-Traffic-Routing-Algorithm
```

### 3. Compile the Source Code

```bash
g++ road_traffic_routing.cpp -o routing.exe
```

### 4. Run the Program

```powershell
.\routing.exe
```

### 5. Save Program Output

```powershell
.\routing.exe > output\sample_output.txt
```

To view the saved output:

```powershell
Get-Content output\sample_output.txt
```

## Author

**Afra Yasmin**

Department of Computer Science and Engineering  
Khulna University of Engineering & Technology (KUET), Bangladesh

GitHub: https://github.com/afrayasmin