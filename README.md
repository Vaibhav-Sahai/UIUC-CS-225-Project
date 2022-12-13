## Final Submission Video:
https://mediaspace.illinois.edu/media/t/1_d7y6dcpb
## Slides:
https://docs.google.com/presentation/d/1KgvU_rU6-xIDafbZzjqfe8VVoF8sUmfImGQSGVJZFNY/edit#slide=id.p

# The Twitch Network

We have access to a dataset of top english speaking twitch streamers where the edges will represent their mutual connection (undirected) and every node will be a streamer with features being the games they play and streaming habits. Our main goal here is to answer the questions: given a game played, what all streamers are playing that game and how are they connected? (Kruskal's algorithm for MST), How can we go from one streamer to another? (BFS traversal), and who is the streamer with the most connections? (PageRank algorithm)

## Installation + Running Code
First, please make sure you've clang++ installed and are inside the `TheTwitchNetwork` directory. Then, the following commands will help you run our `main.cpp` file/clean object and executable files:   

```
  `make` -> Creates a file called `output` in `bin`. To run this file, type out `bin/output`  
  `make test` -> Creates a file called `test` in `bin`. To run this file, type out `bin/test`
  `make clean` -> Deletes all `.o` and exec files from `bin`
```

Make any changes to the `main.cpp` file for it to be reflected in our program.
Our test cases perform a variety of tests, from testing edge cases to complex graphs and can be found in `test.cpp`.
Our dataset is in `/TheTwitchNetwork/DatasetProcessing`, you can insert your own datasets here.
Our output exec files and test exec files are stored in `/TheTwitchNetwork/bin`

## Usage:

First, please reference the list of all allowed categories on twitch from the following link: https://www.twitch.tv/directory and find a streamer's streamer_id from this link: https://www.streamweasels.com/tools/convert-twitch-username-to-user-id/. You would need both to create a streamer node which is required for us to run our algoritms.

1. To find the shortest path from a starting to an ending node, you can run the following command `std::vector<Node> bfs_result = g.BFSPath(Node(streamer_alias[*Insert Name Here*], game_id[*Insert Game Here]), Node(streamer_alias[*Insert Name Here*], game_id[*Insert Game Here*]));`

2. To find a Minimum Spanning Tree, you can run the following command `std::vector<std::pair<Node, Node>> kruskal_result = g.KruskalPath(Node(streamer_alias[*Insert Name Here*], game_id[*Insert Game Here]), Node(streamer_alias[*Insert Name Here*], game_id[*Insert Game Here*]));`

3. To find the most popular streamer for a category, you can run the following command `Node pagerank_result = g.FindMostPopularStreamer(game_id[*Insert Game Here*]);`

### All of these must be run in main.cpp

You can also run our test cases which will run faster because we have used smaller graphs (lesser nodes). PageRank is a demanding algorithm and hence takes a long time to run on a 6.6K node graph.

## Project Structure:

1. You can find our project proposal here: https://github.com/Vaibhav-Sahai/UIUC-CS-225-Project/blob/main/project_proposal.md. 
2. You can find our team contract here: https://github.com/Vaibhav-Sahai/UIUC-CS-225-Project/blob/main/team_contract.md.
3. You can find our results here: https://github.com/Vaibhav-Sahai/UIUC-CS-225-Project/blob/main/results.md.

Our dataset and data processing notebook can be found in this directory: https://github.com/Vaibhav-Sahai/UIUC-CS-225-Project/tree/main/TheTwitchNetwork/DatasetProcessing.

Algorithms Used:
1. BFS
2. Kruskal's
3. PageRank

Classes Implemented:
1. A Node Class implementation
2. A Graph Class implementation
3. A DisjointSet implementation
