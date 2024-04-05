#pragma once

#include "graph.h"
#include <vector>
#include <stack>

using namespace std;

class DFS {
private:
    const vector<vector<pair<int, float>>>& adjacencyList;
    int numVertices;

public:
    DFS(const Graph& graph);

    void traverse(int startVertex) const;
};

