
// COS, Tutorial 4, 2024

#include "ComponentBase.h"
#include <cassert>

ComponentBase::ComponentBase(double aBaseValue,
	const std::string& aMajorUnit,
	const std::string& aMinorUnits ) noexcept:
    fBaseValue(aBaseValue),
    fMajorUnit(aMajorUnit),
    fMinorUnits(aMajorUnit)
{
    assert ( aMajorUnit.size > 0 &&
	    aMinorUnits.size > 0 &&
	    fMinorUnits.size[0] == fMajorUnit[0]
	    );
}

// required virtual destructor (default implementation)
virtual ~ComponentBase() {}

double ComponentBase::getBaseValue() const noexcept 
{
    return fBaseValue;
}

void setBaseValue( double aBaseValue ) noexcept
{
    //
}

const std::string& getMajorUnit() const noexcept;
const std::string& getMinorUnits() const noexcept;

// returns true if aValue exceeds a magnitude
virtual bool mustAdjust( double aValue ) const noexcept = 0;

// returns component dependent scalar
virtual const double getScalar() const noexcept = 0;

// returns (frequency-dependent) passive resistance value
virtual double getReactance( double aFrequency = 0.0 ) const noexcept = 0;

// returns (frequency-dependent) voltage drop
double getPotentialAt( double aCurrent,
	double aFrequency = 0.0 ) const noexcept;

// returns (frequency-dependent) current flowing through a resistor
double getCurrentAt( double aVoltage,
	double aFrequency = 0.0 ) const noexcept;

// Reads text string "56.0 kOhm" to set base value to 56000.0 (register)
friend std::istream& operator>>( std::istream& aIStream, ComponentBase& aObject );

// Writes text string "56.0 kOhm" obtained from base value 56000.0 (register)
friend std::ostream& operator<<( std::ostream& aOStream, const ComponentBase& aObject );
