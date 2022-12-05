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

bool areEqual(std::vector<Node>& first, std::vector<Node>& second) {
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


TEST_CASE("PopulateGraph Tests", "[populate]") {
    Graph g("test");

    // Below are a few requires to check for correct edges 
    Node n1("998", "26936.0");
    std::vector<Node> expected = {
        Node ("1083", "510799.0")
    };

    std::vector<Node> actual = g.GetNeighbors(n1);

    REQUIRE(areEqual(expected, actual));

    Node n2("999", "506237.0");

    std::vector<Node> expected2 = {
        Node ("93", "517072.0"),
        Node ("841", "511746.0"),
        Node ("4649", "493597.0"),
        Node ("5882", "515025.0"),
        Node ("6867", "509658.0"),
        Node ("2974", "1478010775.0")
    };

    std::vector<Node> actual2 = g.GetNeighbors(n2);

    REQUIRE(areEqual(expected2, actual2));
}

TEST_CASE("BFS Tests", "[bfs]") {
    Graph g("test");

    // Below are a few requires to check for correct edges 
    Node n1("998", "26936.0");
    Node n2("997", "515025.0");

    std::vector<Node> expected = {
        Node ("1083", "510799.0"),
        Node ("4406", "890558948.0"),
        Node ("2552", "512710.0"),
        Node ("997", "515025.0")
    };

    std::vector<Node> actual = g.BFSPath(n1, n2);
    REQUIRE(areEqual(expected, actual));
}

// TEST_CASE("Kruskal Test", "[kruskal]") {
//     Graph g("test");

//     Node n1("998", "26936.0");
// }