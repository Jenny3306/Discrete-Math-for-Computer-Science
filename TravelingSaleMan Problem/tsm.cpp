#include "tsm.h"

string Traveling(int edgeList[][3], int numEdge, char start) {
    if (numEdge > 20) return "1"; 

    int graph[128][128];
    char indexToVertex[128];
    int vertexToIndex[128];
    bool exist[128] = {false};
    int vertexCount = 0;

    // Initialize graph with 1e9
    for (int i = 0; i < 128; ++i)
        for (int j = 0; j < 128; ++j)
            graph[i][j] = (i == j ? 0 : 1e9);

    // Build graph and vertex mapping
    for (int i = 0; i < numEdge; ++i) {
        char u = edgeList[i][0];
        char v = edgeList[i][1];
        int w = edgeList[i][2];

        // Skip edges with non-positive weights
        if (w <= 0) continue;

        // Convert character to index (handle printable ASCII characters)
        int uIndex = (int)u;
        int vIndex = (int)v;
        
        // Skip if characters are out of reasonable ASCII range
        if (uIndex < 32 || uIndex >= 127 || vIndex < 32 || vIndex >= 127) continue;

        if (!exist[uIndex]) {
            exist[uIndex] = true;
            indexToVertex[vertexCount] = u;
            vertexToIndex[uIndex] = vertexCount++;
        }
        if (!exist[vIndex]) {
            exist[vIndex] = true;
            indexToVertex[vertexCount] = v;
            vertexToIndex[vIndex] = vertexCount++;
        }
        graph[vertexToIndex[uIndex]][vertexToIndex[vIndex]] = w;
    }

    int n = vertexCount;
    int startIndex = (int)start;
    
    // Check if start vertex exists
    if (n == 0 || !exist[startIndex]) {
        return "No path exists";
    }
    
    // For TSP, we need at least 2 vertices
    if (n < 2) {
        return "No path exists";
    }
    
    int startVertexIndex = vertexToIndex[startIndex];

    // Check if we have too many vertices for the bitmask approach
    if (n > 20) {
        return "No path exists";
    }

    // DP table: dp[mask][vertex] = minimum cost to visit all vertices in mask ending at vertex
    static int dp[1048576][20];
    static int parent[1048576][20];
    
    int maxStates = 1 << n;
    
    // Initialize DP table
    for (int i = 0; i < maxStates; ++i) {
        for (int j = 0; j < n; ++j) {
            dp[i][j] = 1e9;
            parent[i][j] = -1;
        }
    }

    // Base case: starting from the start vertex with only start vertex visited
    dp[1 << startVertexIndex][startVertexIndex] = 0;

    // Fill DP table using Bellman-Held-Karp algorithm
    for (int mask = 0; mask < maxStates; ++mask) {
        for (int u = 0; u < n; ++u) {
            // Skip if u is not in the current subset or unreachable
            if (!(mask & (1 << u)) || dp[mask][u] == 1e9) continue;
            
            // Try to extend to vertex v
            for (int v = 0; v < n; ++v) {
                // Skip if v is already visited or no edge from u to v
                if (mask & (1 << v) || graph[u][v] == 1e9) continue;
                
                int newMask = mask | (1 << v);
                int newCost = dp[mask][u] + graph[u][v];
                
                if (newCost < dp[newMask][v]) {
                    dp[newMask][v] = newCost;
                    parent[newMask][v] = u;
                }
            }
        }
    }

    // Find the minimum cost to complete the tour
    int fullMask = (1 << n) - 1;
    int minCost = 1e9;
    int lastVertex = -1;
    
    // Check all possible ending vertices (except start)
    for (int i = 0; i < n; ++i) {
        if (i == startVertexIndex) continue;
        
        // Check if we can reach this vertex and return to start
        if (dp[fullMask][i] != 1e9 && graph[i][startVertexIndex] != 1e9) {
            int totalCost = dp[fullMask][i] + graph[i][startVertexIndex];
            if (totalCost < minCost) {
                minCost = totalCost;
                lastVertex = i;
            }
        }
    }

    // Check if no valid tour exists
    if (minCost >= 1e9 || lastVertex == -1) {
        return "No path exists";
    }

    // Reconstruct the path
    int path[128];
    int pathLength = 0;
    int currentMask = fullMask;
    int currentVertex = lastVertex;
    
    // Trace back from the last vertex to start
    while (currentVertex != -1) {
        path[pathLength++] = currentVertex;
        int prevVertex = parent[currentMask][currentVertex];
        currentMask ^= (1 << currentVertex);
        currentVertex = prevVertex;
    }
    
    // Build result string manually without stringstream
    string result = "";
    
    // Output the path in correct order (reverse the traced path)
    for (int i = pathLength - 1; i >= 0; --i) {
        result += indexToVertex[path[i]];
        if (i > 0) result += " ";
    }
    result += " ";
    result += indexToVertex[startVertexIndex];
    
    return result;
}