#include "Matrix.h"

namespace vanagandr {
namespace math {

// assume data are from older to newer
Matrix compute_returns(const Matrix& data)
{
    int n = data.rows();
    Matrix ret = data.bottomRows(n - 1).cwiseQuotient(data.topRows(n - 1));
    return mlog(ret);
}

Matrix compute_covariance(const Matrix& data)
{
    Matrix mean = data.colwise().mean();
    // we cant use broadcasting
    // some problem with mean not being a vector
    mean = (data - Matrix::Ones(data.rows(), 1) * mean);
    return (mean.transpose() * mean) / double(data.rows());
}

Matrix compute_correlation(const Matrix& cov)
{
    //Matrix cov = compute_covariance(data);
    Matrix correl = Matrix::Zero(cov.rows(), cov.cols());

    for(int i = 1, n = cov.rows(); i < n; i++)
        for(int j = 0; j < i; j++)
            correl(i, j) = cov(i, j) / sqrt(cov(i, i) * cov(j, j));

    correl = correl + correl.transpose().eval();
    correl.diagonal() = Eigen::Diagonal<Matrix>::Ones(cov.rows(), 1);

    return correl;
}

}
}
