#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/graph.hpp"

#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <queue>
#include <algorithm>

/*
* Test Functions *
*/

bool areEqualBFS(std::vector<Node>& first, std::vector<Node>& second) {
    if (first.size() != second.size()) {
        return false;
    }
    for (int i = 0; i < first.size(); i++) {
        if (first[i].alias_id != second[i].alias_id) {
            return false;
        }
        if (first[i].game_id != second[i].game_id) {
            return false;
        }
    }
    return true;
}

bool areEqualKruskal(std::vector<std::pair<Node, Node>> first, std::vector<std::pair<Node, Node>> second) {
    if (first.size() != second.size()) {
        return false;
    }
    for (int i = 0; i < first.size(); i++) {
        if (first[i].first.alias_id != second[i].first.alias_id) {
            return false;
        }
        if (first[i].first.game_id != second[i].first.game_id) {
            return false;
        }
        if (first[i].second.alias_id != second[i].second.alias_id) {
            return false;
        }
        if (first[i].second.game_id != second[i].second.game_id) {
            return false;
        }
    }
    return true;
}


// TEST_CASE("PopulateGraph Tests", "[populate]") {
//     std::vector<std::pair<std::string, std::string>> streamer_vect = csv2streamer("DatasetProcessing/streamer_features.csv");
// 	std::vector<std::pair<std::string, std::string>> edge_vect = csv2edge("DatasetProcessing/musae_ENGB_edges.csv");

//     Graph g(streamer_vect, edge_vect);

//     // Below are a few requires to check for correct edges 
//     Node n1("998", "26936.0");
//     std::vector<Node> expected = {
//         Node ("1083", "510799.0")
//     };

//     std::vector<Node> actual = g.GetNeighbors(n1);

//     REQUIRE(areEqual(expected, actual));

//     Node n2("999", "506237.0");

//     std::vector<Node> expected2 = {
//         Node ("93", "517072.0"),
//         Node ("841", "511746.0"),
//         Node ("4649", "493597.0"),
//         Node ("5882", "515025.0"),
//         Node ("6867", "509658.0"),
//         Node ("2974", "1478010775.0")
//     };

//     std::vector<Node> actual2 = g.GetNeighbors(n2);

//     REQUIRE(areEqual(expected2, actual2));
// }

TEST_CASE("BFS Tests - Simple", "[bfs]") {
    std::vector<std::pair<std::string, std::string>> streamer_vect = {
        std::make_pair("A", "GOW"),
        std::make_pair("B", "GOW"),
        std::make_pair("C", "GOW"),
        std::make_pair("D", "ER"),
        std::make_pair("E", "DS")
    };

    std::vector<std::pair<std::string, std::string>> edge_vect = {
        std::make_pair("A", "B"),
        std::make_pair("C", "A"),
        std::make_pair("B", "C"),
    };

    // Here, the shortest path is A->C as A->C directly 

    Graph g(streamer_vect, edge_vect);

    std::vector<Node> path = g.BFSPath(Node("A", "GOW"), Node("C", "GOW"));

    std::vector<Node> expected = {
        Node("C", "GOW")
    };

    REQUIRE(areEqualBFS(path, expected));

    edge_vect = {
        std::make_pair("A", "B"),
        std::make_pair("C", "B"),
    };

    // Here, the shortest path is A->B->C as A->B->C directly

    Graph g2(streamer_vect, edge_vect);

    std::vector<Node> path2 = g2.BFSPath(Node("A", "GOW"), Node("C", "GOW"));

    std::vector<Node> expected2 = {
        Node("B", "GOW"),
        Node("C", "GOW")
    };

    REQUIRE(areEqualBFS(path2, expected2));

    edge_vect = {
        std::make_pair("A", "B")
    };

    // Here, no path to C exists as we've a disconnected graph (A->B, but C, D, E have no edges)

    Graph g3(streamer_vect, edge_vect);

    std::vector<Node> path3 = g3.BFSPath(Node("A", "GOW"), Node("C", "GOW"));

    std::vector<Node> expected3 = {};

    REQUIRE(areEqualBFS(path3, expected3));
}

TEST_CASE("BFS Tests - Complex", "[bfs]") {
    std::vector<std::pair<std::string, std::string>> streamer_vect = {
        std::make_pair("A", "GOW"),
        std::make_pair("B", "GOW"),
        std::make_pair("C", "GOW"),
        std::make_pair("D", "ER"),
        std::make_pair("E", "ER")
    };

    std::vector<std::pair<std::string, std::string>> edge_vect = {
        std::make_pair("A", "B"),
        std::make_pair("C", "A"),
        std::make_pair("B", "C"),
        std::make_pair("D", "E")
    };

    // Graph looks like this (undirected):
    // A connected to B and C
    // B connected to A and C
    // C connected to A and B
    // D connected to E
    // E connected to D

    Graph g(streamer_vect, edge_vect);

    std::vector<Node> path = g.BFSPath(Node("A", "GOW"), Node("E", "ER"));

    // No such path exists

    std::vector<Node> expected = {};

    REQUIRE(areEqualBFS(path, expected));

    std::vector<Node> path2 = g.BFSPath(Node("A", "GOW"), Node("D", "ER"));

    // No such path exists
    REQUIRE(areEqualBFS(path2, expected));

    std::vector<Node> path3 = g.BFSPath(Node("A", "GOW"), Node("C", "GOW"));

    // Connection A->C exists
    std::vector<Node> expected3 = {
        Node("C", "GOW")
    };

    REQUIRE(areEqualBFS(path3, expected3));

    std::vector<Node> path4 = g.BFSPath(Node("A", "GOW"), Node("B", "GOW"));

    // Connection A->B exists

    std::vector<Node> expected4 = {
        Node("B", "GOW")
    };

    REQUIRE(areEqualBFS(path4, expected4));

}

TEST_CASE("Kruskal Tests - Simple", "[kruskal]") {
    std::vector<std::pair<std::string, std::string>> streamer_vect = {
        std::make_pair("A", "GOW"),
        std::make_pair("B", "GOW"),
        std::make_pair("C", "GOW"),
        std::make_pair("D", "ER"),
        std::make_pair("E", "ER")
    };

    std::vector<std::pair<std::string, std::string>> edge_vect = {
        std::make_pair("A", "B"),
        std::make_pair("B", "C"),
        std::make_pair("C", "A"),
    };

    // Graph looks like this (undirected):
    // A connected to B
    // B connected to C
    // C connected to A
    // D has no connections
    // E has no connections

    Graph g(streamer_vect, edge_vect);

    std::vector<std::pair<Node, Node>> mst = g.Kruskal("GOW");

    // MST should be A->B and B->C

    std::vector<std::pair<Node, Node>> expected = {
        std::make_pair(Node("A", "GOW"), Node("B", "GOW")),
        std::make_pair(Node("B", "GOW"), Node("C", "GOW"))
    };

    REQUIRE(areEqualKruskal(mst, expected));

    std::vector<std::pair<Node, Node>> mst2 = g.Kruskal("ER");

    // MST should be empty as no connections exist

    std::vector<std::pair<Node, Node>> expected2 = {};

    REQUIRE(areEqualKruskal(mst2, expected2));
}

TEST_CASE("Kruskal Tests - Complex", "[kruskal]") {
    std::vector<std::pair<std::string, std::string>> streamer_vect = {
        std::make_pair("A", "GOW"),
        std::make_pair("B", "GOW"),
        std::make_pair("C", "GOW"),
        std::make_pair("D", "ER"),
        std::make_pair("E", "ER")
    };

    std::vector<std::pair<std::string, std::string>> edge_vect = {
        std::make_pair("A", "B"),
        std::make_pair("C", "A"),
        std::make_pair("B", "C"),
        std::make_pair("D", "E")
    };

    // Graph looks like this (undirected):
    // A connected to B and C
    // B connected to A and C
    // C connected to A and B
    // D connected to E
    // E connected to D

    Graph g(streamer_vect, edge_vect);

    std::vector<std::pair<Node, Node>> mst = g.Kruskal("ER");

    // MST should be D->E

    std::vector<std::pair<Node, Node>> expected = {
        std::make_pair(Node("D", "ER"), Node("E", "ER"))
    };

    REQUIRE(areEqualKruskal(mst, expected));

    std::vector<std::pair<Node, Node>> mst2 = g.Kruskal("No Game");

    // MST should be empty as no such game is in the graph

    std::vector<std::pair<Node, Node>> expected2 = {};

    REQUIRE(areEqualKruskal(mst2, expected2));
}
