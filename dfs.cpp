#include "dfs.h"
#include <iostream>

DFS::DFS(const Graph& graph) : adjacencyList(graph.getAdjacencyList()), numVertices(adjacencyList.size()) {}

void DFS::traverse(int startVertex) const {
    vector<bool> visited(numVertices, false);
    stack<int> s;

    visited[startVertex] = true;
    s.push(startVertex);

    while (!s.empty()) {
        int currentVertex = s.top();
        s.pop();
        cout << currentVertex << " ";

        for (const auto& neighbor : adjacencyList[currentVertex]) {
            int neighborVertex = neighbor.first;
            if (!visited[neighborVertex]) {
                visited[neighborVertex] = true;
                s.push(neighborVertex);
            }
        }
    }
}
