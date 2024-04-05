#include <iostream>
#include <SFML/Graphics.hpp>
#include "graph.h"
#include "kruskal_algorithm.h"
#include "bfs.h"
#include "dfs.h"
#include "prima_algorithm.h"

using namespace std;

int main() {
    int numVertices;
    cout << "Enter number of vertices: ";
    cin >> numVertices;

    if (numVertices <= 0) {
        cout << "Number of vertices should be greater than 0." << endl;
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Visualization");
    window.clear(sf::Color::Black);

    Graph graph(numVertices, window.getSize().x, window.getSize().y);

    cout << "Adjacency List:" << endl;
    const vector<vector<pair<int, float>>>& adjacencyList = graph.getAdjacencyList();
    for (int i = 0; i < numVertices; ++i) {
        cout << "Vertex " << i << " -> ";
        for (const auto& neighbor : adjacencyList[i]) {
            cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
        }
        cout << endl;
    }

    KruskalMST kruskal(graph);
    kruskal.findMST();

    PrimMST prim(adjacencyList, numVertices);
    cout << "Enter the start vertex for Prim's MST: ";
    int startVertex;
    cin >> startVertex;
    prim.findMST(startVertex);

    int startVertexBFS;
    cout << "Enter the start vertex for BFS traversal: ";
    cin >> startVertexBFS;
    cout << "BFS Traversal: ";
    BFS bfs(graph);
    bfs.traverse(startVertexBFS);
    cout << endl;

    int startVertexDFS;
    cout << "Enter the start vertex for DFS traversal: ";
    cin >> startVertexDFS;
    cout << "DFS Traversal: ";
    DFS dfs(graph);
    dfs.traverse(startVertexDFS);
    cout << endl;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        graph.draw(window);
        window.display();
    }

    return 0;
}




