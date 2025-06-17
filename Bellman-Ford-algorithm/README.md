# Bellman-Ford Algorithm

## 📌 Introduction

The **Bellman-Ford algorithm** is a classical algorithm in graph theory used to compute the shortest paths from a single source vertex to all other vertices in a weighted graph. Unlike Dijkstra’s algorithm, Bellman-Ford supports **negative edge weights**, making it more suitable for a wider range of real-world scenarios.

### ✅ Key Features
- Handles graphs with **negative weights**
- Detects **negative-weight cycles**
- Works with graphs represented as **edge lists** or **adjacency matrices**

### 🔧 How It Works
The algorithm repeatedly relaxes all edges in the graph over *V–1* iterations (where *V* is the number of vertices). This ensures the shortest path is found if no negative-weight cycle exists.

### 🧠 Core Concepts
- `Label[]`: stores shortest distance from the source to each vertex.
- `Prev[]`: stores the previous vertex in the shortest path.

### 📂 Main Functions
- `BF()`: updates the `Label` and `Prev` arrays through edge relaxation.
- `BF_Path()`: reconstructs the shortest path from the source to the destination.

---

This implementation is ideal for educational use and can be applied to small-to-medium graph problems involving weighted edges.

