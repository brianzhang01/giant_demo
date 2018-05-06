/*
Generate networks to be used for giant component analysis
*/
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

bool cmp_pedge(const pedge& first, const pedge& second) {
  return first.p < second.p;
}

int main(int argc, char* argv[]) {
  // parse command-line arguments
  string out_name = "network.out";
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

  std::default_random_engine rng(seed);
  std::uniform_real_distribution<double> dist(0.0, 1.0);

  double thresh = ceil(log(1.0*n)) / (n - 1.0);
  vector<pedge> edges;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      double value = dist(rng);
      if (value < thresh) {
        pedge e;
        e.i = i;
        e.j = j;
        e.p = value;
        edges.push_back(e);
      }
    }
  }
  // sort the edges
  std::sort(edges.begin(), edges.end(), cmp_pedge);

  std::ofstream fout;
  fout.open(out_name);
  for (int k = 0; k < edges.size(); ++k) {
    pedge e = edges[k];
    fout << e.p << " " << e.i << " " << e.j << endl;
  }
  fout.close();

  return 0;
}
