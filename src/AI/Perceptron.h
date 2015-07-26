#ifndef VANAGANDR_AI_PERCEPTRON_HEADER
#define VANAGANDR_AI_PERCEPTRON_HEADER

#include <vector>

#include "../containers/Capacity.h"
#include "../enum.h"
#include "../math/Matrix.h"

using namespace std;

namespace vanagandr{

namespace ai{

    /*!
     *  structure:{
     *      input: 400,
     *      hidden: [25],
     *      output: 10,
     *  }
     *
     */
    struct BrainStructure
    {
        BrainStructure(Index in, const vector<Index>& h, Index ou):
            input(in), hidden(h), output(ou), total(count_total())
        {}

        // compute the number of parameters
        Index count_total()
        {
            Index ret = 0, old = input;
            for(Index i = 0, n = hidden.size(); i < n; i++)
            {
                ret += (old  + 1) * hidden[i];
                old = hidden[i];
            }

            return ret + (old  + 1) * output;
        }

        Index input;
        vector<Index> hidden;
        Index output;
        const Index total;
    };

    template<typename T>
    struct Point
    {
        Point(T x, T y, T z):
            x(x), y(y), z(z)
        {}

        T x, y, z;
    };

    typedef BrainStructure Structure;

    /*
     *  Params are allocate as a big chunk of memory then we use Eigen::Maps
     *  to recreate parameter matrix (theta). it also makes numerical gradient computation
     *  easy
     *
     * Memory is allocated using std::vector<double> _???_param
     * allocated memory is then represented as Matrix using Eigen::Map<>
     */
    class Perceptron
    {
        public:
            // Perceptron Structure
            // bool optimize: Should we preallocate memory for optimization

            Perceptron(Structure& s):
                _structure(s), _theta_param(vector<double>(s.total)),
                _layer(s.hidden.size() + 1),
                _theta(vector<Matrix>(_layer)),
                _pre_allocated(false),_a_size(0), _z_size(0)
            {
                _allocate_parameters();
            }

            static Matrix sigmoid(const Matrix& e)
            {
                return (1.0 / (1.0 + (-e.array()).exp())).matrix();
            }

            static Matrix sigmoid_grad(const Matrix& e)
            {
                Eigen::ArrayXXd z = sigmoid(e);
                return (z * (1 - z)).matrix();
            }

            const Index&      parameter_size()          {   return _structure.total;                     }
            unsigned long int used_memory()             {   return (parameter_size() + _a_size + _z_size + _grad_param.size())* sizeof(double);    }
            Index             layer_size() const        {   return _theta.size();                        }

            // return ith layer parameters
            Matrix&           theta(const Index& i)     {   return _theta[i];    }
            Matrix&           a(const Index& i)         {   return _a[i];    }
            Matrix&           z(const Index& i)         {   return _z[i];    }


            void fit(const Matrix& x, const Matrix& y)
            {
                _allocate_temporary(x.rows());
                //

                //BFGS

                //
                shrink();
            }

            double cost(const Matrix& x, const Matrix& y)
            {
                _h = _forward_propagation(x);
                return ((_h.array().log() * y.array()).sum() + ((1.0 - _h.array()).log() * (1 - y.array())).sum()) / x.rows();
            }

            Matrix predict(Matrix& x)
            {
                Matrix aa = Matrix::Ones(x.rows(), x.cols() + 1),
                       zz;

                aa.rightCols(aa.cols() - 1) = x;
                zz = aa * theta(0);

                for(int i = 0, n = _structure.hidden.size(); i < n; i++)
                {
                    aa = Matrix::Ones(zz.rows(),zz.cols() + 1);
                    aa.rightCols(aa.cols() - 1) = sigmoid(zz);
                    zz = aa * theta(i + 1);
                }

                return sigmoid(zz);
            }

            void gradient(const Matrix& y)
            {
                (*_grad.rbegin()) = _h - y;

                for(int i = _grad.size() - 1; i >= 0; --i)
                {
                    Matrix& tt = theta(i);
                    _grad[i - 1] = _grad[i] * tt.rightCols(tt.cols() - 1) * sigmoid_grad(z(i - 1));
                }

                for(int i = 0, n = _grad.size(); i < n; ++i)
                {
                    _grad[i] = _grad[i].transpose() * a(i);
                }
            }

            // Perf Stats
            // return accuracy per column
            double accuracy(Matrix& x, Matrix& y)
            {
                return ((y.array() == predict(x).array()).rowwise().sum() / y.cols())(0, 0);
            }

            double ff1()
            {}//...
            //

            // free Temporary variables allocated for the optimization
            void shrink()
            {
                _a_param = vector<double>(0);
                _z_param = vector<double>(0);
                _grad_param = vector<double>(0);

                _a = vector<Matrix>(0);
                _z = vector<Matrix>(0);
                _grad = vector<Matrix>(0);
                _h = Matrix();

                _pre_allocated = false;
            }

        protected:
            // Perceptron Structure
            Index                 _layer;             // Number of layer
            Structure&            _structure;
            bool                  _pre_allocated;

            // Parameter to optimize
            vector<double>        _theta_param; // Memory
            vector<Matrix>        _theta;       // Representation

            // Preallocation for NN optimization
            // Temporary used to compute Gradient
            Index                 _a_size;
            vector<double>        _a_param;     // Memory
            vector<Matrix>        _a;           // Representation

            Index                 _z_size;
            vector<double>        _z_param;     // Memory
            vector<Matrix>        _z;           // Representation

            // Gradient
            vector<double>        _grad_param;
            vector<Matrix>        _grad;

            // Prediction
            Matrix                _h;          //

    public:

    void _allocate_parameters()
    {
        Index i = 0, old = _structure.input, param_size = 0;

        for(i = 0; i < _structure.hidden.size(); i++)
        {
            _theta[i] = Eigen::Map<Matrix>(&_theta_param[param_size], // Pointer to the first parameter
                                             old + 1,                   // Number of row
                                            _structure.hidden[i]);     // Number of Column

            param_size += (old  + 1) * _structure.hidden[i];
            old = _structure.hidden[i];
        }

        _theta[i] = Eigen::Map<Matrix>(&_theta_param[param_size], // Pointer to the first parameter
                                         old + 1,                   // Number of row
                                        _structure.output);        // Number of Column
    }

    void _compute_temp_size(const Index& train_size)
    {
        _a_size = train_size * (_structure.input + 1);
        _z_size = 0;

        for(Index i = 0; i < _structure.hidden.size(); ++i)
        {
            _a_size += train_size * (_structure.hidden[i] + 1);
            _z_size += train_size * (_structure.hidden[i]);
        }

        _z_size += train_size * (_structure.output);
    }

    void _allocate_temporary(const Index& train_size)
    {
        _compute_temp_size(train_size);

        _a_param = vector<double>(_a_size);
        _z_param = vector<double>(_z_size);
        _grad_param = vector<double>(_structure.total);

        _a = vector<Matrix>(_layer);
        _z = vector<Matrix>(_layer);
        _grad = vector<Matrix>(_layer);

        Index i = 0, old = _structure.input,
                param_size = 0,
                a_size = 0,
                z_size = 0;

        _a[i] = Eigen::Map<Matrix>(&_a_param[a_size], train_size, old + 1);
        _a[i].fill(1);
        a_size += train_size * (old + 1);

        for(i = 0; i < _structure.hidden.size(); i++)
        {
            _a[i]    = Eigen::Map<Matrix>(&_a_param[a_size], train_size, _structure.hidden[i] + 1);
            _a[i].fill(1);
            _z[i]    = Eigen::Map<Matrix>(&_z_param[z_size], train_size, _structure.hidden[i]);
            _z[i].fill(1);

            a_size += train_size * (_structure.hidden[i] + 1);
            z_size += train_size * _structure.hidden[i];

            _grad[i] = Eigen::Map<Matrix>(&_grad_param[param_size], // Pointer to the first parameter
                                            old + 1,                // Number of row
                                           _structure.hidden[i]);   // Number of Column

            param_size += (old  + 1) * _structure.hidden[i];
            old = _structure.hidden[i];
        }

        _z[i]    = Eigen::Map<Matrix>(&_z_param[z_size], train_size, _structure.output);
        _z[i].fill(1);
        _grad[i] = Eigen::Map<Matrix>(&_grad_param[param_size], // Pointer to the first parameter
                                        old + 1,                // Number of row
                                       _structure.output);      // Number of Column
    }

    void printf(ostream& str)
    {
        str <<"Perceptron \n"
              "> "<< parameter_size() << " parameters in " << layer_size() << " layers \n";

        for(int i = 0; i < _theta.size(); i++)
            str << "=> " << i  + 1 << " (" << _theta[i].rows()
                                    << "x" << _theta[i].cols() << ") = "
                                    << _theta[i].rows() * _theta[i].cols() << "\n";

        str << "Memory Usage Total: " << pretty_print_capacity(used_memory(), Power2)<< "\n";
    }


    vector<double> numerical_gradient(const Matrix& x, const Matrix& y, const double e)
    {
        Index n = parameter_size();
        vector<double> grad   = vector<double>(n, 0);

        double loss1 = 0, loss2 = 0, old_val;

        for (int i = 0; i < n; i++)
        {
            old_val = _theta_param[i];

            _theta_param[i] += e;
            loss1 = cost(x, y);

            _theta_param[i] = old_val;

            _theta_param[i] -= e;
            loss2 = cost(x, y);

            grad[i] = (loss2 - loss1) / (2.0 * e);
            _theta_param[i] = old_val;
        }

        return grad;
    }

    Matrix _forward_propagation(const Matrix& x)
    {
        Matrix& aa = a(0), zz = z(0);

        aa.rightCols(aa.cols() - 1) = x;

        zz = aa * theta(0);

        for(int i = 0, n = _structure.hidden.size(); i < n; i++)
        {
            aa = a(i + 1);
            aa.rightCols(aa.cols() - 1) = sigmoid(zz);

            zz = z(i + 1);
            zz = aa * theta(i + 1);
        }

        return sigmoid(zz);
    }
};

}
}

#endif
