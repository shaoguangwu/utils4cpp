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

#ifndef UTILS4CPP_USTRINGCONVERT_HPP
#define UTILS4CPP_USTRINGCONVERT_HPP

#include "utils4cpp/str/UStringGlobal.hpp"

namespace utils4cpp::str {

UTILS4CPP_EXPORT std::string wstringToString(const std::wstring& str);
UTILS4CPP_EXPORT std::wstring stringToWString(const std::string& str);

UTILS4CPP_EXPORT std::string u16stringToString(const std::u16string& str);
UTILS4CPP_EXPORT std::u16string strinngToU16String(const std::string& str);

UTILS4CPP_EXPORT std::string u32stringToString(const std::u32string& str);
UTILS4CPP_EXPORT std::u32string stringToU32String(const std::string& str);

#if UTILS4CPP_HAS_U8STRING

UTILS4CPP_EXPORT std::string u8stringToString(const std::u8string& str);
UTILS4CPP_EXPORT std::u8string stringToU8String(const std::string& str);

#endif // UTILS4CPP_HAS_U8STRING

/**
    \class UStringCvt
*/
template<class InternStringT, class ExternStringT>
class UStringCvt
{
public:
    /*  std::codecvt<char16_t, char, std::mbstate_t> (deprecated in C++20)
        std::codecvt<char32_t, char, std::mbstate_t> (deprecated in C++20)
        std::codecvt<char16_t, char8_t, std::mbstate_t> (since C++20)
        std::codecvt<char32_t, char8_t, std::mbstate_t> (since C++20)
    */
#if !UTILS4CPP_HAS_CPP2A
    /*
       Enabled in C++17: (template parameters: Traits, Allocator)

        UStringCvt<std::basic_string<wchar_t, Traits, Allocator>, std::basic_string<char, Traits, Allocator>>
        UStringCvt<std::basic_string<u16char_t, Traits, Allocator>, std::basic_string<char, Traits, Allocator>>
        UStringCvt<std::basic_string<u32char_t, Traits, Allocator>, std::basic_string<char, Traits, Allocator>>
    */
    using intern_string_type = std::enable_if_t<
        u_and<is_std_basic_string<InternStringT>, u_not<is_std_char_string<InternStringT>>>::value,
        primitive_t<InternStringT>>;
    using extern_string_type = std::enable_if_t<
        is_std_char_string_v<ExternStringT>, primitive_t<ExternStringT>>;
#else
    /*
       Enabled in C++20: (template parameters: Traits, Allocator)

        UStringCvt<std::basic_string<wchar_t, Traits, Allocator>, std::basic_string<char8_t, Traits, Allocator>>
        UStringCvt<std::basic_string<u16char_t, Traits, Allocator>, std::basic_string<char8_t, Traits, Allocator>>
        UStringCvt<std::basic_string<u32char_t, Traits, Allocator>, std::basic_string<char8_t, Traits, Allocator>>
    */
    using intern_string_type = std::enable_if_t<u_or<
        u_and<is_std_basic_string<InternStringT>, u_not<is_std_char_or_char8_string<InternStringT>>>,
        u_and<is_std_wchar_string<InternStringT>, is_std_char_string<ExternStringT>>>::value,
        primitive_t<InternStringT>>;
    using extern_string_type = std::enable_if_t<
        is_std_char8_string_v<ExternStringT>, primitive_t<ExternStringT>>;
#endif
    using intern_char_type = typename intern_string_type::value_type;
    using extern_char_type = typename extern_string_type::value_type;

    static intern_string_type in(const extern_string_type& str, const std::locale& loc = std::locale())
    {
        if (str.empty()) {
            return intern_string_type();
        }

        auto& convertor = std::use_facet<
            std::codecvt<intern_char_type, extern_char_type, std::mbstate_t>>(loc);
        std::mbstate_t state{};
        intern_string_type internal(str.size(), '\0');
        const extern_char_type* from_next;
        intern_char_type* to_next;

        auto result = convertor.in(state, str.data(), str.data() + str.size(), from_next,
            internal.data(), internal.data() + internal.size(), to_next);

        if (result != std::codecvt_base::ok) {
            return intern_string_type();
        }
        internal.resize(to_next - internal.data());
        return internal;

    }

    static extern_string_type out(const intern_string_type& str, const std::locale& loc = std::locale())
    {
        if (str.empty()) {
            return extern_string_type();
        }

        auto& convertor = std::use_facet<
            std::codecvt<intern_char_type, extern_char_type, std::mbstate_t>>(loc);
        std::mbstate_t state{};
        extern_string_type external(str.size() * convertor.max_length(), '\0');
        const intern_char_type* from_next;
        extern_char_type* to_next;

        auto result = convertor.out(state, str.data(), str.data() + str.size(), from_next,
            external.data(), external.data() + external.size(), to_next);

        if (result != std::codecvt_base::ok) {
            return extern_string_type();
        }
        external.resize(to_next - external.data());
        return external;
    }
};

template<class StringT>
class UStringCvt<StringT, StringT>
{
public:
    using intern_string_type = std::enable_if_t<is_std_basic_string_v<StringT>, primitive_t<StringT>>;
    using extern_string_type = intern_string_type;
    using intern_char_type = typename intern_string_type::value_type;
    using extern_char_type = typename extern_string_type::value_type;

    UTILS4CPP_MAYBE_UNUSED static intern_string_type in(
        const extern_string_type& str, const std::locale& loc = std::locale())
    {
        return str;
    }

    UTILS4CPP_MAYBE_UNUSED static extern_string_type out(
        const intern_string_type& str, const std::locale& loc = std::locale())
    {
        return str;
    }
};

} // namespace utils4cpp::str

#endif // UTILS4CPP_USTRINGCONVERT_HPP