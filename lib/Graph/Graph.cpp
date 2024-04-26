#include "Graph.h"

#include <iostream>

void Graph::InsertToNodeList(const NodePointer& node) {
    nodes.push_back(node);
    ++nodes_quantity;
    
    CheckAdjacencyListSize();
}

void Graph::InsertToAdjacencyList(const unsigned& parent_node_id, const unsigned& child_node_id) {
    adjacency_list[parent_node_id].push_back(child_node_id);
    
    CheckAdjacencyListSize();
}

[[nodiscard]] std::stack<unsigned> Graph::TopSort() const {
    std::vector<unsigned> visited(nodes.size(), 0);
    std::stack<unsigned> stack;
    
    for (int i = 0; i < nodes.size(); ++i) {
        if (!visited[i]) {
            DFS(visited, stack, i);
        }
    }
    
    return stack;
}

void Graph::CheckAdjacencyListSize() {
    if (adjacency_list.size() <= nodes.size() + 1) {
        adjacency_list.resize(adjacency_list.size() * 1.5 + 1);
    }
}

void Graph::DFS(std::vector<unsigned>& visited, std::stack<unsigned>& stack, int vertex) const {
    visited[vertex] = 1;
    
    for (int to: adjacency_list[vertex]) {
        if (!visited[to]) {
            DFS(visited, stack, to);
        }
    }
    
    stack.push(vertex);
}
