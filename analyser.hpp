#ifndef ANALYSER_HPP_
#define ANALYSER_HPP_

#include "graph.hpp"
#include <list>
#include <limits.h>

using namespace std;

typedef pair<int, int> pi;

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
                for (auto i = lis -> at(s.getNum()).begin(); i != lis -> at(s.getNum).end(); i++) {
                    if(!visited[i -> getNode().getNum()]) {
                        visited[i -> getNode().getNum()] = true;
                        queue.push_back(i -> getNode());
                    }
                }
            }
        }

        int minDistanceIndex(graph a, int dist[], bool sptSet[]) { 
            int min = INT_MAX, min_index; 
        
            for (int v = 0; v < a.get_number_nodes(); v++) 
                if (sptSet[v] == false && dist[v] <= min) 
                    min = dist[v], min_index = v; 
        
            return min_index; 
        }

        void dijkstra(graph a, int src) { 
            int num_nodes = a.get_number_nodes();
            int dist[num_nodes];
        
            bool sptSet[num_nodes]; 

            for (int i = 0; i < num_nodes; i++) 
                dist[i] = INT_MAX, sptSet[i] = false; 

            dist[src] = 0; 
            vector<vector<point>>* lis = a.get_lis();

            for (int i = 0; i < num_nodes - 1; i++) {  
                int u = minDistanceIndex(a, dist, sptSet); 

                sptSet[u] = true; 

                for (auto v = lis -> at(u).begin(); v != lis -> at(u).end(); v++) {
                    int vIndex = v -> getNode().getNum();
                    if (!sptSet[vIndex] && lis -> at(u).at(vIndex).getWeight() && dist[u] != INT_MAX && dist[u] + lis -> at(u).at(vIndex).getWeight() < dist[vIndex]) {
                        dist[vIndex] = dist[u] + lis -> at(u).at(vIndex).getWeight(); 
                    }
                }
            } 
        
            printf("Vertex \t\t Distance from Source\n"); 
            for (int i = 0; i < num_nodes; i++) 
                printf("%d \t\t %d\n", i, dist[i]);
        }



//STILL NEEDS TESTING AND FORMATTING AND JUST ABOUT EVERYTHING ELSE
void primMST(graph g)
{
    //okay so I don't know how to make this without pairs because i have no clue how PQs in the
    //STL treats putting objects in heaps, with pairs you can order by weight (cost) and heap
    //recognizes the first element of the pair as the thing to prioritize
    priority_queue< pi, vector <pi> , greater<pi> > minheap; 

    vector<vector<point>>* adjlis = a.get_lis();

    //this is just the starting point, pretty sure it gets more stupid if it's negative
    int src = 0; 
  
    vector<int> cost(g.get_number_nodes(), INF); 
  
    vector<int> parent(g.get_number_nodes(), -1); 
  
    vector<bool> inMST(g.get_number_nodes(), false); 

    //this is pushing the weight-node pairs, i don't want to figure out doing it with point objects because this is just easier (i think)
    minheap.push(make_pair(0, src)); 
    cost[src] = 0; 
  
    while (!minheap.empty()) 
    { 
        int u = minheap.top().second; 
        minheap.pop(); 
  
        inMST[u] = true; 
  
        for (auto i = adjlis -> at(u).begin(); i != adjlis -> at(u).end(); i++) 
        { 
            int v = i -> getNode(); 
            int weight = i -> getNode(); 
  
            if (inMST[v] == false && cost[v] > weight) 
            { 
                cost[v] = weight; 
                minheap.push(make_pair(cost[v], v)); 
                parent[v] = u; 
            } 
        } 
    }

    for (int i = 1; i < V; ++i) 
        printf("%d - %d\n", parent[i], i);
} 


};


#endif
