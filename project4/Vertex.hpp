#ifndef _VERTEX_HPP_
#define _VERTEX_HPP_

#include <iostream>
#include "List.hpp"

//Hermela Gebretsion

class Vertex {
    public:
    
    Vertex(int vertex1); //constructor 
    Vertex();//default constructor
    ~Vertex(); //destuctor

    int get_vertex_num();
    List* get_edge_list();
    double get_path_weight();
    int get_parent();

    void set_vertex_num(int vertex);
    void set_edge_list(List* list);
    void set_path_weight(double d);
    void set_parent(int p);

    //member functions
    int vertex_num;
    double path_weight; //to be used in Dijkstra's algorithm
    int parent; //to be used in Dijkstra's algorithm
    List* edge_list;

};

#endif
