/*
Read in generated networks and calculate size of largest component
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

  vector<double> ratios;
  for (int i = 0; i <= 15; ++i) {
    ratios.push_back(0.1 * i);
  }
  for (int i = 4; i <= ceil(log(1.0*n))*2; ++i) {
    ratios.push_back(0.5 * i);
  }

  vector<double> thresholds;
  for (int i = 0; i < ratios.size(); ++i) {
    thresholds.push_back(ratios[i] / (n - 1.0));
  }

  std::ifstream fin;
  fin.open(in_name);

  double p;
  int a, b;
  k = 0;
  vector<int> max_sizes;
  Graph g(n);
  while (fin >> p >> a >> b) {
    while (p >= thresholds[k]) {
      max_sizes.push_back(g.get_largest_component());
      ++k;
    }
    g.add_edge(a, b);
  }
  while (k < thresholds.size()) {
    max_sizes.push_back(g.get_largest_component());
    ++k;
  }

  std::ofstream fout;
  fout.open(out_name);
  for (int i = 0; i < ratios.size(); ++i) {
    fout << ratios[i] << " " << max_sizes[i] << endl;
  }
  fout.close();

  return 0;
}
