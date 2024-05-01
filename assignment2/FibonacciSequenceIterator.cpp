
// FibonacciSequenceIterator.cpp
// Utkarsh Ranjan - 102874485

#include <iostream>
#include "FibonacciSequenceIterator.h"

// for easier typing
// preprocessors will be replaced before compilation anyways so this shouldn't
// make any difference to how the code compiles
typedef FibonacciSequenceIterator FSI;
typedef FibonacciSequenceGenerator FSG;

// Iterator constructor
FSI::FibonacciSequenceIterator(const FSG& aSequenceObject, long long aStart)
noexcept :
    fSequenceObject(aSequenceObject),
    fIndex(aStart)
{}

// Return current Fibonacci number
const long long& FSI::operator*() const noexcept
{ 
    return *fSequenceObject;
}

// Prefix, next Fibonacci number
FSI& FSI::operator++() noexcept
{ 
    fIndex++; // increment counter

    if (fSequenceObject.hasNext()) {
        fSequenceObject.next(); // next fiboncacci
    }
    else {
        fIndex = -1; // signifies end
    }
    
    return *this;
}

// Postfix (extra unused argument)
FSI FSI::operator++(int) noexcept
{ 
    FSI lPrior = *this; // store original val
    ++(*this);          // update val

    return lPrior;      // return original val
}

// check if objects are equal
bool FSI::operator==(const FSI& aOther) const noexcept
{
    return fIndex == aOther.fIndex &&
        fSequenceObject.id() == aOther.fSequenceObject.id();
}

// Check if objects are not equal
bool FSI::operator!=(const FSI& aOther) const noexcept
{
    return !(*this == aOther);
}

// Return new iterator positioned at start
FSI FSI::begin() const noexcept
{
    // new sequence generator object with old id
    const FSG lSequenceGen(fSequenceObject.id()); 
    
    // result sequence iterator object with same init start val
    const FSI Result(lSequenceGen, 1);

    return Result;
}

// Return new iterator positioned at limit
FSI FSI::end() const noexcept
{
    FSI Result = *this;
    Result.fIndex = -1; // signify end

    return Result;
}

