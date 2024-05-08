#pragma once
#include <vector>
#include <limits>
#include "queue"
#include "graph.h"

class Dijkstra {
public:
    Dijkstra(const std::vector<std::vector<std::pair<int, float>>>& graph);

    std::pair<std::vector<int>, std::vector<std::pair<int, int>>> shortestPath(int startVertex) const;


    void draw(sf::RenderWindow& window, const Graph& graph,
              const std::set<std::pair<int, int>>& useEdges) const;

private:
    std::vector<std::vector<std::pair<int, float>>> graph_;

    std::vector<std::pair<int, int>> useEdges;


    int findMinDistanceVertex(const std::vector<int>& distances, const std::vector<bool>& visited) const;

};


