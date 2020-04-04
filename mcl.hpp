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
        
        void normize(Eigen::SparseMatrix<double>& mat) {
            for(int i = 0; i < mat.cols(); i++) {
                double sum = 0;
                for(int j = 0; j < mat.rows(); j++) {
                    sum += mat.coeff(j,i);
                }
                for(int j = 0; j < mat.rows(); j++) {
                    mat.coeffRef(j,i) = mat.coeff(j,i)/sum;
                }
            }
        }

        void expand(Eigen::SparseMatrix<double>& mat, double expand_factor = 2) {
            Eigen::SparseMatrix a = mat;
            for(int i = 1; i < expand_factor; i++) {
                a *= mat;
            }
            mat = a;
        }

        void inflate(Eigen::SparseMatrix<double>& mat, double inflate_factor = 2) {
            Eigen::SparseMatrix a = mat;
            for(int i = 1; i < inflate_factor; i++) {
                a = a.cwiseProduct(mat);
            }
            mat = a;
        }

        Eigen::SparseMatrix<double> mcl_unweighted(graph g, double expand_factor = 2, double inflate_factor = 2, double max_loop = 10, bool self_loops = false) {
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
                double sum;
                if(self_loops) {
                    sum = 1;
                } else {
                    sum = 0;
                }
                for(auto j = i -> begin(); j != i -> end(); j++) {
                    sum += j -> getWeight();
                }
                for(auto j = i -> begin(); j != i -> end(); j++) {
                    trans_mat.insert(row, (j -> getNode()).getNum()) = (j -> getWeight())/sum;
                    if(self_loops) {
                        trans_mat.insert(row, row) = 1.0/sum;
                    }
                }
                ++row;
            }
            for(int t = 0; t < max_loop; t++) { // run til convergence, dont know how to yet
                expand(trans_mat);
                inflate(trans_mat);
                normize(trans_mat);
            }
            return trans_mat; // interpret this to find clusters
        }
};

#endif