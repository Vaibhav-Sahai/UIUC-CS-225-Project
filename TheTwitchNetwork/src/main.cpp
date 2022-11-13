#include <iostream>
#include "graph.hpp"

using namespace std;

int main() {
  Graph g("Hello World!");
  g.CreateStreamerToAliasMap("DatasetProcessing/streamer_features.csv", "DatasetProcessing/musae_ENGB_target.csv");
  g.CreateGameToIDMap("DatasetProcessing/streamer_features.csv");
  return 0;
}
