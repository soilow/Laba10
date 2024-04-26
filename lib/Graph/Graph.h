#pragma once

#include <vector>
#include <stack>
#include "Node.h"

class Graph {
public:
    std::vector<NodePointer> nodes;
    unsigned nodes_quantity = 0;
    
public:
    void InsertToNodeList(const NodePointer& node);
    void InsertToAdjacencyList(const unsigned& parent_node_id, const unsigned& child_node_id);
    
    [[nodiscard]] std::stack<unsigned> TopSort() const;

    [[nodiscard]] inline const NodePointer& GetNodePointer(const unsigned& id) const {
        return nodes[id];
    }

private:
    std::vector<std::vector<unsigned>> adjacency_list;
    
    void CheckAdjacencyListSize();
    void DFS(std::vector<unsigned>& visited, std::stack<unsigned>& stack, int vertex) const;
};
