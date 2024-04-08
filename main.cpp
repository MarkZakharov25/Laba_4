#include <iostream>
#include <SFML/Graphics.hpp>
#include "graph.h"
#include "bfs.h"
#include "dfs.h"
#include "kruskal_algorithm.h"
#include "prima_algorithm.h"
#include "dijkstra.h"

using namespace std;

int main() {
    int numVertices;
    bool isDirected, isWeighted;

    cout << "Enter number of vertices: ";
    cin >> numVertices;

    if (numVertices <= 0) {
        cout << "Number of vertices should be greater than 0." << endl;
        return 1;
    }

    cout << "Is the graph directed? (1 for yes, 0 for no): ";
    cin >> isDirected;

    cout << "Is the graph weighted? (1 for yes, 0 for no): ";
    cin >> isWeighted;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Graph Visualization");
    window.clear(sf::Color::Black);

    Graph graph(numVertices, isDirected, isWeighted, window.getSize().x, window.getSize().y);

    cout << "Adjacency List:" << endl;
    const vector<vector<pair<int, float>>>& adjacencyList = graph.getAdjacencyList();
    for (int i = 0; i < numVertices; ++i) {
        cout << "Vertex " << i << " -> ";
        for (const auto& neighbor : adjacencyList[i]) {
            cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
        }
        cout << endl;
    }

    if (!isDirected && !isWeighted) {
        cout << "Running BFS traversal:" << endl;
        int startVertexBFS;
        cout << "Enter the start vertex for BFS traversal: ";
        cin >> startVertexBFS;
        BFS bfs(graph);
        bfs.traverse(startVertexBFS);
        cout << endl;

        cout << "Running DFS traversal:" << endl;
        int startVertexDFS;
        cout << "Enter the start vertex for DFS traversal: ";
        cin >> startVertexDFS;
        DFS dfs(graph);
        dfs.traverse(startVertexDFS);
        cout << endl;
    } else if (isDirected && !isWeighted) {
        cout << "Running BFS traversal:" << endl;
        int startVertexBFS;
        cout << "Enter the start vertex for BFS traversal: ";
        cin >> startVertexBFS;
        BFS bfs(graph);
        bfs.traverse(startVertexBFS);
        cout << endl;

        cout << "Running DFS traversal:" << endl;
        int startVertexDFS;
        cout << "Enter the start vertex for DFS traversal: ";
        cin >> startVertexDFS;
        DFS dfs(graph);
        dfs.traverse(startVertexDFS);
        cout << endl;


    } else if (!isDirected && isWeighted) {
        cout << "Running Kruskal's algorithm:" << endl;
        KruskalMST kruskal(graph);
        kruskal.findMST();

        cout << "Running Prim's algorithm:" << endl;
        PrimMST prim(adjacencyList, numVertices);
        int startVertex;
        cout << "Enter the start vertex for Prim's MST: ";
        cin >> startVertex;
        prim.findMST(startVertex);

        cout << "Running BFS traversal:" << endl;
        int startVertexBFS;
        cout << "Enter the start vertex for BFS traversal: ";
        cin >> startVertexBFS;
        BFS bfs(graph);
        bfs.traverse(startVertexBFS);
        cout << endl;

        cout << "Running DFS traversal:" << endl;
        int startVertexDFS;
        cout << "Enter the start vertex for DFS traversal: ";
        cin >> startVertexDFS;
        DFS dfs(graph);
        dfs.traverse(startVertexDFS);
        cout << endl;


        int startVertexDijkstra;
        std::cout << "Enter the start vertex for Dijkstra's algorithm: ";
        std::cin >> startVertexDijkstra;
        std::vector<int> shortestDistances = dijkstra(adjacencyList, startVertexDijkstra);

        std::cout << "Shortest distances from vertex " << startVertexDijkstra << ":\n";
        for (int v = 0; v < shortestDistances.size(); ++v) {
            std::cout << "Vertex " << v << ": " << shortestDistances[v] << '\n';
        }

    } else {
        cout << "Running BFS traversal:" << endl;
        int startVertexBFS;
        cout << "Enter the start vertex for BFS traversal: ";
        cin >> startVertexBFS;
        BFS bfs(graph);
        bfs.traverse(startVertexBFS);
        cout << endl;

        cout << "Running DFS traversal:" << endl;
        int startVertexDFS;
        cout << "Enter the start vertex for DFS traversal: ";
        cin >> startVertexDFS;
        DFS dfs(graph);
        dfs.traverse(startVertexDFS);
        cout << endl;
    }

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






