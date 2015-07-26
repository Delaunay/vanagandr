#ifndef VANAGANDR_MATH_PARTIALDIFFERENTIALEQUATION_HEADER
#define VANAGANDR_MATH_PARTIALDIFFERENTIALEQUATION_HEADER

#include "../enum.h"

#include <eigen3/Eigen/Sparse>

namespace vanagandr{
namespace pde{

enum Solver
{
    Explicit = 0,
    Implicit = 1,
    CrankNicolson = 2
};


/*!
 * \brief The FiniteDifference1D class is used to solve one dimension partial differential
 * equations.
 *
 *      \partial g / \partial t + \partial^2 g / \partial S^2 a(S, t) + \partial g / \partial S b(S, t) + g c(S, t)
 *
 *  3 Solvers are available:
 *       - Explicit finite difference
 *       - Implicit
 *       - Crank-Nicolson   <- Best
 *
 */
template<typename T, typename T, Solver solver = Explicit>
class FiniteDifference1D
{
public:

    typedef Eigen::Matrix<T, -1,  1> DenseType;
    typedef Eigen::Matrix<T, -1, -1> SparseType;
    typedef Eigen::Matrix<T, -1,  1> SparseColumnType;

    FiniteDifference1D(
            T Smax, T Smin,
            unsigned int sstep,
            T time,
            unsigned int tstep):
        _dt(time / tstep), _ds((Smax - Smin)/sstep),
        _v1(_dt / (_ds * _ds)), _v2(_dt / _ds),
        _A(SparseType::Zero(sstep - 1, sstep - 1)),
        _sol(DenseType::Zero(sstep - 1, 1)),
        _r(SparseColumnType::Zero(sstep - 1, 1)),
        _tstep(tstep), _smax(Smax), _smin(Smin), _time(time)
    {}

    // functions
    virtual T d2g(const T& S, const T& t) const = 0;
    virtual T dg (const T& S, const T& t) const = 0;
    virtual T g  (const T& S, const T& t) const = 0;

    // Bound Condition
    virtual T initial_time(const T& S) = 0;
    virtual T max         (const T& t) = 0;
    virtual T min         (const T& t) = 0;

    // How time advance
    virtual T time(const unsigned int& ite) {   return T(ite) * _dt;    }

    // virtual T time(const unsigned int& ite) {   return _time - T(ite) * _dt;    }

    virtual const DenseType& solve()
    {
        generate_tridiagonal(0);

        for (int i = 0; i < _tstep; i++)
        {
            _sol = _A * _sol + _r;
            update_r(time(i));
        }
    }

    virtual void generate_tridiagonal(const T& time)
    {
        for(int i = 0; i < _sstep - 1; i++)
        {
            T St = T(i) * _ds + _smin;

            if (i != 0)
                _A(i, i - 1) = A(St, time);

            _A(i, i) = B(St, time);

            if (j < _sstep)
                _A(i, i + 1) = C(St, time);
        }
    }

protected:

    T a(const T& S, const T& t) const    {   return _v1 * d2g(S, t) - _v2 * dg(S, t) / T(2); }
    T b(const T& S, const T& t) const    {   return T(1) - T(2) * _v1 * d2g(S, t) + _dt * g(S, t); }
    T c(const T& S, const T& t) const    {   return _v1 * d2g(S, t) + _v2 * dg(S, t) / T(2); }

    void update_r(const T& time)
    {
        _r(0) =  max(time) * c(_smax, time);
        _r(_sstep - 1) = min(time) * a(_smin, time);
    }

    T _smax;    T _smin;
    T _ds;      T _dt;
    T _v1;      T _v2;
    T _time;

    unsigned int _tstep;

    SparseColumnType _r;
    SparseType       _A;
    DenseType        _sol;
};

}
}


#endif
