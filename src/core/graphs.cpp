#include "graphs.hpp"
#include <algorithm>
#include <functional>
#include <iostream>

namespace GraphOps {
NodeId addNode(Graph &graph, const PropertyMap &properties) {
  NodeId newId = graph.nextNodeId++;
  Node newNode = {
      .id = newId, .properties = properties, .outEdges = {}, .inEdges = {}};
  graph.nodes.insert({newId, newNode});
  return newId;
}

std::optional<Node> getNode(const Graph &graph, NodeId id) {
  auto it = graph.nodes.find(id);
  if (it != graph.nodes.end()) {
    return it->second;
  } else {
    return std::nullopt;
  }
}

bool updateNode(Graph &graph, NodeId id, const PropertyMap &properties) {
  auto it = graph.nodes.find(id);
  if (it != graph.nodes.end()) {
    it->second.properties = properties;
    return true;
  } else
    return false;
}

bool deleteNode(Graph &graph, NodeId id) {
  auto nodeIt = graph.nodes.find(id);
  if (nodeIt == graph.nodes.end()) {
    return false;
  }
  for (EdgeId edgeId : nodeIt->second.outEdges) {
    graph.edges.erase(edgeId);
  }
  for (EdgeId edgeId : nodeIt->second.inEdges) {
    graph.edges.erase(edgeId);
  }
  graph.nodes.erase(id);
  return true;
}

EdgeId addEdge(Graph &graph, NodeId souceNode, NodeId targetNode,
               const std::string &label, const PropertyMap &properties) {
  if (graph.nodes.find(souceNode) == graph.nodes.end() ||
      graph.nodes.find(targetNode) == graph.nodes.end()) {
    throw GraphError("Source or Target Node not found!");
  }

  EdgeId newId = graph.nextEdgeId++;
  Edge newEdge = {.id = newId,
                  .sourceId = souceNode,
                  .targetId = targetNode,
                  .label = label,
                  .properties = properties};

  graph.nodes[souceNode].outEdges.push_back(newId);
  graph.nodes[targetNode].inEdges.push_back(newId);

  graph.edges.insert({newId, newEdge});
  return newId;
}

std::optional<Edge> getEdge(const Graph &graph, EdgeId id) {
  auto it = graph.edges.find(id);
  if (it != graph.edges.end()) {
    return it->second;
  } else {
    return std::nullopt;
  }
}

bool updateEdge(Graph &graph, EdgeId id, const PropertyMap &properties) {
  auto it = graph.edges.find(id);
  if (it != graph.edges.end()) {
    it->second.properties = properties;
    return true;
  } else {
    return false;
  }
}

bool deleteEdge(Graph &graph, EdgeId id) {
  auto edgeIt = graph.edges.find(id);
  if (edgeIt == graph.edges.end()) {
    return false;
  }

  auto &sourceNode = graph.nodes[edgeIt->second.sourceId];
  auto outIt =
      std::find(sourceNode.outEdges.begin(), sourceNode.outEdges.end(), id);
  if (outIt != sourceNode.outEdges.end()) {
    sourceNode.outEdges.erase(outIt);
  }

  auto &targetNode = graph.nodes[edgeIt->second.targetId];
  auto inIt =
      std::find(targetNode.inEdges.begin(), targetNode.inEdges.end(), id);
  if (inIt != targetNode.inEdges.end()) {
    targetNode.inEdges.erase(inIt);
  }

  graph.edges.erase(id);
  return true;
}

void printGraph(const Graph &graph) {
  std::cout << "Nodes:\n";
  for (const auto &[id, node] : graph.nodes) {
    std::cout << "Node " << id << ":\n";
    std::cout << "  Propertes: \n";
    for (const auto &[key, value] : node.properties) {
      std::cout << "    " << key << ": ";
      std::visit([](const auto &v) { std::cout << v; }, value);
      std::cout << '\n';
    }

    std::cout << "  Outgoing edges: ";
    for (EdgeId edgeId : node.outEdges) {
      std::cout << edgeId << " ";
    }
    std::cout << "\n  Incoming edges: ";
    for (EdgeId edgeId : node.inEdges) {
      std::cout << edgeId << " ";
    }
    std::cout << '\n';
  }

  std::cout << "\nEdges:\n";
  for (const auto &[id, edge] : graph.edges) {
    std::cout << "Edge " << id << " (" << edge.sourceId << " -> "
              << edge.targetId << ") Label: " << edge.label << "\n";
    std::cout << "  Properties:\n";
    for (const auto &[key, value] : edge.properties) {
      std::cout << "    " << key << ": ";
      std::visit([](const auto &v) { std::cout << v; }, value);
      std::cout << '\n';
    }
  }
}

std::vector<NodeId> getNeighbors(const Graph &graph, NodeId nodeId) {
  std::vector<NodeId> neighbors;
  auto nodeIt = graph.nodes.find(nodeId);
  if (nodeIt != graph.nodes.end()) {
    for (EdgeId edgeId : nodeIt->second.outEdges) {
      const auto &edge = graph.edges.at(edgeId);
      neighbors.push_back(edge.targetId);
    }
  }
  return neighbors;
}

void bfsTraversal(const Graph &graph, NodeId startNode) {
  if (!graph.nodes.contains(startNode)) {
    throw GraphError("Start node not found!");
  }
  std::queue<NodeId> queue;
  std::unordered_set<NodeId> visited;

  queue.push(startNode);
  visited.insert(startNode);

  while (!queue.empty()) {
    NodeId current = queue.front();
    queue.pop();
    std::cout << current << "\n";
    for (NodeId neighbor : getNeighbors(graph, current)) {
      if (visited.find(neighbor) == visited.end()) {
        queue.push(neighbor);
        visited.insert(neighbor);
      }
    }
  }
}

BFSIterator bfsBegin(const Graph &graph, NodeId startNode) {
  return BFSIterator(graph, startNode);
}

bool bfsHasNext(BFSIterator &it) { return !it.queue.empty(); }

NodeId bfsNext(BFSIterator &it) {
  if (it.queue.empty()) {
    throw GraphError("No more nodes to visit!");
  }
  NodeId current = it.queue.front();
  it.queue.erase(it.queue.begin());
  it.currentNode = current;

  for (NodeId neighbor : getNeighbors(it.graph, current)) {
    if (it.visited.find(neighbor) == it.visited.end()) {
      it.queue.push_back(neighbor);
      it.visited.insert(neighbor);
    }
  }
  return current;
}

} // namespace GraphOps
