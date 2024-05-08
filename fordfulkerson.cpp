#include "fordfulkerson.h"
#include <iostream>
#include <queue>
#include <limits>

FordFulkerson::FordFulkerson(Graph g) : graph(g) {}


int FordFulkerson::min(int a, int b) {
    return (a < b) ? a : b;
}

std::pair<int, std::vector<Iteration>> FordFulkerson::findMaxFlow(int source, int sink) {
    auto adjacencyList = graph.getAdjacencyList();
    std::vector<std::vector<int>> rGraph(adjacencyList.size(), std::vector<int>(adjacencyList.size(), 0));
    for (int i = 0; i < adjacencyList.size(); ++i) {
        for (const auto& neighbor : adjacencyList[i]) {
            rGraph[i][neighbor.first] = neighbor.second;
        }
    }

    std::vector<int> parent(rGraph.size());
    int maxFlow = 0;

    std::vector<Iteration> iterations;

    while (true) {
        fill(parent.begin(), parent.end(), -1);
        parent[source] = source;

        std::queue<int> q;
        q.push(source);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v < rGraph.size(); v++) {
                if (parent[v] == -1 && rGraph[u][v] > 0) {
                    q.push(v);
                    parent[v] = u;
                }
            }
        }

        if (parent[sink] == -1)
            break;

        int pathFlow = std::numeric_limits<int>::max();
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = std::min(pathFlow, rGraph[u][v]);
        }

        maxFlow += pathFlow;
        Iteration iteration;
        iteration.flow = pathFlow;
        iteration.path.push_back(sink);
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            iteration.path.push_back(u);
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
            iteration.usedEdges.push_back({u, v});
        }
        std::reverse(iteration.path.begin(), iteration.path.end());
        iterations.push_back(iteration);

    }

    return {maxFlow, iterations};
}

void FordFulkerson::draw(sf::RenderWindow& window, const Graph& graph, std::vector<Iteration> iterations)  {
    const sf::Color pathColor = sf::Color::Red;

    auto vertices = const_cast<std::vector<sf::CircleShape>&>(graph.getVertices());
    std::vector<std::vector<sf::Vertex>> redEdges;

    for (const auto& iteration : iterations) {
        std::vector<sf::Vertex> currentRedEdges;
        for (const auto& edge : iteration.usedEdges) {
            sf::Vector2f startPos = vertices[edge.first].getPosition() + sf::Vector2f(20.f, 20.f);
            sf::Vector2f endPos = vertices[edge.second].getPosition() + sf::Vector2f(20.f, 20.f);
            currentRedEdges.push_back(sf::Vertex(startPos, pathColor));
            currentRedEdges.push_back(sf::Vertex(endPos, pathColor));
        }
        redEdges.push_back(currentRedEdges);
    }

    int currentIterationIndex = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Right) {
                    currentIterationIndex++;
                    if (currentIterationIndex >= iterations.size()) {
                        currentIterationIndex = iterations.size() - 1;
                    }
                } else if (event.key.code == sf::Keyboard::Left) {
                    currentIterationIndex--;
                    if (currentIterationIndex < 0) {
                        currentIterationIndex = 0;
                    }
                }
            } else if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        graph.draw(window);

        if (currentIterationIndex < redEdges.size()) {
            const auto& currentRedEdges = redEdges[currentIterationIndex];
            window.draw(&currentRedEdges[0], currentRedEdges.size(), sf::Lines);
        }

        window.display();
    }
}





