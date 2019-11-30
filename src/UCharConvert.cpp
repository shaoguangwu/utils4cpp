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

#include "utils4cpp/str/UCharCvt.hpp"

namespace utils4cpp::str {

UTILS4CPP_EXPORT
std::optional<char> wcharToChar(std::wint_t c)
{
    int cn = std::wctob(c);
    return cn == EOF ? std::nullopt : std::optional<char>{ cn };
}

UTILS4CPP_EXPORT 
std::optional<wchar_t> charToWChar(char c)
{
    std::wint_t w = std::btowc(static_cast<int>(c));
    return w == WEOF ? std::nullopt : std::optional<wchar_t>{ w };
}

UTILS4CPP_EXPORT 
std::optional<char16_t> charToU16Char(char c)
{
    std::mbstate_t state{};
    using output_char_type = char16_t;
    output_char_type oc;

    std::size_t rc = std::mbrtoc16(&oc, &c, 1, &state);
    return rc <= static_cast<std::size_t>(-1) / 2 ?
        std::optional<output_char_type>{ oc } : std::nullopt;
}

UTILS4CPP_EXPORT 
std::optional<char32_t> charToU32Char(char c)
{
    std::mbstate_t state{};
    using output_char_type = char32_t;
    output_char_type oc;

    std::size_t rc = std::mbrtoc32(&oc, &c, 1, &state);
    return rc <= static_cast<std::size_t>(-1) / 2 ? 
        std::optional<output_char_type>{ oc } : std::nullopt;
}

#if UTILS4CPP_HAS_CHAR8T

UTILS4CPP_EXPORT 
std::optional<char8_t> charToU8Char(char c)
{
    std::mbstate_t state{};
    using output_char_type = char8_t;
    output_char_type oc;

    std::size_t rc = std::mbrtoc8(&oc, &c, 1, &state);
    return rc <= static_cast<std::size_t>(-1) / 2 ?
        std::optional<output_char_type>{ oc } : std::nullopt;
}

#endif // UTILS4CPP_HAS_U8STRING

} // namespace utils4cpp::str