/*
Graph class for connected components
*/
#ifndef __GRAPH_HPP_
#define __GRAPH_HPP_

#include <algorithm>
#include <vector>

using std::vector;

// Graph class for connected components
// Uses a union-find data structure
class Graph {
public:
  Graph(int _n);
  void clear_edges();
  void add_edge(int a, int b);
  int get_largest_component() { return max_size; }
  int size() { return n; }
private:
  int n;
  int max_size;
  vector<int> parents;
  vector<int> sizes;
};

#endif  // __GRAPH_HPP_
