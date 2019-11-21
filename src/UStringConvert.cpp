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

#include <cuchar>
#include <cwchar>
#include "utils4cpp/str/UStringConvert.hpp"

namespace utils4cpp::str {

UTILS4CPP_EXPORT 
std::string wstr2str(const std::wstring& str)
{
    using output_type = std::string;
    using output_char_type = typename output_type::value_type;

    if (str.empty()) {
        return output_type();
    }

    std::mbstate_t state{};
    auto wstr = str.c_str();
    std::size_t len = std::wcsrtombs(nullptr, &wstr, 0, &state);
    if (static_cast<std::size_t>(-1) == len || len < 1) {
        return output_type();
    }
    output_type result;
    result.resize(len + 1);
    std::wcsrtombs(&result.front(), &wstr, len + 1, &state);
    result.resize(len);
    return result;

}

UTILS4CPP_EXPORT 
std::wstring str2wstr(const std::string& str)
{
    using output_type = std::wstring;
    using output_char_type = typename output_type::value_type;

    if (str.empty()) {
        return output_type();
    }

    std::mbstate_t state{};
    auto mbstr = str.c_str();
    std::size_t len = std::mbsrtowcs(nullptr, &mbstr, 0, &state);
    if (static_cast<std::size_t>(-1) == len || len < 1) {
        return output_type();
    }
    output_type result;
    result.resize(len + 1);
    std::mbsrtowcs(&result.front(), &mbstr, len + 1, &state);
    result.resize(len);
    return result;
}

UTILS4CPP_EXPORT 
std::string u16str2str(const std::u16string& str)
{
    using input_type = std::u16string;
    using input_char_type = typename input_type::value_type;
    using output_type = std::string;
    using output_char_type = typename output_type::value_type;

    output_type result;
    if (str.empty()) {
        return result;
    }

    result.resize(str.size() * MB_LEN_MAX);
    std::mbstate_t state{};
    output_char_type buf[MB_LEN_MAX];
    std::size_t rc = 0;
    std::size_t offset = 0;
    for (input_char_type c : str) {
        rc = std::c16rtomb(buf, c, &state);
        if (static_cast<std::size_t>(-1) == rc) {
            return output_type();
        }
        std::copy(buf, buf + rc, &result[offset]);
        offset += rc;
    }
    result.resize(offset);
    return result;
}

// TODO
UTILS4CPP_EXPORT 
std::u16string str2u16str(const std::string& str)
{
    using output_type = std::u16string;
    using output_char_type = typename output_type::value_type;

    if (str.empty()) {
        return output_type();
    }
}

UTILS4CPP_EXPORT 
std::string u32str2str(const std::u32string& str)
{
    using input_type = std::u32string;
    using input_char_type = typename input_type::value_type;
    using output_type = std::string;
    using output_char_type = typename output_type::value_type;

    output_type result;
    if (str.empty()) {
        return result;
    }

    result.resize(str.size() * MB_LEN_MAX);
    std::mbstate_t state{};
    output_char_type buf[MB_LEN_MAX];
    std::size_t rc = 0;
    std::size_t offset = 0;
    for (input_char_type c : str) {
        rc = std::c32rtomb(buf, c, &state);
        if (static_cast<std::size_t>(-1) == rc) {
            return output_type();
        }
        std::copy(buf, buf + rc, &result[offset]);
        offset += rc;
    }
    result.resize(offset);
    return result;
}

// TODO
UTILS4CPP_EXPORT 
std::u32string str2u32str(const std::string& str)
{
    using output_type = std::u32string;
    using output_char_type = typename output_type::value_type;

    if (str.empty()) {
        return output_type();
    }
}

#if UTILS4CPP_HAS_U8STRING

UTILS4CPP_EXPORT 
std::string u8str2str(const std::u8string& str)
{
    using input_type = std::u8string;
    using input_char_type = typename input_type::value_type;
    using output_type = std::string;
    using output_char_type = typename output_type::value_type;

    output_type result;
    if (str.empty()) {
        return result;
    }

    result.resize(str.size() * MB_LEN_MAX);
    std::mbstate_t state{};
    output_char_type buf[MB_LEN_MAX];
    std::size_t rc = 0;
    std::size_t offset = 0;
    for (input_char_type c : str) {
        rc = std::c8rtomb(buf, c, &state);
        if (static_cast<std::size_t>(-1) == rc) {
            return output_type();
        }
        std::copy(buf, buf + rc, &result[offset]);
        offset += rc;
    }
    result.resize(offset);
    return result;
}

// TODO
UTILS4CPP_EXPORT 
std::u8string str2u8str(const std::string& str)
{
    using output_type = std::u8string;
    using output_char_type = typename output_type::value_type;

    if (str.empty()) {
        return output_type();
    }
}

#endif // UTILS4CPP_HAS_U8STRING

} // namespace utils4cpp::str