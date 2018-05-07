/*
Graph class for connected components
*/
#include "graph.hpp"

// Constructor
// TODO: copy constructor?
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
  max_size = 1;
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
      max_size = std::max(max_size, sizes[a]);
    }
    else {
      parents[a] = b;
      sizes[b] += sizes[a];
      max_size = std::max(max_size, sizes[b]);
    }
  }
}
