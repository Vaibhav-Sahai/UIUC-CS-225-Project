#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <queue>
#include <algorithm>

#include <fstream>
#include <iostream>

// Struct that holds our node attributes
struct Node {
    std::string alias_id;
    std::string game_id;

    // Overload the == operator so we can compare two nodes
    bool operator==(const Node& other) const {
        return (alias_id == other.alias_id) && (game_id == other.game_id);
    }

    // Overload the < operator so we can overload std::less for Node
    bool operator<(const Node& other) const {
        return (alias_id < other.alias_id);
    }

    // constructor for Node
    Node(std::string alias_id, std::string game_id) {
        this->alias_id = alias_id;
        this->game_id = game_id;
    }

    // Default constructor for Node
    Node() {
        this->alias_id = "";
        this->game_id = "";
    }
};

class Graph {
    public:
        Graph(std::string message);
        // std::set<int> BFS(int start_id);
        void PopulateGraph();

        // Get adjacency list
        std::map<Node, std::vector<Node>> GetAdjList() const;

        // Get std::vector<Node> from Node
        std::vector<Node> GetNeighbors(Node node) const;

    private:
        // Map to hold streamer_name to alias ID 
        std::map<std::string, std::string> streamer_to_alias;
        // Map to hold game_name to game ID
        std::map<std::string, std::string> game_to_game;

        // Our adjacency list
        std::map<Node, std::vector<Node>> adj_list;


        // Private Helper
        void CreateStreamerToAliasMap(std::string path_streamer_features, std::string path_musae_ENGB_target);
        void CreateGameToIDMap(std::string path_streamer_features);

        void AddVertex(Node streamer);
        bool VertexInGraph(Node streamer);

        void AddEdge(std::string alias_id_1, std::string alias_id_2);
        Node GetNodeFromAlias(std::string alias_id);

        // Debug Func
        // Print the adjacency list
        void PrintAdjList();
};