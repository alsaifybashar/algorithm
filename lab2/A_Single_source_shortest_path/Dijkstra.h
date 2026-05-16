/*
 * Author: Bashar Al-Saify
 *
 * Dijkstra.h
 *
 * Declares the Dijkstra class, which computes single-source shortest paths
 * from a given start node to all other nodes in a directed, weighted graph
 * with non-negative edge weights.
 *
 * The graph is stored as an adjacency list. Each node holds a list of
 * (neighbor, weight) pairs representing its outgoing edges.
 *
 * Usage:
 *   Dijkstra dijk(numNodes);
 *   dijk.addEdge(u, v, w);
 *   vector<long long> dist = dijk.shortestPaths(startNode);
 *   // dist[v] == -1 means node v is unreachable from startNode
 *
 * Assumptions:
 *   - numNodes >= 1.
 *   - All edge weights are non-negative (required for Dijkstra correctness).
 *   - Node indices are in the range [0, numNodes - 1].
 *   - addEdge() must not be called with out-of-range node indices.
 */

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <queue>

using namespace std;

/*
 * Represents a single directed edge: destination node and edge weight.
 */
struct Edge {
    int to;
    int weight;
};

class Dijkstra {
public:
    /*
     * Params:
     *   numNodes: Total number of nodes (must be >= 1).
     */
    explicit Dijkstra(int numNodes);

    /*
     * Params:
     *   u:      Source node of the edge (0-indexed).
     *   v:      Destination node of the edge (0-indexed).
     *   weight: Non-negative edge weight.
     */
    void addEdge(int u, int v, int weight);

    /*
     * Params:
     *   start: The source node (0-indexed, must be in [0, numNodes - 1]).
     */
    vector<long long> shortestPaths(int start);

private:
    int numNodes;
    vector<vector<Edge>> adjList;
};

#endif
