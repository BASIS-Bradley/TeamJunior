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
        
        Eigen::SparseMatrix<float,1,double> mcl_unweighted(graph g, double expand_factor = 2, double inflate_factor = 2, double max_loop = 10) {
            if(g.get_weighted) {
                std::cout << "Given a weighted graph" << std::endl;
                return;
            }
            std::vector<std::vector<point>>* lis = g.get_lis2();
            Eigen::SparseMatrix<float,1,double> trans_mat;
            trans_mat.resize((g.get_number_nodes(), g.get_number_nodes()));
            trans_mat.reserve(g.get_edges());

        }
};

#endif