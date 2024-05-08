#pragma once

#include "graph.h"
#include <vector>
#include <queue>
#include <SFML/Graphics.hpp>

using namespace std;

class BFS {
private:
    const vector<vector<pair<int, float>>>& adjacencyList;
    int numVertices;

public:
    BFS(const Graph& graph);

    void traverse(int startVertex) const;
    void draw(sf::RenderWindow& window, const Graph& graph, int startVertex) const;
};





