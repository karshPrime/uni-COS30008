
// COS30008, Tutorial 4, 2024

#include "PassiveResistor.h"

// constructor with a default value
PassiveResistor::PassiveResistor( double aBaseValue ) noexcept :
    ComponentBase( aBaseValue, "Ohm", "OkM" )
{}

// returns true if aValue exceeds a magnitude (1000.0)
bool PassiveResistor::mustAdjust( double aValue ) const noexcept
{
    return aValue >= 1000.0;
}

// returns component dependent scalar (1.0/1000.0)
const double PassiveResistor::getScalar() const noexcept
{
    return 1.0/1000.0;
}

// returns (frequency-dependent) passive resistance value (base value)
double PassiveResistor::getReactance( double aFrequency ) const noexcept
{
    return getBaseValue();
}
