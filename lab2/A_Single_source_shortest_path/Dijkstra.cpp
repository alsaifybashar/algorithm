/*
 * Author: Bashar Al-Saify
 *
 * Dijkstra.cpp
 *
 * Implementation of Dijkstra's single-source shortest path algorithm.
 *
 * Algorithm overview:
 *   Dijkstra's algorithm works by greedily expanding the "frontier" of settled
 *   nodes. We maintain a min-heap (priority queue) of (distance, node) pairs.
 *   Initially only the start node is in the heap with distance 0. At each step:
 *     1. Extract the node u with the currently known smallest tentative distance.
 *     2. If u has already been finalized (visited), skip it — this handles
 *        outdated entries that remain in the heap after a distance improvement.
 *     3. Mark u as finalized, then for each edge (u -> v, weight):
 *        - Compute the candidate distance: dist[u] + weight.
 *        - If this is less than dist[v], update dist[v] and push (dist[v], v)
 *          into the heap.
 *   The algorithm terminates when the heap is empty.
 *
 *
 * Time Complexity:  O((n + m) log n)
 */


#include "Dijkstra.h"
#include <climits>

Dijkstra::Dijkstra(int numNodes) {
    this->numNodes = numNodes;
    adjList.resize(numNodes);
}

void Dijkstra::addEdge(int u, int v, int weight) {
    Edge e;
    e.to = v;
    e.weight = weight;
    adjList[u].push_back(e);
}

vector<long long> Dijkstra::shortestPaths(int start) {

    const long long INF = LLONG_MAX / 2;

    vector<long long> dist(numNodes, INF);
    vector<bool> finalized(numNodes, false);

    // Min-heap storing pairs of (distance, node).
    priority_queue<pair<long long, int>,
                   vector<pair<long long, int>>,
                   greater<pair<long long, int>>> minHeap;

    // Start node has distance 0 from itself.
    dist[start] = 0;
    minHeap.push({0, start});

    while (!minHeap.empty()) {
        // Extract the node with the smallest known distance.
        long long currentDist = minHeap.top().first;
        int u = minHeap.top().second;
        minHeap.pop();

        // If this node has already been finalized, this heap entry is outdated.
        if (finalized[u]) {
            continue;
        }
        finalized[u] = true;

        // Relax all outgoing edges from u.
        for (int i = 0; i < (int)adjList[u].size(); i++) {
            int v = adjList[u][i].to;
            int w = adjList[u][i].weight;

            long long newDist = currentDist + w;
            if (newDist < dist[v]) {
                dist[v] = newDist;
                minHeap.push({newDist, v});
            }
        }
    }

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
