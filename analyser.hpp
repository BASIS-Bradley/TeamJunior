#ifndef ANALYSER_HPP_
#define ANALYSER_HPP_

#include "graph.hpp"

using namespace std;

class analyser {
    public:
        analyser() {

        }

        int countEdges(graph a) {
            return a.get_edges();
        }

         int findInDegree(graph a, int x) { // x = node number
            int degree = 0;          
            vector<vector<point>>* lis = a.get_lis2();
            for (auto i = (lis -> at(x)).begin(); i != (lis -> at(x)).end(); i++) {
                ++degree;              
            }
            return degree;  
        }

        int findOutDegree(graph a, int x) {
            int degree = 0;          
            vector<vector<point>>* lis = a.get_lis();
            for (auto i = (lis -> at(x)).begin(); i != (lis -> at(x)).end(); i++) {
                ++degree;              
            }
            return degree;  
        }

        int findDegree(graph a, int x) { // undirected graph
            return findOutDegree(a, x);
        }

        // void bfs(node s) {
        //     node u;
        //     int i, j;
        //     queue<node> que;
        //     bool *visited = new bool[num_nodes];
        //     for(i = 0; i < num_nodes; i++) {
        //         visited[i] = false; //not visited
        //     }
        //     visited[s.getNum()] = true;//visited
        //     que.push(s); //insert starting node
        //     while(!que.empty()){
        //         u = que.front(); //delete from queue and print
        //         que.pop();
        //         cout << char(u.getNum()) << " ";
        //         for(i = 0; i < num_nodes; i++){
        //             if(lis -> at(i).at(u.getNum()).getWeight() == 1){
        //             //when the node is non-visited
        //                 if(visited[i] == false){
        //                     visited[i] == true;
        //                     que.push(visited[i]);
        //                 }
        //             }
        //         }
        //     }
        // }
};


#endif