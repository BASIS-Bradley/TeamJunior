#pragma once

#include <eigen3/Eigen/Sparse>
#include <eigen3/Eigen/Core>
#include <eigen3/unsupported/Eigen/MatrixFunctions>
#include "graph.hpp"

#ifndef MCL_HPP_
#define MCL_HPP_

class mcl {
    public:
        mcl() {

        }
        
        Eigen::SparseMatrix<double> mcl_unweighted(graph g, double expand_factor = 2, double inflate_factor = 2, double max_loop = 10) {
            if(g.get_weighted) {
                std::cout << "Given a weighted graph" << std::endl;
                return;
            }
            std::vector<std::vector<point>>* lis = g.get_lis2();
            Eigen::SparseMatrix<double> trans_mat;
            trans_mat.resize(g.get_number_nodes(), g.get_number_nodes());
            trans_mat.reserve(g.get_edges());
            int row = 0;
            for(auto i = lis -> begin(); i != lis -> end(); i++) {
                int sum = 0;
                for(auto j = i -> begin(); j != i -> end(); j++) {
                    sum += j -> getWeight();
                }
                for(auto j = i -> begin(); j != i -> end(); j++) {
                    trans_mat.insert(row, (j -> getNode()).getNum()) = j -> getWeight();
                }
                ++row;
            }

        }
};

#endif