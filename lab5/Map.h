
// COS30008, Tutorial 5, 2024

#pragma once

#include <istream>
#include <ostream>

template<typename Key, typename Value>
class Map
{
private:
    Key fKey;
    Value fValue;
    
public:
    Map( const Key& aKey = Key{}, const Value& aValue = Value{}) noexcept;

    const Key& key() const noexcept;
    const Value& value() const noexcept;
    
    template<typename U>
    operator U() const noexcept;
    
    friend std::istream& operator>>( std::istream& aIStream, Map& aMap );
	friend std::ostream& operator<<( std::ostream& aOStream, const Map& aMap );
};
