/*
Read in generated networks and calculate size of largest component

TODO: make a lite version to share on GitHub, all in one file (giant-lite)
TODO: keep developing this version, adding
  - Graph class in its own file, with Catch tests. Add exceptions to the library
  - Good style, C++ linting
  - Boost dependencies for connected components, command-line parsing
  - Other zero-one laws besides the giant component
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

int main(int argc, char* argv[]) {
  // parse command-line arguments
  string in_name = "network.out";
  string out_name = "giant.out";
  int n = 100;
  int k = 1;
  while (k < argc) {
    string arg = argv[k];
    if (arg == "-i") in_name = argv[k+1];
    else if (arg == "-o") out_name = argv[k+1];
    else if (arg == "-n") n = arg_to_int(argv[k+1]);
    else {
      cerr << "Unrecognized option: " << arg << endl;
      return 1;
    }
    k += 2;
  }
  cout << "n = " << n << endl;

  // std::ofstream fout;
  // fout.open(out_name);
  // for (int k = 0; k < edges.size(); ++k) {
  //   pedge e = edges[k];
  //   fout << e.p << " " << e.i << " " << e.j << endl;
  // }
  // fout.close();

  return 0;
}

  // Graph g(5);
  // cout << g.get_largest_component() << endl;  // 1
  // g.add_edge(0, 1);
  // cout << g.get_largest_component() << endl;  // 2
  // g.add_edge(1, 2);
  // cout << g.get_largest_component() << endl;  // 3
  // g.add_edge(3, 4);
  // cout << g.get_largest_component() << endl;  // 3
  // g.add_edge(0, 2);
  // cout << g.get_largest_component() << endl;  // 3
  // g.add_edge(1, 4);
  // cout << g.get_largest_component() << endl;  // 5
