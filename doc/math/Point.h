#ifndef VAPOINT_H
#define VAPOINT_H

#include "../Enum.h"

namespace vanagandr
{
    template <typename T = Real>
    class Point : public std::pair<T, T>
	{
		public:
            typedef std::pair<T, T> Pair;

            Point(T xx, T yy):
                Pair(xx, yy)
			{}

            Point():
                Pair(0, 0)
            {}

            Point(Point<T> A, Point<T> B):
                Pair(B.first - A.first, B.second - A.first)
            {}

			Point changeOrigin(Point Origin)
			{
                return Point(this->first - Origin.x(), this->second - Origin.y());
			}

            bool operator<(const Point &a)	const	{	return this->first < a.first;	}

			// Coordonnée Polaire !
			//

            Point rotate(Real degree, Point Origin = Point())
            {
                return Point( (this->first - Origin.x()) * cos(degree) - (this->second - Origin.y()) * sin(degree) + Origin.x(),
                              (this->first - Origin.x()) * sin(degree) + (this->second - Origin.y()) * cos(degree) + Origin.y()    );
            }

            Real angle(Point<T> A)
            {
                return ( A.x() * this->first + A.y() * this->second ) / ( A.width() * width() );
            }

            Real crossProduct(Point<T> A)
            {
                return  A.x() * this->first + A.y() * this->second;
            }

            Real width()
            {
                return pow( this->first * this->first + this->second * this->second, 0.5);
            }

            Real determinant(Point<T> A)
            {
                return this->first * A.y() - this->second * A.x();
            }

            void setX(T x)	{	this->first = x;	}
            void setY(T y)	{	this->second = y;	}

            T x()	{	return this->first;	}
            T y()	{	return this->second;	}

	};

    /*
	template <typename T>
    class Point3D : protected std::pair<T, T>
	{
		public:
            enum Coordinate
            {
                xx,
                yy,
                zz
            };

            Point3D(T xx, T yy, T zz):this->first(xx), this->second(yy), z_(zz)
			{}

            Point3D(Point3D<T> A, Point3D<T> B):this->first(B.x() - A.x()), this->second(B.y() - A.y()), z_(B.z() - A.z())
            {}

            bool operator<(const Point3D &a)	const	{	return this->first < a.this->first;	}

            void setX(T x)	{	this->first = x;	}
            void setY(T y)	{	this->second = y;	}
			void setZ(T z)	{	z_ = z;	}

            Point3D changeOrigin(Point3D Origin)
            {
                return Point3D(this->first - Origin.x(), this->second - Origin.y(), z_ - Origin.z());
            }

            Real angle(Point3D<T> A)
            {
                return ( A.x() * this->first + A.y() * this->second + A.z() * z_) / ( A.width() * width() );
            }

            Point3D vectorialProduct(Point3D<T> A)
            {                                                   //    1         2
                return Point3D<T>( this->second * A.z() - z_ * A.y(),     // u2 * v3 - u3 * v2    1 = determinant(A, x)
                                   z_ * A.x() - this->first * A.z(),     // u3 * v1 - u1 * v3    2 = determinant(A, y)
                                   this->first * A.y() - this->second * A.x());    // u1 * v2 - u2 * v1    3 = determinant(A, z)
            }

            Real determinant(Point3D<T> A, Coordinate a)
            {
                switch (a)
                {
                case xx:
                    return this->second * A.z() - z_ * A.y();
                    break;
                case yy:
                    return z_ * A.x() - this->first * A.z();
                    break;
                case zz:
                    return this->first * A.y() - this->second * A.x();
                    break;
                }
            }

            Real crossProduct(Point3D<T> A)
            {
                return  A.x() * this->first + A.y() * this->second + A.z() * z_;
            }

            Real width()
            {
                return pow( this->first * this->first + this->second * this->second + z_ * z_, 0.5);
            }

            T x()	{	return this->first;	}
            T y()	{	return this->second;	}
			T z()	{	return z_;	}

		protected:

			T z_;
    };*/

	template <typename T, ID N>
	class PointND
	{
		public:
			PointND()
			{}

            PointND(PointND<T, N> A, PointND<T, N> B)
            {
                for(int i = 0; i < N; i++)
                    A_[i] = B.n(i) - A.n(i);
            }

			bool operator<(const PointND &a)	const	{	return A_[0] < a.A_[0];	}

			void setN(T x, ID i)	{	A_[i] = x;		}

			T n(ID i)				{	return A_[i];	}

            Real crossProduct(PointND<T, N> A)
            {
                Real sum = 0;

                for(int i = 0; i < N; i++)
                    sum += A_[i] * A.n(i);

                return sum;
            }

            Real angle(PointND<T, N> A)
            {
                Real sum = 0;

                for(int i = 0; i < N; i++)
                    sum += A_[i] * A.n(i);

                return sum / ( A.width() * width() );
            }

            Real width()
            {
                Real sum = 0;

                for(int i = 0; i < N; i++)
                    sum += A_[i] * A_[i];

                return pow( sum, 0.5);
            }

		protected:

			T A_[N];
	};
}
#endif // VAPOINT_H
