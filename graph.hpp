#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <cstdlib>
#include "point.hpp"

using namespace std;

class graph {
    private:
        vector<vector<point>> *lis;
    public:
        graph() {
            lis = new vector<vector<point>>;
        }
};

#endif