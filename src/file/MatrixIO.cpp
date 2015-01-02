#include "MatrixIO.h"

namespace vanagandr
{
namespace file
{

// Read the size of a CSV File return the number of columns and the number of rows
std::pair<int, int> read_size(std::ifstream* file, bool header, const char* colsep)
{
    std::string line;
    std::getline(*file, line);

    int rows = 1 - header;
    int cols = 1;

    for (auto i = 0; i < line.size(); i++)
        if (line[i] == colsep[0])
            cols++;

    while (std::getline(*file, line))
    {
        // we want the row to be populated with data
        // if there are no sep then there are no data
        // some program add \n at the end of the CSV file
        // creating an empty row, we make sure to not count this last
        // empty row that may or may not be there
        if (line.find(colsep) != 0)
            rows++;
    }

    return std::pair<int, int>(rows, cols);
}

// doesnot handle empty column very well
Matrix read(std::string name, bool header, const char* colsep)
{
    std::ifstream file(name.c_str(), std::ios::in);

    if (!file)
        return Matrix(0, 0);

    std::pair<int, int> size = read_size(&file, header, colsep);

    Matrix A = Matrix::Zero(size.first, size.second);

    std::string line;

    // the cursor should be put to the beginning for better perf
    file.close();
    file.open(name.c_str(), std::ios::in);

    char c;

    if (header)
        std::getline(file, line);

    for(int j = 0; j < size.first; j++)
    {
        std::getline(file, line);
        std::istringstream ss(line);

        for (int i = 0; i < size.second; i++)
        {
            if (i < size.second - 1)
                ss >> A(j, i) >> c;
            else
                ss >> A(j, i);
        }
    }

    file.close();

    return A;
}

void write(std::string name, const Matrix& mat, const char* colsep)
{
    std::fstream file;
    file.open(name.c_str(), std::ios::out);
    Eigen::IOFormat fmt(12, Eigen::DontAlignCols, std::string(colsep), "\n", "","","","");

    file << mat.format(fmt);
}

}
}
