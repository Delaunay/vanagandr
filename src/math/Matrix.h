#ifndef VANAGANDR_MATH_MATRIX_HEADER
#define VANAGANDR_MATH_MATRIX_HEADER

#include "../enum.h"
#include <cmath>

// provide some matrix functions
//
// Matrix.unaryExpr(ptr_fun(log))  => mlog(Matrix)
//                                    msqr(Matrix)  => Matrix .^2
//                                    msqrt(Matrix) => Matrix .^(1/2)

namespace vanagandr
{
namespace math
{

// function are defined such as :
// compute_correlation(compute_covariance(compute_returns(data)))

// compute correlation does not compute the covariance
// compute covariance does not compute the returns
// Users will not ask to compute twice the same thing useless they want to

// assume data are from older to newer
Matrix compute_returns      (const Matrix& data_price);
Matrix compute_covariance   (const Matrix& data_percentage);
Matrix compute_correlation  (const Matrix& data_covariance, bool full=true);

// Not useful
namespace internal{
    template<typename T>
    T log_spec(T x)
    {
        return log(x);
    }

    template<typename T>
    T sqr_spec(T x)
    {
        return pow(x, T(2.0));
    }

    template<typename T>
    T sqrt_spec(T x)
    {
        return sqrt(x);
    }

    template<typename T>
    T sigmoid_spec(T x)
    {
        return 1.0 / (1.0 + exp(- x));
    }

    template<typename T>
    T exp_spec(T x)
    {
        return exp(x);
    }

    template<typename Scalar, int RowsAt, int ColsAt>
    struct pow_visitor
    {
    public:
        pow_visitor(Eigen::Matrix<Scalar, RowsAt, ColsAt> val):
            val(val)
        {}

        void init(const Scalar& value, int i, int j)
        {
            val(i, j) = pow(val(i, j), value);
        }

        void operator() (const Scalar& value, int i, int j)
        {
            val(i, j) = pow(val(i, j), value);
        }

        Eigen::Matrix<Scalar, RowsAt, ColsAt> val;
    };

    template<typename Scalar, int RowsAt, int ColsAt>
    struct pow_visitor_broadcast
    {
    public:
        pow_visitor_broadcast(Scalar s, Eigen::Matrix<Scalar, RowsAt, ColsAt> val):
            s(s), val(val)
        {}

        void init(const Scalar& value, int i, int j)
        {
            val(i, j) = pow(s, value);
        }

        void operator() (const Scalar& value, int i, int j)
        {
            val(i, j) = pow(s, value);
        }

        Scalar s;
        Eigen::Matrix<Scalar, RowsAt, ColsAt>         val;
    };
}

template<typename T>
Eigen::Matrix<T, -1, -1> mlog(const Eigen::Matrix<T, -1, -1>& x)
{
    return x.array().log();//x.unaryExpr(std::ptr_fun(internal::log_spec<T>));
}

template<typename T>
Eigen::Matrix<T, -1, -1> mexp(const Eigen::Matrix<T, -1, -1>& x)
{
    return x.unaryExpr(std::ptr_fun(internal::exp_spec<T>));
}

template<typename T>
Eigen::Matrix<T, -1, -1> msqr(const Eigen::Matrix<T, -1, -1>& x)
{
    return x.unaryExpr(std::ptr_fun(internal::sqr_spec<T>));
}

template<typename T>
Eigen::Matrix<T, -1, -1> msqrt(const Eigen::Matrix<T, -1, -1>& x)
{
    return x.cwiseSqrt();
}

template<typename T>
Eigen::Matrix<T, -1, -1> msigmoid(const Eigen::Matrix<T, -1, -1>& x)
{
    return x.unaryExpr(std::ptr_fun(internal::sigmoid_spec<T>));
}

// a .* b
template<typename T>
Eigen::Matrix<T, -1, -1> product(const Eigen::Matrix<T, -1, -1>& a, const Eigen::Matrix<T, -1, -1>& b)
{
    return a.cwiseProduct(b);
}

// a ./ b
template<typename T>
Eigen::Matrix<T, -1, -1> quotient(const Eigen::Matrix<T, -1, -1>& a, const Eigen::Matrix<T, -1, -1>& b)
{
    return a.cwiseQuotient(b);
}

// makes a copy
// not sure if it is really faster
template<typename Scalar, int RowsAt, int ColsAt>
Eigen::Matrix<Scalar, RowsAt, ColsAt> mpow(const Eigen::Matrix<Scalar, RowsAt, ColsAt>& a, const Eigen::Matrix<Scalar, RowsAt, ColsAt>& b)
{
    // if a.rows() != b.rows || a.cols() != b.cols()
    // size mismatch
    internal::pow_visitor<Scalar, RowsAt, ColsAt> pv(a);
    b.visit(pv);
    return pv.val;
}

template<typename Scalar, int RowsAt, int ColsAt>
Eigen::Matrix<Scalar, RowsAt, ColsAt> mpow(Scalar s, const Eigen::Matrix<Scalar, RowsAt, ColsAt>& b)
{
    // if a.rows() != b.rows || a.cols() != b.cols()
    // size mismatch
    internal::pow_visitor_broadcast<Scalar, RowsAt, ColsAt> pv(s, b);
    b.visit(pv);
    return pv.val;
}

}
}


#endif
