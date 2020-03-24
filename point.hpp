#ifndef POINT_HPP_
#define POINT_HPP_


#include <cstdlib>
#include "node.hpp"


using namespace std;

class point {
    public:
        point() {
            nod = node();
            weight = 1;
        }
        point(int num, int w) {
            nod = node(num);
            weight = w;
        }
        point(int num) {
            nod = node(num);
            weight = 1;
        }
        void setNode(node n) {
            nod = n;
        }
        void setWeight(int w) {
            weight = w;
        }
        node getNode() {
            return nod;
        }
        int getWeight() {
            return weight;
        }
    private:
        node nod;
        int weight;
};

#endif