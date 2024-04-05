#include "prima_algorithm.h"

PrimMST::PrimMST(const std::vector<std::vector<std::pair<int, float>>>& adjacencyList, int numVertices)
        : adjacencyList(adjacencyList), numVertices(numVertices) {}

void PrimMST::findMST(int startVertex) const {
    std::vector<bool> inMST(numVertices, false);
    std::vector<float> minWeight(numVertices, std::numeric_limits<float>::max());
    std::vector<int> parent(numVertices, -1);

    minWeight[startVertex] = 0;

    for (int i = 0; i < numVertices - 1; ++i) {
        int minVertex = -1;
        for (int v = 0; v < numVertices; ++v) {
            if (!inMST[v] && (minVertex == -1 || minWeight[v] < minWeight[minVertex])) {
                minVertex = v;
            }
        }

        inMST[minVertex] = true;

        for (const auto& neighbor : adjacencyList[minVertex]) {
            int v = neighbor.first;
            float weight = neighbor.second;
            if (!inMST[v] && weight < minWeight[v]) {
                parent[v] = minVertex;
                minWeight[v] = weight;
            }
        }
    }

    std::cout << "Edges in the Minimum Spanning Tree (Prim's Algorithm):" << std::endl;
    for (int i = 1; i < numVertices; ++i) {
        if (parent[i] != -1) {
            std::cout << parent[i] << " - " << i << " : " << minWeight[i] << std::endl;
        }
    }
}




