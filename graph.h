#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <set>

class Graph {
private:
    std::vector<std::vector<std::pair<int, float>>> adjacencyList;
    int numVertices;
    bool isDirected;
    bool isWeighted;
    std::vector<sf::CircleShape> vertices;

public:
    Graph(int numVertices, bool isDirected, bool isWeighted, int windowWidth, int windowHeight);

    const std::vector<std::vector<std::pair<int, float>>>& getAdjacencyList() const;

    void generateRandomGraph();

    void createVertices(int windowWidth, int windowHeight);

    void draw(sf::RenderWindow& window) const;
};

