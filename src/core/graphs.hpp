#pragma once
#include "types.hpp"

namespace GraphOps {
NodeId addNode(Graph &graph, const PropertyMap &properties);
std::optional<Node> getNode(const Graph &graph, NodeId id);
bool updateNode(Graph &graph, NodeId id, const PropertyMap &properties);
bool deleteNode(Graph &graph, NodeId id);

EdgeId addEdge(Graph &graph, NodeId sourceId, NodeId targetId,
               const std::string &label, const PropertyMap &properties);
std::optional<Edge> getEdge(const Graph &graph, EdgeId id);
bool updateEdge(Graph &graph, EdgeId id, const PropertyMap &properties);
bool deleteEdge(Graph &graph, EdgeId id);

void printGraph(const Graph &graph);
} // namespace GraphOps
