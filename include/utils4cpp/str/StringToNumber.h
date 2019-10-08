/************************************************************************************
**
**  BSD 3-Clause License
**
**  Copyright (c) 2019, shaoguang
**  All rights reserved.
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

template<typename DstT>
[[noreturn]] 
inline DstT stringToNumber(const std::string &str, std::size_t *pos, int base)
{
    throw std::invalid_argument("invalid argument");
}

template<>
inline short stringToNumber(const std::string &str, std::size_t *pos, int base)
{
    return (short)std::stoi(str, pos, base);
}

template<>
inline unsigned short stringToNumber(const std::string &str, std::size_t *pos, int base)
{
    return (unsigned short)std::stoul(str, pos, base);
}

template<>
inline int stringToNumber(const std::string &str, std::size_t *pos, int base)
{
    return std::stoi(str, pos, base);
}

template<>
inline unsigned int stringToNumber(const std::string &str, std::size_t *pos, int base)
{
    return (unsigned int)std::stoul(str, pos, base);
}

template<>
inline long stringToNumber(const std::string &str, std::size_t *pos, int base)
{
    return std::stol(str, pos, base);
}

template<>
inline unsigned long stringToNumber(const std::string &str, std::size_t *pos, int base)
{
    return std::stoul(str, pos, base);
}

template<>
inline long long stringToNumber(const std::string &str, std::size_t *pos, int base)
{
    return std::stoll(str, pos, base);
}

template<>
inline unsigned long long stringToNumber(const std::string &str, std::size_t *pos, int base)
{
    return std::stoull(str, pos, base);
}

template<typename DstT>
[[noreturn]] 
inline DstT stringToNumber(const std::wstring &str, std::size_t *pos, int base)
{
    throw std::invalid_argument("invalid argument");
}

#endif // UTILS4CPP_STR_STRINGTONUMBER_H_