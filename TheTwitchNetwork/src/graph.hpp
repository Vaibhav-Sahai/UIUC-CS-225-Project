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

    // Overload the != operator so we can compare two nodes
    bool operator!=(const Node& other) const {
        return !(*this == other);
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

        std::vector<Node> BFSPath(Node start, Node end);

        std::vector<Node> FindMostPopularStreamers(int num_streamers);

        Node PageRank(std::string game_name);

        void Kruskal(std::string game_name); 

        // Out here for test reasons
        void AddVertex(Node streamer);
        bool VertexInGraph(Node streamer);

    private:
        // Map to hold streamer_name to alias ID 
        std::map<std::string, std::string> streamer_to_alias;
        // Map to hold game_name to game ID
        std::map<std::string, std::string> game_to_game;
        // Our adjacency list
        std::map<Node, std::vector<Node>> adj_list;
        // Edges in our graph
        std::vector<std::pair<Node, Node>> edges;
        // Map a streamerid to an unique int
        std::map<std::string, int> streamer_to_int;



        // Private Helper
        void CreateStreamerToAliasMap(std::string path_streamer_features, std::string path_musae_ENGB_target);
        void CreateGameToIDMap(std::string path_streamer_features);

        void AddEdge(std::string alias_id_1, std::string alias_id_2);
        Node GetNodeFromAlias(std::string alias_id);

        void StreamerHash();

        // Debug Func
        // Print the adjacency list
        void PrintAdjList();
};
// Disjoint Set using string instead of int

class DisjointSets {
    public:
        DisjointSets();
        DisjointSets(int num_nodes);
        int Find(int node);
        void Union(int node1, int node2);
        int GetNumSets();
        void addelements(int num);
        int size(int elem);
    private:
        std::vector<int> parent;
        std::vector<int> rank;
        int num_sets;
};