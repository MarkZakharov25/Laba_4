#include "dijkstra.h"

int findMinDistanceVertex(const std::vector<int>& distances, const std::vector<bool>& visited) {
    int minDistance = std::numeric_limits<int>::max();
    int minVertex = -1;

    for (int v = 0; v < distances.size(); ++v) {
        if (!visited[v] && distances[v] < minDistance) {
            minDistance = distances[v];
            minVertex = v;
        }
    }

    return minVertex;
}

std::vector<int> dijkstra(const std::vector<std::vector<std::pair<int, float>>>& graph, int startVertex) {
    int numVertices = graph.size();
    std::vector<int> distances(numVertices, std::numeric_limits<int>::max());
    std::vector<bool> visited(numVertices, false);
    distances[startVertex] = 0;

    for (int count = 0; count < numVertices - 1; ++count) {
        int u = findMinDistanceVertex(distances, visited);
        visited[u] = true;

        for (const auto& edge : graph[u]) {
            int v = edge.first;
            float weight = edge.second;
            if (!visited[v] && distances[u] != std::numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
            }
        }
    }

    return distances;
}

