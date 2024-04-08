#include "graph.h"
#include <ctime>

Graph::Graph(int numVertices, bool isDirected, bool isWeighted, int windowWidth, int windowHeight)
        : numVertices(numVertices), isDirected(isDirected), isWeighted(isWeighted) {
    srand(time(0));
    generateRandomGraph();
    createVertices(windowWidth, windowHeight);
}

const std::vector<std::vector<std::pair<int, float>>>& Graph::getAdjacencyList() const {
    return adjacencyList;
}

void Graph::generateRandomGraph() {
    adjacencyList.resize(numVertices);

    int edgesCount = 0;

    while (edgesCount < numVertices * 2) {
        int vertex1 = rand() % numVertices;
        int vertex2 = rand() % numVertices;
        float weight = isWeighted ? static_cast<float>(rand() % 100 + 1) : 1.0f;

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
                if (!isDirected) {
                    adjacencyList[vertex2].emplace_back(vertex1, weight);
                }
                edgesCount += (isDirected ? 1 : 2);
            }
        }
    }
}

void Graph::createVertices(int windowWidth, int windowHeight) {
    vertices.reserve(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        sf::CircleShape vertex(20.f);
        vertex.setFillColor(sf::Color::Blue);
        vertex.setPosition(rand() % (windowWidth - 100) + 50, rand() % (windowHeight - 100) + 50);
        vertices.push_back(vertex);
    }
}

void Graph::draw(sf::RenderWindow& window) const {
    std::set<std::pair<int, int>> visitedEdges;

    for (int i = 0; i < numVertices; ++i) {
        for (const auto& neighbor : adjacencyList[i]) {
            int neighborIndex = neighbor.first;

            if (visitedEdges.find({i, neighborIndex}) != visitedEdges.end() ||
                visitedEdges.find({neighborIndex, i}) != visitedEdges.end()) {
                continue;
            }

            visitedEdges.insert({i, neighborIndex});

            sf::Vertex line[] = {
                    sf::Vertex(vertices[i].getPosition() + sf::Vector2f(20.f, 20.f)),
                    sf::Vertex(vertices[neighborIndex].getPosition() + sf::Vector2f(20.f, 20.f))
            };
            window.draw(line, 2, sf::Lines);
        }
    }

    // Draw vertices with their numbers
    sf::Font font;
    if (!font.loadFromFile("C:/Users/D/CLionProjects/untitled/arial.ttf")) {
        // Handle font loading error
    }

    for (int i = 0; i < numVertices; ++i) {
        window.draw(vertices[i]);

        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(i));
        text.setCharacterSize(15);
        text.setFillColor(sf::Color::White);
        text.setPosition(vertices[i].getPosition().x + 10, vertices[i].getPosition().y + 10);
        window.draw(text);
    }
}




