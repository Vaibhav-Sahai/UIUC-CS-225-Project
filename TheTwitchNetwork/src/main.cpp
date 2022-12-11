#include <iostream>
#include "graph.hpp"

using namespace std;

int main() {
  // Graph g("Hello World!");
  std::vector<std::pair<std::string, std::string>> streamer_vect = csv2streamer("DatasetProcessing/streamer_features.csv");
	std::vector<std::pair<std::string, std::string>> edge_vect = csv2edge("DatasetProcessing/musae_ENGB_edges.csv");

  Graph g(streamer_vect, edge_vect);

  auto streamer_alias = g.GetStreamerToAliasMap();
  auto game_id = g.GetGameToGameMap();

  // Below, you can enter a game name and get the game id
  // For example, "Music" maps to "26936.0"
  // You can also enter a streamer name and get the alias id
  // For example, "Stephen_Bailey" maps to "2404"

  // An example of bfs traversal is shown below
  // You can uncomment the below lines to run bfs search on the graph

  // std::vector<Node> bfs_result = g.BFSPath(Node(streamer_alias[*Insert Name Here*], game_id[*Insert Game Here]), Node(streamer_alias[*Insert Name Here*], game_id[*Insert Game Here*]));
  // for (int i = 0; i < bfs_result.size(); i++) {
  //   std::cout << bfs_result[i].alias_id << " " << bfs_result[i].game_id << std::endl;
  // }

  // An example of kruskal traversal is shown below

  // std::vector<std::pair<Node, Node>> kruskal_result = g.KruskalPath(Node(streamer_alias[*Insert Name Here*], game_id[*Insert Game Here]), Node(streamer_alias[*Insert Name Here*], game_id[*Insert Game Here*]));

  // for (int i = 0; i < kruskal_result.size(); i++) {
  //   std::cout << kruskal_result[i].first.alias_id << " " << kruskal_result[i].first.game_id << " " << kruskal_result[i].second.alias_id << " " << kruskal_result[i].second.game_id << std::endl;
  // }

  // An example of pagerank is shown below

  // Node pagerank_result = g.FindMostPopularStreamer(game_id[*Insert Game Here*]);

  // std::cout << pagerank_result.alias_id << " " << pagerank_result.game_id << std::endl;


  return 0;
}
