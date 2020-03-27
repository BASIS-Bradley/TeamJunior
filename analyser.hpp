#ifndef ANALYSER_HPP_
#define ANALYSER_HPP_

#include "graph.hpp"
#include <list>

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



        void bfs(graph a, node s) {
            int num_nodes = a.get_number_nodes();
            //make helper array that keeps tracks of which nodes have been visited, sets it all to false before starting
            bool *visited = new bool[num_nodes];
            for(int i = 0; i < num_nodes; i++) {
                visited[i] = false;
            }
            //creates a queue for the BFS, list data stucture makes sense https://embeddedartistry.com/blog/2017/09/11/choosing-the-right-container-sequential-containers/
            list<node> queue;
            //add node that was passed to list of visited and then queue it up
            visited[s.getNum()] = true;
            queue.push_back(s);
            vector<vector<point>>* lis = a.get_lis();

            while(!queue.empty()) {

                //pop vertex from the front and print it
                s = queue.front();
                cout << s.getNum() << ", ";
                queue.pop_front();

                // Get all adjacent vertices of the dequeued-
                // // vertex s. If a adjacent has not been visited,--
                // // then mark it visited and enqueue it
                for (auto i = lis -> at(s).begin(); i != lis -> at(s).end(); i++) {
                    if(!visited[*i]) {
                        visited[*i] = true;
                        queue.push_back(*i);
                    }
                }
            }
        }



};


#endif
