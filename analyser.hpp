#ifndef ANALYSER_HPP_
#define ANALYSER_HPP_

#include "graph.hpp"
#include <stack>
#include <list>
#include <limits.h>
#include <fstream>
#define INF INT_MAX
#define INF2 0x3f3f3f3f

using namespace std;

typedef pair<int, int> pi;

class analyser {
    public:
        graph a;
        int num_nodes;
        analyser() {

        }

        analyser(graph A) {
            a = A;
            num_nodes = a.get_number_nodes();
        }

        int countEdges() {
            return a.get_edges();
        }

        int findInDegree(int x) { // x = node number
            int degree = 0;          
            vector<vector<point>>* lis = a.get_lis2();
            for (auto i = (lis -> at(x)).begin(); i != (lis -> at(x)).end(); i++) {
                ++degree;              
            }
            return degree;  
        }

        int findOutDegree(int x) {
            int degree = 0;          
            vector<vector<point>>* lis = a.get_lis();
            for (auto i = (lis -> at(x)).begin(); i != (lis -> at(x)).end(); i++) {
                ++degree;              
            }
            return degree;  
        }

        int findDegree(int x) { // undirected graph
            return findOutDegree(x);
        }

        void bfs(node s) {
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
                for (auto i = lis -> at(s.getNum()).begin(); i != lis -> at(s.getNum()).end(); i++) {
                    if(!visited[i -> getNode().getNum()]) {
                        visited[i -> getNode().getNum()] = true;
                        queue.push_back(i -> getNode());
                    }
                }
            }
        }

        int minDistanceIndex(int dist[], bool sptSet[]) { 
            int min = INF, min_index; 
        
            for (int v = 0; v < a.get_number_nodes(); v++) 
                if (sptSet[v] == false && dist[v] <= min) 
                    min = dist[v], min_index = v; 
        
            return min_index; 
        }

        void dijkstra(int src) { 
            priority_queue<pi, vector <pi>, greater<pi>> minheap;

            vector<int> dist(num_nodes, INF2); 

            minheap.push(make_pair(0, src)); 
            dist[src] = 0; 

            while (!minheap.empty()) { 
                int u = minheap.top().second; 
                minheap.pop(); 

                for (auto i = a.get_lis() -> at(u).begin(); i != a.get_lis() -> at(u).end(); ++i) { 
                    int v = i -> getNode().getNum(); 
                    int weight = i -> getWeight(); 
        
                    if (dist[v] > dist[u] + weight) { 
                        dist[v] = dist[u] + weight; 
                        minheap.push(make_pair(dist[v], v)); 
                    } 
                } 
            }

            ofstream ofs;
            ofs.open("./results/dijkstra.txt", ofstream::out | ofstream::trunc); // clears text file
            ofs.close();
            ofstream myfile;
            myfile.open ("./results/dijkstra.txt");
            for (int i = 0; i < num_nodes; i++) {
                myfile << i << " " << dist[i] << endl;
            }
            myfile.close();
        }

    //STILL NEEDS TESTING AND FORMATTING AND JUST ABOUT EVERYTHING ELSE
        // void primMST(graph g) {
        //     //okay so I don't know how to make this without pairs because i have no clue how PQs in the
        //     //STL treats putting objects in heaps, with pairs you can order by weight (cost) and heap
        //     //recognizes the first element of the pair as the thing to prioritize
        //     priority_queue<pi, vector <pi>, greater<pi>> minheap; 

        //     vector<vector<point>>* adjlis = g.get_lis();

        //     //this is just the starting point, pretty sure it gets more stupid if it's negative
        //     int src = 0; 
        
        //     vector<int> cost(g.get_number_nodes(), INT_MAX); 
        
        //     vector<int> parent(g.get_number_nodes(), -1); 
        
        //     vector<bool> inMST(g.get_number_nodes(), false); 

        //     //this is pushing the weight-node pairs, i don't want to figure out doing it with point objects because this is just easier (i think)
        //     minheap.push(make_pair(0, src)); 
        //     cost[src] = 0; 
        
        //     while (!minheap.empty()) 
        //     { 
        //         int u = minheap.top().second; 
        //         minheap.pop(); 
        
        //         inMST[u] = true; 
        
        //         for (auto i = adjlis -> at(u).begin(); i != adjlis -> at(u).end(); i++) 
        //         { 
        //             int v = i -> getNode().getNum(); 
        //             int weight = i -> getWeight(); 
        
        //             if (inMST[v] == false && cost[v] > weight) 
        //             { 
        //                 cost[v] = weight; 
        //                 minheap.push(make_pair(cost[v], v)); 
        //                 parent[v] = u; 
        //             } 
        //         } 
        //     }

        //     // for (int i = 1; i < g.get_number_nodes(); ++i) // I think num_nodes = # vertices = # nodes, double check though
        //     //     printf("%d - %d\n", parent[i], i);

        //     // check if I did this right
        //     ofstream ofs;
        //     ofs.open("./results/prim.txt", ofstream::out | ofstream::trunc); // clears text file
        //     ofs.close();
        //     ofstream myfile;
        //     myfile.open ("./results/prim.txt");
        //     for (int i = 0; i < g.get_number_nodes(); i++) {
        //         myfile << parent[i] << " " << i << endl;
        //     }
        //     myfile.close();
        // } 

        bool isCyclicUtil(int v, bool visited[], bool *rStack) { 
            if (visited[v] == false) { 
                visited[v] = true; 
                rStack[v] = true; 
        
                for (auto i = a.get_lis() -> at(v).begin(); i != a.get_lis() -> at(v).end(); ++i) { 
                    if (!visited[i -> getNode().getNum()] && isCyclicUtil(i -> getNode().getNum(), visited, rStack)) 
                        return true; 
                    else if (rStack[i -> getNode().getNum()]) 
                        return true; 
                } 
            } 

            rStack[v] = false;  
            return false; 
        }    

        bool isCyclicUtil(int v, bool visited[], int parent) { 
            visited[v] = true; 

            for (auto i = a.get_lis() -> at(v).begin(); i != a.get_lis() -> at(v).end(); ++i) { 
                    if (!visited[i -> getNode().getNum()] && isCyclicUtil(i -> getNode().getNum(), visited, v)) 
                        return true; 
                    else if (i -> getNode().getNum() != parent) 
                        return true; 
            } 

            return false; 
        }
        
        bool isCyclic() { 
            bool *visited = new bool[num_nodes]; 
            if (a.get_directed()){
                bool *rStack = new bool[num_nodes]; 
                for (int i = 0; i < num_nodes; i++) { 
                    visited[i] = false; 
                    rStack[i] = false; 
                } 
            
                for(int i = 0; i < num_nodes; i++) {
                    if (isCyclicUtil(i, visited, rStack)) {
                        return true; 
                    }
                }
            
                return false; 
            } else {
                for (int i = 0; i < num_nodes; i++)
                    visited[i] = false;
                for(int i = 0; i < num_nodes; i++) {
                    if (!visited[i] && isCyclicUtil(i, visited, -1)) {
                            return true;
                    }
                }

                return false;
            }

        }

        void topologicalSortUtil(int v, bool visited[], stack<int> &Stack) { 
            visited[v] = true; 
        
            for (auto i = a.get_lis() -> at(v).begin(); i != a.get_lis() -> at(v).end(); ++i) 
                if (!visited[i -> getNode().getNum()]) 
                    topologicalSortUtil(i -> getNode().getNum(), visited, Stack); 

            Stack.push(v); 
        }

        void topologicalSort() {
            if (a.get_directed() && !isCyclic()) {
                stack<int> Stack; 

                bool *visited = new bool[num_nodes]; 
                for (int i = 0; i < num_nodes; i++) 
                    visited[i] = false; 

                for (int i = 0; i < num_nodes; i++) 
                    if (!visited[i]) 
                        topologicalSortUtil(i, visited, Stack); 

                while (Stack.empty() == false) { 
                    cout << Stack.top() << " "; 
                    Stack.pop(); 
                } 
            } else {
                cout << "Graph is not a directed acyclic graph" << endl;
            }
        }

        void shortestPath(int s) { 
            if (a.get_directed() && !isCyclic()) {
                stack<int> Stack; 
                int dist[num_nodes]; 

                bool *visited = new bool[num_nodes]; 
                for (int i = 0; i < num_nodes; i++) 
                    visited[i] = false; 

                for (int i = 0; i < num_nodes; i++) 
                    if (visited[i] == false) 
                        topologicalSortUtil(i, visited, Stack); 

                for (int i = 0; i < num_nodes; i++) 
                    dist[i] = INF; 
                dist[s] = 0; 

                while (Stack.empty() == false) { 
                    int u = Stack.top(); 
                    Stack.pop(); 

                    if (dist[u] != INF) { 
                    for (auto i = a.get_lis2() -> at(u).begin(); i != a.get_lis2() -> at(u).end(); ++i) 
                        if (dist[i -> getNode().getNum()] > dist[u] + i -> getWeight()) 
                            dist[i -> getNode().getNum()] = dist[u] + i -> getWeight(); 
                    } 
                } 
            
                for (int i = 0; i < num_nodes; i++) 
                    (dist[i] == INF)? cout << "INF ": cout << dist[i] << " "; 
            } else {
                cout << "Graph is not a directed acyclic graph" << endl;
            }
        }

        int FordFulkerson(int &source, int &sink) {
            int maxflow = 0;
            vector<vector<point>>* lis = a.get_lis();

            vector<vector<int>> res_lis;
            int num_nodes = a.get_number_nodes();
            for(int i; i < num_nodes; i++) {
                vector<int> row;
                res_lis.push_back(row);
                for(auto j = a.get_lis() -> at(i).begin(); j != a.get_lis() -> at(i).end(); ++j) {
                    res_lis[i].push_back(lis -> at(i).at(j -> getWeight()))
                }
            }
 
            vector<int> parent;
            for(int i = 0; i < num_nodes; i++) 
                parent.push_back(-1);

            while(FordFulkersonUtil(res_lis, source, sink, parent)) {
                int pathflow = 10000007;

                int v = sink;
                while(v != source) {
                    int u = parent[v];

                    int capacity = res_lis[u][v];
                    pathflow = min(pathflow, capacity);

                    v = u;
                }

                v = sink;
                while(v != source) {
                    int u = parent[v];
                    
                    res_lis[u][v] -= pathflow;
                    res_lis[v][u] += pathflow;

                    v = u;
                }

                maxflow += pathflow;
            }
            
            return maxflow;
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
                for (auto i = lis -> at(s.getNum()).begin(); i != lis -> at(s.getNum()).end(); i++) {
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
            priority_queue<pi, vector <pi>, greater<pi>> minheap;

            vector<int> dist(num_nodes, INF2); 

            minheap.push(make_pair(0, src)); 
            dist[src] = 0; 

            while (!minheap.empty()) { 
                int u = minheap.top().second; 
                minheap.pop(); 

                for (auto i = a.get_lis() -> at(u).begin(); i != a.get_lis() -> at(u).end(); ++i) { 
                    int v = i -> getNode().getNum(); 
                    int weight = i -> getWeight(); 
        
                    if (dist[v] > dist[u] + weight) { 
                        dist[v] = dist[u] + weight; 
                        minheap.push(make_pair(dist[v], v)); 
                    } 
                } 
            }
            ofstream ofs;
            ofs.open("./results/dijkstra.txt", ofstream::out | ofstream::trunc); // clears text file
            ofs.close();
            ofstream myfile;
            myfile.open ("./results/dijkstra.txt");
            for (int i = 0; i < num_nodes; i++) {
                myfile << i << " " << dist[i] << endl;
            }
            myfile.close();
        }

    //STILL NEEDS TESTING AND FORMATTING AND JUST ABOUT EVERYTHING ELSE
        // void primMST(graph g) {
        //     //okay so I don't know how to make this without pairs because i have no clue how PQs in the
        //     //STL treats putting objects in heaps, with pairs you can order by weight (cost) and heap
        //     //recognizes the first element of the pair as the thing to prioritize
        //     priority_queue< pi, vector <pi> , greater<pi> > minheap; 

        //     vector<vector<point>>* adjlis = g.get_lis();

        //     //this is just the starting point, pretty sure it gets more stupid if it's negative
        //     int src = 0; 
        
        //     vector<int> cost(g.get_number_nodes(), INT_MAX); 
        
        //     vector<int> parent(g.get_number_nodes(), -1); 
        
        //     vector<bool> inMST(g.get_number_nodes(), false); 

        //     //this is pushing the weight-node pairs, i don't want to figure out doing it with point objects because this is just easier (i think)
        //     minheap.push(make_pair(0, src)); 
        //     cost[src] = 0; 
        
        //     while (!minheap.empty()) 
        //     { 
        //         int u = minheap.top().second; 
        //         minheap.pop(); 
        
        //         inMST[u] = true; 
        
        //         for (auto i = adjlis -> at(u).begin(); i != adjlis -> at(u).end(); i++) 
        //         { 
        //             int v = i -> getNode().getNum(); 
        //             int weight = i -> getWeight(); 
        
        //             if (inMST[v] == false && cost[v] > weight) 
        //             { 
        //                 cost[v] = weight; 
        //                 minheap.push(make_pair(cost[v], v)); 
        //                 parent[v] = u; 
        //             } 
        //         } 
        //     }

        //     // for (int i = 1; i < g.get_number_nodes(); ++i) // I think num_nodes = # vertices = # nodes, double check though
        //     //     printf("%d - %d\n", parent[i], i);

        //     // check if I did this right
        //     ofstream ofs;
        //     ofs.open("./results/prim.txt", ofstream::out | ofstream::trunc); // clears text file
        //     ofs.close();
        //     ofstream myfile;
        //     myfile.open ("./results/prim.txt");
        //     for (int i = 0; i < g.get_number_nodes(); i++) {
        //         myfile << parent[i] << " " << i << endl;
        //     }
        //     myfile.close();
        // } 

        bool isCyclicUtil(graph a, int v, bool visited[], bool *rStack) { 
            if (visited[v] == false) { 
                visited[v] = true; 
                rStack[v] = true; 
        
                for (auto i = a.get_lis() -> at(v).begin(); i != a.get_lis() -> at(v).end(); ++i) { 
                    if (!visited[i -> getNode().getNum()] && isCyclicUtil(a, i -> getNode().getNum(), visited, rStack)) 
                        return true; 
                    else if (rStack[i -> getNode().getNum()]) 
                        return true; 
                } 
            } 

            rStack[v] = false;  
            return false; 
        }    

        bool isCyclicUtil(graph a, int v, bool visited[], int parent) { 
            visited[v] = true; 

            for (auto i = a.get_lis() -> at(v).begin(); i != a.get_lis() -> at(v).end(); ++i) { 
                    if (!visited[i -> getNode().getNum()] && isCyclicUtil(a, i -> getNode().getNum(), visited, v)) 
                        return true; 
                    else if (i -> getNode().getNum() != parent) 
                        return true; 
            } 

            return false; 
        }
        
        bool isCyclic(graph a) { 
            int num_nodes = a.get_number_nodes();
            bool *visited = new bool[num_nodes]; 
            if (a.get_directed()){
                bool *rStack = new bool[num_nodes]; 
                for (int i = 0; i < num_nodes; i++) { 
                    visited[i] = false; 
                    rStack[i] = false; 
                } 
            
                for(int i = 0; i < num_nodes; i++) {
                    if (isCyclicUtil(a, i, visited, rStack)) {
                        return true; 
                    }
                }
            
                return false; 
            } else {
                for (int i = 0; i < num_nodes; i++)
                    visited[i] = false;
                for(int i = 0; i < num_nodes; i++) {
                    if (!visited[i] && isCyclicUtil(a, i, visited, -1)) {
                            return true;
                    }
                }

                return false;
            }

        }

        void topologicalSortUtil(graph a, int v, bool visited[], stack<int> &Stack) { 
            visited[v] = true; 
        
            for (auto i = a.get_lis() -> at(v).begin(); i != a.get_lis() -> at(v).end(); ++i) 
                if (!visited[i -> getNode().getNum()]) 
                    topologicalSortUtil(a, i -> getNode().getNum(), visited, Stack); 

            Stack.push(v); 
        }

        void topologicalSort(graph a) {
            if (a.get_directed() && !isCyclic(a)) {
                int num_nodes = a.get_number_nodes();

                stack<int> Stack; 

                bool *visited = new bool[num_nodes]; 
                for (int i = 0; i < num_nodes; i++) 
                    visited[i] = false; 

                for (int i = 0; i < num_nodes; i++) 
                    if (!visited[i]) 
                        topologicalSortUtil(a, i, visited, Stack); 

                while (Stack.empty() == false) { 
                    cout << Stack.top() << " "; 
                    Stack.pop(); 
                } 
            } else {
                cout << "Graph is not a directed acyclic graph" << endl;
            }
        }

        void shortestPath(graph a, int s) {
            if (a.get_directed() && !isCyclic(a)) {
                int num_nodes = a.get_number_nodes();
                stack<int> Stack; 
                int dist[num_nodes]; 

                bool *visited = new bool[num_nodes]; 
                for (int i = 0; i < num_nodes; i++) 
                    visited[i] = false; 

                for (int i = 0; i < num_nodes; i++) 
                    if (visited[i] == false) 
                        topologicalSortUtil(a, i, visited, Stack); 

                for (int i = 0; i < num_nodes; i++) 
                    dist[i] = INF; 
                dist[s] = 0; 

                while (Stack.empty() == false) { 
                    int u = Stack.top(); 
                    Stack.pop(); 

                    if (dist[u] != INF) { 
                    for (auto i = a.get_lis2() -> at(u).begin(); i != a.get_lis2() -> at(u).end(); ++i) 
                        if (dist[i -> getNode().getNum()] > dist[u] + i -> getWeight()) 
                            dist[i -> getNode().getNum()] = dist[u] + i -> getWeight(); 
                    } 
                } 
            
                for (int i = 0; i < num_nodes; i++) 
                    (dist[i] == INF)? cout << "INF ": cout << dist[i] << " ";
            } else {
                cout << "Graph is not a directed acyclic graph" << endl;
            }
        }

        bool FordFulkersonUtil(vector<vector<int>> &res_lis, int &src, int &sink, vector<int> &parent) {
            int num_nodes = res_lis.size();
            bool visited[num_nodes] = {false};

            queue<int> q;

            q.push(src);
            visited[src] = true;
            parent[src] = -1;

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int i = 0; i < num_nodes; i++) {
                    int v = i;
                    int capacity = res_lis[u][v];
              
                    if (!visited[v] && capacity > 0) {
                        q.push(v);
                        parent[v] = u;
                        visited[v] = true;
                    }
                }
            }

            if (visited[sink]) 
                return true;
                
            return false;
        }  

        int FordFulkerson(graph a, int &source, int &sink) {
            int maxflow = 0;
            vector<vector<point>>* lis = a.get_lis();

            vector<vector<int>> res_lis;
            int num_nodes = a.get_number_nodes();
            for(int i; i < num_nodes; i++) {
                vector<int> row;
                res_lis.push_back(row);
                for(auto j = a.get_lis() -> at(i).begin(); j != a.get_lis() -> at(i).end(); ++j) {
                    res_lis[i].push_back(lis -> at(i).at(j -> getWeight()))
                }
            }
 
            vector<int> parent;
            for(int i = 0; i < num_nodes; i++) 
                parent.push_back(-1);

            while(FordFulkersonUtil(res_lis, source, sink, parent)) {
                int pathflow = 10000007;

                int v = sink;
                while(v != source) {
                    int u = parent[v];

                    int capacity = res_lis[u][v];
                    pathflow = min(pathflow, capacity);

                    v = u;
                }

                v = sink;
                while(v != source) {
                    int u = parent[v];
                    
                    res_lis[u][v] -= pathflow;
                    res_lis[v][u] += pathflow;
.
                    v = u;
                }

                maxflow += pathflow;
            }
            
            return maxflow;
        } 
};

#endif