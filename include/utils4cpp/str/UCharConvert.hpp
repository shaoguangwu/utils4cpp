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

#ifndef UTILS4CPP_STR_UCHARCONVERT_HPP
#define UTILS4CPP_STR_UCHARCONVERT_HPP

#include <optional>

#include "utils4cpp/str/UStringGlobal.hpp"

namespace utils4cpp::str {

UTILS4CPP_EXPORT std::optional<wchar_t> charToWChar(char c);
UTILS4CPP_EXPORT std::optional<char> wcharToChar(std::wint_t c);

UTILS4CPP_EXPORT std::optional<char16_t> charToU16Char(char c);
UTILS4CPP_EXPORT std::optional<char32_t> charToU32Char(char c);

#if UTILS4CPP_HAS_U8STRING
UTILS4CPP_EXPORT std::optional<char8_t> charToU8Char(char c);
#endif // UTILS4CPP_HAS_U8STRING


/**
    \class UCharCvt
    \brief 
    \TODO comments
*/
template<class InputT, class OutputT>
class UCharCvt 
{
public:
    using input_type = std::enable_if_t<is_char_v<InputT>, primitive_t<InputT>>;
    using output_type = std::enable_if_t<is_character_v<OutputT>, primitive_t<OutputT>>;

    static std::optional<output_type> convert(input_type c)
    {
        if constexpr (std::is_same_v<output_type, wchar_t>) {
            return charToWChar(c);
        }
        else if constexpr (std::is_same_v<output_type, char16_t>) {
            return charToU16Char(c);
        }
        else if constexpr (std::is_same_v<output_type, char32_t>) {
            return charToU32Char(c);
        }
#if UTILS4CPP_HAS_CHAR8T
        else if constexpr (std::is_same_v<output_type, char8_t>) {
            return charToU8Char(c);
        }
#endif // UTILS4CPP_HAS_CHAR8T
        else {
            return std::nullopt;
        }
    }
};

template<class InputT>
class UCharCvt<InputT, InputT>
{
public:
    using input_type = std::enable_if_t<is_character_v<InputT>, primitive_t<InputT>>;
    using output_type = input_type;

    static std::optional<output_type> convert(input_type c)
    {
        return c;
    }
};

template<>
class UCharCvt<wchar_t, char>
{
public:
    using input_type = wchar_t;
    using output_type = char;

    static std::optional<output_type> convert(input_type c)
    {
        return wcharToChar(c);
    }
};

}

#endif // UTILS4CPP_STR_UCHARCONVERT_HPP