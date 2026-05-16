/*
 * Author: Bashar Al-Saify
 *
 * Problem:
 * Reads several test cases, each describing a directed weighted graph. For
 * each test case, runs Dijkstra's algorithm from a given start node and
 * answers q shortest-path queries. Outputs "Impossible" if a queried node
 * is unreachable.
 *
 * Algorithm:
 * Dijkstra's single-source shortest path algorithm with a min-heap priority
 * queue. Correct for all non-negative edge weights. Runs once per test case
 * and answers all queries from the resulting distance array in O(1) each.
 *
 * Usage:
 *   Compile:  g++ main.cpp Dijkstra.cpp
 *   Run:      ./a.out < sample.in
 *
 * Time Complexity: O((n + m) log n) per test case.
 */

#include <iostream>
#include <vector>
#include "Dijkstra.h"

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

        // Build the graph using the Dijkstra helper class.
        Dijkstra dijk(n);

        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            dijk.addEdge(u, v, w);
        }

        // Compute all shortest distances from the source node s.
        vector<long long> dist = dijk.shortestPaths(s);

        // Answer each query: print the distance or "Impossible".
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
