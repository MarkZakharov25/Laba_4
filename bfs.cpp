#include <SFML/Graphics.hpp>
#include "bfs.h"
#include "graph.h"
#include <queue>
#include <iostream>
#include "cmath"

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


void BFS::draw(sf::RenderWindow& window, const Graph& graph, int startVertex) const {
    const sf::Color visitedColor = sf::Color::Green;
    const sf::Color unvisitedColor = sf::Color::Blue;
    const sf::Color pathColor = sf::Color::Red;

    auto& vertices = const_cast<std::vector<sf::CircleShape>&>(graph.getVertices());

    std::vector<bool> visited(vertices.size(), false);

    std::queue<int> q;

    q.push(startVertex);
    visited[startVertex] = true;

    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> redEdges;

    graph.draw(window);

    int currentEdgeIndex = -1;

    while (!q.empty()) {
        int currentVertex = q.front();
        q.pop();

        const auto& neighbors = graph.getAdjacencyList()[currentVertex];

        for (const auto& neighbor : neighbors) {
            int neighborVertex = neighbor.first;
            if (!visited[neighborVertex]) {
                q.push(neighborVertex);
                visited[neighborVertex] = true;

                sf::Vector2f startPoint = vertices[currentVertex].getPosition() + sf::Vector2f(20.f, 20.f);
                sf::Vector2f endPoint = vertices[neighborVertex].getPosition() + sf::Vector2f(20.f, 20.f);

                sf::Vertex line[] = {
                        sf::Vertex(startPoint, pathColor),
                        sf::Vertex(endPoint, pathColor)
                };

                redEdges.push_back({startPoint, endPoint});
            }
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Right) {
                    currentEdgeIndex++;
                    if (currentEdgeIndex >= redEdges.size()) {
                        currentEdgeIndex = redEdges.size() - 1;
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
            const auto& edge = redEdges[i];
            sf::Vertex line[] = {
                    sf::Vertex(edge.first, pathColor),
                    sf::Vertex(edge.second, pathColor)
            };
            window.draw(line, 2, sf::Lines);
        }

        window.display();
    }
}











