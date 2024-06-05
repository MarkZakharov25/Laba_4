#include "dijkstra.h"

Dijkstra::Dijkstra(const std::vector<std::vector<std::pair<int, float>>>& graph) : graph_(graph) {}

std::pair<std::vector<int>, std::vector<std::tuple<int, int, float>>> Dijkstra::shortestPath(int startVertex) {
    int numVertices = graph_.size();
    std::vector<int> distances(numVertices, std::numeric_limits<int>::max());
    std::vector<bool> visited(numVertices, false);
    std::vector<std::tuple<int, int, float>> traversedEdges;
    std::vector<int> parent(numVertices, -1);

    distances[startVertex] = 0;

    for (int count = 0; count < numVertices - 1; ++count) {
        int u = findMinDistanceVertex(distances, visited);
        if (u == -1) break;

        visited[u] = true;

        for (const auto& edge : graph_[u]) {
            int v = edge.first;
            float weight = edge.second;
            if (!visited[v] && distances[u] != std::numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                parent[v] = u;
            }
        }
    }

    for (int v = 0; v < numVertices; ++v) {
        if (parent[v] != -1) {
            traversedEdges.push_back({parent[v], v, distances[v]});
        }
    }

    std::sort(traversedEdges.begin(), traversedEdges.end(), [](const std::tuple<int, int, float>& a, const std::tuple<int, int, float>& b) {
        return std::get<2>(a) < std::get<2>(b);
    });

    return {distances, traversedEdges};
}

int Dijkstra::findMinDistanceVertex(const std::vector<int>& distances, const std::vector<bool>& visited) {
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

void Dijkstra::draw(sf::RenderWindow& window, const Graph& graph, const std::vector<std::tuple<int, int, float>>& useEdges) const {
    const sf::Color pathColor = sf::Color::Red;

    auto& vertices = const_cast<std::vector<sf::CircleShape>&>(graph.getVertices());

    std::vector<sf::Vertex> redEdges;

    for (const auto& edge : useEdges) {
        int u = std::get<0>(edge);
        int v = std::get<1>(edge);
        sf::Vector2f startPoint = vertices[u].getPosition() + sf::Vector2f(20.f, 20.f);
        sf::Vector2f endPoint = vertices[v].getPosition() + sf::Vector2f(20.f, 20.f);
        redEdges.push_back(sf::Vertex(startPoint, pathColor));
        redEdges.push_back(sf::Vertex(endPoint, pathColor));
    }

    int currentEdgeIndex = -1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Right) {
                    currentEdgeIndex++;
                    if (currentEdgeIndex >= useEdges.size()) {
                        currentEdgeIndex = useEdges.size() - 1;
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
                window.draw(&redEdges[2 * i], 2, sf::Lines);
            }
        }

        window.display();
    }
}
