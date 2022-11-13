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
        Graph(std::string message);
        std::set<int> BFS(int start_id);

    private:

};