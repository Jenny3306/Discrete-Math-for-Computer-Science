# Introduction to the Bellman-Ford Algorithm

The Bellman-Ford algorithm is a fundamental algorithm in graph theory used to compute the shortest paths from a single source vertex to all other vertices in a weighted graph. Unlike Dijkstra’s algorithm, Bellman-Ford can handle graphs with negative edge weights, making it more versatile in real-world scenarios.

The algorithm works by iteratively relaxing edges — updating the shortest path estimates — over V–1 iterations, where V is the number of vertices. This process guarantees that the shortest paths are found as long as there are no negative-weight cycles reachable from the source. If such a cycle exists, the algorithm can detect it.

This algorithm is designed to operate on a graph represented as a weighted matrix or an edge list. It maintains two main arrays: Label for storing shortest distance estimates and Prev for tracking the previous vertex in the shortest path. The function BF() updates these arrays, while BF_Path() reconstructs the shortest path between two specified nodes.

Overall, Bellman-Ford is a reliable and essential tool in the toolbox of any computer scientist dealing with graph-related problems.
