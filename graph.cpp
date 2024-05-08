#include "graph.h"
#include <ctime>
#include "cmath"

Graph::Graph(int numVertices, bool isDirected, bool isWeighted, int windowWidth, int windowHeight)
        : numVertices(numVertices), isDirected(isDirected), isWeighted(isWeighted) {
    srand(time(0));
    generateRandomGraph();
    createVertices(windowWidth, windowHeight);
}

const std::vector<std::vector<std::pair<int, float>>>& Graph::getAdjacencyList() const {
    return adjacencyList;
}

std::vector<sf::CircleShape>& Graph::getVertices() const {
    return vertices;
}


void Graph::generateRandomGraph() {
    adjacencyList.resize(numVertices);

    int edgesCount = 0;

    while (edgesCount < numVertices * 1.5) {
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
                if (isDirected && vertex1 > vertex2) {
                    continue;
                }

                adjacencyList[vertex1].emplace_back(vertex2, weight);
                if (!isDirected) {
                    adjacencyList[vertex2].emplace_back(vertex1, weight);
                }
                edgesCount++;
            }
        }
    }
}


int Graph::getNumEdges() const {
    int count = 0;
    std::set<std::pair<int, int>> visitedEdges;

    for (int i = 0; i < numVertices; ++i) {
        for (const auto& neighbor : adjacencyList[i]) {
            int neighborIndex = neighbor.first;

            if (visitedEdges.find({i, neighborIndex}) != visitedEdges.end() ||
                (!isDirected && visitedEdges.find({neighborIndex, i}) != visitedEdges.end())) {
                continue;
            }

            visitedEdges.insert({i, neighborIndex});
            ++count;
        }
    }

    return count;
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
                (!isDirected && visitedEdges.find({neighborIndex, i}) != visitedEdges.end())) {
                continue;
            }

            visitedEdges.insert({i, neighborIndex});

            sf::Vector2f startPoint = vertices[i].getPosition() + sf::Vector2f(20.f, 20.f);
            sf::Vector2f endPoint = vertices[neighborIndex].getPosition() + sf::Vector2f(20.f, 20.f);

            sf::Vector2f direction = endPoint - startPoint;
            float length = sqrt(direction.x * direction.x + direction.y * direction.y);
            if (length != 0) {
                direction /= length;
            }
            sf::Vector2f arrowPoint = endPoint - direction * 20.f;

            sf::Vertex line[] = {
                    sf::Vertex(startPoint),
                    sf::Vertex(endPoint)
            };

            window.draw(line, 2, sf::Lines);

            if (isDirected) {
                sf::Vector2f arrowPoint = endPoint - direction * 20.f;

                sf::VertexArray arrow(sf::Triangles, 3);
                arrow[0].position = arrowPoint;
                arrow[1].position = arrowPoint + sf::Vector2f(-5.f * direction.y - 5.f * direction.x, 5.f * direction.x - 5.f * direction.y);
                arrow[2].position = arrowPoint + sf::Vector2f(5.f * direction.y - 5.f * direction.x, -5.f * direction.x - 5.f * direction.y);
                arrow[0].color = sf::Color::Green;
                arrow[1].color = sf::Color::Green;
                arrow[2].color = sf::Color::Green;

                window.draw(arrow);
            }
        }
    }


    sf::Font font;
    if (!font.loadFromFile("C:/Users/D/CLionProjects/untitled/arial.ttf")) {
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





