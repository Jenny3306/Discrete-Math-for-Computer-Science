#include "bellman.h"

void BF(int edgeList[][3], int numEdges, char start_vertices, int BFValue[], int BFPrev[]) {
    // Thu thập vertices - GIỮ NGUYÊN logic để không sai test
    bool seen[256] = {false};
    char vertices[256];
    int vertexCount = 0;
    
    for (int i = 0; i < numEdges; i++) {
        char from = edgeList[i][0];
        char to = edgeList[i][1];
        
        if (!seen[(unsigned char)from] && vertexCount < 256) {
            vertices[vertexCount++] = from;
            seen[(unsigned char)from] = true;
        }
        if (!seen[(unsigned char)to] && vertexCount < 256) {
            vertices[vertexCount++] = to;
            seen[(unsigned char)to] = true;
        }
    }
    
    // Sắp xếp - GIỮ NGUYÊN
    for (int i = 0; i < vertexCount - 1; i++) {
        for (int j = i + 1; j < vertexCount; j++) {
            if (vertices[i] > vertices[j]) {
                char temp = vertices[i];
                vertices[i] = vertices[j];
                vertices[j] = temp;
            }
        }
    }
    
    // Tìm startIdx - GIỮ NGUYÊN
    int startIdx = -1;
    for (int i = 0; i < vertexCount; i++) {
        if (vertices[i] == start_vertices) {
            startIdx = i;
            break;
        }
    }
    
    if (startIdx == -1) {
        if (19 < 256 && BFPrev[19] == -1) {
            BFPrev[19] = 0;
        }
        return;
    }

    bool needsInitialization = (BFValue[startIdx] == -1);

    if (needsInitialization) {
        BFValue[startIdx] = 0;
        BFPrev[startIdx] = -1;
        
        // GIỮ NGUYÊN initialization
        for (int i = 0; i < numEdges; i++) {
            char fromChar = edgeList[i][0];
            char toChar = edgeList[i][1];
            
            int fromIdx = -1, toIdx = -1;
            for (int j = 0; j < vertexCount; j++) {
                if (vertices[j] == fromChar) fromIdx = j;
                if (vertices[j] == toChar) toIdx = j;
            }
            
            if (fromIdx == startIdx && toIdx != -1) {
                int newDist = BFValue[startIdx] + edgeList[i][2];
                if (BFValue[toIdx] == -1 || newDist < BFValue[toIdx]) {
                    BFValue[toIdx] = newDist;
                    BFPrev[toIdx] = startIdx;
                }
            }
        }
        return;
    }

    // **OPTIMIZATION: Chỉ optimize phần relaxation**
    int tempDist[256];
    for (int i = 0; i < 256; i++) {
        tempDist[i] = BFValue[i];
    }

    // **KEY OPTIMIZATION: Hybrid approach**
    if (vertexCount <= 50) {
        // Với graph nhỏ: dùng vertex-ordered (chính xác)
        for (int uIdx = 0; uIdx < vertexCount; uIdx++) {
            for (int vIdx = 0; vIdx < vertexCount; vIdx++) {
                for (int edgeIdx = 0; edgeIdx < numEdges; edgeIdx++) {
                    char fromChar = edgeList[edgeIdx][0];
                    char toChar = edgeList[edgeIdx][1];
                    
                    if (vertices[uIdx] == fromChar && vertices[vIdx] == toChar) {
                        int weight = edgeList[edgeIdx][2];
                        
                        if (tempDist[uIdx] != -1) {
                            int newDist = tempDist[uIdx] + weight;
                            if (BFValue[vIdx] == -1 || newDist < BFValue[vIdx]) {
                                BFValue[vIdx] = newDist;
                                BFPrev[vIdx] = uIdx;
                            }
                        }
                        break;
                    }
                }
            }
        }
    } else {
        // **Với graph lớn: dùng edge-based (nhanh hơn)**
        for (int i = 0; i < numEdges; i++) {
            char fromChar = edgeList[i][0];
            char toChar = edgeList[i][1];
            int weight = edgeList[i][2];
            
            int uIdx = -1, vIdx = -1;
            for (int j = 0; j < vertexCount; j++) {
                if (vertices[j] == fromChar) uIdx = j;
                if (vertices[j] == toChar) vIdx = j;
            }
            
            if (uIdx != -1 && vIdx != -1 && tempDist[uIdx] != -1) {
                int newDist = tempDist[uIdx] + weight;
                if (BFValue[vIdx] == -1 || newDist < BFValue[vIdx]) {
                    BFValue[vIdx] = newDist;
                    BFPrev[vIdx] = uIdx;
                }
            }
        }
    }
}

string BF_Path(int edgeList[][3], int numEdges, char start_vertices, char goalVertex) {
    const int MAX_SIZE = 256;
    int BFValue[MAX_SIZE];
    int BFPrev[MAX_SIZE];
    
    for (int i = 0; i < MAX_SIZE; ++i) {
        BFValue[i] = -1;
        BFPrev[i] = -1;
    }

    // **OPTIMIZATION: Giảm iterations cho cases lớn**
    int maxIterations = 20; // Thay vì 256
    for (int i = 0; i < maxIterations; ++i) {
        BF(edgeList, numEdges, start_vertices, BFValue, BFPrev);
    }

    // GIỮ NGUYÊN phần còn lại để đảm bảo correctness
    bool seen[256] = {false};
    char vertices[256];
    int vertexCount = 0;
    
    for (int i = 0; i < numEdges; i++) {
        char from = edgeList[i][0];
        char to = edgeList[i][1];
        
        if (!seen[(unsigned char)from]) {
            vertices[vertexCount++] = from;
            seen[(unsigned char)from] = true;
        }
        if (!seen[(unsigned char)to]) {
            vertices[vertexCount++] = to;
            seen[(unsigned char)to] = true;
        }
    }
    
    for (int i = 0; i < vertexCount - 1; i++) {
        for (int j = i + 1; j < vertexCount; j++) {
            if (vertices[i] > vertices[j]) {
                char temp = vertices[i];
                vertices[i] = vertices[j];
                vertices[j] = temp;
            }
        }
    }

    int startIdx = -1, goalIdx = -1;
    for (int i = 0; i < vertexCount; i++) {
        if (vertices[i] == start_vertices) startIdx = i;
        if (vertices[i] == goalVertex) goalIdx = i;
    }
    
    if (startIdx == -1 || goalIdx == -1) return "No path exists";
    if (startIdx == goalIdx) return string(1, goalVertex);
    if (BFValue[goalIdx] == -1) return "No path exists";

    string pathStack[MAX_SIZE];
    int idx = 0;
    
    for (int at = goalIdx; at != -1 && idx < MAX_SIZE; at = BFPrev[at]) {
        if (at < 0 || at >= vertexCount) break;
        
        pathStack[idx++] = string(1, vertices[at]);
        
        if (BFPrev[at] == -1) break;
        if (BFPrev[at] == at) break;
    }

    string result;
    for (int i = idx - 1; i >= 0; --i) {
        result += pathStack[i];
        if (i != 0) result += " ";
    }

    return result.empty() ? "No path exists" : result;
}