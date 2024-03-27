
// COS30008

#include "Vector3D.h"

#include <sstream>
#include <string>
#include <cmath>

// return Vector3D( 1.0f, 2.0f, 3.0f ) as "[1,2,3]"
// rounded to 4 decimal points
std::string Vector3D::toString() const noexcept 
{
    std::stringstream result;

    const float lX = std::roundf(x() * 10000.0f) / 10000.0f;
    const float lY = std::roundf(y() * 10000.0f) / 10000.0f;
    const float lW = std::roundf(w() * 10000.0f) / 10000.0f;

    result << "[" << lX << "," << lY << "," << lW << "]";

    return result.str();
}

