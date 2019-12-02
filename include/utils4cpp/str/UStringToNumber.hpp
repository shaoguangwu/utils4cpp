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

#ifndef UTILS4CPP_STR_USTRINGTONUMBER_INL
#define UTILS4CPP_STR_USTRINGTONUMBER_INL

#include "utils4cpp/str/UStringGlobal.hpp"

namespace utils4cpp::str {

/**
    \brief Converts a string to a signed or unsigned integer value.

    Interprets a signed or unsigned integer value in the string \a str. calls:
    <code> std::stoi(str, pos, base) </code> or <code> std::stol(str, pos, base) </code> 
    or <code> std::stoll(str, pos, base) </code> ,
    or <code> std::stoul(str, pos, base) </code> or <code> std::stoull(str, pos, base) </code> .

    \tparam StringT input string type, must be \c std::basic_string<char, Traits, Allocator>
        or \c std::basic_string<wchar_t, Traits, Allocator>.
    \tparam NumberT type of return value, must be an integral type.
    \tparam Except if true, this function may throw exception; otherwise, does not throw exceptions and 
        returns \c primitive_t<NumberT>(0) if an exception occurred.

    \note This overload only participates in overload resolution if \c StringT equals to \c std::basic_string<char, Traits, Allocator>
        or \c std::basic_string<wchar_t, Traits, Allocator> and \c NumberT is an integral type.

    \exception std::invalid_argument or \c std::out_of_range if the template param \c Except is true, 
        see std::stoi(), std::stol(), std::stoll(), std::stoul(), std::stoull().

    \sa if_std_string_or_wstring, if_integral
*/
template<class StringT, class NumberT, bool Except = true,
    class = if_std_char_or_wchar_string<StringT>,
    class = if_integral<primitive_t<NumberT>>>
inline primitive_t<NumberT> stringToNumber(const StringT& str, std::size_t* pos = 0, int base = 0) noexcept(!Exception)
{
    try {
        if constexpr (std::is_signed_v<primitive_t<NumberT>>) {
            if constexpr (sizeof(NumberT) <= sizeof(int)) {
                return static_cast<primitive_t<NumberT>>(std::stoi(str, pos, base));
            }
            else if constexpr (sizeof(NumberT) == sizeof(long)) {
                return static_cast<primitive_t<NumberT>>(std::stol(str, pos, base));
            }
            else {
                return static_cast<primitive_t<NumberT>>(std::stoll(str, pos, base));
            }
        }
        else {
            if constexpr (sizeof(NumberT) <= sizeof(unsigned long)) {
                return static_cast<primitive_t<NumberT>>(std::stoul(str, pos, base));
            }
            else {
                return static_cast<primitive_t<NumberT>>(std::stoull(str, pos, base));
            }
        }
    }
    catch (...) {
        if constexpr (Exception) {
            throw;
        }
        else {
            return primitive_t<NumberT>(0);
        }
    }
}

/**
    \brief Converts a string to a floating point value.

    Interprets a floating point value in the string \a str. calls:
    \c std::stof(str, pos) or \c std::stod(str, pos) or \c std::stold(str, pos)

    \tparam StringT input string type, must be \c std::basic_string<char, Traits, Allocator>
        or \c std::basic_string<wchar_t, Traits, Allocator>.
    \tparam NumberT type of return value, must be an floating point type.
    \tparam Exception if true, this function may throw exception; otherwise, does not throw exceptions and
        returns \c primitive_t<NumberT>(0.) if an exception occurred.

    \note This overload only participates in overload resolution if \c StringT equals to \c std::basic_string<char, Traits, Allocator>
        or \c std::basic_string<wchar_t, Traits, Allocator> and \c NumberT is an floating point type.

    \exception std::invalid_argument or \c std::out_of_range if the template param \c Except is true,
        see std::stof(str, pos) or std::stod(str, pos) or std::stold(str, pos).

    \sa if_std_string_or_wstring, if_floating_point
*/
template<class StringT, class NumberT, bool Except = true,
    class = if_std_char_or_wchar_string<StringT>,
    class = if_floating_point<primitive_t<NumberT>>>
inline primitive_t<NumberT> stringToNumber(const StringT& str, std::size_t* pos = 0) noexcept(!Except)
{
    try {
        if constexpr (std::is_same_v<primitive_t<NumberT>, float>) {
            return std::stof(str, pos);
        }
        else if constexpr (std::is_same_v<primitive_t<NumberT>, double>) {
            return std::stod(str, pos);
        }
        else {
            return std::stold(str, pos);
        }
    }
    catch (...) {
        if constexpr (Exception) {
            throw;
        }
        else {
            return primitive_t<NumberT>(0.);
        }
    }
}

} // namespace utils4cpp::str

#endif // UTILS4CPP_STR_USTRINGTONUMBER_INL