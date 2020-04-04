#include <iostream>
#include <fstream>
#include "analyser.hpp"
#include "mcl.hpp"
#include <eigen3/Eigen/Core>

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

void testing() {
    graph g = graph(false, false, 3);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    analyser a = analyser();
    cout << a.findDegree(g, 0) << endl;
    cout << a.findDegree(g, 1) << endl;

    graph f = graph(true, false, 4);
    cerr << "s1" << endl;
    f.addEdge(0, 3);
    f.addEdge(0, 1);
    f.addEdge(0, 2);
    f.addEdge(1, 3);
    f.addEdge(1, 2);
    f.addEdge(3, 0);
    f.addEdge(2, 3);
    cerr << "s2" << endl;
    cout << a.findInDegree(f, 0) << a.findOutDegree(f, 3) << a.findOutDegree(f, 1) << a.findOutDegree(f, 2) << endl;
}

void test_clustering() {
    graph g = graph(false, false, 12);
    g.addEdge(0,5);
    g.addEdge(0,6);
    g.addEdge(0,1);
    g.addEdge(0,9);
    g.addEdge(1,4);
    g.addEdge(1,2);
    g.addEdge(2,4);
    g.addEdge(2,3);
    g.addEdge(3,7);
    g.addEdge(3,8);
    g.addEdge(3,10);
    g.addEdge(4,6);
    g.addEdge(4,7);
    g.addEdge(5,9);
    g.addEdge(6,9);
    g.addEdge(7,8);
    g.addEdge(7,10);
    g.addEdge(8,10);
    g.addEdge(8,11);
    g.addEdge(10,11);

    // g.print_graph();
    mcl a = mcl();
    Eigen::SparseMatrix<double> s = a.mcl_unweighted(g, 2, 2, 15, true);
    cout << Eigen::MatrixXd(s) << endl;
}

int main() {
    test_clustering();
}
