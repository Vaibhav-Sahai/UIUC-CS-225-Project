# Results

## Overview 

Through this project, we used the popular platform Twitch to deduce which streamers play a given game and how they are linked together. We did so by implementing a **BFS algorithm** to find a connection between the nodes given a start and end node. We also used a **PageRank algorithm** to identify the most popular node which we defined as the node with the most connections. Our third algorithm was **Kruskal's algorithm** which was used to convert a MST to a visual graph. This gives insight into popular streamers for a certain game and other similar streamers. 

Our project was successful as we were able to accomplish this goal and answer the following questions.      

1) Given a game played, what all streamers are playing that game and how are they connected?      
2) How can we go from one streamer to another?      
3) Who is the streamer with the most connections?     

We ran through test cases, testing everything from edge cases to complex graphs containing multiple edges, and concluded that our findings were correct.

## Algorithms

### BFS Algorithm :    
    Input: The Start and End Nodes (String type).   
    Goal: To find the shortest path between the given nodes (Establishes a link between the nodes).  
    Output: A vector of nodes that depicts the shortest path between the start and end nodes. An example output is as follows
    The path is as follows: 
    leon_xci Teamfight Tactics
    Nick28T FIFA 23
    Keeno654 Fortnite
    Test: Defined two nodes and manually derived path and compared it to the path generated by the function to ensure it was accurate in both a simple and complex graph.

### PageRank Algorithm :    
    Input: Game Name (String type).   
    Goal: To find the most popular streamer for a given game (Streamer with most connections).   
    Output: A node that represents the most popular streamer. An example output is as follows
    leon_xci Teamfight Tactics
    Test: Have a simple and complex graph that is compared with the function output, followed by a complex graphs.


### Kruskal's Algorithm :   
    Input: Game Name (String type).   
    Goal: To create an MST that can be converted to a graph for a visual output.   
    Output: A MST structure. An example output is as follows:
    leon_xci FIFA 23
    Nick28T FIFA 23
    Test: Compare the output of the function with a simple, undirected graph and a complex multiple edges graph.

