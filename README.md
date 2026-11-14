## Problem Statement

Consider a large road network represented by a connected, undirected, weighted graph `G = (V, E, w)`, where vertices represent intersections, edges represent bidirectional roads, and edge weights represent distances. Assume that all intersections and vehicles are of the same type.

At each discrete time step `t`, a set of transportation requests arrives. Each request `r_i = (n_i, s_i, d_i)` specifies the number of vehicles, source intersection, and destination intersection.

The objective is to distribute the vehicles of each request among one or more valid paths from `s_i` to `d_i` such that traffic load is balanced across the road network while minimizing total travel distance.

## Proposed Approach: ALBR

**Adaptive Load-Balancing Routing (ALBR)** dynamically distributes vehicles across candidate paths by considering both road distance and current traffic load.

The algorithm uses the following dynamic edge cost:

$$
c_e = w(e) + \\lambda(2L_e + 1)
$$

Where:

- `w(e)` = Original distance of road `e`.
- `L_e` = Current number of vehicles assigned to road `e`.
- `λ` = Load-balancing parameter.

The algorithm generates up to three candidate paths for each request using repeated Dijkstra-based searches. Vehicles are assigned individually, and road loads and candidate-path costs are updated after every assignment.

This allows multiple paths to be used for a single transportation request.