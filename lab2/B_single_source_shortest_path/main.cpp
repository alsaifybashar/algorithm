/*
 * Author: Bashar Al-Saify
 *
 * Problem:
 * Reads several test cases, each describing a directed graph with time-dependent
 * edges. Each edge is only traversable at periodic time windows. For each test
 * case, finds the earliest arrival time from a given start node (at time 0) to
 * each queried node, or outputs "Impossible" if unreachable.
 *
 * Algorithm:
 * Modified Dijkstra's algorithm where the effective cost of an edge depends on
 * the current arrival time at its source node. When we reach a node at time T,
 * we may need to wait for the next available departure window before using an
 * outgoing edge. We greedily expand by earliest arrival time, which remains
 * correct even with time-dependent costs because waiting never shortcuts paths.
 *
 * Usage:
 *   Compile:  g++ main.cpp TimedGraph.cpp
 *   Run:      ./a.out < sample.in
 *
 * Time Complexity: O((n + m) log n) per test case.
 */

#include <iostream>
#include <vector>
#include "TimedGraph.h"

using namespace std;

int main() {
    int n, m, q, s;

    bool firstCase = true;

    // Read test cases until the terminating "0 0 0 0" line.
    while (cin >> n >> m >> q >> s) {
        if (n == 0 && m == 0 && q == 0 && s == 0) {
            break;
        }

        // Print a blank line between consecutive test cases (not before the first).
        if (!firstCase) {
            cout << "\n";
        }
        firstCase = false;

        TimedGraph graph(n);

        for (int i = 0; i < m; i++) {
            int u, v, t0, P, d;
            cin >> u >> v >> t0 >> P >> d;
            graph.addEdge(u, v, t0, P, d);
        }

        // Run modified Dijkstra from the start node (we depart at time 0).
        vector<long long> dist = graph.shortestTimes(s);

        // Answer each query.
        for (int i = 0; i < q; i++) {
            int queryNode;
            cin >> queryNode;

            if (dist[queryNode] == -1) {
                cout << "Impossible\n";
            } else {
                cout << dist[queryNode] << "\n";
            }
        }
    }

    return 0;
}
