#include "dijkstra.h"

Dijkstra::Dijkstra(const std::vector<std::vector<std::pair<int, float>>>& graph) : graph_(graph) {}

std::pair<std::vector<int>, std::vector<std::pair<int, int>>> Dijkstra::shortestPath(int startVertex) const {
    int numVertices = graph_.size();
    std::vector<int> distances(numVertices, std::numeric_limits<int>::max());
    std::vector<bool> visited(numVertices, false);
    distances[startVertex] = 0;
    std::vector<std::pair<int, int>> edges;

    std::vector<int> shortestPathParent(numVertices, -1);
    for (int count = 0; count < numVertices - 1; ++count) {
        int u = findMinDistanceVertex(distances, visited);
        visited[u] = true;

        for (const auto& edge : graph_[u]) {
            int v = edge.first;
            float weight = edge.second;
            if (!visited[v] && distances[u] != std::numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                edges.push_back({u, v});
                shortestPathParent[v] = u;
            }
        }
    }

    std::sort(edges.begin(), edges.end(), [this](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return graph_[a.first][a.second].second < graph_[b.first][b.second].second;
    });

    std::vector<std::pair<int, int>> useEdges;
    for (int v = 0; v < numVertices; ++v) {
        if (v != startVertex && distances[v] != std::numeric_limits<int>::max()) {
            int parent = v;
            while (parent != startVertex) {
                int grandparent = shortestPathParent[parent];
                useEdges.push_back({grandparent, parent});
                parent = grandparent;
            }
        }
    }

    return {distances, useEdges};
}



int Dijkstra::findMinDistanceVertex(const std::vector<int>& distances, const std::vector<bool>& visited) const {
    int minDistance = std::numeric_limits<int>::max();
    int minVertex = -1;

    for (int v = 0; v < distances.size(); ++v) {
        if (!visited[v] && distances[v] < minDistance) {
            minDistance = distances[v];
            minVertex = v;
        }
    }

    return minVertex;
}

void Dijkstra::draw(sf::RenderWindow& window, const Graph& graph, const std::set<std::pair<int, int>>& useEdges) const {

    const sf::Color pathColor = sf::Color::Red;
    auto& vertices = const_cast<std::vector<sf::CircleShape>&>(graph.getVertices());
    std::vector<std::pair<int, int>> highlightedEdges;
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> redEdges;

    for (const auto& edge : useEdges) {
        int u = edge.first;
        int v = edge.second;
        highlightedEdges.push_back({u, v});

        sf::Vector2f startPoint = vertices[u].getPosition() + sf::Vector2f(20.f, 20.f);
        sf::Vector2f endPoint = vertices[v].getPosition() + sf::Vector2f(20.f, 20.f);

        sf::Vertex line[] = {
                sf::Vertex(startPoint, pathColor),
                sf::Vertex(endPoint, pathColor)
        };
        window.draw(line, 2, sf::Lines);
    }

    int currentEdgeIndex = -1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Right) {
                    currentEdgeIndex++;
                    if (currentEdgeIndex >= highlightedEdges.size()) {
                        currentEdgeIndex = highlightedEdges.size() - 1;
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
            const auto& edge = highlightedEdges[i];
            sf::Vertex line[] = {
                    sf::Vertex(vertices[edge.first].getPosition() + sf::Vector2f(20.f, 20.f), pathColor),
                    sf::Vertex(vertices[edge.second].getPosition() + sf::Vector2f(20.f, 20.f), pathColor)
            };
            window.draw(line, 2, sf::Lines);
        }

        window.display();
    }
}


