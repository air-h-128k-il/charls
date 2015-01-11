// 
// (C) Jan de Vaan 2007-2010, all rights reserved. See the accompanying "License.txt" for licensed use. 
// 


#ifndef CHARLS_UTIL
#define CHARLS_UTIL

#include "config.h"
#include "publictypes.h"
#include <cstdlib>
#include <cstring>
#include <vector>
#include <system_error>

#ifndef MAX
#define MAX(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a,b)            (((a) < (b)) ? (a) : (b))
#endif

enum constants
{
    INT32_BITCOUNT = sizeof(int32_t) * 8
};


inline void push_back(std::vector<uint8_t>& values, uint16_t value)
{
    values.push_back(uint8_t(value / 0x100));
    values.push_back(uint8_t(value % 0x100));
}


inline int32_t log_2(int32_t n)
{
    int32_t x = 0;
    while (n > (int32_t(1) << x))
    {
        ++x;
    }
    return x;
}


inline int32_t Sign(int32_t n)
{
    return (n >> (INT32_BITCOUNT - 1)) | 1;
}


inline int32_t BitWiseSign(int32_t i)
{
    return i >> (INT32_BITCOUNT - 1);
}


struct Size
{
    Size(int32_t width, int32_t height) :
        cx(width),
        cy(height)
    {}
    int32_t cx;
    int32_t cy;
};


template<class SAMPLE>
struct Triplet
{
    Triplet() :
        v1(0),
        v2(0),
        v3(0)
    {}

    Triplet(int32_t x1, int32_t x2, int32_t x3) :
        v1((SAMPLE)x1),
        v2((SAMPLE)x2),
        v3((SAMPLE)x3)
    {}

    union
    {
        SAMPLE v1;
        SAMPLE R;
    };
    union
    {
        SAMPLE v2;
        SAMPLE G;
    };
    union
    {
        SAMPLE v3;
        SAMPLE B;
    };
};


inline bool operator==(const Triplet<uint8_t>& lhs, const Triplet<uint8_t>& rhs)
{
    return lhs.v1 == rhs.v1 && lhs.v2 == rhs.v2 && lhs.v3 == rhs.v3;
}


inline bool  operator!=(const Triplet<uint8_t>& lhs, const Triplet<uint8_t>& rhs)
{
    return !(lhs == rhs);
}


template<class sample>
struct Quad : public Triplet<sample>
{
    Quad() : 
        v4(0)
        {}

    Quad(Triplet<sample> triplet, int32_t alpha) : Triplet<sample>(triplet), A((sample)alpha)
        {}

    union
    {
        sample v4;
        sample A;
    };
};


template <int size>
struct FromBigEndian
{
};


template <>
struct FromBigEndian<4>
{
    inlinehint static unsigned int Read(uint8_t* pbyte)
    {
        return  (pbyte[0] << 24) + (pbyte[1] << 16) + (pbyte[2] << 8) + (pbyte[3] << 0);
    }
};


template <>
struct FromBigEndian<8>
{
    inlinehint static uint64_t Read(uint8_t* pbyte)
    {
        return (uint64_t(pbyte[0]) << 56) + (uint64_t(pbyte[1]) << 48) + (uint64_t(pbyte[2]) << 40) + (uint64_t(pbyte[3]) << 32) +
                (uint64_t(pbyte[4]) << 24) + (uint64_t(pbyte[5]) << 16) + (uint64_t(pbyte[6]) <<  8) + (uint64_t(pbyte[7]) << 0);
    }
};


const std::error_category& CharLSCategoryInstance();


inline ByteStreamInfo FromStream(std::basic_streambuf<char>* stream)
{
    ByteStreamInfo info = ByteStreamInfo();
    info.rawStream = stream;
    return info;
}


inline void SkipBytes(ByteStreamInfo* streamInfo, std::size_t count)
{
    if (!streamInfo->rawData)
        return;

    streamInfo->rawData += count;
    streamInfo->count -= count;
}


#endif