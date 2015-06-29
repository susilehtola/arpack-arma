#ifndef DENSEGENSHIFTSOLVE_H
#define DENSEGENSHIFTSOLVE_H

#include <armadillo>
#include <stdexcept>
#include "../LinAlg/GeneralLU.h"

template <typename Scalar>
class DenseGenShiftSolve
{
private:
    typedef arma::Mat<Scalar> Matrix;
    typedef arma::Col<Scalar> Vector;

    const Matrix mat;
    const int dim_n;
    GeneralLU<Scalar> solver;
public:
    DenseGenShiftSolve(Matrix &mat_) :
        mat(mat_.memptr(), mat_.n_rows, mat_.n_cols, false),
        dim_n(mat_.n_rows)
    {
        if(!mat_.is_square())
            throw std::invalid_argument("DenseGenShiftSolve: matrix must be square");
    }

    virtual ~DenseGenShiftSolve() {}

    int rows() { return dim_n; }
    int cols() { return dim_n; }

    // setting real sigma
    void set_shift(Scalar sigma)
    {
        solver.compute(mat - sigma * arma::eye<Matrix>(dim_n, dim_n));
    }

    // y_out = inv(A - sigma * I) * x_in
    void perform_op(Scalar *x_in, Scalar *y_out)
    {
        Vector x(x_in,  dim_n, false);
        Vector y(y_out, dim_n, false);
        solver.solve(x, y);
    }
};


#endif // DENSEGENSHIFTSOLVE_H