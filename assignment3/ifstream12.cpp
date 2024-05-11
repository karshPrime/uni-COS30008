
// COS30008 - Problem Set 3
// Utkarsh Ranjan - 102874485

#include "ifstream12.h"
#include <cassert>

// resets stream indices and byte counters to initial state
void ifstream12::reset()
{
    fByteCount = 0;
    fByteIndex = 0;
    fBitIndex  = 7;  // start from the most significant bit
}

// fetches data from file into buffer and resets indices
void ifstream12::fetch_data()
{
    fIStream.read(reinterpret_cast<char *>(fBuffer), fBufferSize); // read from file into buffer
    fByteCount = static_cast<size_t>(fIStream.gcount()); // count bytes actually read
    fByteIndex = 0; 
    fBitIndex  = 7;
}

// reads a single bit from the buffer
std::optional<size_t> ifstream12::readBit()
{
    if (fByteCount == 0 || fByteIndex >= fBufferSize) // check if buffer is exhausted
    {
        fetch_data(); 
        if (fByteCount == 0) // if no data left, return nullopt
        {
            return std::nullopt;
        }
    }

    // extract bit using bitwise and and shift operations
    std::byte lByte = fBuffer[fByteIndex] & (std::byte{1} << fBitIndex);

    // convert to size_t and normalize to 0 or 1
    size_t lResult = std::to_integer<size_t>(lByte) > 0 ? 1 : 0; 
   
    // move to the next bit in byte
    fBitIndex--; 

    // if all bits in the current byte are read
    if (fBitIndex < 0) 
    {
        fByteIndex++; 
        fBitIndex = 7;
        fByteCount--;

        // if buffer is exhausted and stream is still good, fetch next chunk of data
        if (fByteCount == 0 && fIStream.good()) 
            fetch_data();
    }

    return lResult; // Return the read bit.
}

// constructor initializes buffer and opens the file
ifstream12::ifstream12(const char* aFileName, size_t aBufferSize) :
    fBuffer(new std::byte[aBufferSize]),
    fBufferSize(aBufferSize),
    fByteCount(0),
    fByteIndex(0),
    fBitIndex(7)
{
    reset(); // reset all counters and indices
    open(aFileName); // open the file for reading
}

// destructor closes the stream and deallocates buffer
ifstream12::~ifstream12()
{
    close();
    delete[] fBuffer; // deallocate the dynamic buffer.
}

// opens a file stream in binary mode
void ifstream12::open(const char* aFileName)
{
    assert(!isOpen()); // assert that the stream is not already open

    if (aFileName)
    {
        fIStream.open(aFileName, std::ifstream::binary); // open the file in binary mode
    }
}

// closes the file stream
void ifstream12::close()
{
    fIStream.close(); // close the file stream
}

// returns whether the file stream is open
bool ifstream12::isOpen() const
{
    return fIStream.is_open();
}

// returns the good state of the file stream
bool ifstream12::good() const
{
    return fIStream.good();
}

// returns true if end of file is reached
bool ifstream12::eof() const
{
    // check if buffer and stream are exhausted.
    return fByteCount == 0 && fIStream.eof(); 
}

// stream extraction operator reads a 12-bit value
ifstream12& ifstream12::operator>>(size_t& aValue)
{
    aValue = 0; // initialise the value to 0
    for (int i = 0; i < 12; i++) // loop to read 12 bits
    {
        auto bit = readBit(); // read each bit
        if (!bit) // if no bit is read, break the loop
        {
            break;
        }

        // combine bits into the final value using bitwise or and shift
        aValue |= static_cast<size_t>(*bit) << i; 
    }

    return *this;
}

