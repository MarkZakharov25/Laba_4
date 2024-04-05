#include <iostream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <queue>
#include <stack>

using namespace std;

struct Edge {
    int source, destination, weight;
};

class Graph {
private:
    vector<vector<pair<int, float>>> adjacencyList;
    int numVertices;
    vector<sf::CircleShape> vertices;

public:
    Graph(int numVertices, int windowWidth, int windowHeight) : numVertices(numVertices) {
        srand(time(0));
        generateRandomGraph();
        createVertices(windowWidth, windowHeight);
    }

    const vector<vector<pair<int, float>>>& getAdjacencyList() const {
        return adjacencyList;
    }

    void generateRandomGraph() {
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
};

class KruskalMST {
private:
    const vector<vector<pair<int, float>>>& adjacencyList;
    int numVertices;

public:
    KruskalMST(const Graph& graph) : adjacencyList(graph.getAdjacencyList()), numVertices(adjacencyList.size()) {}

    void findMST() const {
        vector<Edge> edges;
        for (int i = 0; i < numVertices; ++i) {
            for (const auto& neighbor : adjacencyList[i]) {
                edges.push_back({i, neighbor.first, static_cast<int>(neighbor.second)});

            }
        }

        vector<int> parent(numVertices, -1);
        vector<Edge> result;
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.weight < b.weight;
        });

        int edgeCount = 0;
        for (Edge edge : edges) {
            if (edgeCount == numVertices - 1)
                break;

            int sourceParent = findParent(parent, edge.source);
            int destParent = findParent(parent, edge.destination);

            if (sourceParent != destParent) {
                result.push_back(edge);
                unionSets(parent, sourceParent, destParent);
                edgeCount++;
            }
        }

        cout << "Edges in the Minimum Spanning Tree:" << endl;
        for (Edge edge : result) {
            cout << edge.source << " - " << edge.destination << " : " << edge.weight << endl;
        }
    }

    int findParent(vector<int>& parent, int vertex) const {
        if (parent[vertex] == -1)
            return vertex;
        return findParent(parent, parent[vertex]);
    }

    void unionSets(vector<int>& parent, int x, int y) const {
        int xset = findParent(parent, x);
        int yset = findParent(parent, y);
        if (xset != yset)
            parent[xset] = yset;
    }
};

class BFS {
private:
    const vector<vector<pair<int, float>>>& adjacencyList;
    int numVertices;

public:
    BFS(const Graph& graph) : adjacencyList(graph.getAdjacencyList()), numVertices(adjacencyList.size()) {}

    void traverse(int startVertex) const {
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
};

class DFS {
private:
    const vector<vector<pair<int, float>>>& adjacencyList;
    int numVertices;

public:
    DFS(const Graph& graph) : adjacencyList(graph.getAdjacencyList()), numVertices(adjacencyList.size()) {}

    void traverse(int startVertex) const {
        vector<bool> visited(numVertices, false);
        stack<int> s;

        visited[startVertex] = true;
        s.push(startVertex);

        while (!s.empty()) {
            int currentVertex = s.top();
            s.pop();
            cout << currentVertex << " ";

            for (const auto& neighbor : adjacencyList[currentVertex]) {
                int neighborVertex = neighbor.first;
                if (!visited[neighborVertex]) {
                    visited[neighborVertex] = true;
                    s.push(neighborVertex);
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

    cout << "Adjacency List:" << endl;
    const vector<vector<pair<int, float>>>& adjacencyList = graph.getAdjacencyList();
    for (int i = 0; i < numVertices; ++i) {
        cout << "Vertex " << i << " -> ";
        for (const auto& neighbor : adjacencyList[i]) {
            cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
        }
        cout << endl;
    }

    KruskalMST kruskal(graph);
    kruskal.findMST();

    int startVertex;
    cout << "Enter the start vertex for BFS traversal: ";
    cin >> startVertex;
    cout << "BFS Traversal: ";
    BFS bfs(graph);
    bfs.traverse(startVertex);
    cout << endl;

    cout << "Enter the start vertex for DFS traversal: ";
    cin >> startVertex;
    cout << "DFS Traversal: ";
    DFS dfs(graph);
    dfs.traverse(startVertex);
    cout << endl;

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


