#include "graph.hpp"
#include <iostream>


/*
 * Parameterized constructor for Graph
 * @param streamers: Vector of streamer names paired with game_id
 * @param edges: Vector of edges
*/
Graph::Graph(std::vector<std::pair<std::string, std::string>> streamers, std::vector<std::pair<std::string, std::string>> edges) {
	this->CreateStreamerToAliasMap("DatasetProcessing/streamer_features.csv", "DatasetProcessing/musae_ENGB_target.csv");
  	this->CreateGameToIDMap("DatasetProcessing/streamer_features.csv");
	// Iterate through the streamers vector and add each streamer to the graph
	for (unsigned int i = 0; i < streamers.size(); i++) {
		Node streamer(streamers[i].first, streamers[i].second);
		this->AddVertex(streamer);
	}

	// Iterate through the edges vector and add each edge to the graph
	for (unsigned int i = 0; i < edges.size(); i++) {
		this->AddEdge(edges[i].first, edges[i].second);
	}
	this->StreamerHash();

	// DEBUG:
	// std::cout << "Size of adj_list: " << adj_list.size() << std::endl;
	// this->PrintAdjList();
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
	// std::cout << "Size of adj list: " << adj_list.size() << std::endl;

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
	// PrintAdjList();
	std::cout << "Size of adj list: " << adj_list.size() << std::endl;

	// We also can populate the streamer hash map here
	this->StreamerHash();
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

	edges.push_back(std::make_pair(streamer_1, streamer_2));

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
	// Loop through all keys in adj list
	for (auto it = adj_list.begin(); it != adj_list.end(); ++it) {
		if (it->first.alias_id == alias_id) {
			return it->first;
		}
	}
	std::cout << "Alias ID: " << alias_id << std::endl;
	throw std::invalid_argument("Streamer not in graph");
}

/*
* Function to get adjacency list
*/

 std::map<Node, std::vector<Node>> Graph::GetAdjList() const {
	return adj_list;
}

/*
* Function to get std::vector<Node> from Node
*/

 std::vector<Node> Graph::GetNeighbors(Node node) const {
	return adj_list.at(node);
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

/*
 * Function to find the shortest path between two nodes
 * @param start: The starting node
 * @param end: The ending node
 * @return: A BFS tree that contains the shortest path between the start and end nodes
*/

std::vector<Node> Graph::BFSPath(Node start, Node end) {
	std::queue<Node> q;
	std::map<Node, bool> visited;
	std::map<Node, Node> parent;
	
	// initialize visited map
	for (auto it = adj_list.begin(); it != adj_list.end(); ++it) {
		visited[it->first] = false;
		parent[it->first] = Node();
	}

	// add start node to queue
	q.push(start);
	visited[start] = true;

	while (!q.empty()) {
		Node curr = q.front();
		q.pop();
		auto neighbors = GetNeighbors(curr);
		for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
			if (!visited[*it]) {
				visited[*it] = true;
				q.push(*it);
				parent[*it] = curr;
			}

			if (*it == end) {
				break;
			}
		}
	}

	std::vector<Node> path;
	while(parent[end] != Node()) {
		path.push_back(end);
		end = parent[end];
	}

	// Reverse the path
	std::reverse(path.begin(), path.end());
	return path;
}

// Pagerank to return node with most connections given a game name
Node Graph::PageRank(std::string game_name) {
	//get node from given game name
	Node game_node = GetNodeFromAlias(game_name);

	//get all neighbors of game node
	std::vector<Node> neighbors = GetNeighbors(game_node);

	Node popular;

	//get most popular neighbor
	for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
		if (it->alias_id == game_name) {
			continue;
		}
		if (it->alias_id == popular.alias_id) {
			continue;
		}
		if (it->alias_id != popular.alias_id) {
			if (GetNeighbors(*it).size() > GetNeighbors(popular).size()) {
				popular = *it;
			}
		}
	}

	return popular;
}


/*
 * Function to create kruskal mst
 * @param game_name: The name of the game to create the mst for
 * @return: A vector of edges that make up the mst
*/
std::vector<std::pair<Node, Node>> Graph::Kruskal(std::string game_name) {
	std::vector<std::pair<Node, Node>> mst;
	DisjointSets ds(adj_list.size());

	for (auto it = edges.begin(); it != edges.end(); ++it) {
		Node u = it->first;
		Node v = it->second;
 		// only add edge if both nodes are in the game
		if (u.game_id == game_name && v.game_id == game_name) {
			int set_u = ds.Find(streamer_to_int[u.alias_id]);
			int set_v = ds.Find(streamer_to_int[v.alias_id]);

			if (set_u != set_v) {
				mst.push_back(std::make_pair(u, v));
				// Print out the edge
				// std::cout << u.alias_id << "-" << v.alias_id << std::endl;
				ds.Union(set_u, set_v);
			} 
		}

	}
	return mst;
}

/*
 * Functions to get streamer alias map
*/

std::map<std::string, std::string> Graph::GetStreamerToAliasMap() const {
	return streamer_to_alias;
}
std::map<std::string, std::string> Graph::GetGameToGameMap() const {
	return game_to_game;
}

void Graph::StreamerHash() {
	// Iterate through all streamers in the graph and default value to -1
	for(auto it = adj_list.begin(); it != adj_list.end(); ++it) {
		streamer_to_int[it->first.alias_id] = -1;
	}

	// convert streamer to int
	int i = 0;
	for(auto it = adj_list.begin(); it != adj_list.end(); ++it) {
		streamer_to_int[it->first.alias_id] = i;
		i++;
	}

	// // print out the map
	// for(auto it = streamer_to_int.begin(); it != streamer_to_int.end(); ++it) {
	// 	std::cout << it->first << " " << it->second << std::endl;
	// }
}

/*
 * Function to take a csv path and convert it to a vector of pairs
 * @param path: The path to the csv file
 * @return: A vector of pairs that contains the streamer and game
*/
std::vector<std::pair<std::string, std::string>> csv2streamer(std::string path) {
	std::ifstream streamer_features(path);
	std::string line = "";

	std::vector<std::pair<std::string, std::string>> streamers;

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
		streamers.push_back(std::make_pair(line, tokens[2]));
	}
	return streamers;
}

/*
 * Function to take a csv path for edges and convert it to a vector of pairs
 * @param path: The path to the csv file
 * @return: A vector of pairs that contains the streamer and game
*/

std::vector<std::pair<std::string, std::string>> csv2edge(std::string path) {
	std::ifstream streamer_features(path);
	std::string line = "";

	std::vector<std::pair<std::string, std::string>> edges;

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
		edges.push_back(std::make_pair(tokens[0], tokens[1]));
	}
	return edges;
}

/*
* Implementing Disjoint Set
*/

DisjointSets::DisjointSets(int n) {
	for (int i = 0; i < n; i++) {
		parent.push_back(i);
		rank.push_back(-1);
	}
}

int DisjointSets::Find(int node) {
	if (parent[node] != node) {
		parent[node] = Find(parent[node]);
	}
	return parent[node];
}

void DisjointSets::Union(int node1, int node2) {
	int parent1 = Find(node1);
	int parent2 = Find(node2);

	if (rank[parent1] > rank[parent2]) {
		parent[parent2] = parent1;
	}
	else if (rank[parent1] < rank[parent2]) {
		parent[parent1] = parent2;
	}
	else {
		parent[parent2] = parent1;
		rank[parent1]++;
	}
}

int DisjointSets::GetNumSets() {
	int num_sets = 0;
	for (int i = 0; i < parent.size(); i++) {
		if (parent[i] == i) {
			num_sets++;
		}
	}
	return num_sets;
}