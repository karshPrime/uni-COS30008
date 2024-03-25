
// COS30008

#include "Matrix3x3.h"

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

float Matrix3x3::det() const noexcept
{
    const float lM1 = row(0)[0] * (row(1)[1]*row(2)[2] - row(2)[1]*row(1)[2]);
    const float lM2 = row(0)[1] * (row(1)[0]*row(2)[2] - row(2)[0]*row(1)[2]);
    const float lM3 = row(0)[2] * (row(1)[0]*row(2)[1] - row(2)[0]*row(1)[1]);

    return lM1 - lM2 + lM3;
}

Matrix3x3 Matrix3x3::transpose() const noexcept {
    return Matrix3x3(
	    Vector3D(column(0)), 
	    Vector3D(column(1)), 
	    Vector3D(column(2))
    );
}

bool Matrix3x3::hasInverse() const noexcept {
    return det() != 0;
}

Matrix3x3 Matrix3x3::inverse() const noexcept {
    Matrix3x3 result;

    if (hasInverse()) {
	result = Matrix3x3(
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
    }

    return result;
}

std::ostream& operator<<( std::ostream& aOStream, const Matrix3x3& aMatrix ) {
    return aOStream << "["
	<< aMatrix.row(0).toString() << ","
	<< aMatrix.row(1).toString() << ","
	<< aMatrix.row(2).toString() << "]";
}

