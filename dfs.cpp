#include "dfs.h"
#include <iostream>

DFS::DFS(const Graph& graph) : adjacencyList(graph.getAdjacencyList()), numVertices(adjacencyList.size()) {}

std::vector<std::pair<int, int>> DFS::traverse(int startVertex) const {
    vector<bool> visited(numVertices, false);
    stack<int> s;
    std::vector<std::pair<int, int>> traversedEdges;

    visited[startVertex] = true;
    s.push(startVertex);

    while (!s.empty()) {
        int currentVertex = s.top();
        s.pop();
        cout << currentVertex << " ";

        vector<int> unvisitedNeighbors;

        for (const auto& neighbor : adjacencyList[currentVertex]) {
            int neighborVertex = neighbor.first;
            if (!visited[neighborVertex]) {
                unvisitedNeighbors.push_back(neighborVertex);
            }
        }

        if (!unvisitedNeighbors.empty()) {
            sort(unvisitedNeighbors.begin(), unvisitedNeighbors.end());
            s.push(unvisitedNeighbors.front());
            traversedEdges.push_back({currentVertex, unvisitedNeighbors.front()});
            visited[unvisitedNeighbors.front()] = true;
        }
    }
    return traversedEdges;
}



void DFS::draw(sf::RenderWindow& window, const Graph& graph, const std::vector<std::pair<int, int>>& traversedEdges) const {
    const sf::Color pathColor = sf::Color::Red;
    auto& vertices = const_cast<std::vector<sf::CircleShape>&>(graph.getVertices());
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> redEdges;

    for (const auto& edge : traversedEdges) {
        int startVertex = edge.first;
        int endVertex = edge.second;
        sf::Vector2f startPoint = vertices[startVertex].getPosition() + sf::Vector2f(20.f, 20.f);
        sf::Vector2f endPoint = vertices[endVertex].getPosition() + sf::Vector2f(20.f, 20.f);
        redEdges.push_back({startPoint, endPoint});
    }

    int currentEdgeIndex = -1;

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





