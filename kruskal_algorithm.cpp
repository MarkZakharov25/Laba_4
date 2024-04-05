#include "kruskal_algorithm.h"

KruskalMST::KruskalMST(const Graph& graph) : adjacencyList(graph.getAdjacencyList()), numVertices(adjacencyList.size()) {}

void KruskalMST::findMST() const {
    vector<Edge> edges;
    for (int i = 0; i < numVertices; ++i) {
        for (const auto& neighbor : adjacencyList[i]) {
            edges.push_back({i, neighbor.first, static_cast<int>(neighbor.second)});
        }
    }

    vector<int> parent(numVertices, -1);
    vector<Edge> result;
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    int edgeCount = 0;
    for (Edge edge : edges) {
        if (edgeCount == numVertices - 1)
            break;

        int sourceParent = findParent(parent, edge.source);
        int destParent = findParent(parent, edge.destination);

        if (sourceParent != destParent) {
            result.push_back(edge);
            unionSets(parent, sourceParent, destParent);
            edgeCount++;
        }
    }

    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (Edge edge : result) {
        cout << edge.source << " - " << edge.destination << " : " << edge.weight << endl;
    }
}

int KruskalMST::findParent(vector<int>& parent, int vertex) const {
    if (parent[vertex] == -1)
        return vertex;
    return findParent(parent, parent[vertex]);
}

void KruskalMST::unionSets(vector<int>& parent, int x, int y) const {
    int xset = findParent(parent, x);
    int yset = findParent(parent, y);
    if (xset != yset)
        parent[xset] = yset;
}
