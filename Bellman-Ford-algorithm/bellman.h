#ifndef _BELLMAN_H_
#define _BELLMAN_H_

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <climits>
#include <string>

using namespace std;

void BF(int edgeList[][3], int numEdges, char start_vertices, int BFValue[], int BFPrev[]);
string BF_Path(int edgeList[][3], int numEdges, char start_vertices, char goalVertex);

#endif //_BELLMAN_H_