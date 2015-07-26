#ifndef VANAGANDR_CONTAINERS_DATAFRAME_HEADER
#define VANAGANDR_CONTAINERS_DATAFRAME_HEADER

#include "../enum.h"

//typedef Eigen::ArrayXXd Array;

namespace vanagandr
{
namespace containers
{

/*!
 *  Eigen Matrix with one index
 */

template<typename Type, typename IndexType>
class DataFrame
{
public:
    typedef Eigen::Array<Type, -1, -1> Array;
    typedef Eigen::Array<IndexType, -1, 1> Index;

    DataFrame()
    {}


    Array values;
    Index index;
};

}
}

#endif
