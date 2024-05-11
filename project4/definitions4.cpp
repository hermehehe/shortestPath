#include <iostream>
#include "Graph.hpp"
#include "MyQueue.hpp"
#include "MyException.hpp"
#include <fstream>
#include <string>
#include <climits>
#include <cmath>
using namespace std;
///////////////////Exception Class Defintions////////////////
MyException::MyException(const std::string &error)
{
    msg = error;
}

const char *MyException::what() const
{
    return msg.c_str();
}
//////////////////////Vertex Class Definitions////////////////////////
Vertex::Vertex(int vertex1){
    vertex_num = vertex1;
    edge_list = nullptr;
    path_weight = INT_MAX; //how to set to infinity from chatgpt

}
Vertex::Vertex(){
    vertex_num = -1;
    edge_list = nullptr;
}
Vertex::~Vertex(){
    if (edge_list != nullptr){
        delete edge_list;
        edge_list=nullptr;
    }

}
//getters
int Vertex::get_vertex_num(){
    return vertex_num;
}
List* Vertex::get_edge_list(){
    return edge_list;
}
double Vertex::get_path_weight(){
    return path_weight;
}
int Vertex::get_parent(){
    return parent;
}
//setters
void Vertex::set_vertex_num(int vertex){
    vertex_num = vertex;
}

void Vertex::set_edge_list(List* list){
    edge_list = list;
}
void Vertex::set_path_weight(double d){
    path_weight = d;
}
void Vertex::set_parent(int p){
    parent = p;
}


//////////////////////Edge Class Definitions////////////////////////
Edge::Edge(int vertex2, double d, double s){
    adj_factor = 1; //initially setting adjustment factor to 1
    destination_vertex  = vertex2;
    distance = d;
    speed = s;
    time = d/(s+adj_factor);

    next_edge = nullptr;
}
Edge::~Edge(){

}

//getters and setters
Edge* Edge::get_next(){
    return next_edge;
}
double Edge::get_distance(){
    return distance;
}
double Edge::get_adj_factor(){
    return adj_factor;
}
double Edge::get_speed(){
    return speed;
}
double Edge::get_time(){
    return time;
}
int Edge::get_destination_vertex(){
    return destination_vertex;
}

void Edge::set_next(Edge* next){
    next_edge = next;
}
void Edge::set_distance(double d){
    distance = d;
}
void Edge::set_adj_factor(double a){
    adj_factor = a;
}
void Edge::set_speed(double s){
    speed = s;
}
void Edge::set_time(double t){
    time = t;
}
void Edge::set_destination_vertex(int v){
    destination_vertex = v;
}

//////////////////List Class Definitions//////////////////////////////////////
List::List()
{
    p_head = nullptr;
}

List::~List()
{
    Edge *current = p_head;
    while (current != nullptr)
    {
        // create temporary pointers to walk through linked list
        Edge *p_temp = current;
        current = current->get_next();
        delete p_temp;
    }
    p_head = nullptr;
}
// getters and setters
Edge* List::get_head()
{
    return p_head;
}
void List::set_head(Edge *head)
{
    p_head = head;
}



///////////////////////Graph Class Definitions//////////////////////////
Graph::Graph(){
    size = 500001;
    graph_array = new Vertex*[size];
    for (int i = 0; i < size; i++)
    {
        graph_array[i] = nullptr;
    }
 } 

Graph::~Graph(){
    if (graph_array != nullptr){
        for (int i = 0; i < size; i++)
        {
            if (graph_array[i] != nullptr){
                delete graph_array[i];
                graph_array[i] = nullptr;
            }
            
        }
        delete[] graph_array;
        graph_array = nullptr;
    }
}

//getters and setters
Vertex** Graph::get_graph_array(){
    return graph_array;
}



std::string Graph::insert(int vertex1, int vertex2, double distance, double speed){
    //check if a and b are in the array, if not, add them
    //insert a and b into array slots, add new edge to the start of the edge list

    //this is the case where the vertex doesnt exist in the array, create vertex and new edgelist
        if (graph_array[vertex1] == nullptr){
            Vertex* v = new Vertex(vertex1);
            graph_array[vertex1] = v;
            List* edge_list = new List();
            graph_array[vertex1]->set_edge_list(edge_list);
            Edge* edge_head = (graph_array[vertex1]->get_edge_list())->get_head();
            //if the list is empty
            Edge* input_edge = new Edge(vertex2, distance, speed);
            input_edge->set_time(distance/speed);
            (graph_array[vertex1]->get_edge_list())->set_head(input_edge);

        }
     

            //if the vertex exists and list is not empty 
           else{
            Edge* p_temp = (graph_array[vertex1]->get_edge_list())->get_head();
            //first check if the edge already exists
            bool edge_exists = false;
            while (p_temp != nullptr){
                if (p_temp->get_destination_vertex() == vertex2){
                    //update edge with new input values
                    p_temp->set_distance(distance);
                    p_temp->set_speed(speed);

                    //if the adjustment factor is 0, don't update time (time = infinity), otherwise update time with new distance and speed
                    if ((p_temp->get_adj_factor()) != 0){
                    p_temp->set_time(distance/(speed*p_temp->get_adj_factor()));
                    }
                    edge_exists = true;

                    break;

                }
                p_temp = p_temp->get_next();
               
            }
            
            //if the list is not empty but the edge doesnt already exist
            //insert new edge at the beginning of the list
            if (!edge_exists){
                Edge* edge_head = (graph_array[vertex1]->get_edge_list())->get_head();
                Edge* input_edge = new Edge(vertex2, distance, speed);
                input_edge ->set_time(distance/speed); //assuming the adjustment factor is 1
                input_edge->set_next(edge_head);
                (graph_array[vertex1]->get_edge_list())->set_head(input_edge);
            }
           }
        

    return "success";

    }

    
        

std::string Graph::load(std::fstream &fin){//load data from a file and apply insert function
    double data;
    int a,b;
    double d,s;
    while (fin >> a >> b >> d >> s){

        insert(a,b,d,s);
        insert(b,a,d,s);
    }

    return "success";
}
bool Graph::update(std::fstream &fin){
    double data;
    int a,b;
    double adj_f;
    bool updated_edge = false;
    while (fin >> a >> b >>adj_f){
       
        string s = traffic(a,b,adj_f);
        traffic(b,a,adj_f);

        if (s == "success"){
            updated_edge = true;
        }
    }

    return updated_edge;
}

std::string Graph::path(int a, int b){//using Dijkstra's algorithm to find the shortest path from vertex 1 to 2
//referenced from wikipedia page on Dijkstra's algorithm
    if ((graph_array[a] == nullptr) || graph_array[b] == nullptr){
        return "failure"; //one or both vertices are not in the graph
    }
    //create priority Queue
    MyQueue* Q = new MyQueue(500000); //initialize as 500000
   for (int i = 1; i < 500001; i++){
    
    if (graph_array[i] != nullptr){
        graph_array[i]->set_path_weight(INT_MAX);
        graph_array[i]->set_parent(-1);//set parent as -1, basically undefined
        if (i == a){//if (i = a), set the distance to 0 instead of infinity, parent should still be -1
        graph_array[a]->set_path_weight(0);
        }
        //add to priority queue:
        Q->add_with_priority(graph_array[i]->get_vertex_num(), graph_array[i]->get_path_weight());
    }     
   }


   while(!(Q->isEmpty())){
       int u = Q->extractMin(); //u should be the vertex_num of the min Vertex in the heap
       List* edges = graph_array[u]->get_edge_list();
       Edge* current = edges->get_head();

       while(current != nullptr){
            double alt = graph_array[u]->get_path_weight()+current->get_time(); //total path weight plus the edge weight
            int v = current->get_destination_vertex();

                if (alt < graph_array[v]->get_path_weight()){ //this is the relaxation step
                    graph_array[v]->set_path_weight(alt);
                    graph_array[v]->set_parent(u);
                    Q->decrease_priority(v, graph_array[v]->get_vertex_num());
                }
                current = current->get_next();
             }
        }
   //done searching for shortest path
    delete Q;
   if((graph_array[b]->get_path_weight()) == INT_MAX){
    return "failure"; //as no path exists
   }
   int vertex = b ;//b is the target vertex num
   string shortest_path = to_string(b);
   while (vertex != a){
    shortest_path = to_string(graph_array[vertex]->get_parent()) + " " + shortest_path;
    vertex = graph_array[vertex]->get_parent();
   }

    return shortest_path;
   
}
std::string Graph::lowest(int vertex1, int vertex2){
    string output="";
    string s = path(vertex1,vertex2);
    if ( s == "failure"){
        output = "failure";
    }

    else{
        double dist = graph_array[vertex2]->get_path_weight();
        output = "the lowest is " + to_string(dist);
    }
    

    return output ;
}

std::string Graph::del(int vertex){//delete this vertex and any edge containing this vertex

    if (graph_array[vertex] == nullptr){//case where vertex doesnt exist
        return "failure";
    }

    else {
        //go through the edge list of the vertex we want to delete
        List* edges = graph_array[vertex]->get_edge_list();
        Edge* temp_edge = edges->get_head();

        while(temp_edge != nullptr){
            int vertex2 = temp_edge->get_destination_vertex();
            List* v2_edges = graph_array[vertex2]->get_edge_list(); //get the edge list of the connected vertex

            Edge* v2_current = v2_edges->get_head();
                //in the case where we want to delete the head node
                if ((v2_current == v2_edges->get_head()) && ((v2_current->get_destination_vertex()) == vertex) ){
                        Edge* v2_temp = v2_current;
                        v2_edges->set_head(v2_current->get_next());        //set the new head as teh next edge
                        delete v2_temp;
                }

                //case where we want to delete a node other than the head
                else{
                    //keep l
                    while (v2_current->get_next() != nullptr){
                        if ((v2_current->get_next())->get_destination_vertex() == vertex){
                            Edge* temp1 = v2_current->get_next();
                            Edge* temp2 = (v2_current->get_next())->get_next();
                            v2_current->set_next(temp2);

                            delete temp1;
                            break;  //break beacuse the list will have only one edge connected to the delete vertex
                        }
                        v2_current = v2_current->get_next();
                    }
                } 
    
               temp_edge = temp_edge ->get_next(); //keep checking the edge list of the vertex i want to delete   
            }

        //once we finish deleting the edges containing vertex we delete the actual vertex itself
        delete graph_array[vertex];
        graph_array[vertex] = nullptr;
    }
    
    return "success";
}

std::string Graph::traffic(int vertex1, int vertex2, double adj_f){
    bool edge_exists = false;

    if (adj_f > 1 || adj_f < 0){//if the adjustment factor is invalid
        return "failure";
    }
    if ((graph_array[vertex1] == nullptr)||(graph_array[vertex2] == nullptr)){ //if one of the vertices does not exist
        return "failure";
    }

    else {
    List* edges = graph_array[vertex1]->get_edge_list();
    Edge* temp_edge = edges->get_head();

    
    while (temp_edge != nullptr){ //while loop to check for edge containing vertex2
        if ((temp_edge->get_destination_vertex()) == vertex2){ 
            //update adjustment factor and time
            temp_edge->set_adj_factor(adj_f);
            if (adj_f == 0){ //if the adjustment factor is 0 time equals infinty
                double time = INT_MAX; //from chatgpt
                temp_edge->set_time(time); 
            }
            else {
                double time = temp_edge->get_distance()/ (temp_edge->get_speed() * adj_f);
                temp_edge->set_time(time);
            }
            edge_exists = true;     //edge connecting both vertices has been found
            break;
        }

        else{
            temp_edge = temp_edge->get_next();
        }
    }

    if(!edge_exists){
        return "failure";
    }
    }

    return "success";
}


std::string Graph::print(int vertex){ //print all vertex numbers adjacent to vertex
    string adjacent_vertices = "";
    if (graph_array[vertex] == nullptr){
        return adjacent_vertices;
    }

    else {
        //print the destination vertex from each edge in the edgelist 
        List* edges = graph_array[vertex]->get_edge_list();
        if (edges != nullptr){
            Edge* temp_edge = edges->get_head();

            while (temp_edge != nullptr){
                adjacent_vertices = adjacent_vertices + to_string(temp_edge->get_destination_vertex()) + " ";
                temp_edge = temp_edge->get_next();
            }
        }
        
    }
    
    return adjacent_vertices;
}

////////////////////QueueEntry Class Definitions////////////////////////////
QueueEntry::QueueEntry(int vertex, double weight){
    vertex_num = vertex;
    path_weight = weight;
}
//default constructor
QueueEntry::QueueEntry(){
    vertex_num = -1;
    path_weight = -1;
}  
QueueEntry::~QueueEntry(){

}

int QueueEntry::get_vertex(){
    return vertex_num;
}

double QueueEntry::get_weight(){
    return path_weight;
}

void QueueEntry::set_vertex(int v){
    vertex_num = v;
}
void QueueEntry::set_weight(double w){
    path_weight = w;
}
//////////////////myQueue Class Definitions////////////////////////////////
MyQueue::MyQueue(int cap){
    capacity = cap;
    size = 0;

    minHeap = new QueueEntry[capacity];
}

MyQueue::~MyQueue(){
    if (minHeap != nullptr){
        delete [] minHeap;
    }
}

bool MyQueue::isEmpty(){
    if (size == 0){
        return true;
    }
    return false;
}


void MyQueue::heapifyUp(int pos)
{
    int parent_pos = 0;
    while (pos > 0){
        parent_pos = (pos-1)/2; //find the parent element
        if (minHeap[pos].get_weight() < minHeap[parent_pos].get_weight()){ //if child is less than parent swap them to maintain minHeap strucuture
            QueueEntry temp = minHeap[pos];
            minHeap[pos] = minHeap[parent_pos];
            minHeap[parent_pos] = temp;
        }
        else {
            break;
        }
    }
}

void MyQueue::heapifyDown(int pos){
    int left = (2*pos)+1;
    int right = (2*pos) + 2;
    int parent = pos;
    int swapped = false;
    if (left < size){//make sure it is not out of scope
        if(minHeap[parent].get_weight() > minHeap[left].get_weight()){
            parent = left;
            //swap the two elements
            QueueEntry temp = minHeap[pos];
            minHeap[pos] = minHeap[parent];
            minHeap[parent] = temp;

            swapped = true;
        }

    }

    if (right < size){//make sure it is not out of scope
        if(minHeap[parent].get_weight() > minHeap[right].get_weight()){
            parent = right;
            //swap the two elements
            QueueEntry temp = minHeap[pos];
            minHeap[pos] = minHeap[parent];
            minHeap[parent] = temp;

            swapped=true;
        }

    }

    if(swapped){ 
        heapifyDown(parent); //repeat process with new parent
    }

}

int MyQueue::extractMin(){ //we want to extract the root nodes vertex number
    QueueEntry min = minHeap[0];

    minHeap[0]= minHeap[size-1];
    size--;
    heapifyDown(0);
    return min.get_vertex(); //return the vertex number of the root of the heap

}

void MyQueue::decrease_priority(int v, double weight){
//update values in heap and restructure heap accordingly
    for (int i = 0; i < size; i++){
        if (minHeap[i].get_vertex() == v){
            minHeap[i].set_weight(weight);
            heapifyUp(i);
            break;
        }
    }

    return;

}

void MyQueue::add_with_priority(int v, double weight){
    //adding new entry to heap and restructuring accordingly
    minHeap[size] = QueueEntry(v, weight);
    heapifyUp(size);
    size++;
    return;
}



