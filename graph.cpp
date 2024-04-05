#include "graph.h"

Graph::Graph(int numVertices, int windowWidth, int windowHeight) : numVertices(numVertices) {
    srand(time(0));
    generateRandomGraph();
    createVertices(windowWidth, windowHeight);
}

const vector<vector<pair<int, float>>>& Graph::getAdjacencyList() const {
    return adjacencyList;
}

void Graph::generateRandomGraph() {
    adjacencyList.resize(numVertices);

    int edgesCount = 0;

    while (edgesCount < numVertices * 2) {
        int vertex1 = rand() % numVertices;
        int vertex2 = rand() % numVertices;
        int weight = static_cast<int>(rand() % 100 + 1); // Перетворюємо float на int

        if (vertex1 != vertex2) {
            bool alreadyConnected = false;
            for (const auto& neighbor : adjacencyList[vertex1]) {
                if (neighbor.first == vertex2) {
                    alreadyConnected = true;
                    break;
                }
            }

            if (!alreadyConnected) {
                adjacencyList[vertex1].emplace_back(vertex2, weight);
                adjacencyList[vertex2].emplace_back(vertex1, weight);
                edgesCount += 2;
            }
        }
    }
}

void Graph::createVertices(int windowWidth, int windowHeight) {
    for (int i = 0; i < numVertices; ++i) {
        sf::CircleShape vertex(20.f);
        vertex.setFillColor(sf::Color::Blue);
        vertex.setPosition(rand() % (windowWidth - 100) + 50, rand() % (windowHeight - 100) + 50);
        vertices.push_back(vertex);
    }
}

void Graph::draw(sf::RenderWindow& window) const {
    for (int i = 0; i < numVertices; ++i) {
        for (const auto& neighbor : adjacencyList[i]) {
            int neighborIndex = neighbor.first;
            sf::Vertex line[] = {
                    sf::Vertex(vertices[i].getPosition() + sf::Vector2f(20.f, 20.f)),
                    sf::Vertex(vertices[neighborIndex].getPosition() + sf::Vector2f(20.f, 20.f))
            };
            window.draw(line, 2, sf::Lines);
        }
    }

    for (const auto& vertex : vertices) {
        window.draw(vertex);
    }
}

