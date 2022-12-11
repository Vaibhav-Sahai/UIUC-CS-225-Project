#include <iostream>
#include "graph.hpp"

using namespace std;

int main() {
  // Graph g("Hello World!");
  std::vector<std::pair<std::string, std::string>> streamer_vect = csv2streamer("DatasetProcessing/streamer_features.csv");
	std::vector<std::pair<std::string, std::string>> edge_vect = csv2edge("DatasetProcessing/musae_ENGB_edges.csv");

  Graph g(streamer_vect, edge_vect);

  return 0;
}
