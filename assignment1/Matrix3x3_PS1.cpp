
// COS30008 Assignment 1 
// Utkarsh Ranjan - 102874485

#include "Matrix3x3.h"

// calculate matrix cross product
Matrix3x3 Matrix3x3::operator*( const Matrix3x3& aOther ) const noexcept 
{
    return Matrix3x3( 
	Vector3D(
	    row(0).dot(aOther.column(0)),
	    row(0).dot(aOther.column(1)),
	    row(0).dot(aOther.column(2))),
	Vector3D(
	    row(1).dot(aOther.column(0)),
	    row(1).dot(aOther.column(1)),
	    row(1).dot(aOther.column(2))),
	Vector3D(
	    row(2).dot(aOther.column(0)),
	    row(2).dot(aOther.column(1)),
	    row(2).dot(aOther.column(2)))
    );
}

// calculate matrix determinant
float Matrix3x3::det() const noexcept
{
    // using const for further compile time optimisation
    // these local variables aren't changed after once defined
    const float lM1 = row(0)[0] * (row(1)[1]*row(2)[2] - row(2)[1]*row(1)[2]);
    const float lM2 = row(0)[1] * (row(1)[0]*row(2)[2] - row(2)[0]*row(1)[2]);
    const float lM3 = row(0)[2] * (row(1)[0]*row(2)[1] - row(2)[0]*row(1)[1]);

    return lM1 - lM2 + lM3;
}

// calculate matrix transpose 
Matrix3x3 Matrix3x3::transpose() const noexcept 
{
    // define new matrix as columns of base as rows
    return Matrix3x3(
	    Vector3D(column(0)), 
	    Vector3D(column(1)), 
	    Vector3D(column(2))
    );
}

// check if invertable
bool Matrix3x3::hasInverse() const noexcept 
{
    // can only have inverse when determinant is not 0
    return det() != 0;
}

// calculate matrix inverse 
Matrix3x3 Matrix3x3::inverse() const noexcept 
{
    Matrix3x3 Result;

    // return null matrix if inverse is not possible
    // otherwise return inverse matrix
    if (hasInverse()) {
	Result = Matrix3x3(
	    Vector3D(
		(row(1)[1]*row(2)[2] - row(1)[2]*row(2)[1]),
		(row(0)[2]*row(2)[1] - row(0)[1]*row(2)[2]),
		(row(0)[1]*row(1)[2] - row(0)[2]*row(1)[1])),
	    Vector3D(
		(row(1)[2]*row(2)[0] - row(1)[0]*row(2)[2]),
		(row(0)[0]*row(2)[2] - row(0)[2]*row(2)[0]),
		(row(0)[2]*row(1)[0] - row(0)[0]*row(1)[2])),
	    Vector3D(
		(row(1)[0]*row(2)[1] - row(1)[1]*row(2)[0]),
		(row(0)[1]*row(2)[0] - row(0)[0]*row(2)[1]),
		(row(0)[0]*row(1)[1] - row(0)[1]*row(1)[0]))
	) * (1/det()); 
	// taking advantage of defined matrix scalar multiplication operator 
	// overload
    }

    return Result;
}

// << operator overload  
std::ostream& operator<<( std::ostream& aOStream, const Matrix3x3& aMatrix ) 
{
    // broken down statement into multiple lines as a convention of sticking to
    // character 80 column limit
    return aOStream << "["
	<< aMatrix.row(0).toString() << ","
	<< aMatrix.row(1).toString() << ","
	<< aMatrix.row(2).toString() << "]";
}

