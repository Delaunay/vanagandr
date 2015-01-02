#ifndef VANAGANDR_FINANCE_MDFE_HEADER
#defien VANAGANDR_FINANCE_MDFE_HEADER

//#include <Eigen/Dense>

//typedef Eigen::MatrixXd Matrix;
//typedef Eigen::VectorXd Column;

template<typename Real = double>
struct Heston
{
public:
    Heston(Real K, Real r, Real Ka, Real the, Real sig, Real rho):
        K(K), r(r), kappa(ka), theta(the), sigma(sig), rho(rho)
    {}

    Real kappa;
    Real theta;
    Real sigma;
    Real rho;

    Real r;
    Real K;
};


template<typename Real = double, typename ModelType = Heston<> >
class MDF
{
public:
    typedef Eigen::Matrix<Real, -1, -1> Matrix;
    typedef Eigen::Matrix<Real, -1,  1> Column;

    struct GridSize
    {
    public:
        GridSize(Real xma, Real xmi, Real dx,
                 Real yma, Real ymi, Real dy):
            xMin(xmi), xMax(xma), dx(dx), yMin(ymi), yMax(yma), dy(dy)
        {}

        Real xMin;
        Real xMax;
        Real dx;
        Real yMin;
        Real yMax;
        Real dy;
    };


    MDF():
    {}

    // function multiplied by the derivatives
    virtual Real func_d2g_d2x(const Real& x, const Real& y) { return y * x * x / 2.0;}
    virtual Real func_dg_dx  (const Real& x, const Real& y) { return _Model->r * x;   }
    virtual Real func_d2g_d2y(const Real& x, const Real& y) { return y * _Model->sigma * _Model->sigma / 2.0; }
    virtual Real func_dg_dy  (const Real& x, const Real& y) { return _Model->kappa * (_Model.beta - y); }
    virtual Real func_d2g_dxy(const Real& x, const Real& y) { return _Model->sigma * x * y * _Model->rho; }
    virtual Real func_g      (const Real& x, const Real& y) { return - _Model->r; }

//    // aliases of func_xx
//    virtual Real a(const Real& x, const Real& y) { return func_d2g_d2x(x, y); }
//    virtual Real b(const Real& x, const Real& y) { return func_dg_dx(x, y); }
//    virtual Real c(const Real& x, const Real& y) { return func_g(x, y); }
//    virtual Real d(const Real& x, const Real& y) { return func_d2g_d2y(x, y); }
//    virtual Real e(const Real& x, const Real& y) { return func_dg_dy(x, y); }
//    virtual Real f(const Real& x, const Real& y) { return func_d2g_dxy(x, y); }

    // boundaries
    virtual Column boundary_xmin(const unsigned int& i);
    virtual Column boundary_xmax(const unsigned int& i);
    virtual Column boundary_ymin(const unsigned int& i);
    virtual Column boundary_ymax(const unsigned int& i);
    virtual Matrix boundary_tmin();

    // weights
    Real value_a(const Real& x, const Real& y, const Real& dt);
    Real value_b(const Real& x, const Real& y, const Real& dt);
    Real value_d(const Real& x, const Real& y, const Real& dt);
    Real value_e(const Real& x, const Real& y, const Real& dt);
    Real value_f(const Real& x, const Real& y, const Real& dt);
    Real value_h(const Real& x, const Real& y, const Real& dt);

    virtual Matrix solve_explicit(Real T, unsigned int n)
    {
        unsigned int nx = (_GridSize->xMax - _GridSize->xMin)/ _GridSize->dx;
        unsigned int ny = (_GridSize->yMax - _GridSize->yMin)/ _GridSize->dy;
        Real dt = T / Real(n);

        Matrix Un0 = boundary_tmin();
        Matrix Un1;

        unsigned int nbx = nx - 2;
        unsigned int nby = ny - 2;

        // generate func_xx matrix
        Matrix A = ;
        Matrix B = ;
        Matrix D = ;

        Matrix E = ;
        Matrix F = ;
        Matrix H = ;

        for (unsigned int i = 0; i < n; i++)
        {
            Un1.block(1, 1, nbx, nby) =
                            E.cwiseProduct(Un0.block(1, 1, nbx, nby)) +
                            B.cwiseProduct(Un0.block(0, 1, nbx, nby)) +
                            D.cwiseProduct(Un0.block(1, 0, nbx, nby)) +
                            H.cwiseProduct(Un0.block(2, 1, nbx, nby)) +
                            F.cwiseProduct(Un0.block(1, 2, nbx, nby)) +
                            A.cwiseProduct(Un0.block(0, 0, nbx, nby) +
                                           Un0.block(2, 2, nbx, nby) -
                                           Un0.block(0, 2, nbx, nby) -
                                           Un0.block(2, 0, nbx, nby));

            Un0 = Un1;

            // add missing boundaries
            Un0.col(0) = boundary_xmin();
            Un0.col()  = boundary_xmin();
            Un0.row(0) = boundary_xmin();
            Un0.row()  = boundary_xmin();
        }

        return Un0;
    }


private:
    ModelType* _Model;
    GridSize*  _GridSize;

};
#endif
