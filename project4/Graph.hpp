#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <iostream>
#include "Vertex.hpp"
using namespace std;
//Hermela Gebretsion

//from ece150 lecture notes
class Graph {
    public:
    
    Graph(); //constructor 
    ~Graph(); //destuctor

    //member functions
    std::string load(std::fstream& fin);
    std::string insert(int vertex1, int vertex2, double distance, double speed);
    std::string print(int vertex);
    std::string del(int vertex);
    std::string path(int a, int b);
    std::string traffic(int vertex1, int vertex2, double adj_f);
    bool update(std::fstream& fin);
    std::string lowest(int vertex1, int vertex2);

    //getters and setters
    Vertex** get_graph_array();
 

    
   
    private:
    Vertex** graph_array;
    int size;

};

#endif