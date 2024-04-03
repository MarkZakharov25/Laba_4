#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

class Graph {
private:
    vector<vector<int>> adjacencyMatrix;
    int numVertices;
    vector<sf::CircleShape> vertices;

public:
    Graph(int numVertices, int windowWidth, int windowHeight) : numVertices(numVertices) {
        srand(time(0));
        generateRandomGraph();
        createVertices(windowWidth, windowHeight);
    }

    // Оголошення публічного методу для отримання матриці суміжності
    const vector<vector<int>>& getAdjacencyMatrix() const {
        return adjacencyMatrix;
    }

    void generateRandomGraph() {
        adjacencyMatrix.resize(numVertices, vector<int>(numVertices, 0));

        int edgesCount = 0;

        while (edgesCount < numVertices * 2) {
            int vertex1 = rand() % numVertices;
            int vertex2 = rand() % numVertices;

            if (vertex1 != vertex2 && adjacencyMatrix[vertex1][vertex2] == 0) {
                adjacencyMatrix[vertex1][vertex2] = 1;
                adjacencyMatrix[vertex2][vertex1] = 1;
                edgesCount += 2;
            }
        }
    }

    void createVertices(int windowWidth, int windowHeight) {
        for (int i = 0; i < numVertices; ++i) {
            sf::CircleShape vertex(20.f);
            vertex.setFillColor(sf::Color::Blue);
            vertex.setPosition(rand() % (windowWidth - 100) + 50, rand() % (windowHeight - 100) + 50);
            vertices.push_back(vertex);
        }
    }

    void draw(sf::RenderWindow& window) const {
        for (int i = 0; i < numVertices; ++i) {
            for (int j = i + 1; j < numVertices; ++j) {
                if (adjacencyMatrix[i][j] == 1) {
                    sf::Vertex line[] = {
                            sf::Vertex(vertices[i].getPosition() + sf::Vector2f(20.f, 20.f)),
                            sf::Vertex(vertices[j].getPosition() + sf::Vector2f(20.f, 20.f))
                    };
                    window.draw(line, 2, sf::Lines);
                }
            }
        }

        for (const auto& vertex : vertices) {
            window.draw(vertex);
        }
    }

    void BFS(int startVertex) const {
        vector<bool> visited(numVertices, false);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int currentVertex = q.front();
            q.pop();
            cout << currentVertex << " ";

            for (int neighbor = 0; neighbor < numVertices; ++neighbor) {
                if (adjacencyMatrix[currentVertex][neighbor] == 1 && !visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }
};

int main() {
    int numVertices;
    cout << "Enter number of vertices: ";
    cin >> numVertices;

    if (numVertices <= 0) {
        cout << "Number of vertices should be greater than 0." << endl;
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Visualization");
    window.clear(sf::Color::Black);

    Graph graph(numVertices, window.getSize().x, window.getSize().y);

    cout << "Adjacency Matrix:" << endl;
    // Використовуємо метод getAdjacencyMatrix для отримання матриці суміжності
    const vector<vector<int>>& adjacencyMatrix = graph.getAdjacencyMatrix();
    for (const auto& row : adjacencyMatrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    int startVertex;
    cout << "Enter the start vertex for BFS traversal: ";
    cin >> startVertex;
    cout << "BFS Traversal: ";
    graph.BFS(startVertex);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        graph.draw(window);
        window.display();
    }

    return 0;
}









