/*
Generate random networks and calculate the giant component size at different thresholds

This implementation uses a union-find data structure for its graph operations,
implemented in graph.cpp and graph.hpp
*/
#include "graph.hpp"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int arg_to_int(char* arg) {
  string next = arg;
  return atoi(next.c_str());
}

// an edge with a probability
struct pedge {
  int i, j;
  double p;
};

// comparison function for edges
bool cmp_pedge(const pedge& first, const pedge& second) {
  return first.p < second.p;
}

int main(int argc, char* argv[]) {
  // parse command-line arguments
  string out_name = "giant.out";
  int n = 100, seed = 0;
  int k = 1;
  while (k < argc) {
    string arg = argv[k];
    if (arg == "-o") out_name = argv[k+1];
    else if (arg == "-n") n = arg_to_int(argv[k+1]);
    else if (arg == "-s") seed = arg_to_int(argv[k+1]);
    else {
      cerr << "Unrecognized option: " << arg << endl;
      return 1;
    }
    k += 2;
  }
  cout << "n = " << n << ", seed = " << seed << endl;

  // define thresholds to compute giant component size at
  // the quantities threshold*(n-1) go from steps of 0.1 from 0.1 to 1.5, then
  // in steps of 0.5 from 1.5 to ceil(log(n))
  vector<double> mean_degrees;
  for (int i = 0; i <= 15; ++i) {
    mean_degrees.push_back(0.1 * i);
  }
  for (int i = 4; i <= ceil(log(1.0*n))*2; ++i) {
    mean_degrees.push_back(0.5 * i);
  }
  vector<double> thresholds;
  for (int i = 0; i < mean_degrees.size(); ++i) {
    thresholds.push_back(mean_degrees[i] / (n - 1.0));
  }

  // simulate a probability for each of the (n choose 2) edges in the graph
  // only keep edges with probability below the max threshold, to cut down on
  // memory
  std::default_random_engine rng(seed);
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  double max_thresh = thresholds[thresholds.size() - 1];
  vector<pedge> edges;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      double value = dist(rng);
      if (value < max_thresh) {
        pedge e;
        e.i = i;
        e.j = j;
        e.p = value;
        edges.push_back(e);
      }
    }
  }

  // sort the kept edges in increasing order of probability
  std::sort(edges.begin(), edges.end(), cmp_pedge);

  // successively add edges to the graph, and at the thresholds, compute
  // the giant component sizes
  double p;
  int a, b;
  k = 0;
  vector<int> giant_sizes;
  Graph g(n);
  for (int i = 0; i < edges.size(); ++i) {
    pedge e = edges[i];
    while (e.p >= thresholds[k]) {
      giant_sizes.push_back(g.get_largest_component());
      ++k;
    }
    g.add_edge(e.i, e.j);
  }
  while (k < thresholds.size()) {
    giant_sizes.push_back(g.get_largest_component());
    ++k;
  }

  // write output
  std::ofstream fout;
  fout.open(out_name);
  for (int i = 0; i < mean_degrees.size(); ++i) {
    fout << mean_degrees[i] << " " << giant_sizes[i] << endl;
  }
  fout.close();

  return 0;
}
