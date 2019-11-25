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
std::string wstringToString(const std::wstring& str)
{
    using output_type = std::string;

    output_type result;
    if (str.empty()) {
        return result;
    }

    std::mbstate_t state{};
    auto wstr = str.c_str();
#ifdef UTILS4CPP_CC_MSVC
#pragma warning(push)
#pragma warning(disable:4996)
#endif
    std::size_t len = std::wcsrtombs(nullptr, &wstr, 0, &state);
#ifdef UTILS4CPP_CC_MSVC
#pragma warning(pop)
#endif
    if (static_cast<std::size_t>(-1) == len || len == 0) {
        return result;
    }

    result.resize(len);
#ifdef UTILS4CPP_CC_MSVC
#pragma warning(push)
#pragma warning(disable:4996)
#endif
    std::wcsrtombs(&result.front(), &wstr, len, &state);
#ifdef UTILS4CPP_CC_MSVC
#pragma warning(pop)
#endif
    return result;
}

UTILS4CPP_EXPORT 
std::wstring stringToWString(const std::string& str)
{
    using output_type = std::wstring;

    output_type result;
    if (str.empty()) {
        return result;
    }

    std::mbstate_t state{};
    auto mbstr = str.c_str();
#ifdef UTILS4CPP_CC_MSVC
#pragma warning(push)
#pragma warning(disable:4996)
#endif
    std::size_t len = std::mbsrtowcs(nullptr, &mbstr, 0, &state);
#ifdef UTILS4CPP_CC_MSVC
#pragma warning(pop)
#endif
    if (static_cast<std::size_t>(-1) == len || len == 0) {
        return result;
    }
    result.resize(len);
#ifdef UTILS4CPP_CC_MSVC
#pragma warning(push)
#pragma warning(disable:4996)
#endif
    std::mbsrtowcs(&result.front(), &mbstr, len, &state);
#ifdef UTILS4CPP_CC_MSVC
#pragma warning(pop)
#endif
    return result;
}

UTILS4CPP_EXPORT 
std::string u16stringToString(const std::u16string& str)
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
    std::size_t n = 0;

    for (input_char_type c : str) {
        rc = std::c16rtomb(buf, c, &state);
        if (static_cast<std::size_t>(-1) == rc) {
            return output_type();
        }
        std::copy(buf, buf + rc, &result[n]);
        n += rc;
    }

    result.resize(n);
    return result;
}

UTILS4CPP_EXPORT 
std::u16string strinngToU16String(const std::string& str)
{
    using input_type = std::string;
    using input_char_type = typename input_type::value_type;
    using output_type = std::u16string;
    using output_char_type = typename output_type::value_type;

    output_type result;
    if (str.empty()) {
        return result;
    }

    std::mbstate_t state{};
    output_char_type c;
    const input_char_type* ptr = str.c_str();
    const input_char_type* end = str.c_str() + str.size() + 1;
    result.resize(str.size());
    std::size_t n = 0;

    while (std::size_t rc = std::mbrtoc16(&c, ptr, end - ptr, &state)) {
        if (rc <= static_cast<std::size_t>(-1) / 2) {
            result[n++] = c;
            ptr += rc;
        }
        else if (rc == static_cast<std::size_t>(-3)) {
            // earlier surrogate pair.
        }
        else if (rc == static_cast<std::size_t>(-1)) {
            return output_type();
        }
        else {
            break;
        }
    }
    result.resize(n);
    return result;
}

UTILS4CPP_EXPORT 
std::string u32stringToString(const std::u32string& str)
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
    std::size_t n = 0;
    for (input_char_type c : str) {
        rc = std::c32rtomb(buf, c, &state);
        if (static_cast<std::size_t>(-1) == rc) {
            return output_type();
        }
        std::copy(buf, buf + rc, &result[n]);
        n += rc;
    }
    result.resize(n);
    return result;
}

// TODO
UTILS4CPP_EXPORT 
std::u32string stringToU32String(const std::string& str)
{
    using input_type = std::string;
    using input_char_type = typename input_type::value_type;
    using output_type = std::u32string;
    using output_char_type = typename output_type::value_type;

    output_type result;
    if (str.empty()) {
        return result;
    }

    std::mbstate_t state{};
    output_char_type c;
    const input_char_type* ptr = str.c_str();
    const input_char_type* end = str.c_str() + str.size() + 1;
    result.resize(str.size());
    std::size_t n = 0;

    while (std::size_t rc = std::mbrtoc32(&c, ptr, end - ptr, &state)) {
        if (rc <= static_cast<std::size_t>(-1) / 2) {
            result[n++] = c;
            ptr += rc;
        }
        else if (rc == static_cast<std::size_t>(-1)) {
            return output_type();
        }
        else {
            break;
        }
    }
    result.resize(n);
    return result;
}

#if UTILS4CPP_HAS_U8STRING

UTILS4CPP_EXPORT 
std::string u8stringToString(const std::u8string& str)
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
    std::size_t n = 0;
    for (input_char_type c : str) {
        rc = std::c8rtomb(buf, c, &state);
        if (static_cast<std::size_t>(-1) == rc) {
            return output_type();
        }
        std::copy(buf, buf + rc, &result[n]);
        n += rc;
    }
    result.resize(n);
    return result;
}

// TODO
UTILS4CPP_EXPORT 
std::u8string stringToU8String(const std::string& str)
{
    using input_type = std::string;
    using input_char_type = typename input_type::value_type;
    using output_type = std::u8string;
    using output_char_type = typename output_type::value_type;

    output_type result;
    if (str.empty()) {
        return result;
    }

    std::mbstate_t state{};
    output_char_type c;
    const input_char_type* ptr = str.c_str();
    const input_char_type* end = str.c_str() + str.size() + 1;
    result.resize(str.size());
    std::size_t n = 0;

    while (std::size_t rc = std::mbrtoc8(&c, ptr, end - ptr, &state)) {
        if (rc <= static_cast<std::size_t>(-1) / 2) {
            result[n++] = c;
            ptr += rc;
        }
        else if (rc == static_cast<std::size_t>(-1)) {
            return output_type();
        }
        else {
            break;
        }
    }
    result.resize(n);
    return result;
}

#endif // UTILS4CPP_HAS_U8STRING

} // namespace utils4cpp::str