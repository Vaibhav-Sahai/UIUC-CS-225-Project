#pragma once

#include <vector>
#include <unordered_map>
#include <set>
#include <string>
#include <queue>
#include <algorithm>



#include <fstream>
#include <iostream>

using namespace std;

class Graph {
    public:
        Graph(const std::string& people_fpath);
        void SocialGraph(const std::vector<std::string>& vertices, std::vector<std::vector<std::string>>& relations);
        void populateAdjacencyGraph(std::string ids_fpath, std::string edges_fpath);
        std::set<int> BFS(int start_id);

    private:
        std::unordered_map<int,std::set<int>> _adjacency_graph;
};