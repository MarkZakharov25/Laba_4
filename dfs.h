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

    std::vector<std::pair<int, int>> traverse(int startVertex) const;
    void draw(sf::RenderWindow& window, const Graph& graph, const std::vector<std::pair<int, int>>& traversedEdges) const;
};

