
#include <bits/stdc++.h>
using namespace std;

int U[500], V[500], W[500];
int edgeCount;

vector<vector<pair<int, int>>> adj;
vector<vector<int>> paths;
vector<int> tempPath;
vector<bool> visited;

int N, maxPaths = 30;

// Calculate distance of a path
long long getDistance(vector<int> path)
{
    long long sum = 0;

    for (int id : path)
    {
        sum += W[id];
    }

    return sum;
}

// Convert path into readable form
string showPath(int src, vector<int> path)
{
    string result = to_string(src);
    int current = src;

    for (int id : path)
    {
        if (U[id] == current)
        {
            current = V[id];
        }
        else
        {
            current = U[id];
        }

        result += " -> " + to_string(current);
    }

    return result;
}

// Generate connected undirected weighted graph
void generateGraph(int n, int m, mt19937 &rng)
{
    N = n;
    edgeCount = 0;

    adj.assign(n, {});

    vector<pair<int, int>> used;

    uniform_int_distribution<int> weight(1, 10);

    // Create a spanning tree
    for (int i = 1; i < n; i++)
    {
        int parent = uniform_int_distribution<int>(0, i - 1)(rng);
        int w = weight(rng);

        U[edgeCount] = parent;
        V[edgeCount] = i;
        W[edgeCount] = w;

        adj[parent].push_back({i, edgeCount});
        adj[i].push_back({parent, edgeCount});

        used.push_back({parent, i});

        edgeCount++;
    }

    // Add extra edges
    while (edgeCount < m)
    {
        int u = uniform_int_distribution<int>(0, n - 1)(rng);
        int v = uniform_int_distribution<int>(0, n - 1)(rng);

        if (u == v)
        {
            continue;
        }

        int a = min(u, v);
        int b = max(u, v);

        if (find(used.begin(), used.end(), make_pair(a, b)) != used.end())
        {
            continue;
        }

        used.push_back({a, b});

        int w = weight(rng);

        U[edgeCount] = u;
        V[edgeCount] = v;
        W[edgeCount] = w;

        adj[u].push_back({v, edgeCount});
        adj[v].push_back({u, edgeCount});

        edgeCount++;
    }
}

// Dijkstra shortest path
vector<int> dijkstra(int src, int dest)
{
    vector<long long> d(N, LLONG_MAX);
    vector<int> par(N, -1);
    vector<int> parEdge(N, -1);

    priority_queue<
        pair<long long, int>,
        vector<pair<long long, int>>,
        greater<pair<long long, int>>>
        pq;

    d[src] = 0;
    pq.push({0, src});

    while (!pq.empty())
    {
        auto [cost, u] = pq.top();
        pq.pop();

        if (cost != d[u])
        {
            continue;
        }

        for (auto [v, id] : adj[u])
        {
            int w = W[id];

            if (d[u] + w < d[v])
            {
                d[v] = d[u] + w;

                par[v] = u;
                parEdge[v] = id;

                pq.push({d[v], v});
            }
        }
    }

    vector<int> path;

    if (d[dest] == LLONG_MAX)
    {
        return path;
    }

    int current = dest;

    while (current != src)
    {
        path.push_back(parEdge[current]);
        current = par[current];
    }

    reverse(path.begin(), path.end());

    return path;
}

// DFS to generate alternative simple paths
void dfs(int u, int dest)
{
    if ((int)paths.size() >= maxPaths)
    {
        return;
    }

    if (u == dest)
    {
        paths.push_back(tempPath);
        return;
    }

    for (auto [v, id] : adj[u])
    {
        if (!visited[v])
        {
            visited[v] = true;
            tempPath.push_back(id);

            dfs(v, dest);

            tempPath.pop_back();
            visited[v] = false;
        }

        if ((int)paths.size() >= maxPaths)
        {
            return;
        }
    }
}

// Generate candidate paths
vector<vector<int>> getPaths(int src, int dest)
{
    paths.clear();
    tempPath.clear();

    visited.assign(N, false);
    visited[src] = true;

    dfs(src, dest);

    // Ensure shortest path is available
    vector<int> shortest = dijkstra(src, dest);

    if (find(paths.begin(), paths.end(), shortest) == paths.end())
    {
        paths.push_back(shortest);
    }

    return paths;
}

// Display performance metrics
void evaluate(string name, vector<long long> load, long long totalDistance)
{
    long long mx = 0;
    double sum = 0;

    for (int i = 0; i < edgeCount; i++)
    {
        mx = max(mx, load[i]);
        sum += load[i];
    }

    double avg = sum / edgeCount;
    double variance = 0;

    for (int i = 0; i < edgeCount; i++)
    {
        variance += (load[i] - avg) * (load[i] - avg);
    }

    variance /= edgeCount;

    cout << "\n\n"
         << name << "\n";

    cout << "Maximum Road Load: " << mx << "\n";
    cout << "Average Road Load: " << avg << "\n";
    cout << "Load Variance: " << variance << "\n";
    cout << "Total Travel Distance: " << totalDistance << "\n";

    cout << "Road-wise Loads:\n";

    for (int i = 0; i < edgeCount; i++)
    {
        cout << U[i] << " - " << V[i] << " : " << load[i] << "\n";
    }
}

// Display assigned paths
void displayAssignments(map<string, int> assigned)
{
    for (auto p : assigned)
    {
        cout << p.first << " : " << p.second << " vehicles\n";
    }
}

// Algorithm 1: Shortest path routing
void shortestRouting(vector<tuple<int, int, int>> requests)
{
    vector<long long> load(edgeCount, 0);
    long long totalDistance = 0;

    map<string, int> assigned;

    for (auto [vehicles, src, dest] : requests)
    {
        vector<int> path = dijkstra(src, dest);

        for (int id : path)
        {
            load[id] += vehicles;
        }

        long long distance = getDistance(path);

        totalDistance += vehicles * distance;

        assigned[showPath(src, path)] += vehicles;
    }

    cout << "\n\nAssigned Paths:\n";
    displayAssignments(assigned);

    evaluate("SHORTEST PATH ROUTING", load, totalDistance);
}

// Algorithm 2: Greedy load balancing
void greedyRouting(vector<tuple<int, int, int>> requests)
{
    vector<long long> load(edgeCount, 0);
    long long totalDistance = 0;

    map<string, int> assigned;

    for (auto [vehicles, src, dest] : requests)
    {
        vector<vector<int>> candidate = getPaths(src, dest);

        int best = 0;
        long long bestLoad = LLONG_MAX;
        long long bestDist = LLONG_MAX;

        for (int i = 0; i < (int)candidate.size(); i++)
        {
            long long mx = 0;

            for (int id : candidate[i])
            {
                mx = max(mx, load[id]);
            }

            long long dist = getDistance(candidate[i]);

            if (mx < bestLoad || (mx == bestLoad && dist < bestDist))
            {
                bestLoad = mx;
                bestDist = dist;
                best = i;
            }
        }

        vector<int> path = candidate[best];

        for (int id : path)
        {
            load[id] += vehicles;
        }

        totalDistance += vehicles * getDistance(path);

        assigned[showPath(src, path)] += vehicles;
    }

    cout << "\n\nAssigned Paths:\n";
    displayAssignments(assigned);

    evaluate("GREEDY LOAD BALANCING", load, totalDistance);
}

// Algorithm 3: Proposed combined algorithm
void proposedRouting(vector<tuple<int, int, int>> requests, double lambda)
{
    vector<long long> load(edgeCount, 0);
    long long totalDistance = 0;

    map<string, int> assigned;

    for (auto [vehicles, src, dest] : requests)
    {
        vector<vector<int>> candidate = getPaths(src, dest);

        // Assign vehicles one at a time
        for (int k = 0; k < vehicles; k++)
        {
            int best = 0;
            double bestScore = 1e18;

            for (int i = 0; i < (int)candidate.size(); i++)
            {
                long long dist = getDistance(candidate[i]);

                double loadCost = 0;

                for (int id : candidate[i])
                {
                    loadCost += 2.0 * load[id] + 1;
                }

                double score = dist + lambda * loadCost;

                if (score < bestScore)
                {
                    bestScore = score;
                    best = i;
                }
            }

            vector<int> path = candidate[best];

            for (int id : path)
            {
                load[id]++;
            }

            totalDistance += getDistance(path);

            assigned[showPath(src, path)]++;
        }
    }

    cout << "\nAssigned Paths:\n";
    displayAssignments(assigned);

    evaluate("PROPOSED COMBINED ALGORITHM", load, totalDistance);
}

int main()
{
    mt19937 rng(42);

    // Three different graph sizes
    int sizes[] = {8, 40, 100};

    for (int test = 0; test < 3; test++)
    {
        int n = sizes[test];
        int m = n + 4;

        cout << "\n\n================================\n";
        cout << "TEST CASE " << test + 1 << "\n";
        cout << "Vertices: " << n << "\n";
        cout << "================================\n";

        generateGraph(n, m, rng);

        cout << "\n\nGenerated Roads:\n";

        for (int i = 0; i < edgeCount; i++)
        {
            cout << U[i] << " - " << V[i]
                 << " Weight: " << W[i] << "\n";
        }

        // Generate requests for 3 time steps
        vector<tuple<int, int, int>> requests;

        cout << "\n\nTransportation Requests:\n";

        for (int t = 1; t <= 3; t++)
        {
            cout << "\nTime Step " << t << ":\n";

            for (int j = 0; j < 5; j++)
            {
                int src = uniform_int_distribution<int>(0, n - 1)(rng);
                int dest = uniform_int_distribution<int>(0, n - 1)(rng);

                while (src == dest)
                {
                    dest = uniform_int_distribution<int>(0, n - 1)(rng);
                }

                int vehicles = uniform_int_distribution<int>(5, 15)(rng);

                requests.push_back({vehicles, src, dest});

                cout << vehicles << " vehicles: "
                     << src << " -> " << dest << "\n";
            }
        }

        // Display algorithm results once
        shortestRouting(requests);
        greedyRouting(requests);
        proposedRouting(requests, 0.5);

        // Benchmark algorithms
        auto T = [&](function<void()> f)
        {
            int R = 300;

            cout.setstate(ios::failbit);

            auto a = chrono::steady_clock::now();

            for (int i = 0; i < R; i++)
            {
                f();
            }

            auto b = chrono::steady_clock::now();

            cout.clear();

            return chrono::duration<double, milli>(b - a).count() / R;
        };

        // Calculate execution time
        double t1 = T([&]()
                      { shortestRouting(requests); });

        double t2 = T([&]()
                      { greedyRouting(requests); });

        double t3 = T([&]()
                      { proposedRouting(requests, 0.5); });

        // Display execution time
        cout << "\n\nExecution Time Results:\n";

        cout << "Number of Vertices: " << n << "\n";
        cout << "Number of Edges: " << edgeCount << "\n";

        cout << fixed << setprecision(6);

        cout << "Shortest Path Routing: " << t1 << " ms\n";
        cout << "Greedy Load Balancing: " << t2 << " ms\n";
        cout << "Proposed Combined Algorithm: " << t3 << " ms\n";
    }

    return 0;
}
