#include "src/core/graphs.hpp"
#include <iostream>

int main() {
  Graph graph;

  PropertyMap node1_props = {{"name", std::string("Alice")}, {"age", 30}};
  PropertyMap node2_props = {{"name", std::string("Bob")}, {"age", 25}};

  NodeId node1_id = GraphOps::addNode(graph, node1_props);
  NodeId node2_id = GraphOps::addNode(graph, node2_props);

  PropertyMap edge_props = {{"since", 2020}, {"strength", 0.8}};

  EdgeId edge_id =
      GraphOps::addEdge(graph, node1_id, node2_id, "KNOWS", edge_props);

  GraphOps::printGraph(graph);

  node1_props["age"] = 31;
  GraphOps::updateNode(graph, node1_id, node1_props);

  GraphOps::deleteEdge(graph, edge_id);

  std::cout << "\nAfter updates:\n";
  GraphOps::printGraph(graph);

  return 0;
}
