#include "core/graphs.hpp"
#include <iostream>

void printDivider() { std::cout << "\n" << std::string(50, '=') << "\n"; }

void testBasicNodeOperations(Graph &graph) {
  std::cout << "TESTING BASIC NODE OPERATIONS\n";

  // Test node creation with different property types
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

  // Test node retrieval
  std::cout << "\nTesting node retrieval...\n";
  auto node1Data = GraphOps::getNode(graph, node1);
  if (node1Data) {
    std::cout << "Found node " << node1Data->id << "\n";
    std::cout << "Properties:\n";
    for (const auto &[key, value] : node1Data->properties) {
      std::cout << "  " << key << ": ";
      std::visit([](const auto &v) { std::cout << v; }, value);
      std::cout << '\n';
    }
  }

  // Test invalid node retrieval
  auto invalidNode = GraphOps::getNode(graph, 999);
  if (!invalidNode) {
    std::cout << "\nCorrectly couldn't find invalid node (ID: 999)\n";
  }

  // Test node update
  std::cout << "\nTesting node property update...\n";
  PropertyMap updatedProps = {{"name", std::string("Updated First Node")},
                              {"value", 50},
                              {"weight", 3.141592},
                              {"new_property", std::string("test")}};

  bool updateResult = GraphOps::updateNode(graph, node1, updatedProps);
  std::cout << "Node update result: " << (updateResult ? "success" : "failure")
            << "\n";

  // Verify update
  auto updatedNode = GraphOps::getNode(graph, node1);
  if (updatedNode) {
    std::cout << "Updated node properties:\n";
    for (const auto &[key, value] : updatedNode->properties) {
      std::cout << "  " << key << ": ";
      std::visit([](const auto &v) { std::cout << v; }, value);
      std::cout << '\n';
    }
  }
}

void testEdgeOperations(Graph &graph) {
  std::cout << "\nTESTING EDGE OPERATIONS\n";

  // Get existing nodes (assuming they exist from previous operations)
  NodeId node1 = 0;
  NodeId node2 = 1;
  NodeId node3 = 2;

  // Test edge creation with different properties
  PropertyMap edge1Props = {
      {"weight", 1.5}, {"type", std::string("direct")}, {"priority", 1}};
  PropertyMap edge2Props = {
      {"weight", 2.5}, {"type", std::string("indirect")}, {"priority", 2}};
  PropertyMap edge3Props = {
      {"weight", 3.0}, {"type", std::string("bidirectional")}, {"priority", 3}};

  try {
    std::cout << "Adding edges to the graph...\n";
    EdgeId edge1 =
        GraphOps::addEdge(graph, node1, node2, "CONNECTS_TO", edge1Props);
    EdgeId edge2 =
        GraphOps::addEdge(graph, node2, node3, "LEADS_TO", edge2Props);
    EdgeId edge3 =
        GraphOps::addEdge(graph, node3, node1, "RETURNS_TO", edge3Props);

    // Test edge retrieval
    std::cout << "\nTesting edge retrieval...\n";
    auto edge1Data = GraphOps::getEdge(graph, edge1);
    if (edge1Data) {
      std::cout << "Found edge " << edge1Data->id << " with label "
                << edge1Data->label << "\n";
      std::cout << "Edge properties:\n";
      for (const auto &[key, value] : edge1Data->properties) {
        std::cout << "  " << key << ": ";
        std::visit([](const auto &v) { std::cout << v; }, value);
        std::cout << '\n';
      }
    }

    // Test edge update
    std::cout << "\nTesting edge property update...\n";
    PropertyMap updatedEdgeProps = {{"weight", 4.0},
                                    {"type", std::string("updated")},
                                    {"priority", 10},
                                    {"new_edge_property", std::string("test")}};

    bool edgeUpdateResult =
        GraphOps::updateEdge(graph, edge1, updatedEdgeProps);
    std::cout << "Edge update result: "
              << (edgeUpdateResult ? "success" : "failure") << "\n";

    // Test invalid edge operations
    std::cout << "\nTesting invalid edge operations...\n";
    bool invalidEdgeUpdate = GraphOps::updateEdge(graph, 999, edge1Props);
    std::cout << "Invalid edge update result: "
              << (invalidEdgeUpdate ? "success" : "failure") << "\n";

    // Print current graph state
    std::cout << "\nCurrent graph state:\n";
    GraphOps::printGraph(graph);

    // Test edge deletion
    std::cout << "\nTesting edge deletion...\n";
    bool edgeDeleteResult = GraphOps::deleteEdge(graph, edge1);
    std::cout << "Edge deletion result: "
              << (edgeDeleteResult ? "success" : "failure") << "\n";

    // Test invalid edge deletion
    bool invalidEdgeDelete = GraphOps::deleteEdge(graph, 999);
    std::cout << "Invalid edge deletion result: "
              << (invalidEdgeDelete ? "success" : "failure") << "\n";
  } catch (const GraphError &e) {
    std::cerr << "Edge operation failed: " << e.message << "\n";
  }
}

void testBFSTraversal(Graph &graph) {
  std::cout << "\nTESTING BFS TRAVERSAL\n";

  try {
    // Create a new graph specifically for BFS testing
    Graph bfsGraph;

    // Create nodes
    PropertyMap nodeProps;
    NodeId node0 = GraphOps::addNode(bfsGraph, nodeProps);
    NodeId node1 = GraphOps::addNode(bfsGraph, nodeProps);
    NodeId node2 = GraphOps::addNode(bfsGraph, nodeProps);
    NodeId node3 = GraphOps::addNode(bfsGraph, nodeProps);
    NodeId node4 = GraphOps::addNode(bfsGraph, nodeProps);

    // Create edges to form a specific graph structure
    PropertyMap edgeProps;
    GraphOps::addEdge(bfsGraph, node0, node1, "EDGE", edgeProps);
    GraphOps::addEdge(bfsGraph, node0, node2, "EDGE", edgeProps);
    GraphOps::addEdge(bfsGraph, node1, node3, "EDGE", edgeProps);
    GraphOps::addEdge(bfsGraph, node2, node3, "EDGE", edgeProps);
    GraphOps::addEdge(bfsGraph, node2, node4, "EDGE", edgeProps);

    std::cout << "\nGraph structure for BFS:\n";
    GraphOps::printGraph(bfsGraph);

    std::cout << "\nPerforming BFS traversal starting from node 0:\n";
    GraphOps::bfsTraversal(bfsGraph, node0);

    std::cout << "\nTesting BFS Iterator:\n";
    auto it = GraphOps::bfsBegin(bfsGraph, node0);
    while (GraphOps::bfsHasNext(it)) {
      NodeId current = GraphOps::bfsNext(it);
      std::cout << "Visited node: " << current << "\n";
    }

    // Test BFS from non-existent node
    try {
      std::cout << "\nTesting BFS from non-existent node:\n";
      GraphOps::bfsTraversal(bfsGraph, 999);
    } catch (const GraphError &e) {
      std::cout << "Expected error caught: " << e.message << "\n";
    }

  } catch (const GraphError &e) {
    std::cerr << "BFS operation failed: " << e.message << "\n";
  }
}

void testNodeDeletion(Graph &graph) {
  std::cout << "\nTESTING NODE DELETION\n";

  // Print initial state
  std::cout << "Initial graph state:\n";
  GraphOps::printGraph(graph);

  // Test node deletion with existing edges
  NodeId nodeToDelete = 1; // Delete middle node
  std::cout << "\nDeleting node " << nodeToDelete << "...\n";
  bool nodeDeleteResult = GraphOps::deleteNode(graph, nodeToDelete);
  std::cout << "Node deletion result: "
            << (nodeDeleteResult ? "success" : "failure") << "\n";

  // Test invalid node deletion
  std::cout << "\nTesting invalid node deletion...\n";
  bool invalidNodeDelete = GraphOps::deleteNode(graph, 999);
  std::cout << "Invalid node deletion result: "
            << (invalidNodeDelete ? "success" : "failure") << "\n";

  // Print final state
  std::cout << "\nFinal graph state:\n";
  GraphOps::printGraph(graph);
}

int main() {
  try {
    Graph graph;

    printDivider();
    testBasicNodeOperations(graph);

    printDivider();
    testEdgeOperations(graph);

    printDivider();
    testBFSTraversal(graph);

    printDivider();
    testNodeDeletion(graph);

    printDivider();
    std::cout << "All tests completed successfully!\n";

  } catch (const GraphError &e) {
    std::cerr << "Fatal error occurred: " << e.message << "\n";
    return 1;
  } catch (const std::exception &e) {
    std::cerr << "Unexpected error occurred: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
