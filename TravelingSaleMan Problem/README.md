# 🧭 Bellman-Held-Karp Algorithm for Travelling Salesman Problem (TSP)

## 📌 Introduction

The **Bellman-Held-Karp algorithm** is a dynamic programming technique used to solve the **Travelling Salesman Problem (TSP)** — the challenge of finding the shortest possible route that visits each city exactly once and returns to the starting point.

Unlike brute-force approaches that require evaluating all permutations (with factorial complexity), Bellman-Held-Karp reduces computation by solving subproblems and storing results.

---

## 🔧 How It Works

- Represents subsets of cities using **bitmasking**.
- Builds a DP table of size `2^n × n`, where `n` is the number of cities.
- `Y[S][v]` stores the minimum cost to reach city `v` after visiting all cities in subset `S`.
- `X[S][v]` keeps track of the city visited just before `v` in the optimal path.
- After visiting all cities, it adds the cost to return to the starting point.
- The final tour is reconstructed by backtracking through matrix `X`.

---

## ✅ Advantages

- Efficient for small to medium graphs (up to ~20 cities).
- Avoids redundant calculations using memoization.
- Finds the globally optimal tour.
- Works for both **symmetric** and **asymmetric** distance matrices.

---

## 🧪 Example

**Given Cities:** A, B, C  
**Distance Matrix:**

|     | A  | B  | C  |
|-----|----|----|----|
| A   | 0  | 10 | 15 |
| B   | 10 | 0  | 35 |
| C   | 15 | 35 | 0  |

**Optimal Tour:** `A → B → C → A`  
**Total Distance:** `10 + 35 + 15 = 60`


