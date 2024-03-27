
// COS30008 Assignment 1 
// Utkarsh Ranjan - 102874485

#include "Polygon.h"
#include "Vector2D.h"
#include "Vector3D.h"

#include <cstddef>

// calculate signed area for shape created by a set of coords
float Polygon::getSignedArea() const noexcept 
{
    float Result = 0;

    for ( size_t i = 0; i+1 < fNumberOfVertices; i++ )
    {
	Result += (fVertices[i].x() - fVertices[i+1].x())*
	          (fVertices[i].y() + fVertices[i+1].y());
    }

    Result += (fVertices[fNumberOfVertices-1].y() + fVertices[0].y())* 
              (fVertices[fNumberOfVertices-1].x() - fVertices[0].x());

    return Result/2;
}

// transform polygon with the 3d matrix 
Polygon Polygon::transform( const Matrix3x3& aMatrix ) const noexcept
{
    Polygon Result;

    for ( size_t i = 0; i < fNumberOfVertices; i++ )
    {
	Result.fVertices[i] = static_cast<Vector2D>( 
		aMatrix * Vector3D(fVertices[i])
	);
    }
    Result.fNumberOfVertices = fNumberOfVertices;

    return Result;
}
