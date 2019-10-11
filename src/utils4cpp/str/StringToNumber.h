/************************************************************************************
**
**  BSD 3-Clause License
**
**  Copyright (c) 2019, shaoguang. All rights reserved.
**
**  Redistribution and use in source and binary forms, with or without
**  modification, are permitted provided that the following conditions are met:
**
**  1. Redistributions of source code must retain the above copyright notice, this
**     list of conditions and the following disclaimer.
**
**  2. Redistributions in binary form must reproduce the above copyright notice,
**     this list of conditions and the following disclaimer in the documentation
**     and/or other materials provided with the distribution.
**
**  3. Neither the name of the copyright holder nor the names of its
**     contributors may be used to endorse or promote products derived from
**     this software without specific prior written permission.
**
**  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
**  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
**  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
**  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
**  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
**  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
**  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
**  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
**  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
************************************************************************************/

#ifndef UTILS4CPP_STR_STRINGTONUMBER_H_
#define UTILS4CPP_STR_STRINGTONUMBER_H_

#include <string>
#include <stdexcept>

#include "utils4cpp/core/Core.h"

namespace utils4cpp {
namespace str {
namespace internal {

/*!
    template<typename DstT> DstT stringToNumber(const std::string& str, std::size_t* pos, int base)

    Interprets an integer value in the string str.
    std::string ==> short, unsigned short, int unsigned int, long, unsigned long, 
                    long long, unsigned long long.
    
    \param str the string to convert.
    \param pos address of an integer to store the number of characters processed.
    \param base the number base.

    \exception  std::invalid_argument if no conversion could be performed.
    \exception  std::out_of_range if the converted value would fall out of the range of the result type or if the 
                underlying function (std::strtol, std::strtoll, std::strtoul or std::strtoull) sets errno to ERANGE.

    \sa std::stoi(), std::stol(), std::stoll(), std::stoul(), std::stoull()
*/

template<typename DstT>
[[noreturn]] 
inline DstT stringToNumber(const std::string& str, std::size_t* pos, int base)
{
    throw std::invalid_argument("invalid template argument");
}

template<>
inline short stringToNumber(const std::string& str, std::size_t* pos, int base)
{
    return (short)std::stoi(str, pos, base);
}

template<>
inline unsigned short stringToNumber(const std::string& str, std::size_t* pos, int base)
{
    return (unsigned short)std::stoul(str, pos, base);
}

template<>
inline int stringToNumber(const std::string& str, std::size_t* pos, int base)
{
    return std::stoi(str, pos, base);
}

template<>
inline unsigned int stringToNumber(const std::string& str, std::size_t* pos, int base)
{
    return (unsigned int)std::stoul(str, pos, base);
}

template<>
inline long stringToNumber(const std::string& str, std::size_t* pos, int base)
{
    return std::stol(str, pos, base);
}

template<>
inline unsigned long stringToNumber(const std::string& str, std::size_t* pos, int base)
{
    return std::stoul(str, pos, base);
}

template<>
inline long long stringToNumber(const std::string& str, std::size_t* pos, int base)
{
    return std::stoll(str, pos, base);
}

template<>
inline unsigned long long stringToNumber(const std::string& str, std::size_t* pos, int base)
{
    return std::stoull(str, pos, base);
}

/*!
    template<typename DstT> DstT stringToNumber(const std::string& str, std::size_t* pos)

    Interprets an integer value or a floating point value in the string str.
    std::string ==> short, unsigned short, int unsigned int, long, unsigned long, 
                    long long, unsigned long long, float, double, long double.
    
    \param str the string to convert.
    \param pos address of an integer to store the number of characters processed.

    \exception  std::invalid_argument if no conversion could be performed.
    \exception  std::out_of_range if the converted value would fall out of the range of the result type or if the underlying 
                function (std::strtol, std::strtoll, std::strtoul, std::strtoull, strtof, (since C++17)strtod or strtold) 
                sets errno to ERANGE.

    \note Converses to decimal base integer by default.

    \sa std::stoi(), std::stol(), std::stoll(), std::stoul(), std::stoull(), std::stof(), std::stod(), std::stold()
*/

template<typename DstT>
[[noreturn]]
inline DstT stringToNumber(const std::string& str, std::size_t* pos)
{
    throw std::invalid_argument("invalid template argument");
}

template<>
inline short stringToNumber(const std::string& str, std::size_t* pos)
{
    return (short)std::stoi(str, pos);
}

template<>
inline unsigned short stringToNumber(const std::string& str, std::size_t* pos)
{
    return (unsigned short)std::stoul(str, pos);
}

template<>
inline int stringToNumber(const std::string& str, std::size_t* pos)
{
    return std::stoi(str, pos);
}

template<>
inline unsigned int stringToNumber(const std::string& str, std::size_t* pos)
{
    return (unsigned int)std::stoul(str, pos);
}

template<>
inline long stringToNumber(const std::string& str, std::size_t* pos)
{
    return std::stol(str, pos);
}

template<>
inline unsigned long stringToNumber(const std::string& str, std::size_t* pos)
{
    return std::stoul(str, pos);
}

template<>
inline long long stringToNumber(const std::string& str, std::size_t* pos)
{
    return std::stoll(str, pos);
}

template<>
inline unsigned long long stringToNumber(const std::string& str, std::size_t* pos)
{
    return std::stoull(str, pos);
}

template<>
inline float stringToNumber(const std::string& str, std::size_t* pos)
{
    return std::stof(str, pos);
}

template<>
inline double stringToNumber(const std::string& str, std::size_t* pos)
{
    return std::stod(str, pos);
}

template<>
inline long double stringToNumber(const std::string& str, std::size_t* pos)
{
    return std::stold(str, pos);
}

/*!
    template<typename DstT> DstT stringToNumber(const std::string& str)

    Interprets an integer value or a floating point value in the string str.
    std::string ==> short, unsigned short, int unsigned int, long, unsigned long, 
                    long long, unsigned long long, float, double, long double.
    
    \param str the string to convert.

    \exception  std::invalid_argument if no conversion could be performed.
    \exception  std::out_of_range if the converted value would fall out of the range of the result type or if the underlying 
                function (std::strtol, std::strtoll, std::strtoul, std::strtoull, strtof, (since C++17)strtod or strtold) 
                sets errno to ERANGE.

    \note Converses to decimal base integer by default.

    \sa std::stoi(), std::stol(), std::stoll(), std::stoul(), std::stoull(), std::stof(), std::stod(), std::stold()
*/

template<typename DstT>
[[noreturn]]
inline DstT stringToNumber(const std::string& str)
{
    throw std::invalid_argument("invalid template argument");
}

template<>
inline short stringToNumber(const std::string& str)
{
    return (short)std::stoi(str);
}

template<>
inline unsigned short stringToNumber(const std::string& str)
{
    return (unsigned short)std::stoul(str);
}

template<>
inline int stringToNumber(const std::string& str)
{
    return std::stoi(str);
}

template<>
inline unsigned int stringToNumber(const std::string& str)
{
    return (unsigned int)std::stoul(str);
}

template<>
inline long stringToNumber(const std::string& str)
{
    return std::stol(str);
}

template<>
inline unsigned long stringToNumber(const std::string& str)
{
    return std::stoul(str);
}

template<>
inline long long stringToNumber(const std::string& str)
{
    return std::stoll(str);
}

template<>
inline unsigned long long stringToNumber(const std::string& str)
{
    return std::stoull(str);
}

template<>
inline float stringToNumber(const std::string& str)
{
    return std::stof(str);
}

template<>
inline double stringToNumber(const std::string& str)
{
    return std::stod(str);
}

template<>
inline long double stringToNumber(const std::string& str)
{
    return std::stold(str);
}



/*!
    template<typename DstT> DstT stringToNumber(const std::wstring& str, std::size_t* pos, int base)

    Interprets an integer value in the string str.
    std::wstring ==> short, unsigned short, int unsigned int, long, unsigned long, 
                    long long, unsigned long long.
    
    \param str the string to convert.
    \param pos address of an integer to store the number of characters processed.
    \param base the number base.

    \exception  std::invalid_argument if no conversion could be performed.
    \exception  std::out_of_range if the converted value would fall out of the range of the result type or if the 
                underlying function (std::strtol, std::strtoll, std::strtoul or std::strtoull) sets errno to ERANGE.

    \sa std::stoi(), std::stol(), std::stoll(), std::stoul(), std::stoull()
*/

template<typename DstT>
[[noreturn]] 
inline DstT stringToNumber(const std::wstring& str, std::size_t* pos, int base)
{
    throw std::invalid_argument("invalid template argument");
}

template<>
inline short stringToNumber(const std::wstring& str, std::size_t* pos, int base)
{
    return (short)std::stoi(str, pos, base);
}

template<>
inline unsigned short stringToNumber(const std::wstring& str, std::size_t* pos, int base)
{
    return (unsigned short)std::stoul(str, pos, base);
}

template<>
inline int stringToNumber(const std::wstring& str, std::size_t* pos, int base)
{
    return std::stoi(str, pos, base);
}

template<>
inline unsigned int stringToNumber(const std::wstring& str, std::size_t* pos, int base)
{
    return (unsigned int)std::stoul(str, pos, base);
}

template<>
inline long stringToNumber(const std::wstring& str, std::size_t* pos, int base)
{
    return std::stol(str, pos, base);
}

template<>
inline unsigned long stringToNumber(const std::wstring& str, std::size_t* pos, int base)
{
    return std::stoul(str, pos, base);
}

template<>
inline long long stringToNumber(const std::wstring& str, std::size_t* pos, int base)
{
    return std::stoll(str, pos, base);
}

template<>
inline unsigned long long stringToNumber(const std::wstring& str, std::size_t* pos, int base)
{
    return std::stoull(str, pos, base);
}

/*!
    template<typename DstT> DstT stringToNumber(const std::wstring& str, std::size_t* pos)

    Interprets an integer value or a floating point value in the string str.
    std::wstring ==> short, unsigned short, int unsigned int, long, unsigned long, 
                    long long, unsigned long long, float, double, long double.
    
    \param str the string to convert.
    \param pos address of an integer to store the number of characters processed.

    \exception  std::invalid_argument if no conversion could be performed.
    \exception  std::out_of_range if the converted value would fall out of the range of the result type or if the underlying 
                function (std::strtol, std::strtoll, std::strtoul, std::strtoull, strtof, (since C++17)strtod or strtold) 
                sets errno to ERANGE.

    \note Converses to decimal base integer by default.

    \sa std::stoi(), std::stol(), std::stoll(), std::stoul(), std::stoull(), std::stof(), std::stod(), std::stold()
*/

template<typename DstT>
[[noreturn]]
inline DstT stringToNumber(const std::wstring& str, std::size_t* pos)
{
    throw std::invalid_argument("invalid template argument");
}

template<>
inline short stringToNumber(const std::wstring& str, std::size_t* pos)
{
    return (short)std::stoi(str, pos);
}

template<>
inline unsigned short stringToNumber(const std::wstring& str, std::size_t* pos)
{
    return (unsigned short)std::stoul(str, pos);
}

template<>
inline int stringToNumber(const std::wstring& str, std::size_t* pos)
{
    return std::stoi(str, pos);
}

template<>
inline unsigned int stringToNumber(const std::wstring& str, std::size_t* pos)
{
    return (unsigned int)std::stoul(str, pos);
}

template<>
inline long stringToNumber(const std::wstring& str, std::size_t* pos)
{
    return std::stol(str, pos);
}

template<>
inline unsigned long stringToNumber(const std::wstring& str, std::size_t* pos)
{
    return std::stoul(str, pos);
}

template<>
inline long long stringToNumber(const std::wstring& str, std::size_t* pos)
{
    return std::stoll(str, pos);
}

template<>
inline unsigned long long stringToNumber(const std::wstring& str, std::size_t* pos)
{
    return std::stoull(str, pos);
}

template<>
inline float stringToNumber(const std::wstring& str, std::size_t* pos)
{
    return std::stof(str, pos);
}

template<>
inline double stringToNumber(const std::wstring& str, std::size_t* pos)
{
    return std::stod(str, pos);
}

template<>
inline long double stringToNumber(const std::wstring& str, std::size_t* pos)
{
    return std::stold(str, pos);
}

/*!
    template<typename DstT> DstT stringToNumber(const std::string& str)

    Interprets an integer value or a floating point value in the string str.
    std::string ==> short, unsigned short, int unsigned int, long, unsigned long, 
                    long long, unsigned long long, float, double, long double.
    
    \param str the string to convert.

    \exception  std::invalid_argument if no conversion could be performed.
    \exception  std::out_of_range if the converted value would fall out of the range of the result type or if the underlying 
                function (std::strtol, std::strtoll, std::strtoul, std::strtoull, strtof, (since C++17)strtod or strtold) 
                sets errno to ERANGE.

    \note Converses to decimal base integer by default.

    \sa std::stoi(), std::stol(), std::stoll(), std::stoul(), std::stoull(), std::stof(), std::stod(), std::stold()
*/

template<typename DstT>
[[noreturn]]
inline DstT stringToNumber(const std::wstring& str)
{
    throw std::invalid_argument("invalid template argument");
}

template<>
inline short stringToNumber(const std::wstring& str)
{
    return (short)std::stoi(str);
}

template<>
inline unsigned short stringToNumber(const std::wstring& str)
{
    return (unsigned short)std::stoul(str);
}

template<>
inline int stringToNumber(const std::wstring& str)
{
    return std::stoi(str);
}

template<>
inline unsigned int stringToNumber(const std::wstring& str)
{
    return (unsigned int)std::stoul(str);
}

template<>
inline long stringToNumber(const std::wstring& str)
{
    return std::stol(str);
}

template<>
inline unsigned long stringToNumber(const std::wstring& str)
{
    return std::stoul(str);
}

template<>
inline long long stringToNumber(const std::wstring& str)
{
    return std::stoll(str);
}

template<>
inline unsigned long long stringToNumber(const std::wstring& str)
{
    return std::stoull(str);
}

template<>
inline float stringToNumber(const std::wstring& str)
{
    return std::stof(str);
}

template<>
inline double stringToNumber(const std::wstring& str)
{
    return std::stod(str);
}

template<>
inline long double stringToNumber(const std::wstring& str)
{
    return std::stold(str);
}

} // namespace internal
} // namespace str
} // namespace utils4cpp

#endif // UTILS4CPP_STR_STRINGTONUMBER_H_