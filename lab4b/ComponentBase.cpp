
// COS30008, Tutorial 4, 2024

#include "ComponentBase.h"

#include <cassert>

ComponentBase::ComponentBase( double aBaseValue,
                              const std::string& aMajorUnit,
                              const std::string& aMinorUnits ) noexcept :
    fBaseValue(aBaseValue),
    fMajorUnit(aMajorUnit),
    fMinorUnits(aMinorUnits)
{
    // basic format assertions
    assert(aMajorUnit.size() > 0 && aMinorUnits.size() > 0 && fMinorUnits[0] == fMajorUnit[0]);
}

double ComponentBase::getBaseValue() const noexcept
{
    return fBaseValue;
}

void ComponentBase::setBaseValue( double aBaseValue ) noexcept
{
    fBaseValue = aBaseValue;
}

const std::string& ComponentBase::getMajorUnit() const noexcept
{
    return fMajorUnit;
}

const std::string& ComponentBase::getMinorUnits() const noexcept
{
    return fMinorUnits;
}

double ComponentBase::getPotentialAt( double aCurrent,
                                      double aFrequency ) const noexcept
{
    // Ohm's law
    return getReactance( aFrequency ) * aCurrent;
}

// returns (frequency-dependent) current flowing through a resistor
double ComponentBase::getCurrentAt( double aVoltage,
                                    double aFrequency ) const noexcept
{
    // division by zero check
    assert(getReactance( aFrequency ) != 0.0);
    
    // Ohm's law
    return aVoltage / getReactance( aFrequency );
}

std::istream& operator>>( std::istream& aIStream, ComponentBase& aObject )
{
    double lValue;
    std::string lUnit;

    aIStream >> lValue >> lUnit;

    aObject.setBaseValue(lValue, lUnit);
    
    return aIStream;
}

std::ostream& operator<<( std::ostream& aOStream, const ComponentBase& aObject )
{
    double lValue;
    std::string lUnit;
    
    aObject.toUnitValue(lValue, lUnit);
    
    return aOStream << lValue << " " << lUnit;
}
