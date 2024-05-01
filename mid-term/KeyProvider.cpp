
// COS30008 MidTerm 
// Utkarsh Ranjan - 102874485

#include <cctype>
#include <cassert>
#include "KeyProvider.h"

// for easier typing and code understanding
using KP = KeyProvider;
using string = std::string;

// returns string of CAPITALTEXT with no gap or any special char
string KP::preprocessString(const string& aString) noexcept 
{
    std::string Result;
    
    for (char letter: aString)
        if (isalpha(letter))
            Result.push_back(toupper(letter));
   
    return Result;
}

// Class Constructor
KP::KeyProvider(const string& aKeyword, const string& aSource) noexcept:
    fIndex(0) // initialise fIndex with index 0
{ 
    fKeys = ""; // memory leak prevention

    // max compiler const optimisation
    // since these are read only values and aren't required to me mutable
    const string lprocessedKeywords = preprocessString(aKeyword);
    const size_t lKeyLen = lprocessedKeywords.length(); 
    const size_t lSourceLen = preprocessString(aSource).length(); 

    // loop is skipped when keyword is bigger than source
    for (size_t i = 0; i < (lSourceLen / lKeyLen); i++)
        fKeys += lprocessedKeywords;

    // wouldn't add anything if (lSourceLen % lKeyLen) = 0
    fKeys += lprocessedKeywords.substr(0, (lSourceLen % lKeyLen));
   
    assert(fKeys.length() == lSourceLen);
}

// Dereferece
char KP::operator*() const noexcept
{
    return fKeys[fIndex];
}

// Increment instance by 1 and return new value
KP& KP::operator++() noexcept
{
    if (fIndex < fKeys.length()) 
        ++fIndex;
    
    return *this;
}

// Increment instance by 1 and return old value
KP KP::operator++(int) noexcept
{
    KP Result = *this;
    ++(*this);
    return Result;
}

// Compare instances
bool KP::operator==(const KP& aOther) const noexcept
{
    return (fKeys == aOther.fKeys && fIndex == aOther.fIndex);
}

// Inverse compare instances
bool KP::operator!=(const KP& aOther) const noexcept
{
    return !(*this == aOther);
}

// For range-based loop : start
KP KP::begin() const noexcept
{
    KP Result = *this;
    Result.fIndex = 0;

    return Result;
}

// For range-based loop : end
KP KP::end() const noexcept
{
    KP Result(*this);
    Result.fIndex = fKeys.length();

    return Result;
}

