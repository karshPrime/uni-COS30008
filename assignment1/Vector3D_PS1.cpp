
// COS30008 Assignment 1
// Utkarsh Ranjan - 102874485

#include "Vector3D.h"

#include <sstream>
#include <string>
#include <cmath>

// return Vector3D( 1.0f, 2.0f, 3.0f ) as "[1,2,3]"
// rounded to 4 decimal points
std::string Vector3D::toString() const noexcept 
{
    std::stringstream Result;

    // using const for compile time optimisation 
    // since these vars wouldn't be changing their values after assignment
    const float lX = std::roundf(x() * 10000.0f) / 10000.0f;
    const float lY = std::roundf(y() * 10000.0f) / 10000.0f;
    const float lW = std::roundf(w() * 10000.0f) / 10000.0f;

    Result << "[" << lX << "," << lY << "," << lW << "]";

    return Result.str();
}

