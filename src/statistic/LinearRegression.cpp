#include "LinearRegression.h"
#include <cmath>

namespace vanagandr
{
namespace statistics
{

Matrix estimator_variance(const Matrix& X, const Matrix& res)
{
    Matrix xx = (X.transpose() * X).inverse();
    return xx * X.transpose() * res * res.transpose() * X * xx;
}

double square(double x)
{
    return pow(x, 2.0);
}

double rsquare(const Matrix& ymod, const Matrix& ytrue)
{
    double meant = ytrue.mean();
    double meanm = ymod.mean();

    return (ymod  - meant * Matrix::Ones(ymod.rows(), 1)).unaryExpr(std::ptr_fun(square)).sum() /
           (ytrue - meanm * Matrix::Ones(ymod.rows(), 1)).unaryExpr(std::ptr_fun(square)).sum();
}

Matrix lag_op(const Matrix& Y, int lag) {   return Y.topRows(Y.rows() - lag); }

Matrix ar_matrix(const Matrix& Y, int p)
{
    // rows are cut by p
    // the matrix becomes |1| Y t - 1 | ... | Y t - p|
    int rows = Y.rows() - p;

    Matrix ret = Matrix::Ones(rows, p * Y.cols() + 1);

    for(int i = 0; i < p; i++)
        ret.block(0, i * Y.cols() + 1, rows, Y.cols()) = Y.middleRows(p - i - 1, rows);

    return ret;
}

}
}
