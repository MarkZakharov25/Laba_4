#include "bfs.h"
#include <iostream>

BFS::BFS(const Graph& graph) : adjacencyList(graph.getAdjacencyList()), numVertices(adjacencyList.size()) {}

void BFS::traverse(int startVertex) const {
    vector<bool> visited(numVertices, false);
    queue<int> q;

    visited[startVertex] = true;
    q.push(startVertex);

    while (!q.empty()) {
        int currentVertex = q.front();
        q.pop();
        cout << currentVertex << " ";

        for (const auto& neighbor : adjacencyList[currentVertex]) {
            int neighborVertex = neighbor.first;
            if (!visited[neighborVertex]) {
                visited[neighborVertex] = true;
                q.push(neighborVertex);
            }
        }
    }
}
