
// COS30008 MidTerm 
// Utkarsh Ranjan - 102874485

#include <cctype>

#include "VigenereForwardIterator.h"
#include "KeyProvider.h"

// for easier typing. shouldn't make any difference in the compiled binary
#define CHARACTERS 26
using VFI = VigenereForwardIterator;
using KP = KeyProvider;
using string = std::string;

// Class Constructor
VFI::VigenereForwardIterator(const string &aKeyword, const string &aSource,
    EVigenereMode aMode) noexcept: 
        fMode(aMode), 
        fKeys(KP(aKeyword, aSource)), 
        fSource(aSource), 
        fIndex(0) 
{
  initializeTable(); // initialise fMappingTable

  if (aMode == EVigenereMode::Encode)
    encodeCurrentChar();
  else
    decodeCurrentChar();
}

// Encode single plain text char with its subsequent key char
void VFI::encodeCurrentChar() noexcept
{
    // why search for same indexed element multiple times
    // with const we'd have more compile time optimisation
    const char lToEncode = fSource[fIndex];

    if (isalpha(lToEncode))
    {
        // const because these values are read only
        const bool lIsLower = islower(lToEncode); // remember case state
        const int lKeyIndex = *fKeys - 'A';
        const int lSourceIndex = toupper(lToEncode) - 'A';

        // use fMappingTable
        fCurrentChar = fMappingTable[lKeyIndex][lSourceIndex];

        // revert back to lowercase if that was base state
        if (lIsLower)
            fCurrentChar = tolower(fCurrentChar);
    }
    else
        // dont encode 123!@#.,
        fCurrentChar = lToEncode;
}

// Decode single cipher char with its subsequent key char
void VFI::decodeCurrentChar() noexcept
{
    char lToDecode = fSource[fIndex];

    if (isalpha(lToDecode))
    {
        const bool lIsLower = islower(lToDecode);
        const int lKeyIndex = *fKeys - 'A';
        lToDecode = toupper(lToDecode);

        for (int i = 0; i < CHARACTERS; i++)
            if (lToDecode == fMappingTable[lKeyIndex][i]) {
                fCurrentChar = 'A' + i;
                break; // no need for the loop to further move on
                       // since we have found what we were after
            }

        if (lIsLower)
            fCurrentChar = tolower(fCurrentChar);
    }
    else
        fCurrentChar = lToDecode;
    
}

// Dereference 
char VFI::operator*() const noexcept
{
    return fCurrentChar;
}

// Increment instance by 1 and return new value
VFI& VFI::operator++() noexcept
{
    ++fIndex;

    if (fIndex < fSource.length())
    {
        if (isalpha(fCurrentChar))
            ++fKeys; // only increment when used with alpha

        if (fMode == EVigenereMode::Encode)
            encodeCurrentChar();
        else
            decodeCurrentChar();
    }
    else
        fCurrentChar = fSource[fIndex];

    return *this;
}

// Increment instance by 1 and return old value
VFI VFI::operator++(int) noexcept
{
    VFI Result = *this;
    ++(*this);

    return Result;
}

// Compare instances
bool VFI::operator==(const VFI& aOther) const noexcept
{
    return (aOther.fIndex == fIndex && aOther.fKeys == fKeys);
}

// Inverse compare instances
bool VFI::operator!=(const VFI& aOther) const noexcept
{
    return fIndex <= fSource.size();
}

// For range-based loop : start
VFI VFI::begin() const noexcept
{
    VFI Result = *this;
    Result.fIndex = 0;
    Result.fKeys.begin();

    return Result;
}

// For range-based loop : end
VFI VFI::end() const noexcept
{
    VFI Result = *this;
    Result.fIndex = fSource.length();
    Result.fKeys.end();

    return Result;
}

