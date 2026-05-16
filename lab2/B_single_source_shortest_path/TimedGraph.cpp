/*
 * Author: Bashar Al-Saify
 *
 * TimedGraph.cpp
 *
 * Implementation of shortest-time pathfinding on a graph with periodic
 * time-dependent edge availability.
 *
 * Algorithm overview:
 *   This is a modified Dijkstra's algorithm. Instead of tracking the shortest
 *   cumulative distance, we track the earliest arrival time at each node.
 *
 *   The core challenge compared to standard Dijkstra is computing the effective
 *   edge cost: when we arrive at node u at time T and want to use an edge with
 *   parameters (t0, P, d), we may need to wait until the next available
 *   departure window. The earliest departure time is:
 *
 *     - If P == 0: the edge is only available at t0. If T > t0, we can never
 *       use it. Otherwise we depart at t0.
 *     - If P > 0:  the edge is available at t0, t0+P, t0+2P, ...
 *       We need the smallest t0 + k*P >= T, which is:
 *         k = ceil((T - t0) / P)  (clamped to 0 if T <= t0)
 *         departure = t0 + k * P
 *
 *   Arrival at v = departure + d.
 *
 *   Correctness: Even though effective edge costs depend on the current time,
 *   greedy expansion by earliest arrival is still correct. Waiting at a node
 *   can only increase (or maintain) arrival times elsewhere — it can never
 *   create a "shortcut" that would invalidate an already-finalized node.
 *
 * Time Complexity:  O((n + m) log n)
 */

#include "TimedGraph.h"
#include <climits>

TimedGraph::TimedGraph(int numNodes) {
    this->numNodes = numNodes;
    adjList.resize(numNodes);
}

void TimedGraph::addEdge(int u, int v, int t0, int P, int d) {
    TimedEdge e;
    e.to = v;
    e.t0 = t0;
    e.P  = P;
    e.d  = d;
    adjList[u].push_back(e);
}

long long TimedGraph::earliestDeparture(long long arrivalTime, int t0, int P) {
    if (arrivalTime <= t0) {
        // We arrive before or exactly at the first window — depart at t0.
        return (long long)t0;
    }

    // We arrive after t0. The edge is only usable if it repeats (P > 0).
    if (P == 0) {
        return -1;
    }

    long long diff = arrivalTime - t0;
    long long k = (diff + P - 1) / P; // integer ceiling division
    return (long long)t0 + k * P;
}

vector<long long> TimedGraph::shortestTimes(int start) {
    const long long INF = LLONG_MAX / 2;

    // dist[i] = earliest time we can arrive at node i.
    vector<long long> dist(numNodes, INF);
    vector<bool> finalized(numNodes, false);

    // Min-heap: (earliest arrival time, node index).
    priority_queue<pair<long long, int>,
                   vector<pair<long long, int>>,
                   greater<pair<long long, int>>> minHeap;

    // We start at 'start' at time 0.
    dist[start] = 0;
    minHeap.push({0, start});

    while (!minHeap.empty()) {
        long long currentTime = minHeap.top().first;
        int u = minHeap.top().second;
        minHeap.pop();

        // Skip outdated heap entries (a shorter arrival time was found later).
        if (finalized[u]) {
            continue;
        }
        finalized[u] = true;

        // Try to use each outgoing edge from u.
        for (int i = 0; i < (int)adjList[u].size(); i++) {
            TimedEdge& edge = adjList[u][i];

            // Compute the earliest time we can board this edge.
            long long depart = earliestDeparture(currentTime, edge.t0, edge.P);

            // If depart == -1, this edge is impossible to use from here.
            if (depart == -1) {
                continue;
            }

            long long arriveAtV = depart + edge.d;

            if (arriveAtV < dist[edge.to]) {
                dist[edge.to] = arriveAtV;
                minHeap.push({arriveAtV, edge.to});
            }
        }
    }

    // Build the result, replacing INF with -1 to signal "unreachable".
    vector<long long> result(numNodes);
    for (int i = 0; i < numNodes; i++) {
        if (dist[i] == INF) {
            result[i] = -1;
        } else {
            result[i] = dist[i];
        }
    }

    return result;
}
