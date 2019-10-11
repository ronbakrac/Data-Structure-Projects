This program reads from an input file (must be named input.txt) the amount of nodes, the starting node, and the exit node. The program then reads an adjacency list from the input file where the last node for each adjacency list must having a '-1' to signify the end of the list.

For example:

6
2
3
2 3 5 -1
2 3 4 5 -1
0 1 4 5 -1
0 1 5 -1
1 2 5 -1
0 1 2 3 4 -1

6 refers to the total number of nodes (which is why we have 6 rows, adjacency list for each node)
2 refers to which node we start at
3 refers to the exit node
every row thereafter refers to what nodes are adjacent to the that specific node ('ith' index node). Must end in -1 for program to work.

User can choose to print the DFS path or BFS path. To compile, simply type:
g++ -std=c++11 test_bfs.cpp maze.cpp

