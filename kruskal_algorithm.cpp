#include "kruskal_algorithm.h"

KruskalMST::KruskalMST(const Graph& graph) : adjacencyList(graph.getAdjacencyList()), numVertices(adjacencyList.size()) {}

void KruskalMST::findMST() const {
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

int KruskalMST::findParent(vector<int>& parent, int vertex) const {
    if (parent[vertex] == -1)
        return vertex;
    return findParent(parent, parent[vertex]);
}

void KruskalMST::unionSets(vector<int>& parent, int x, int y) const {
    int xset = findParent(parent, x);
    int yset = findParent(parent, y);
    if (xset != yset)
        parent[xset] = yset;
}


void KruskalMST::draw(sf::RenderWindow& window, const Graph& graph) const {
    const sf::Color pathColor = sf::Color::Red;

    auto& vertices = const_cast<std::vector<sf::CircleShape>&>(graph.getVertices());

    std::vector<bool> visitedEdges(graph.getNumEdges(), false);

    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> redEdges;

    std::vector<Edge> edges;
    for (int i = 0; i < numVertices; ++i) {
        for (const auto& neighbor : adjacencyList[i]) {
            edges.push_back({i, neighbor.first, static_cast<int>(neighbor.second)});
        }
    }


    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    std::vector<int> parent(numVertices, -1);

    int currentEdgeIndex = -1;

    int edgeCount = 0;
    for (Edge edge : edges) {
        if (edgeCount == numVertices - 1)
            break;

        int sourceParent = findParent(parent, edge.source);
        int destParent = findParent(parent, edge.destination);

        if (sourceParent != destParent) {
            visitedEdges[edgeCount] = true;
            redEdges.push_back({vertices[edge.source].getPosition() + sf::Vector2f(20.f, 20.f),
                                vertices[edge.destination].getPosition() + sf::Vector2f(20.f, 20.f)});
            unionSets(parent, sourceParent, destParent);
            edgeCount++;
        }
    }

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
            if (visitedEdges[i]) {
                const auto& edge = redEdges[i];
                sf::Vertex line[] = {
                        sf::Vertex(edge.first, pathColor),
                        sf::Vertex(edge.second, pathColor)
                };
                window.draw(line, 2, sf::Lines);
            }
        }

        window.display();
    }
}
