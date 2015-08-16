#include "../file/File.h"


/*
if ( !boost::filesystem::exists( "myfile.txt" ) )
{
  std::cout << "Can't find my file!" << std::endl;
}*/

namespace vanagandr
{

	double stringToNumber ( const std::string &Text )//Text not by const reference so that the function can be used with a
	{                               //character array as argument
		std::stringstream ss(Text);
		double result;
		return ss >> result ? result : 0;
	}
	std::string numberToString(double number)
	{
		std::ostringstream ostr;
		ostr << number;

		return ostr.str();
	}
	double charToNumber(char buffer[MAXSIZE + 2])
	{
		std::string b(buffer);
		return stringToNumber(b);
	}

	void reinitializeBuffer(char buffer[MAXSIZE + 2])
	{
		for (int i = 0 ; i < MAXSIZE + 1; i++)
			buffer[i] = 0;

		buffer[MAXSIZE + 1] = '\0';
	}


	bool		exportCSV	(std::string name, Matrix a)
	{
		return exportCSV(name,  a, ',');
	}
	bool exportCSV(std::string name, Matrix a, char separator)
	{
		std::ofstream file;
		file.open(name.c_str());

		for (int i = 0, n = a.rows(); i < n; i++)
		{
			for (int j = 0, m = a.cols(); j < m; j++)
			{
				file << a(i, j);

				if ( j < m - 1)
					file << separator;
			}

			if (i < n - 1)
				file << std::endl;
		}

		file.close();

		return true;
	}

	/*
	FINMatrix FINData::importCSV(std::string name)
	{
		return FINData::importCSV(name, 0, 0, 0, 0, ',');
	}
	FINMatrix FINData::importCSV(std::string name, int rowb)
	{
		return FINData::importCSV(name, rowb, 0, 0, 0, ',');
	}
	FINMatrix FINData::importCSV(std::string name, int rowb, int colb)
	{
		return FINData::importCSV(name, rowb, colb, 0, 0, ',');
	}
	FINMatrix FINData::importCSV(std::string name, int rowb, int colb, int rowe)
	{
		return FINData::importCSV(name, rowb, colb, rowe, 0, ',');
	}
	FINMatrix FINData::importCSV(std::string name, int rowb, int colb, int rowe, int cole)
	{
		return FINData::importCSV(name, rowb, colb, rowe, cole, ',');
	}*/
	Matrix importCSV(std::string name, int rowb, int colb, int rowe, int cole)
	{
		return importCSV(name, rowb, colb, rowe, cole, ',');
	}
	Matrix importCSV(std::string name, int rowb, int colb, int rowE, int colE, char separator)
	{
		Vector2D<double> Vector;

		std::ifstream file(name.c_str(), std::ios::in);

		//FILE* file = fopen(name.c_str(), "r");

		if (!file)
			std::cerr << "File "<< name <<" does not exist" << std::endl;

		char buffer[MAXSIZE + 2];

		reinitializeBuffer(buffer);

		//bool reading = true;
		char c;

		int i = 0;
		int j = 0;
		int k = 0;

		while (file.get(c))
		{
			//c = getc(file);
			//if (c == -1)
			//	reading = false;

			if ( c == separator)
			{
				Vector.addElement(i, j, charToNumber(buffer));

				k = 0;
				j++;

				reinitializeBuffer(buffer);
			}
			else if (c == '\n')
			{
				Vector.addElement(i, j, charToNumber(buffer));

				j = 0;
				k = 0;
				i++;

				reinitializeBuffer(buffer);
			}
			else
			{
				if (k < MAXSIZE)
				{
					buffer[k] = c;
					k++;
				}
				else
					std::cerr << "Number is Too big" << std::endl; //throw std::length_error("Number is Too big");
			}
		}

		file.close();

		return Vector.exportVector(rowb, colb, rowE, colE);
	}
}
/*
FINMatrix	importExcel();
bool		exportExcel(FINMatrix a);*/

