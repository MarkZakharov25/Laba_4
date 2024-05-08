#pragma once

#include "graph.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int source, destination, weight;
};

class KruskalMST {
private:
    const vector<vector<pair<int, float>>>& adjacencyList;
    int numVertices;

public:
    KruskalMST(const Graph& graph);

    void findMST() const;

    int findParent(vector<int>& parent, int vertex) const;

    void unionSets(vector<int>& parent, int x, int y) const;

    void draw(sf::RenderWindow& window, const Graph& graph) const;
};

