#pragma once

#include <vector>
#include <limits>

int findMinDistanceVertex(const std::vector<int>& distances, const std::vector<bool>& visited);

std::vector<int> dijkstra(const std::vector<std::vector<std::pair<int, float>>>& graph, int startVertex);


