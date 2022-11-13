#include "graph.hpp"
#include <iostream>

Graph::Graph(std::string message) {
	std::cout << message << std::endl;
}


/*
 * Function to create a map of streamer name to alias ID
 * @param path_streamer_features: Path to streamer_features.csv
 * @param path_musae_ENGB_target: Path to musae_ENGB_target.csv
*/

void Graph::CreateStreamerToAliasMap(std::string path_streamer_features, std::string path_musae_ENGB_target) {
	// Open the files
	std::ifstream streamer_features(path_streamer_features);
	std::ifstream musae_ENGB_target(path_musae_ENGB_target);

	std::string line = "";

	// Skip the first line
	std::getline(streamer_features, line);

	while (std::getline(streamer_features, line)) {
		std::cout << "Line: " << line << std::endl;
		// Split the line by the comma
		std::string delimiter = ",";
		size_t pos = 0;
		std::string token;
		std::vector<std::string> tokens;

		while ((pos = line.find(delimiter)) != std::string::npos) {
			token = line.substr(0, pos);
			tokens.push_back(token);
			line.erase(0, pos + delimiter.length());
		}

		// Add the last token
		tokens.push_back(line);

		// Add the streamer name to new_id to the map
		streamer_to_alias[tokens[4]] = tokens[1];
	}
	std::cout << "Streamer to Alias Map Created" << std::endl;
	// // DEBUG:
	// std::cout << "Size of map: " << streamer_to_alias.size() << std::endl;
	// for (auto it = streamer_to_alias.begin(); it != streamer_to_alias.end(); ++it) {
	// 	std::cout << it->first << " => " << it->second << '\n';
	// }

}

/*
 * Function to create a map of game name to game ID
 * @param path_streamer_features: Path to streamer_features.csv
*/

void Graph::CreateGameToIDMap(std::string path_streamer_features) {
	// Open the file
	std::ifstream streamer_features(path_streamer_features);

	std::string line = "";

	// Skip the first line
	std::getline(streamer_features, line);

	while (std::getline(streamer_features, line)) {
		// Split the line by the comma
		std::string delimiter = ",";
		size_t pos = 0;
		std::string token;
		std::vector<std::string> tokens;

		while ((pos = line.find(delimiter)) != std::string::npos) {
			token = line.substr(0, pos);
			tokens.push_back(token);
			line.erase(0, pos + delimiter.length());
		}

		// Add the last token
		tokens.push_back(line);

		// Add the game name to game ID to the map
		game_to_game[tokens[2]] = tokens[3];
	}
	std::cout << "Game to ID Map Created" << std::endl;
	// // DEBUG:
	// std::cout << "Size of map: " << game_to_game.size() << std::endl;
	// for (auto it = game_to_game.begin(); it != game_to_game.end(); ++it) {
	// 	std::cout << it->first << " => " << it->second << '\n';
	// }
}

// Graph::Graph(const std::string& people_fpath) {
//     //
// }

// void Graph::SocialGraph(const std::vector<std::string> & vertices, std::vector<std::vector<std::string>>& relations) {
//     //
// }

// 1. load new_ids from musae_ENGB_target.csv (notstreamer_names from streamer_features.csv) into unordered_map 
//  - use ifstream library, getline to get each new line...
//  - use unordered_map(more efficient than normal map)
//  - maybe map notstreamer_names from streamer_features.csvs to respective ids from musae_ENGB_target.csv later
// 2. use ifstream, getline to go through each line's edges in musae_ENGB_edges.csv
// - add each opposing id of edge (2x) to the respective key's value set
// - rinse and repeat for all edges
// void Graph::populateAdjacencyGraph(std::string ids_fpath, std::string edges_fpath) {
//     //populate adjacency graph keys with new_ids
//     std::string line;
//     std::ifstream ifs_ids(ids_fpath);
//     if (ifs_ids.is_open()) {
//         auto temp = getline(ifs_ids.line); //get rid of first line (column headers)
//         while(getline(ifs_ids.line)) {
//             int curr_new_id = std::stoi(line.substr(line.find_last_of(',')+1,line.size())); //get new_id (happens to be last column)
//             _adjacency_graph[curr_new_id] = std::set<int>(); //initialize empty set of edges in to this pair's value
//         }
//         ifs_ids.close();
//     }

//     line = "";
//     //populate adjacency graph values with edges
//     std::ifstream ifs_edges(edges_fpath, std::ifstream::in);
//     if (ifs_edges.is_open()) {
//         auto temp = getline(ifs_edges.line); //get rid of first line (column headers)
//         while(getline(ifs_edges.line)) {
//             int first_id = std::stoi(line.substr(0,line.find_last_of(',')));
//             int second_id = std::stoi(line.substr(line.find_last_of(',')+1,line.size()));



// BFS queue
// creating a visited set
// add start_id to queue
// while queue is not empty
//  - pop front of queue
//  - if popped id is not in visited set
//      - add popped id to visited set
//      - add popped id's edges to queue
// return visited set

// std::set<int> Graph::BFS(int start_id) {
//     std::queue<int> bfs_queue;
//     std::set<int> visited;
//     bfs_queue.push(start_id);
//     while(!bfs_queue.empty()) {
//         int curr_id = bfs_queue.front();
//         bfs_queue.pop();
//         if (visited.find(curr_id) == visited.end()) {
//             visited.insert(curr_id);
//             auto curr_iter = _adjacency_graph.find(curr_id);
//             for (auto edge : curr_iter.second) {
//                 bfs_queue.push(edge);
//             }
//         }
//     }
//     return visited;
// }