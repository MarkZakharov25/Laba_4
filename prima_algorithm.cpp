#include "prima_algorithm.h"
#include <queue>

PrimMST::PrimMST(const std::vector<std::vector<std::pair<int, float>>>& adjacencyList, int numVertices)
        : adjacencyList(adjacencyList), numVertices(numVertices) {}

void PrimMST::findMST(int startVertex) const {
    std::vector<bool> inMST(numVertices, false);
    std::vector<float> minWeight(numVertices, std::numeric_limits<float>::max());
    std::vector<int> parent(numVertices, -1);

    minWeight[startVertex] = 0;

    for (int i = 0; i < numVertices - 1; ++i) {
        int minVertex = -1;
        for (int v = 0; v < numVertices; ++v) {
            if (!inMST[v] && (minVertex == -1 || minWeight[v] < minWeight[minVertex])) {
                minVertex = v;
            }
        }

        inMST[minVertex] = true;

        for (const auto& neighbor : adjacencyList[minVertex]) {
            int v = neighbor.first;
            float weight = neighbor.second;
            if (!inMST[v] && weight < minWeight[v]) {
                parent[v] = minVertex;
                minWeight[v] = weight;
            }
        }
    }

    std::cout << "Edges in the Minimum Spanning Tree (Prim's Algorithm):" << std::endl;
    for (int i = 1; i < numVertices; ++i) {
        if (parent[i] != -1) {
            std::cout << parent[i] << " - " << i << " : " << minWeight[i] << std::endl;
        }
    }
}


void PrimMST::draw(sf::RenderWindow& window, const Graph& graph, int startVertex) const {
    int currentEdgeIndex = -1;

    std::vector<std::pair<int, int>> displayedEdges;

    const sf::Color mstColor = sf::Color::Green;

    auto &vertices = const_cast<std::vector<sf::CircleShape> &>(graph.getVertices());
    std::vector<bool> inMST(numVertices, false);

    std::vector<std::pair<int, int>> mstEdges;
    float mstWeight = 0;

    inMST[startVertex] = true;

    std::priority_queue<std::pair<float, std::pair<int, int>>, std::vector<std::pair<float, std::pair<int, int>>>, std::greater<>> pq;

    for (const auto &neighbor: adjacencyList[startVertex]) {
        pq.push({neighbor.second, {startVertex, neighbor.first}});
    }

    while (!pq.empty()) {
        auto edge = pq.top();
        pq.pop();

        int u = edge.second.first;
        int v = edge.second.second;
        float weight = edge.first;

        if (inMST[v]) {
            continue;
        }

        mstEdges.push_back({u, v});
        mstWeight += weight;
        inMST[v] = true;

        for (const auto &neighbor: adjacencyList[v]) {
            if (!inMST[neighbor.first]) {
                pq.push({neighbor.second, {v, neighbor.first}});
            }
        }
    }

    std::cout << "Minimum Spanning Tree Weight: " << mstWeight << std::endl;

    graph.draw(window);

    for (const auto &edge: mstEdges) {
        int u = edge.first;
        int v = edge.second;

        sf::Vector2f startPoint = vertices[u].getPosition() + sf::Vector2f(20.f, 20.f);
        sf::Vector2f endPoint = vertices[v].getPosition() + sf::Vector2f(20.f, 20.f);

        sf::Vertex line[] = {
                sf::Vertex(startPoint, mstColor),
                sf::Vertex(endPoint, mstColor)
        };

        displayedEdges.push_back({u, v});
        window.draw(line, 2, sf::Lines);
    }

    window.display();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Right) {
                    currentEdgeIndex++;
                    if (currentEdgeIndex >= displayedEdges.size()) {
                        currentEdgeIndex = displayedEdges.size() - 1;
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
            const auto &edge = displayedEdges[i];
            int u = edge.first;
            int v = edge.second;

            sf::Vector2f startPoint = vertices[u].getPosition() + sf::Vector2f(20.f, 20.f);
            sf::Vector2f endPoint = vertices[v].getPosition() + sf::Vector2f(20.f, 20.f);

            sf::Vertex line[] = {
                    sf::Vertex(startPoint, mstColor),
                    sf::Vertex(endPoint, mstColor)
            };

            window.draw(line, 2, sf::Lines);
        }

        window.display();
    }
}




