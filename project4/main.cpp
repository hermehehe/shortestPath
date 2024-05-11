#include <iostream>
#include <fstream>
#include <string>
#include "Graph.hpp"
#include "MyException.hpp"
using namespace std;
//from parsing_input_files video on learn
int main(){
string input_cmd;
Graph* graph = new Graph();
while(cin >> input_cmd){
  try {  
    if (input_cmd == "INSERT"){
        int a,b;
        double d,s;
        cin >> a;
        cin >> b;
        cin >> d;
        cin >> s;
        if (a > 500000 || a <=0 || b > 500000 || b <=0 || d <=0 || s <=0){
            throw MyException("Illegal argument");
        }
        else{
           string output = graph->insert(a,b,d,s);
           graph -> insert(b,a,d,s);
            cout<<output<<endl;
        }
    }
    else if(input_cmd == "LOAD"){
        string filename;
        cin>>filename;
        fstream fin(filename.c_str());
       string s = graph->load(fin);
       cout << s <<endl;
    }  
    else if (input_cmd == "PRINT"){
        int a;
        cin >> a;
        if ( a <=0 || a > 500000){
             throw MyException("Illegal argument");
        }
        else {
            string s = graph->print(a);
            cout << s << endl;
        }       
    }
    else if (input_cmd == "DELETE"){
        int a;
        cin >> a;      
        if (a > 500000 || a <= 0){
            throw MyException("Illegal argument");
        }
        else if (graph == nullptr){
            cout<<"failure"<<endl;
        }  
        else  {
        string s = graph->del(a);
        cout <<s<<endl;
        }    
    }
    else if (input_cmd == "PATH"){
        int a, b;
        cin >> a;
        cin >> b;
        if (a > 500000 || b > 500000 || a <= 0 || b <= 0){
             throw MyException("Illegal argument");
        }
        
       else{
        string s = graph->path(a,b);
        cout << s << endl;
       } 
    }
    else if (input_cmd == "TRAFFIC"){
        int a, b;
        double A;
        cin >> a;
        cin >> b;
        cin >> A;
        if ( a <=0 || a > 500000 || b <= 0 || b>500000){
             throw MyException("Illegal argument");
        }
        else {
        string s = graph->traffic(a,b,A);
        graph->traffic(b, a, A);
        cout << s << endl;
        }     
    }
    else if(input_cmd == "UPDATE"){
        std::string filename;
        std::cin>>filename;
        std::fstream fin(filename.c_str());
        if (graph->update(fin)){
            cout << "success" << endl;
        }
        else{
            cout << "failure" << endl;
        }
        
    }  
    else if (input_cmd == "LOWEST"){
        int a, b;
        cin >> a;
        cin >> b;  
        if (a > 500000 || b > 500000 || a <= 0 || b <= 0){
             throw MyException("Illegal argument");
        }   
        else {
            string s = graph->lowest(a,b);
            cout<<s<<endl;
        }
        
    }
    else if(input_cmd == "END"){
       break;
    }
  }
  catch (const MyException& except){
    std::cout<<except.what()<<"\n"<<std::flush;
}
}
if(graph != nullptr){
    delete graph;
}
return 0;
}