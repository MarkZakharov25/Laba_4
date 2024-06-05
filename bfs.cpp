#include <SFML/Graphics.hpp>
#include "bfs.h"
#include "graph.h"
#include <queue>
#include <iostream>
#include "cmath"

BFS::BFS(const Graph& graph) : adjacencyList(graph.getAdjacencyList()), numVertices(adjacencyList.size()) {}

std::vector<std::pair<int, int>> BFS::traverse(int startVertex) const {
    std::vector<bool> visited(numVertices, false);
    std::queue<int> q;
    std::vector<std::pair<int, int>> traversedEdges;

    visited[startVertex] = true;
    q.push(startVertex);

    while (!q.empty()) {
        int currentVertex = q.front();
        q.pop();

        for (const auto& neighbor : adjacencyList[currentVertex]) {
            int neighborVertex = neighbor.first;
            if (!visited[neighborVertex]) {
                visited[neighborVertex] = true;
                q.push(neighborVertex);
                traversedEdges.push_back({currentVertex, neighborVertex});
            }
        }
    }

    return traversedEdges;
}

void BFS::draw(sf::RenderWindow& window, const Graph& graph, const std::vector<std::pair<int, int>>& traversedEdges) const {
    const sf::Color pathColor = sf::Color::Red;

    auto& vertices = const_cast<std::vector<sf::CircleShape>&>(graph.getVertices());

    std::vector<std::vector<sf::Vertex>> redEdges;

    for (const auto& edge : traversedEdges) {
        int startVertex = edge.first;
        int endVertex = edge.second;
        sf::Vector2f startPoint = vertices[startVertex].getPosition() + sf::Vector2f(20.f, 20.f);
        sf::Vector2f endPoint = vertices[endVertex].getPosition() + sf::Vector2f(20.f, 20.f);
        redEdges.push_back({sf::Vertex(startPoint, pathColor), sf::Vertex(endPoint, pathColor)});
    }

    int currentEdgeIndex = -1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Right) {
                    currentEdgeIndex++;
                    if (currentEdgeIndex >= traversedEdges.size()) {
                        currentEdgeIndex = traversedEdges.size() - 1;
                    }
                } else if (event.key.code == sf::Keyboard::Left) {
                    currentEdgeIndex--;
                    if (currentEdgeIndex < -1) {
                        currentEdgeIndex = -1;
                    }
                }
            } else if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        graph.draw(window);

        for (int i = 0; i <= currentEdgeIndex; ++i) {
            if (i >= 0 && i < redEdges.size()) {
                window.draw(&redEdges[i][0], 2, sf::Lines);
            }
        }

        window.display();
    }
}














