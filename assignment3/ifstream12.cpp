// COS30008, Problem Set 3, 2024

#include "ifstream12.h"
#include <cassert>

void ifstream12::reset()
{
    fByteCount = 0;
    fByteIndex = 0;
    fBitIndex  = 7;
}

void ifstream12::fetch_data()
{
    fIStream.read(reinterpret_cast<char *>(fBuffer), fBufferSize);
    fByteCount = static_cast<size_t>(fIStream.gcount());
    fByteIndex = 0;
    fBitIndex  = 7;
}

std::optional<size_t> ifstream12::readBit()
{
    if (fByteCount == 0 || fByteIndex >= fBufferSize)
    {
        fetch_data();
        if (fByteCount == 0)
        {
            return std::nullopt;
        }
    }

    std::byte lByte = fBuffer[fByteIndex] & (std::byte{1} << fBitIndex);
    size_t lResult = std::to_integer<size_t>(lByte) > 0 ? 1 : 0;
    fBitIndex--;

    if (fBitIndex < 0)
    {
        fByteIndex++;
        fBitIndex = 7;
        fByteCount--;

        if (fByteCount == 0 && fIStream.good())
            fetch_data();
    }

    return lResult;
}

ifstream12::ifstream12(const char* aFileName, size_t aBufferSize) :
    fBuffer(new std::byte[aBufferSize]),
    fBufferSize(aBufferSize),
    fByteCount(0),
    fByteIndex(0),
    fBitIndex(7)
{
    reset();
    open(aFileName);
}

ifstream12::~ifstream12()
{
    close();
    delete[] fBuffer;
}

void ifstream12::open(const char* aFileName)
{
    assert(!isOpen());

    if (aFileName)
    {
        fIStream.open(aFileName, std::ifstream::binary);
    }
}

void ifstream12::close()
{
    fIStream.close();
}

bool ifstream12::isOpen() const
{
    return fIStream.is_open();
}

bool ifstream12::good() const
{
    return fIStream.good();
}

bool ifstream12::eof() const
{
    return fByteCount == 0 && fIStream.eof();
}

ifstream12& ifstream12::operator>>(size_t& aValue)
{
    aValue = 0;
    for (int i = 0; i < 12; i++)
    {
        auto bit = readBit();
        if (!bit)
        {
            break;
        }
        aValue |= static_cast<size_t>(*bit) << i;
    }

    return *this;
}

