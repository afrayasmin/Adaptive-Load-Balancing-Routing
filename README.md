# Adaptive Load-Balancing Routing (ALBR) for Road Networks

## Problem Statement

Consider a large road network represented by a connected, undirected, weighted graph \(G=(V,E,w)\), where vertices represent intersections, edges represent bidirectional roads, and edge weights represent distances.

At each discrete time step, a set of transportation requests arrives. Each request specifies the number of vehicles, a source intersection, and a destination intersection.

The objective is to design an adaptive load-balancing routing algorithm that distributes vehicles among multiple valid paths while minimizing travel distance and reducing traffic congestion.

The algorithm considers road distances, current traffic loads, and road capacities when selecting and distributing vehicles across available routes. It aims to prevent excessive traffic concentration and ensure that road capacities are not exceeded.

## How to Run

### Requirements

- C++ compiler (G++ recommended).
- Windows, Linux, or macOS.

### Compilation

```bash
g++ road_traffic_routing.cpp -o routing
```

### Execution

**Windows (PowerShell):**

```powershell
.\routing.exe
```

**Linux / macOS:**

```bash
./routing
```

### Output

The program displays routing results and performance evaluation in the terminal.

Sample execution output is available in the [`output/`](output/) directory.