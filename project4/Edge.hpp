#ifndef _EDGE_HPP_
#define _EDGE_HPP_
#include <iostream>

//Hermela Gebretsion

//from ece150 lecture notes
class Edge {
    public:
    
    Edge(int vertex2, double d, double s); //constructor 
    ~Edge(); //destuctor

    //member functions
    Edge* get_next();
    double get_distance();
    double get_adj_factor();
    double get_speed();
    double get_time();
    int get_destination_vertex();

    void set_next(Edge* next);
    void set_distance(double d);
    void set_adj_factor(double a);
    void set_speed(double s);
    void set_time(double t);
    void set_destination_vertex(int v);

//private variables
    private:
    int destination_vertex;
    double distance;
    double adj_factor;
    double speed;
    double time;
    Edge* next_edge;

    

};

#endif