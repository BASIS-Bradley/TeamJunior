#ifndef EDGE_HPP_
#define EDGE_HPP_

using namespace std;

class edge {
    public:
        edge(){
            v1=0;
            v2=0;
            weight = 0;
        }

        edge(int source, int dest, int weight) {
            v1 = source;
            v2 = dest;
            this.weight = weight;
        }


    private:
        int v1;
        int v2;
        int weight;
        //might have to add a custom comparator so that using STL sort is easy

};




#endif
