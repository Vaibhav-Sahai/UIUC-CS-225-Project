#pragma once

#include <vector>

using namespace std;

class Graph {
    public:
        Graph(const std::string& people_fpath);
        void SocialGraph(const std::vector<std::string>& vertices, std::vector<std::vector<std::string>>& relations);

    private:
};