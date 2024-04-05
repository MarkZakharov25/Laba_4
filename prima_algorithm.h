#pragma once

#include <vector>
#include <iostream>
#include <limits>

class PrimMST {
private:
    const std::vector<std::vector<std::pair<int, float>>>& adjacencyList;
    int numVertices;

public:
    PrimMST(const std::vector<std::vector<std::pair<int, float>>>& adjacencyList, int numVertices);

    void findMST(int startVertex) const;
};



