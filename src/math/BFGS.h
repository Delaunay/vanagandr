#ifndef VANAGANDR_MATH_BFGS_HEADER
#define VANAGANDR_MATH_BFGS_HEADER

#include <cmath>
#include "../enum.h"

namespace vanagandr {
namespace math{


typedef double Real;

//template<typename Real>
struct CostFunction
{

    //  provide objective function and gradient evaluations.
    // cost function
    virtual Real evaluate (Real const* parameters, Real* grad, const step)
    {
        return 0;
    }

    virtual Real evaluate (const Vector& parameters, Vector& grad, const step)
    {
        return 0;
    }

    int n;
};




//template<typename Real>
struct Options
{
    Options():
        m(6), epsilon(1e-5), past(0), delta(0), max_iterations(100), linesearch(0),
        max_linesearch(20), min_step(1e-20), max_step(1e+20), ftol(1e-4), wolfe(0.9),
        gtol(0.9), xtol(0),

        orthantwise_c(0), orthantwise_end(0), orthantwise_start(0)
    {}

    int  m;        // The number of corrections to approximate the inverse hessian matrix.
    Real epsilon;  // 1e-5 Parameters change
    int  past;     // 0
    Real delta;    // This parameter determines the minimum rate of decrease of the objective function
    int  max_iterations;
    int  linesearch;
    int  max_linesearch;
    Real min_step;          // 1e-20 The minimum step of the line search routine
    Real max_step;          // 1e+20
    Real ftol;              // 1e-4  accuracy of the line search routine should be smaller than 0.5
    Real wolfe;             // 0.9 A coefficient for the Wolfe condition. smaller than 1 greater than ftol
    Real gtol;              // 0.9 accuracy of the line search routine smaller for large probs
    Real xtol;              // The machine precision for floating-point values.

    // OWL QN
    Real orthantwise_c;     // 0
    int  orthantwise_start;
    int  orthantwise_end;
};



#include <vector>

typedef Eigen::VectorXd Vector;

struct IterationData {

    IterationData():
        alpha(0), ys(0)
    {}

    Real   alpha;
    Vector s;     /* [n] */
    Vector y;     /* [n] */
    Real   ys;    /* vecdot(y, s) */
};


struct LineSearch
{
    int evaluate(Vector& x, Vector& f, Vector& g, Vector& s,
                 Real step,
                 const Vector& xp, const Vector& gp,

                 const Vector& param)
    {

    }
};

typedef int (*line_search_proc)(
    int n,
    Vector x,
    Vector f,
    Real *g,
    Real *s,
    Real *stp,
    const Real* xp,
    const Real* gp,
    Real *wa,
    const Real *param
    );

static int line_search_morethuente(
    int n,
    Real *x,
    Real *f,
    Real *g,
    Real *s,
    Real *stp,
    const Real* xp,
    const Real* gp,
    Real *wa,
    const Real *param
    );


int bfgs(CostFunction* cost, Options opt = Options())
{
    // >> Allocate Memory
    int ret, i, j, k, ls, end, bound,
          n = cost->n,
          m = opt->m;

    Vector  x = Vector::Zero(n);
           xp = Vector::Zero(n);
            g = Vector::Zero(n),
           gp = Vector::Zero(n),
            d = Vector::Zero(n),
            w = Vector::Zero(n);

    Real step, ys, yy, xnorm, gnorm, beta,
           fx = 0,
         rate = 0;

    line_search_proc linesearch = line_search_morethuente;

    std::vector<IterationData> lm(m);
    for (i = 0;i < m; i++)
    {
       lm[i].s = Vector::Zero(n);
       lm[i].y = Vector::Zero(n);
    }

    // Allocate Memory End <<

    // First Evaluation
    fx = cost->evaluate(x, g, 0);


    // H_0 => eye matrix

    // direction
    d = g;

    xnorm = x.norm();
    gnorm = g.norm();

    if (xnorm < 1.0)
        xnorm = 1.0;

    if (gnorm / xnorm <= opt.epsilon)
        return LBFGS_ALREADY_MINIMIZED;

    step = 1.0 / d.norm();

    k = 1;
    end = 0;

    for(;;)
    {
        xp = x;
        gp = g;

        ls = linesearch.evaluate();

        // ls error
        if (ls < 0)
        {
            x = xp;
            g = gp;
            ret = ls;
        }

        xnorm = x.norm();
        gnorm = g.norm();

        if (xnorm < 1.0)
            xnorm = 1.0;

        if (gnorm / xnorm <= opt.epsilon)
            return LBFGS_SUCCESS;

        if (opt.max_iterations < k+1)
            return LBFGSERR_MAXIMUMITERATION;

        lm[end]->s = x - xp;
        lm[end]->y = g - gp;

        ys = lm[end]->s.dot(lm[end]->y);
        yy = lm[end]->y.dot(lm[end]->y);

        lm[end]->ys = ys;

        bound = (m <= k) ? m : k;
        k++;
        end = (end + 1) % m;

        // steepest direction
        d = g;

        j = end;

        for(i = 0; i < bound; i++)
        {
            j = (j + m - 1) % m;    /* if (--j == -1) j = m-1; */
            it = &lm[j];

            /* \alpha_{j} = \rho_{j} s^{t}_{j} \cdot q_{k+1}. */

            vecdot(lm[j]->alpha, it->s, d, n);

            lm[j]->alpha /= lm[j]->ys;

            /* q_{i} = q_{i+1} - \alpha_{i} y_{i}. */
            vecadd(d, lm[j]->y, -lm[j]->alpha, n);
        }


    }

    return ret;
}


}
}
#endif
