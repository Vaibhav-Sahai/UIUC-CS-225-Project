#include "graph.hpp"

using namespace std;

Graph::Graph(const std::string& people_fpath) {
    //
}

void Graph::SocialGraph(const std::vector<std::string> & vertices, std::vector<std::vector<std::string>>& relations) {
    //
}

// 1. load new_ids from musae_ENGB_target.csv (notstreamer_names from streamer_features.csv) into unordered_map 
//  - use ifstream library, getline to get each new line...
//  - use unordered_map(more efficient than normal map)
//  - maybe map notstreamer_names from streamer_features.csvs to respective ids from musae_ENGB_target.csv later
// 2. use ifstream, getline to go through each line's edges in musae_ENGB_edges.csv
// - add each opposing id of edge (2x) to the respective key's value set
// - rinse and repeat for all edges
void populateAdjacencyGraph(std::string ids_fpath, std::string edges_fpath) {
    //populate adjacency graph keys with new_ids
    std::string line;
    std::ifstream ifs_ids(ids_fpath);
    if (ifs_ids.is_open()) {
        auto temp = getline(ifs_ids.line); //get rid of first line (column headers)
        while(getline(ifs_ids.line)) {
            int curr_new_id = std::stoi(line.substr(line.find_last_of(',')+1,line.size())); //get new_id (happens to be last column)
            _adjacency_graph[curr_new_id] = std::set<int>(); //initialize empty set of edges in to this pair's value
        }
        ifs_ids.close();
    }

    line = "";
    //populate adjacency graph values with edges
    std::ifstream ifs_edges(edges_fpath, std::ifstream::in);
    if (ifs_edges.is_open()) {
        auto temp = getline(ifs_edges.line); //get rid of first line (column headers)
        while(getline(ifs_edges.line)) {
            int first_id = std::stoi(line.substr(0,line.find_last_of(',')));
            int second_id = std::stoi(line.substr(line.find_last_of(',')+1,line.size()));
            
            auto first_iter = _adjacency_graph.find(first_id);
            first_iter.second.insert(second_id);

            auto second_iter = _adjacency_graph.find(second_id);
            second_iter.second.insert(first_id);
        }
        ifs_edges.close();
    }
}