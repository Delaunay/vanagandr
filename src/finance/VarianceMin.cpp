#include "VarianceMin.h"

namespace vanagandr
{
namespace finance
{

Matrix variance_min(const Matrix& cov, bool full)
{
    Matrix A = Matrix::Zero(cov.rows() + 1, cov.cols() + 1);

    // Derivatives
    A.block(0, 0, cov.rows(), cov.cols()) = cov;

    //Weights
    A.block(0, cov.cols(), cov.rows(), 1) = - Matrix::Ones(cov.rows(), 1);
    A.block(cov.rows(), 0, 1, cov.cols()) =   Matrix::Ones(1, cov.cols());

    // Derivatives = 0
    Matrix B = Matrix::Zero(cov.rows() + 1, 1);

    // sum of weights = 1
    B(cov.rows(), 0) = 1;

    // PartialPivLU 	Invertible                          Fast
    // LLT              Positive definite                   Very fast
    // LDLT             Positive or negative semidefinite1 	Very fast
    if (full)
        return A.lu().solve(B);

    return A.lu().solve(B).topRows(cov.rows());
}

Matrix variance_min(const Matrix& cov, const Matrix& ret, const double rt, bool full)
{
    Matrix A = Matrix::Zero(cov.rows() + 2, cov.cols() + 2);

    // Derivatives
    A.block(0, 0, cov.rows(), cov.cols()) = cov;

    //Weights
    A.block(0, cov.cols(), cov.rows(), 1) = - Matrix::Ones(cov.rows(), 1);
    A.block(cov.rows(), 0, 1, cov.cols()) =   Matrix::Ones(1, cov.cols());

    // Returns
    A.block(0, cov.cols() + 1, cov.rows(), 1) = - ret;
    A.block(cov.rows() + 1, 0, 1, cov.cols()) =   ret.transpose();

    // Derivatives = 0
    Matrix B = Matrix::Zero(cov.rows() + 2, 1);

    // sum of weights = 1
    B(cov.rows(), 0) = 1;

    // returns
    B(cov.rows() + 1, 0) = rt;

    if (full)
        return A.lu().solve(B);

    return A.lu().solve(B).topRows(cov.rows());
}

Matrix variance_min(const Matrix& cov, const Matrix& ret, const double rt,
                    const double rf, bool full)
{
    Matrix A = Matrix::Zero(cov.rows() + 3, cov.cols() + 3);

    // Derivatives
    A.block(0, 0, cov.rows(), cov.cols()) = cov;

    //Weights
    A.block(0, cov.cols() + 1, cov.rows() + 1, 1) = - Matrix::Ones(cov.rows() + 1, 1);
    A.block(cov.rows() + 1, 0, 1, cov.cols() + 1) =   Matrix::Ones(1, cov.cols() + 1);

    // Returns
    A.block(0, cov.cols() + 2, cov.rows(), 1) = - ret;
    A.block(cov.rows() + 2, 0, 1, cov.cols()) =   ret.transpose();

    A(cov.cols(), cov.rows() + 2) = - rf;
    A(cov.cols() + 2, cov.rows()) =   rf;

    // Derivatives = 0
    Matrix B = Matrix::Zero(cov.rows() + 3, 1);

    // sum of weights = 1
    B(cov.rows() + 1, 0) = 1;

    // returns
    B(cov.rows() + 2, 0) = rt;

    if (full)
        return A.lu().solve(B);

    return A.lu().solve(B).topRows(cov.rows());
}

Matrix variance_min(const Matrix& cov, const Matrix& ret, const Matrix& rt, bool full)
{
    Matrix A = Matrix::Zero(cov.rows() + 2, cov.cols() + 2);

    // Derivatives
    A.block(0, 0, cov.rows(), cov.cols()) = cov;

    //Weights
    A.block(0, cov.cols(), cov.rows(), 1) = - Matrix::Ones(cov.rows(), 1);
    A.block(cov.rows(), 0, 1, cov.cols()) =   Matrix::Ones(1, cov.cols());

    // Returns
    A.block(0, cov.cols() + 1, cov.rows(), 1) = - ret;
    A.block(cov.rows() + 1, 0, 1, cov.cols()) =   ret.transpose();

    // Derivatives = 0
    Matrix B = Matrix::Zero(cov.rows() + 2, rt.rows());

    // sum of weights = 1
    B.row(cov.rows()) = Matrix::Ones(1, rt.rows());

    // returns
    B.row(cov.rows() + 1) = rt.transpose();

    if (full)
        return A.lu().solve(B);

    return A.lu().solve(B).topRows(cov.rows());
}

Matrix variance_min(const Matrix& cov, const Matrix& ret, const Matrix& rt,
                    const double rf, bool full)
{
    Matrix A = Matrix::Zero(cov.rows() + 3, cov.cols() + 3);

    // Derivatives
    A.block(0, 0, cov.rows(), cov.cols()) = cov;

    //Weights
    A.block(0, cov.cols() + 1, cov.rows() + 1, 1) = - Matrix::Ones(cov.rows() + 1, 1);
    A.block(cov.rows() + 1, 0, 1, cov.cols() + 1) =   Matrix::Ones(1, cov.cols() + 1);

    // Returns
    A.block(0, cov.cols() + 2, cov.rows(), 1) = - ret;
    A.block(cov.rows() + 2, 0, 1, cov.cols()) =   ret.transpose();

    A(cov.cols(), cov.rows() + 2) = - rf;
    A(cov.cols() + 2, cov.rows()) =   rf;

    // Derivatives = 0
    Matrix B = Matrix::Zero(cov.rows() + 3, rt.rows());

    // sum of weights = 1
    B.row(cov.rows() + 1) = Matrix::Ones(1, rt.rows());

    // returns
    B.row(cov.rows() + 2) = rt.transpose();

    if (full)
        return A.lu().solve(B);

    return A.lu().solve(B).topRows(cov.rows());
}

Matrix correl(const Matrix& cov, bool lower)
{
    Matrix cor = Matrix::Zero(cov.rows(), cov.cols());

    for(int i = 1, n = cov.rows(); i < n; i ++)
        for(int j = 0; j < i; j++)
            cor(i, j) = cov(i, j)/ sqrt(cov(i, i) * cov(j, j));

    //cor = cor + cor.transpose();
    cor.diagonal() = Eigen::Diagonal<Matrix>::Ones(cov.rows(), 1);

    if (lower)
        return cor;
    else
        return cor.transpose();
}

} // finance namespace
} // vanagandr namespace
