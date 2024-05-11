#ifndef _LIST_HPP_
#define _LIST_HPP_

#include <iostream>
#include "Edge.hpp"

//Hermela Gebretsion

//from ece150 lecture notes
class List {
    public:
    
    List(); //constructor 
    ~List(); //destuctor

    //member functions
    Edge* get_head();
    void set_head(Edge* head);
    //private variables
    private:
    Edge* p_head;

};

#endif