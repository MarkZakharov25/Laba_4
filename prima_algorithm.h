#pragma once

#include <vector>
#include <iostream>
#include <limits>
#include "graph.h"

class PrimMST {
private:
    const std::vector<std::vector<std::pair<int, float>>>& adjacencyList;
    int numVertices;

public:
    PrimMST(const std::vector<std::vector<std::pair<int, float>>>& adjacencyList, int numVertices);

    void findMST(int startVertex) const;
    void draw(sf::RenderWindow& window, const Graph& graph, int startVertex) const;
};



