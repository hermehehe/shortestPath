# shortestPath

In this project I designed a graph structure which stores a weighted, undirected graph. The program uses Dijkstra's algorithim to determine the lowest-weight path between two vertices. For this programs purposes, the graph's vertices represents a city intersection, the edges are roads, and the weight of these edges are the travel time between two intersections. This program challenged me as it was the first time I implemented an algorithm such as Dijkstra's in my own code, through this I got to learn more about using heaps and queues as well.

**Adjustment Factor**

Traffic data is constantly changing, especially in cities, to emulate this, traffic data is represented by a number from 0-1 (adjustment factor). The formula to calculate the travel time, T, between two vertices is T = d/(SxA), where d is the distance in metres between vertices, S is the speed limit on the road in m/s and A is the adjustment factor. If A = 0, the road is fully blocked and time is infinite.

![image](https://github.com/hermehehe/shortestPath/assets/166939272/e115f49d-6673-4fb1-9605-0c0b8f70e861)

* The graph is an array of vertex pointers.
* Each vertex stores its vertex number, which corresponds to the graph_array index position it will be placed in, for a quick look up of O(1). It has a parent and path_weight which are variables that will be used in the implementation of Dijkstra's algorithm. A vertex also contains a linked list of edges.
* Each edge contains the distance, speed, time information between two edges as well as the destination edge. It has a pointer to the next edge as well, so it can be used in the List class to construct a linked list of edges. * A Queue class has been made to implement Dijkstra’s algorithm. It contains a pointer to an array of QueueEntry elements. I made a QueueEntry class instead of reusing the vertex data type to avoid issues with double deletion as pointers from different classes would be pointing to the same object.

