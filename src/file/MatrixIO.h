#ifndef VANAGANDR_FILE_MATRIXIO_HEADER
#define VANAGANDR_FILE_MATRIXIO_HEADER

#include <tuple>
#include <fstream>
#include <sstream>

#include "../enum.h"

// TODO rewrite it with a std::vector => Eigen::Map => Eigen::Matrix/Array

namespace vanagandr
{
namespace file
{

// Read the size of a CSV File return the number of columns and the number of rows
std::pair<int, int> read_size(std::ifstream* file, bool header = false, const char* colsep = ",");


// doesnot handle empty column very well
Matrix read(std::string name, bool header = false, const char* colsep = ",");


void write(std::string name, const Matrix& mat, const char* colsep = ",");


}   // file
}   // vanagandr

#endif // MATRIXIO_H
