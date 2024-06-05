#include <iostream>
#include <SFML/Graphics.hpp>
#include "graph.h"
#include "bfs.h"
#include "dfs.h"
#include "kruskal_algorithm.h"
#include "prima_algorithm.h"
#include "dijkstra.h"
#include "fordfulkerson.h"

using namespace std;

int main() {
    int numVertices;
    bool isDirected, isWeighted;
    int window_height = 1920;
    int window_width = 1080;
    int algorithm_choice;

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

    sf::RenderWindow window(sf::VideoMode(window_height, window_width), "Graph Visualization");
    sf::RenderWindow window_bfs(sf::VideoMode(window_height, window_width), "BFS Visualization");
    sf::RenderWindow window_dfs(sf::VideoMode(window_height, window_width), "DFS Visualization");
    sf::RenderWindow window_kruskal(sf::VideoMode(window_height, window_width), "Kruskal Visualization");
    sf::RenderWindow window_prima(sf::VideoMode(window_height, window_width), "Prima Visualization");
    sf::RenderWindow window_dijkstra(sf::VideoMode(window_height, window_width), "Dijkstra Visualization");
    sf::RenderWindow window_fulkerson(sf::VideoMode(window_height, window_width), "Ford-Fulkerson Visualization");

    Graph graph(numVertices, isDirected, isWeighted, window.getSize().x, window.getSize().y);

    cout << " " << endl;
    const vector<vector<pair<int, float>>>& adjacencyList = graph.getAdjacencyList();
    for (int i = 0; i < numVertices; ++i) {
        cout << "Vertex " << i << " -> ";
        for (const auto& neighbor : adjacencyList[i]) {
            cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
        }
        cout << endl;
    }

    if (!isDirected && !isWeighted) {
        cout << "Choose algorithm:" << endl;
        cout << "1. BFS" << endl;
        cout << "2. DFS" << endl;
        cout << "Your choice: ";
        cin >> algorithm_choice;

        switch (algorithm_choice) {
            case 1: {
                cout << "Running BFS traversal:" << endl;
                int startVertexBFS;
                cout << "Enter the start vertex for BFS traversal: ";
                cin >> startVertexBFS;
                BFS bfs(graph);
                auto traversedEdges = bfs.traverse(startVertexBFS);
                bfs.draw(window_bfs, graph, traversedEdges);
                cout << endl;
                break;
            }
            case 2: {
                cout << "Running DFS traversal:" << endl;
                int startVertexDFS;
                cout << "Enter the start vertex for DFS traversal: ";
                cin >> startVertexDFS;
                DFS dfs(graph);
                auto traversedEdges = dfs.traverse(startVertexDFS);

                // Initialize sf::RenderWindow window_dfs here

                dfs.draw(window_dfs, graph, traversedEdges);
                cout << endl;
                break;
            }

        }

    } else if (isDirected && !isWeighted) {

        cout << "Choose algorithm:" << endl;
        cout << "1. BFS" << endl;
        cout << "2. DFS" << endl;
        cout << "Your choice: ";
        cin >> algorithm_choice;

        switch (algorithm_choice) {
            case 1: {
                cout << "Running BFS traversal:" << endl;
                int startVertexBFS;
                cout << "Enter the start vertex for BFS traversal: ";
                cin >> startVertexBFS;
                BFS bfs(graph);
                auto traversedEdges = bfs.traverse(startVertexBFS);
                bfs.draw(window_bfs, graph, traversedEdges);
                cout << endl;
                break;
            }
            case 2: {
                cout << "Running DFS traversal:" << endl;
                int startVertexDFS;
                cout << "Enter the start vertex for DFS traversal: ";
                cin >> startVertexDFS;
                DFS dfs(graph);
                auto traversedEdges = dfs.traverse(startVertexDFS);

                // Initialize sf::RenderWindow window_dfs here

                dfs.draw(window_dfs, graph, traversedEdges);
                cout << endl;
                break;
            }

        }

    } else if (!isDirected && isWeighted) {

        cout << "Choose algorithm:" << endl;
        cout << "1. BFS" << endl;
        cout << "2. DFS" << endl;
        cout << "3. Kruskal's algorithm" << endl;
        cout << "4. Prim's algorithm" << endl;
        cout << "5. Dijkstra's algorithm" << endl;
        cout << "Enter your choice: ";
        cin >> algorithm_choice;

        switch (algorithm_choice) {
            case 1: {
                cout << "Running BFS traversal:" << endl;
                int startVertexBFS;
                cout << "Enter the start vertex for BFS traversal: ";
                cin >> startVertexBFS;
                BFS bfs(graph);
                auto traversedEdges = bfs.traverse(startVertexBFS);
                bfs.draw(window_bfs, graph, traversedEdges);
                cout << endl;
                break;
            }

            case 2: {
                cout << "Running DFS traversal:" << endl;
                int startVertexDFS;
                cout << "Enter the start vertex for DFS traversal: ";
                cin >> startVertexDFS;
                DFS dfs(graph);
                auto traversedEdges = dfs.traverse(startVertexDFS);

                // Initialize sf::RenderWindow window_dfs here

                dfs.draw(window_dfs, graph, traversedEdges);
                cout << endl;
                break;
            }

            case 3: {
                cout << "Running Kruskal's algorithm:" << endl;
                KruskalMST kruskal(graph);
                kruskal.findMST();
                kruskal.draw(window_kruskal, graph);
                break;
            }
            case 4: {
                cout << "Running Prim's algorithm:" << endl;
                PrimMST prim(adjacencyList, numVertices);
                int startVertex;
                cout << "Enter the start vertex for Prim's MST: ";
                cin >> startVertex;
                prim.findMST(startVertex);
                prim.draw(window_prima, graph, startVertex);
                break;
            }
            case 5: {
                int startVertexDijkstra;
                std::cout << "Enter the start vertex for Dijkstra's algorithm: ";
                std::cin >> startVertexDijkstra;

                Dijkstra dijkstraAlgorithm(adjacencyList);
                auto result = dijkstraAlgorithm.shortestPath(startVertexDijkstra);
                const std::vector<int>& shortestDistances = result.first;
                const std::vector<std::tuple<int, int, float>>& traversedEdges = result.second;

                std::cout << "Shortest distances from vertex " << startVertexDijkstra << ":\n";
                for (int v = 0; v < shortestDistances.size(); ++v) {
                    std::cout << "Vertex " << v << ": " << shortestDistances[v] << '\n';
                }

                if (traversedEdges.empty()) {
                    std::cout << "No edges traversed by Dijkstra's algorithm.\n";
                } else {
                    std::cout << "Edges traversed by Dijkstra's algorithm (sorted by weight):\n";
                    for (const auto& edge : traversedEdges) {
                        std::cout << "Edge: " << std::get<0>(edge) << " -> " << std::get<1>(edge) << " (Weight: " << std::get<2>(edge) << ")\n";
                    }
                }

                dijkstraAlgorithm.draw(window_dijkstra, graph, traversedEdges);

                break;
            }
        }
    }

    else {

        cout << "Choose algorithm:" << endl;
        cout << "1. BFS" << endl;
        cout << "2. DFS" << endl;
        cout << "3. Ford-Fulkerson algorithm" << endl;
        cout << "Enter your choice: ";
        cin >> algorithm_choice;

        switch (algorithm_choice){

            case 1: {
                cout << "Running BFS traversal:" << endl;
                int startVertexBFS;
                cout << "Enter the start vertex for BFS traversal: ";
                cin >> startVertexBFS;
                BFS bfs(graph);
                auto traversedEdges = bfs.traverse(startVertexBFS);
                bfs.draw(window_bfs, graph, traversedEdges);
                cout << endl;
                break;
            }

            case 2: {
                cout << "Running DFS traversal:" << endl;
                int startVertexDFS;
                cout << "Enter the start vertex for DFS traversal: ";
                cin >> startVertexDFS;
                DFS dfs(graph);
                auto traversedEdges = dfs.traverse(startVertexDFS);

                // Initialize sf::RenderWindow window_dfs here

                dfs.draw(window_dfs, graph, traversedEdges);
                cout << endl;
                break;
            }

            case 3: {
                int source, sink;
                std::cout << "Enter the source vertex for Ford-Fulkerson algorithm: ";
                std::cin >> source;
                std::cout << "Enter the sink vertex for Ford-Fulkerson algorithm: ";
                std::cin >> sink;

                FordFulkerson ff(graph);

                int maxFlow = ff.findMaxFlow(source, sink).first;
                std::cout << "Maximum flow from " << source << " to " << sink << " is " << maxFlow << std::endl;

                std::vector<Iteration> iterations = ff.findMaxFlow(source, sink).second;

                for (int i = 0; i < iterations.size(); ++i) {
                    std::cout << "Edges for iteration " << i + 1 << ":\n";
                    std::vector<std::pair<int, int>> sortedEdges = iterations[i].usedEdges;

                    std::sort(sortedEdges.begin(), sortedEdges.end());

                    for (const auto& edge : sortedEdges) {
                        std::cout << edge.first << " -> " << edge.second << "\n";
                    }
                    std::cout << std::endl;
                }

                ff.draw(window_fulkerson, graph, iterations);
            }
        }
    }

    return 0;
}






