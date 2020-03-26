#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <queue>
#include "point.hpp"

using namespace std;

class graph {
    private:
        vector<vector<point>> *lis; // from, to
        vector<vector<point>> *lis2; // to, from
        bool directed;
        bool weighted;
        int num_nodes;
        int count_edges;
    public:
        graph() {
            lis = new vector<vector<point>>;
            lis2 = new vector<vector<point>>;
            num_nodes = 0;
            directed = false;
            weighted = false;
            count_edges = 0;
        }

        graph(bool x, bool y) {
            lis = new vector<vector<point>>;
            lis2 = new vector<vector<point>>;
            num_nodes = 0;
            directed = x;
            weighted = y;
            count_edges = 0;
        }

        graph(bool x, bool y, int num) {
            lis = new vector<vector<point>>;
            lis2 = new vector<vector<point>>;
            num_nodes = num;
            directed = x;
            weighted = y;
            for(int i = 0; i < num; i++) {
                lis -> push_back(vector<point>());
                lis2 -> push_back(vector<point>());
            }
            count_edges = 0;
        }

        void addEdge(int a, int b) { // only works if number nodes is given
            if(weighted) {
                cout << "graph is weighted but no weight given" << endl;
            } else { // I guess space efficiency can be way more efficient if graph is given as undirected
                if(directed) {
                    lis -> at(a).push_back(point(b, 1));
                    lis2 -> at(b).push_back(point(a, 1));
                    ++count_edges;
                } else {
                    lis -> at(a).push_back(point(b, 1)); // lis = lis2
                    lis -> at(b).push_back(point(a, 1));
                    ++count_edges;
                }
            }
        }

        void addEdge(int a, int b, int w) { // only works if number nodes is given
            if(!weighted) {
                cout << "graph is unweighted but weight is given" << endl;
            } else {
                if(directed) {
                    lis -> at(a).push_back(point(b, w));
                    lis2 -> at(b).push_back(point(a, w));
                    ++count_edges;
                } else {
                    lis -> at(a).push_back(point(b, w));
                    lis -> at(b).push_back(point(a, w));
                    ++count_edges;
                }
            }
        }

        void print_graph() {
            if(num_nodes == 0) {

            } else {
                for(auto i = lis-> begin(); i != lis -> end(); i++) {
                    for(auto j = i -> begin(); j != i -> end(); j++) {
                        cout << (j -> getNode()).getNum() << "," << j -> getWeight() << " ";
                    }
                    cout << endl;
                }
            }
        }

        int get_edges() {
            return count_edges;
        }

        vector<vector<point>>* get_lis() {
            return lis;
        }

        vector<vector<point>>* get_lis2() {
            return lis2;
        }

        bool get_directed() {
            return directed;
        }

        bool get_weighted() {
            return weighted;
        }

        int get_number_nodes() {
            return num_nodes;
        }        
};

#endif
