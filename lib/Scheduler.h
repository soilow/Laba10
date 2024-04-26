#pragma once

#include <stack>
#include "Graph/Graph.h"

class TTaskScheduler {
public:
    template <typename Expression, typename T>
    [[nodiscard]] NodePointer Add(Expression&& expression, const T& argument1, const T& argument2) {
        NodePointer new_node = CreateNode(std::move(expression), argument1, argument2);

        graph.InsertToNodeList(new_node);

        return new_node;
    }

    template <typename Expression, typename T>
    [[nodiscard]] NodePointer Add(Expression&& expression, const T& argument1, const T* argument2) {
        NodePointer new_node = CreateNode(std::move(expression), argument1, argument2);

        graph.InsertToNodeList(new_node);

        return new_node;
    }

    template <typename Expression, typename T>
    [[nodiscard]] NodePointer Add(Expression&& expression, const T* argument1, const T* argument2) {
        NodePointer new_node = CreateNode(std::move(expression), argument1, argument2);

        graph.InsertToNodeList(new_node);

        return new_node;
    }

    template <typename Expression, typename T>
    [[nodiscard]] NodePointer Add(Expression&& expression, const T& argument1) {
        NodePointer new_node = CreateNode(std::move(expression), argument1);

        graph.InsertToNodeList(new_node);

        return new_node;
    }

    template <typename Expression, typename T>
    [[nodiscard]] NodePointer Add(Expression&& expression, const T* argument1) {
        NodePointer new_node = CreateNode(std::move(expression), argument1);

        graph.InsertToNodeList(new_node);

        return new_node;
    }

    template <typename T>
    [[nodiscard]] T GetResult(NodePointer& node) const {
        if (node->GetIsResultCalculated() == false) {
            ExecuteAll();
        }

        return *static_cast<const T*>(node->GetResult());
    }

    template <typename T>
    [[nodiscard]] inline const T* GetFutureResult(const NodePointer& node) {
        graph.InsertToAdjacencyList(node->GetNodeId(), graph.nodes_quantity);

        return static_cast<const T*>(node->GetResult());
    }

    void ExecuteAll() const;

private:
    Graph graph;
};


