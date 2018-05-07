// Tests for graph.cpp / graph.hpp
#include "catch.hpp"
#include "graph.hpp"

TEST_CASE("A simple graph with 5 vertices", "[simple]") {
  Graph g(5);
  REQUIRE(g.get_largest_component() == 1);
  g.add_edge(0, 1);
  REQUIRE(g.get_largest_component() == 2);
  g.add_edge(1, 2);
  REQUIRE(g.get_largest_component() == 3);
  g.add_edge(3, 4);
  REQUIRE(g.get_largest_component() == 3);
  g.add_edge(0, 2);
  REQUIRE(g.get_largest_component() == 3);
  g.add_edge(1, 4);
  REQUIRE(g.get_largest_component() == 5);
  g.clear_edges();
  REQUIRE(g.get_largest_component() == 1);
}
