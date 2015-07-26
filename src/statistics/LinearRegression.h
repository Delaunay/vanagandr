#ifndef VANAGANDR_STATISTIC_LINEARREG_HEADER
#define VANAGANDR_STATISTIC_LINEARREG_HEADER

#include "../enum.h"
// #define CERES_SOLVER

// TODO add Regularization and Robust option
// add Ceres SOlver

namespace vanagandr
{
namespace statistics
{
    enum Method
    {
        NormalEquation,
        JacobiSVD,
        Iterative
    };

    enum LROption
    {
        Pure,
        Regularized,
        Robust,
    };

    /*!
     * \brief lag operator, remove the most recent observation
     * \param Y
     * \return
     */
    Matrix lag_op(const Matrix& Y, int lag);


    // need to review this piece of code
    /*!
     * \brief ar_matrix return the matrix X used to compute the ols estimate of an AR model
     * with p lags. if Y is a matrix then each columns has the same treatment. a column of 1 is
     * also added
     * \param Y
     * \param p AR order
     * \return
     */
    Matrix ar_matrix(const Matrix& Y, int p);
    Matrix ar_matrix(const Matrix& Y, int p, const Matrix& u);

    Matrix estimator_variance(const Matrix& X, const Matrix& res);

    /*!
     * \brief rsquare % of variance explained by the model
     * Models Variance / True variance = ESS / TSS
     * \param ymod  : Y values fitted by the model  : size(nx1)
     * \param ytrue : True Y Values                 : size(nx1)
     * \return scalar size(1x1)
     */
    double rsquare(const Matrix& ymod, const Matrix& ytrue);

    template<Method m = NormalEquation, LROption o = Pure>
    struct LinearRegression
    {
    public:
        /*!
         * \brief solve the linear least square by solving
         *  (X' X) * B = (X' Y)
         * faster than JacobiSVD but less reliable
         * \param X
         * \param Y
         * \return the solution B
         */
        static Matrix linear_regression(const Matrix& X, const Matrix& Y)
        {
            return (X.transpose() * X).ldlt().solve(X.transpose() * Y);
        }

        static Matrix auto_regress(const Matrix& Y, int p)
        {
            return linear_regression(ar_matrix(Y, p), Y.bottomRows(Y.rows() - p));
        }
        static Matrix auto_regress(const Matrix& Y, int p, const Matrix& U)
        {
            return linear_regression(ar_matrix(Y, p, U), Y.bottomRows(Y.rows() - p));
        }
    };

    template<>
    struct LinearRegression<JacobiSVD>
    {
    public:
        /*!
         * \brief linear_regression
         * more reliable than NormalEquation method but slower
         * \param X
         * \param Y
         * \return the solution t
         */
        static Matrix linear_regression(const Matrix& X, const Matrix& Y)
        {
            return X.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(Y);
        }

        static Matrix auto_regress(const Matrix& Y, int p)
        {
            return linear_regression(ar_matrix(Y, p), Y.bottomRows(Y.rows() - p));
        }
        static Matrix auto_regress(const Matrix& Y, int p, const Matrix& U)
        {
            return linear_regression(ar_matrix(Y, p, U), Y.bottomRows(Y.rows() - p));
        }
    };

#if CERES_SOLVER
    template<>
    struct LinearRegression<Iterative>
    {
        /*!
         * \brief solve the linear least square using Ceres Solver
         * for Non linear least square
         * good for big problems
         * \param X
         * \param Y
         * \return the solution B
         */
        static Matrix linear_regression(const Matrix& X, const Matrix& Y)
        {

        }

        static Matrix auto_regress(const Matrix& Y, int p)
        {
            return linear_regression(ar_matrix(Y, p), Y.bottomRows(Y.rows() - p));
        }
    };
#endif



}
}

#endif
