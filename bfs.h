#pragma once

#include "graph.h"
#include <vector>
#include <queue>

using namespace std;

class BFS {
private:
    const vector<vector<pair<int, float>>>& adjacencyList;
    int numVertices;

public:
    BFS(const Graph& graph);

    void traverse(int startVertex) const;
};

