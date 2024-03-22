
// COS30008, Tutorial 4, 2024

#define _USE_MATH_DEFINES     // must be defined before any #include

#include "Inductor.h"

#include <cmath>

// constructor with a default value
Inductor::Inductor( double aBaseValue ) noexcept :
    ComponentBase( aBaseValue, "H", "Hmunp" )
{}

// returns true if aValue exceeds a magnitude (<1.0)
bool Inductor::mustAdjust( double aValue ) const noexcept
{
    return aValue < 1.0;
}

// returns component dependent scalar (1000.0)
const double Inductor::getScalar() const noexcept
{
    return 1000.0;
}

// returns (frequency-dependent) passive resistance value (inductive reactance)
double Inductor::getReactance( double aFrequency ) const noexcept
{
    return 2 * M_PI * aFrequency * getBaseValue();
}
