# Synapse

A lightweight, in-memory graph database implementation in C++20.

## Overview
Synapse is a graph database that runs entirely in memory, offering fast operations for managing nodes, edges, and their properties. It supports various data types and traversal algorithms.

## Quick Start

### Prerequisites
- C++20 compatible compiler
- Make sure you have g++ installed

### Building
```bash
g++ -std=c++20 src/core/graphs.cpp src/main.cpp -o graph
```

### Running
```bash
./graph
```

## Features
- Node creation, deletion, and updates
- Edge management with labels and properties
- Property support for integers, doubles, and strings
- Breadth-First Search (BFS) traversal
- Comprehensive error handling

## Project Status
🚧 **Under Active Development** - More features coming soon!
