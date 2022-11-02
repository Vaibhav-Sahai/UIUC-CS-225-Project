## Leading Question 
We have access to a dataset of top english speaking twitch streamers where the edges will represent their mutual connection (undirected) and every node will be a streamer with features being the games they play and streaming habits. Our main goal here is to answer the questions: given a game played, what all streamers are playing that game and how are they connected? (Kruskal's algorithm for MST), How can we go from one streamer to another? (BFS traversal), and who is the streamer with the most connections? (PageRank algorithm)
## Dataset Acquisition
We will be using the following dataset from snap: https://snap.stanford.edu/data/twitch-social-networks.html.

## Data Format
The dataset consists of .json and .csv files which detail features and edges respectively. This dataset in total has 34K nodes and 420K edges approximately. We will only be considering english speaking streamers and only take the features to be streaming habits and games liked.

## Data Correction
To ensure that the data is error free, we will run a null check. If the number of nulls are negligible, we can discard them as our dataset is large enough without them. Alongside this, we will also ensure that human errors like incorrect insertions haven't occured by seeing if we have nodes with no connections/invalid features etc.

## Data Storage
We will use a map that will have its first argument as the Node class and second argument as a set of nodes it points to. This will take O(n+m) space where n is number of nodes and m is number of edges. Worst case scenario where we encounter a complete graph (every node connected to every node), we will have O(n^2), but due to the nature of our data, we don't forcast this happening.

## Algorithm 
Since we will preprocess our data, we dont have to worry about incorrect inputs from the point of data. Our algorithms will take in the map we have discussed before, alongside optionally taking in to and from nodes. 

Our expected output will be a vector of nodes that connect one node to another (in the case of BFS), in our other cases we will print out the most popular node (PageRank), and use a tool to convert a MST into a visual graph (Kruskal's). 

Our expected Big O time for (assuming adjacency list implementation, where E is edges and V is vertices):  
BFS: O(V+E) and O(1) space   
Kruskal: O(E logV) and O(1) space  
Pagerank: O(E+V) and O(1) space  

## Timeline
Week 1: Preprocess our data and create templates on github 
Week 2: Start Implementing BFS + Construct test cases for BFS  
Week 3: Start Implementing Kruskal + Test cases 
Week 4: Start Implementing Pagerank + Test cases  
Week 5: Gap week (use this time in case something hasn't been completed/needs more attention)  
Week 6: Debug errors, cleanup code, review code, and catch up on any pending work


