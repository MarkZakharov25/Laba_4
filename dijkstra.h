#pragma once

#include <vector>
#include <limits>
#include "SFML/Graphics.hpp"
#include "graph.h"

struct Dijkstra {
    Dijkstra(const std::vector<std::vector<std::pair<int, float>>>& graph);

    std::pair<std::vector<int>, std::vector<std::tuple<int, int, float>>> shortestPath(int startVertex);

    void draw(sf::RenderWindow& window, const Graph& graph, const std::vector<std::tuple<int, int, float>>& useEdges) const;


private:
    std::vector<std::vector<std::pair<int, float>>> graph_;

    int findMinDistanceVertex(const std::vector<int>& distances, const std::vector<bool>& visited);
};
