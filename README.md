# The Twitch Network

We have access to a dataset of top english speaking twitch streamers where the edges will represent their mutual connection (undirected) and every node will be a streamer with features being the games they play and streaming habits. Our main goal here is to answer the questions: given a game played, what all streamers are playing that game and how are they connected? (Kruskal's algorithm for MST), How can we go from one streamer to another? (BFS traversal), and who is the streamer with the most connections? (PageRank algorithm)

## Installation + Running Code
First, please make sure you've clang++ installed and are inside the `TheTwitchNetwork` directory. Then, the following commands will help you run our `main.cpp` file/clean object and executable files:   

```
  `make` -> Creates a file called `output` in `bin`. To run this file, type out `bin/output`  
  `make clean` -> Deletes all `.o` and exec files from `bin`
```

Make any changes to the `main.cpp` file for it to be reflected in our program

## Usage:
