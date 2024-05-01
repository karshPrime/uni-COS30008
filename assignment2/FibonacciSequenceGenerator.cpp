
// FibonacciSequenceGenerator.cpp
// Utkarsh Ranjan - 102874485

#include <cassert>
#include <iostream>
#include "FibonacciSequenceGenerator.h"

// for easier typing
// preprocessors will be replaced before compilation anyways so this shouldn't
// make any difference to how the code compiles
typedef FibonacciSequenceGenerator FSG;

// Constructor to set up a Fibonacci sequence
FSG::FibonacciSequenceGenerator( const std::string &aID ) noexcept : 
        fID(aID),
        fPrevious(0),
        fCurrent(1)
{}

// Get sequence ID
const std::string& FSG::id() const noexcept
{
    return fID;
}

// Get current Fibonacci number
const long long& FSG::operator*() const noexcept
{
    return fCurrent;
}

// Type conversion to bool
FSG::operator bool() const noexcept
{
    return hasNext();
}

// Reset sequence generator to first Fibonacci number
void FSG::reset() noexcept
{
    fPrevious = 0;
    fCurrent = 1;
}

// Tests if there is a next Fibonacci number.
bool FSG::hasNext() const noexcept
{
    // for this purpose this check should be sufficient as the result is only
    // the sum of two long longs, i.e. in the worst case scenario overflow val
    // would be -2 (and otherwise would be lower than that x < -2).
    // hence no reason to import <limits> and check against max long long val
    return (fCurrent + fPrevious) > 0 ;
}

// Advance to next Fibonacci number
void FSG::next() noexcept
{
    const long long lNext = fCurrent + fPrevious;
    assert(lNext > 0);

    fPrevious = fCurrent;
    fCurrent = lNext;
}

