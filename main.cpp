#include <iostream>
#include <fstream>
#include "graph.hpp"

using namespace std;

graph graph_ud_uw(false,false);
graph graph_ud_w(false,true);
graph graph_d_uw(true,false);
graph graph_d_w(false,true);



void read_ud_uw (graph g){
    ifstream infile("./data/facebook_undirected.txt");
    int a, b;
    while (infile >> a >> b) {
        g.addEdge(a,b);
    }
    
}


void read_d_uw(graph g){
    ifstream infile(""); //change file path
    int a, b;
    while (infile >> a >> b) {
        g.addEdge(a,b);
    }
    
}

void read_ud_w(graph g){
    ifstream infile(""); //change file path
    int a, b, c;
    while (infile >> a >> b >> c) {
        g.addEdge(a, b, c);
    }
    
}


void read_d_w(graph g){
    ifstream infile(""); //change file path
    int a, b, c;
    while (infile >> a >> b >> c) {
        g.addEdge(a, b, c);
    }
    
}



int main() {
    
}
