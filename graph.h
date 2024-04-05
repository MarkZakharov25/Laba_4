#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <ctime>

using namespace std;

class Graph {
private:
    vector<vector<pair<int, float>>> adjacencyList;
    int numVertices;
    vector<sf::CircleShape> vertices;

public:
    Graph(int numVertices, int windowWidth, int windowHeight);

    const vector<vector<pair<int, float>>>& getAdjacencyList() const;

    void generateRandomGraph();

    void createVertices(int windowWidth, int windowHeight);

    void draw(sf::RenderWindow& window) const;
};
