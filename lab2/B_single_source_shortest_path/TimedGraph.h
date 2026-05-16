/*
 * Author: Bashar Al-Saify
 *
 * TimedGraph.h
 *
 * Declares the TimedGraph class, which computes single-source shortest travel
 * times in a directed graph where each edge is only available at specific
 * periodic time steps.
 *
 * Each edge (u -> v) is described by four values:
 *   t0: The first time the edge becomes available.
 *   P:  The period (repeat interval). If P == 0, the edge is only available
 *       at exactly time t0 and never again.
 *   d:  The traversal time (how long it takes to cross the edge).
 *
 * If you arrive at node u at time T, the earliest you can depart on a
 * given edge is the smallest value t0 + k*P >= T (for integer k >= 0).
 * The arrival time at v is then: departure_time + d.
 *
 * Usage:
 *   TimedGraph g(numNodes);
 *   g.addEdge(u, v, t0, P, d);
 *   vector<long long> dist = g.shortestTimes(startNode);
 *   // dist[v] == -1 means node v is unreachable from startNode
 *
 * Assumptions:
 *   - numNodes >= 1.
 *   - Node indices are in the range [0, numNodes - 1].
 *   - t0, P, d are all non-negative.
 *   - We start at startNode at time 0.
 */

#ifndef TIMED_GRAPH_H
#define TIMED_GRAPH_H

#include <vector>
#include <queue>

using namespace std;

/*
 * Represents a single directed timed edge.
 *
 * Fields:
 *   to: Destination node.
 *   t0: Time the edge first becomes available.
 *   P:  Period between availability windows (0 = only available at t0).
 *   d:  Time units needed to traverse the edge.
 */
struct TimedEdge {
    int to;
    int t0;
    int P;
    int d;
};

class TimedGraph {
public:
    /*
     * Params:
     *   numNodes: Total number of nodes in the graph (must be >= 1).
     */
    explicit TimedGraph(int numNodes);

    /*
     * Adds a directed timed edge from node u to node v.
     *
     * Params:
     *   u:  Source node (0-indexed).
     *   v:  Destination node (0-indexed).
     *   t0: First time the edge is available (>= 0).
     *   P:  Period of availability (0 means only available at t0).
     *   d:  Traversal duration (>= 0).
     */
    void addEdge(int u, int v, int t0, int P, int d);

    /*
     * Params:
     *   start: The source node (0-indexed, must be in [0, numNodes - 1]).
     *
     * Returns:
     *   A vector<long long> of length numNodes. Entry i holds the earliest
     *   time we can reach node i, or -1 if node i is unreachable.
     *
     * Time Complexity:  O((n + m) log n) where n = nodes, m = edges.
     * Memory Complexity: O(n + m) for the adjacency list, dist array, and heap.
     */
    vector<long long> shortestTimes(int start);

private:
    int numNodes;
    vector<vector<TimedEdge>> adjList;

    /*
     * Computes the earliest departure time on an edge given we arrive at its
     * source node at time 'arrivalTime'.
     *
     * Returns -1 if the edge can never be used (P == 0 and arrivalTime > t0).
     *
     * Params:
     *   arrivalTime: The time we reach the source node of this edge.
     *   t0:          First available time for this edge.
     *   P:           Period (0 = one-time only).
     */
    long long earliestDeparture(long long arrivalTime, int t0, int P);
};

#endif
