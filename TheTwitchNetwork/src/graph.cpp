#include "graph.hpp"
#include <iostream>

Graph::Graph(std::string message) {
	std::cout << message << std::endl;
	this->CreateStreamerToAliasMap("DatasetProcessing/streamer_features.csv", "DatasetProcessing/musae_ENGB_target.csv");
  	this->CreateGameToIDMap("DatasetProcessing/streamer_features.csv");
	this->PopulateGraph();
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

/*
 * Function to populate the graph with nodes and edges
*/

void Graph::PopulateGraph() {
	// open streamer_features.csv and read the game_id and new_id columns
	std::ifstream streamer_features("DatasetProcessing/streamer_features.csv");
	std::string line = "";

	// Skip the first line
	std::getline(streamer_features, line);

	while (std::getline(streamer_features, line)) {
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

		// Create the node, add it to the graph
		// alias_id is always the last element in our sentence, so we can use line for that
		// game_id is always the 3rd element in our array
		// NOTE: We would've to deal with ',' if this arrangement ever changes
		Node node(line, tokens[2]);
		this->AddVertex(node);
		
	}
	std::cout << "Nodes Added" << std::endl;
	std::cout << "Size of adj list: " << adj_list.size() << std::endl;

	// use musae_ENGB_edges.csv to add edges to the graph

	std::ifstream musae_ENGB_edges("DatasetProcessing/musae_ENGB_edges.csv");

	// Skip the first line
	std::getline(musae_ENGB_edges, line);

	while (std::getline(musae_ENGB_edges, line)) {
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

		// Add the edge to the graph
		this->AddEdge(tokens[0], tokens[1]);
	}
	// DEBUG:
	PrintAdjList();
	std::cout << "Size of adj list: " << adj_list.size() << std::endl;
}

/*
 * Function to add a vertex to the graph
 * @param streamer: Node struct that holds the streamer's alias ID and game ID
 * throws: std::invalid_argument if the streamer is already in the graph
*/

void Graph::AddVertex(Node streamer) {
	if (VertexInGraph(streamer)) {
		std::cout << streamer.alias_id << std::endl;
		throw std::invalid_argument("Streamer already in graph");
	}
	// std::cout << "Adding " << streamer.alias_id << std::endl;
	adj_list[streamer] = std::vector<Node>(); // Create an empty adj list for the streamer
	// check if added correctly
	// std::cout << adj_list.size() << std::endl;
}

/*
 * Function to check if a vertex is in the graph
 * @param streamer: Node struct that holds the streamer's alias ID and game ID
 * @return: True if the streamer is in the graph, false otherwise
*/

bool Graph::VertexInGraph(Node streamer) {
	// Loop through all keys in adj list, dont use iterators
	for (auto it = adj_list.begin(); it != adj_list.end(); ++it) {
		if (it->first.alias_id == streamer.alias_id) {
			// std::cout << "First alias: " << it->first.alias_id << std::endl;
			// std::cout << "Second alias: " << streamer.alias_id << std::endl;
			return true;
		}
	}
	return false;
}

/*
 * Function to add an edge to the graph
 * @param alias_id_1: The alias ID of the first streamer
 * @param alias_id_2: The alias ID of the second streamer
*/

void Graph::AddEdge(std::string alias_id_1, std::string alias_id_2) {
	// Check if both streamers are in the graph
	Node streamer_1 = GetNodeFromAlias(alias_id_1);
	Node streamer_2 = GetNodeFromAlias(alias_id_2);

	// Add the edge to the graph
	adj_list[streamer_1].push_back(streamer_2);
	adj_list[streamer_2].push_back(streamer_1);
}

/*
 * Function to get a node from an alias ID
 * @param alias_id: The alias ID of the streamer
 * @return: The node with the given alias ID
 * throws: std::invalid_argument if the streamer is not in the graph
*/

Node Graph::GetNodeFromAlias(std::string alias_id) {
	// Loop through all keys in adj list, dont use iterators
	for (auto it = adj_list.begin(); it != adj_list.end(); ++it) {
		if (it->first.alias_id == alias_id) {
			return it->first;
		}
	}
	std::cout << "Alias ID: " << alias_id << std::endl;
	throw std::invalid_argument("Streamer not in graph");
}

/* 
 * Function to print the adj list
*/

void Graph::PrintAdjList() {
	for (auto it = adj_list.begin(); it != adj_list.end(); ++it) {
		// second arg is a vector of nodes, so we need to iterate through that
		std::cout << "Alias_ID: " << it->first.alias_id << ", " << "Game_ID: " << it->first.game_id << " => " << std::endl;
		for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
			std::cout << it2->alias_id << " " << std::endl;
		}
	}
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