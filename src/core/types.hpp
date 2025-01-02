#pragma once

#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

using NodeId = int;
using EdgeId = int;
using PropertyValue = std::variant<int, double, std::string>;
using PropertyMap = std::unordered_map<std::string, PropertyValue>;

struct GraphError {
  std::string message;
  explicit GraphError(std::string msg) : message(std::move(msg)) {}
};

struct Node {
  NodeId id;
  PropertyMap properties;
  std::vector<EdgeId> outEdges, inEdges;
};

struct Edge {
  EdgeId id;
  NodeId sourceId, targetId;
  std::string label;
  PropertyMap properties;
};

struct Graph {
  std::unordered_map<NodeId, Node> nodes;
  std::unordered_map<EdgeId, Edge> edges;
  NodeId nextNodeId = 0;
  EdgeId nextEdgeId = 0;
};

struct BFSIterator {
  const Graph &graph;
  NodeId currentNode;
  std::vector<NodeId> queue;
  std::unordered_set<NodeId> visited;

  explicit BFSIterator(const Graph &g, NodeId startNode)
      : graph(g), currentNode(startNode) {
    if (graph.nodes.contains(startNode)) {
      queue.push_back(startNode);
      visited.insert(startNode);
    }
  }
};
