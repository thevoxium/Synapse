#include "core/graphs.hpp"
#include <iostream>

int main() {
  Graph graph;

  PropertyMap node1Props = {
      {"name", std::string("First Node")}, {"value", 42}, {"weight", 3.14}};

  PropertyMap node2Props = {
      {"name", std::string("Second Node")}, {"value", 100}, {"weight", 2.718}};

  PropertyMap node3Props = {
      {"name", std::string("Third Node")}, {"value", 200}, {"weight", 1.618}};

  std::cout << "Adding nodes to the graph...\n";
  NodeId node1 = GraphOps::addNode(graph, node1Props);
  NodeId node2 = GraphOps::addNode(graph, node2Props);
  NodeId node3 = GraphOps::addNode(graph, node3Props);

  std::cout << "\nTesting getNode...\n";
  auto node1Data = GraphOps::getNode(graph, node1);
  if (node1Data) {
    std::cout << "Found node " << node1Data->id << "\n";
  }

  auto invalidNode = GraphOps::getNode(graph, 999);
  if (!invalidNode) {
    std::cout << "Correctly couldn't find invalid node\n";
  }

  std::cout << "\nTesting node update...\n";
  PropertyMap updatedProps = {{"name", std::string("Updated First Node")},
                              {"value", 50},
                              {"weight", 3.141592}};

  bool updateResult = GraphOps::updateNode(graph, node1, updatedProps);
  std::cout << "Node update result: " << (updateResult ? "success" : "failure")
            << "\n";

  std::cout << "\nAdding edges to the graph...\n";
  PropertyMap edge1Props = {{"weight", 1.5}, {"type", std::string("direct")}};

  PropertyMap edge2Props = {{"weight", 2.5}, {"type", std::string("indirect")}};

  try {
    EdgeId edge1 =
        GraphOps::addEdge(graph, node1, node2, "CONNECTS_TO", edge1Props);
    EdgeId edge2 =
        GraphOps::addEdge(graph, node2, node3, "LEADS_TO", edge2Props);

    std::cout << "\nTesting getEdge...\n";
    auto edge1Data = GraphOps::getEdge(graph, edge1);
    if (edge1Data) {
      std::cout << "Found edge " << edge1Data->id << " with label "
                << edge1Data->label << "\n";
    }

    std::cout << "\nTesting edge update...\n";
    PropertyMap updatedEdgeProps = {{"weight", 3.0},
                                    {"type", std::string("updated")}};

    bool edgeUpdateResult =
        GraphOps::updateEdge(graph, edge1, updatedEdgeProps);
    std::cout << "Edge update result: "
              << (edgeUpdateResult ? "success" : "failure") << "\n";

    std::cout << "\nPrinting complete graph:\n";
    GraphOps::printGraph(graph);

    std::cout << "\nTesting edge deletion...\n";
    bool edgeDeleteResult = GraphOps::deleteEdge(graph, edge1);
    std::cout << "Edge deletion result: "
              << (edgeDeleteResult ? "success" : "failure") << "\n";

    std::cout << "\nTesting invalid edge deletion...\n";
    bool invalidEdgeDelete = GraphOps::deleteEdge(graph, 999);
    std::cout << "Invalid edge deletion result: "
              << (invalidEdgeDelete ? "success" : "failure") << "\n";

    std::cout << "\nTesting node deletion...\n";
    bool nodeDeleteResult = GraphOps::deleteNode(graph, node1);
    std::cout << "Node deletion result: "
              << (nodeDeleteResult ? "success" : "failure") << "\n";

    std::cout << "\nFinal graph state:\n";
    GraphOps::printGraph(graph);

  } catch (const GraphError &e) {
    std::cerr << "Graph operation failed: " << e.message << "\n";
    return 1;
  }

  return 0;
}
