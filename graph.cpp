/*
Graph class for connected components
*/
#include "graph.hpp"

// Constructor
Graph::Graph(int _n) : n(_n) {
  parents.resize(n);
  sizes.resize(n);
  clear_edges();
}

void Graph::clear_edges() {
  for (int i = 0; i < n; ++i) {
    parents[i] = i;
    sizes[i] = 1;
  }
}

// Adds an edge using union by size
// Does nothing if the edge already exists
// TODO: throw an exception if a or b are out of bounds
void Graph::add_edge(int a, int b) {
  while (parents[a] != a) {
    a = parents[a];
  }
  while (parents[b] != b) {
    b = parents[b];
  }
  if (a != b) {
    if (sizes[a] >= sizes[b]) {
      parents[b] = a;
      sizes[a] += sizes[b];
    }
    else {
      parents[a] = b;
      sizes[b] += sizes[a];
    }
  }
}

int Graph::get_largest_component() {
  int max_size = 0;
  for (int i = 0; i < n; ++i) {
    if (parents[i] == i) {
      max_size = std::max(sizes[i], max_size);
    }
  }
  return max_size;
}
