#pragma once

#include "graph.h"

struct Iteration {
    int flow;
    std::vector<int> path;
    std::vector<std::pair<int, int>> usedEdges;
};

class FordFulkerson {
private:
    Graph graph;

    int source;
    int sink;

    std::vector<Iteration> iterations;
    int currentIteration;
    std::vector<int> currentPathVertices;

public:

    FordFulkerson(Graph g);

    int min(int a, int b);

    std::pair<int, std::vector<Iteration>> findMaxFlow(int source, int sink);

    void draw(sf::RenderWindow& window, const Graph& graph, std::vector<Iteration> iterations);
};

