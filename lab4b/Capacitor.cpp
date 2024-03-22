
// COS30008, Tutorial 4, 2024

#define _USE_MATH_DEFINES     // must be defined before any #include

#include "Capacitor.h"

#include <cassert>
#include <cmath>

// constructor with a default value
Capacitor::Capacitor( double aBaseValue ) noexcept :
    ComponentBase( aBaseValue, "F", "Fmunp" )
{}

// returns true if aValue exceeds a magnitude (<1.0)
bool Capacitor::mustAdjust( double aValue ) const noexcept
{
    return aValue < 1.0;
}

// returns component dependent scalar (1000.0)
const double Capacitor::getScalar() const noexcept
{
    return 1000.0;
}

// returns (frequency-dependent) passive resistance value (capacitive reactance)
double Capacitor::getReactance( double aFrequency ) const noexcept
{
    assert( aFrequency != 0.0 && getBaseValue() != 0.0 );
    
    return 1.0 / (2 * M_PI * aFrequency * getBaseValue());
}
