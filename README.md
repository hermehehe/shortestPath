# shortestPath

In this project I designed a graph structure which stores a weighted, undirected graph. The program uses Dijkstra's algorithim to determine the lowest-weight path between two vertices. For this programs purposes, the graph's vertices represents a city intersection, the edges are roads, and the weight of these edges are the travel time between two intersections. This program challenged me as it was the first time I implemented an algorithm such as Dijkstra's in my own code, through this, I got to learn more about using heaps and queues as well.

**Adjustment Factor**

Traffic data is constantly changing, especially in cities, to emulate this, traffic data is represented by a number from 0-1 (adjustment factor). The formula to calculate the travel time, T, between two vertices is T = d/(SxA), where d is the distance in metres between vertices, S is the speed limit on the road in m/s and A is the adjustment factor. If A = 0, the road is fully blocked and time is infinite.

![image](https://github.com/hermehehe/shortestPath/assets/166939272/e115f49d-6673-4fb1-9605-0c0b8f70e861)

* The graph is an array of vertex pointers.
* Each vertex stores its vertex number, which corresponds to the graph_array index position it will be placed in, for a quick look up of O(1). It has a parent and path_weight which are variables that will be used in the implementation of Dijkstra's algorithm. A vertex also contains a linked list of edges.
* Each edge contains the distance, speed, time information between two edges as well as the destination edge. It has a pointer to the next edge as well, so it can be used in the List class to construct a linked list of edges. * A Queue class has been made to implement Dijkstra’s algorithm. It contains a pointer to an array of QueueEntry elements. I made a QueueEntry class instead of reusing the vertex data type to avoid issues with double deletion as pointers from different classes would be pointing to the same object.

*COMMANDS*

Keep in mind when writing commands if arguments don't follow these requirements, the program will throw an exception.

![image](https://github.com/hermehehe/shortestPath/assets/166939272/e9c12d16-aaae-4214-8f86-54defea756b6)

*LOAD* filename - loads a dataset into the graph. Can call this multiple times. This command assumes that no illegal arguments are in the datasets, all rows in the file should has the same format as a single INSERT command, assumes A=1 when inserting. Outputs "success".

*INSERT* a b d s - insert a new edge into the graph from vertex a to vertex b, distance d and speed limit of s. If vertices already exist, d and s are updated. Outputs "success" if edge was added/updated, else outputs "illegal argument".

*PRINT* a - Prints all vertices adjacent to vertex a. Outputs "failure" if vertex is not in the graph.

*DELETE* a - Deletes the vertex a and any edges containing a. Ouputs "success" if vertex was deleted or "failure" if vertex is not in the graph, or the graph is empty.

*PATH* a b - Prints the nodes along the lowest-weight path between vertices a and b. Outputs "failure" if graph is empty or there is no path between the two vertices or one of the vertices is not in the graph.

*TRAFFIC* a b A - Updates the adjustment factor, A, for edge between vertices A and B. Outputs "success" if both vertices exist, there is an edge between them and A is a number from 0-1, otherwise ouputs "failure".

*UPDATE* filename - Update traffice data between all vertices in teh file, traffic data should be given in the same format as the TRAFFIC command. Outputs "success" if at least one edge had traffic data updated, if not, outputs "failure".

*LOWEST* a b - Determine the weight of the lowest-weight path. Outputs "lowest is x" if at leat one path between vertices a and b exists otherwise outputs "failure".


