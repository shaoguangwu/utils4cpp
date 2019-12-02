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
UTILS4CPP_EXPORT std::u16string stringToU16String(const std::string& str);

UTILS4CPP_EXPORT std::string u32stringToString(const std::u32string& str);
UTILS4CPP_EXPORT std::u32string stringToU32String(const std::string& str);

#if UTILS4CPP_HAS_CHAR8T

UTILS4CPP_EXPORT std::string u8stringToString(const std::u8string& str);
UTILS4CPP_EXPORT std::u8string stringToU8String(const std::string& str);

#endif // UTILS4CPP_HAS_U8STRING

/**
    若 std::has_facet<Facet>(loc) == false 则为 std::bad_cast
*/
template<class InternStringT, class ExternStringT>
class UStringCvt
{
public:
    using intern_string_type = InternStringT;
    using extern_string_type = ExternStringT;
    using intern_char_type = typename intern_string_type::value_type;
    using extern_char_type = typename extern_string_type::value_type;

    template<bool Except = true>
    static intern_string_type in(const extern_string_type& str,
        const std::locale& loc = std::locale())
    {
        if (str.empty()) {
            return intern_string_type();
        }

        try {
            auto& convertor = std::use_facet<
                std::codecvt<intern_char_type, extern_char_type, std::mbstate_t>>(loc);
        }
        catch (...) {
            if constexpr (Except) throw;
            else return intern_string_type();
        }
        std::mbstate_t state{};
        intern_string_type intern(str.size(), '\0');
        const extern_char_type* from_next;
        intern_char_type* to_next;

        auto result = convertor.in(state, str.data(), str.data() + str.size(), from_next,
            intern.data(), intern.data() + intern.size(), to_next);

        if (result != std::codecvt_base::ok) {
            return intern_string_type();
        }
        intern.resize(to_next - intern.data());
        return intern;
    }

    static extern_string_type out(const intern_string_type& str,
        const std::locale& loc = std::locale())
    {
        if (str.empty()) {
            return extern_string_type();
        }

        try {
            auto& convertor = std::use_facet<
                std::codecvt<intern_char_type, extern_char_type, std::mbstate_t>>(loc);
        } catch (...) {
            if constexpr (Except) throw;
            else return extern_string_type();
        }

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

/**
    Template specialization for identity conversion.
*/
template<class StringT>
class UStringCvt<StringT, StringT>
{
public:
    using intern_string_type = StringT;
    using extern_string_type = StringT;
    using intern_char_type = typename intern_string_type::value_type;
    using extern_char_type = typename extern_string_type::value_type;

    static intern_string_type in(const extern_string_type& str,
        UTILS4CPP_ATTR_MAYBE_UNUSED const std::locale& loc = std::locale())
    {
        return str;
    }

    static extern_string_type out(const intern_string_type& str,
        UTILS4CPP_ATTR_MAYBE_UNUSED const std::locale& loc = std::locale())
    {
        return str;
    }
};

/**
    Template specialization for std::u16string and std::string interconversion.

    Since C++20, <code> std::codecvt<char16_t, char, StateT> </code> will be deprecate, 
    so use <code> std::codecvt<std::int16_t, char, StateT> </code> to instead.
    There is a bug std::codecvt<char16_t, char, StateT> (error LNK1120) for msvc compiler.
    Also use <code> std::codecvt<std::int16_t, char, StateT> </code> to avoid it.
*/
template<>
class UStringCvt<std::u16string, std::string>
{
public:
    using intern_string_type = std::u16string;
    using extern_string_type = std::string;
    using intern_char_type = typename intern_string_type::value_type;
    using extern_char_type = typename extern_string_type::value_type;

private:
    // for msvc std::codecvt bug (error LNK1120).
#if (UTILS4CPP_CC_MSVC && UTILS4CPP_CC_MSVC >= 1900 && UTILS4CPP_CC_MSVC < 1920 ) || UTILS4CPP_HAS_CHAR8T
    using substitute_intern_char_type = std::int16_t;
    using substitute_intern_string_type = std::basic_string<substitute_intern_char_type>;
#else
    using substitute_intern_char_type = intern_char_type;
    using substitute_intern_string_type = intern_string_type;
#endif

public:

    static intern_string_type in(const extern_string_type& str,
        const std::locale& loc = std::locale())
    {
        if (str.empty()) {
            return intern_string_type();
        }

        auto& convertor = std::use_facet<
            std::codecvt<substitute_intern_char_type, extern_char_type, std::mbstate_t>>(loc);
        std::mbstate_t state{};

#if UTILS4CPP_HAS_CHAR8T
        substitute_intern_string_type intern(str.size(), '\0');
        const extern_char_type* from_next = nullptr;
        substitute_intern_char_type* to_next = nullptr;

        auto result = convertor.in(state, str.data(), str.data() + str.size(), from_next,
            intern.data(), intern.data() + intern.size(), to_next);

        if (result != std::codecvt_base::ok) {
            return intern_string_type();
        }
        return { intern.cbegin(), intern.cbegin() + (to_next - intern.data()) };
#else
        intern_string_type intern(str.size(), '\0');
        const extern_char_type* from_next = nullptr;
        substitute_intern_char_type* to_next = nullptr;

        auto result = convertor.in(state, str.data(), str.data() + str.size(), from_next,
            reinterpret_cast<substitute_intern_char_type*>(intern.data()),
            reinterpret_cast<substitute_intern_char_type*>(intern.data() + intern.size()), to_next);

        if (result != std::codecvt_base::ok) {
            return intern_string_type();
        }
        intern.resize(to_next - reinterpret_cast<substitute_intern_char_type*>(intern.data()));
        return intern;
#endif
    }

    static extern_string_type out(const intern_string_type& str,
        UTILS4CPP_ATTR_MAYBE_UNUSED const std::locale& loc = std::locale())
    {
        if (str.empty()) {
            return extern_string_type();
        }

        auto& convertor = std::use_facet<
            std::codecvt<substitute_intern_char_type, extern_char_type, std::mbstate_t>>(loc);
        std::mbstate_t state{};
        extern_string_type external(str.size() * convertor.max_length(), '\0');
        const substitute_intern_char_type* from_next = nullptr;
        extern_char_type* to_next = nullptr;

        auto result = convertor.out(state, 
            reinterpret_cast<const substitute_intern_char_type *>(str.data()), 
            reinterpret_cast<const substitute_intern_char_type *>(str.data() + str.size()), from_next,
            external.data(), external.data() + external.size(), to_next);

        if (result != std::codecvt_base::ok) {
            return extern_string_type();
        }
        external.resize(to_next - external.data());
        return external;
    }
};

/**
    Template specialization for std::u32string and std::string interconversion.

    Since C++20, <code> std::codecvt<char32_t, char, StateT> </code> will be deprecate,
    so use <code> std::codecvt<std::int32_t, char, StateT> </code> to instead.
    There is a bug std::codecvt<char32_t, char, StateT> (error LNK1120) for msvc compiler.
    Also use <code> std::codecvt<std::int32_t, char, StateT> </code> to avoid it.
*/
template<>
class UStringCvt<std::u32string, std::string>
{
public:
    using intern_string_type = std::u32string;
    using extern_string_type = std::string;
    using intern_char_type = typename intern_string_type::value_type;
    using extern_char_type = typename extern_string_type::value_type;

private:
    // for msvc std::codecvt bug (error LNK1120).
#if (UTILS4CPP_CC_MSVC && UTILS4CPP_CC_MSVC >= 1900 && UTILS4CPP_CC_MSVC < 1920 ) || UTILS4CPP_HAS_CHAR8T
    using substitute_intern_char_type = std::int32_t;
    using substitute_intern_string_type = std::basic_string<substitute_intern_char_type>;
#else
    using substitute_intern_char_type = intern_char_type;
    using substitute_intern_string_type = intern_string_type;
#endif

public:

    static intern_string_type in(const extern_string_type& str,
        const std::locale& loc = std::locale())
    {
        if (str.empty()) {
            return intern_string_type();
        }

        auto& convertor = std::use_facet<
            std::codecvt<substitute_intern_char_type, extern_char_type, std::mbstate_t>>(loc);
        std::mbstate_t state{};

#if UTILS4CPP_HAS_CHAR8T
        substitute_intern_string_type intern(str.size(), '\0');
        const extern_char_type* from_next = nullptr;
        substitute_intern_char_type* to_next = nullptr;

        auto result = convertor.in(state, str.data(), str.data() + str.size(), from_next,
            intern.data(), intern.data() + intern.size(), to_next);

        if (result != std::codecvt_base::ok) {
            return intern_string_type();
        }
        return { intern.cbegin(), intern.cbegin() + (to_next - intern.data()) };
#else
        intern_string_type intern(str.size(), '\0');
        const extern_char_type* from_next = nullptr;
        substitute_intern_char_type* to_next = nullptr;

        auto result = convertor.in(state, str.data(), str.data() + str.size(), from_next,
            reinterpret_cast<substitute_intern_char_type*>(intern.data()),
            reinterpret_cast<substitute_intern_char_type*>(intern.data() + intern.size()), to_next);

        if (result != std::codecvt_base::ok) {
            return intern_string_type();
        }
        intern.resize(to_next - reinterpret_cast<substitute_intern_char_type*>(intern.data()));
        return intern;
#endif
    }

    static extern_string_type out(const intern_string_type& str,
        UTILS4CPP_ATTR_MAYBE_UNUSED const std::locale& loc = std::locale())
    {
        if (str.empty()) {
            return extern_string_type();
        }

        auto& convertor = std::use_facet<
            std::codecvt<substitute_intern_char_type, extern_char_type, std::mbstate_t>>(loc);
        std::mbstate_t state{};
        extern_string_type external(str.size() * convertor.max_length(), '\0');
        const substitute_intern_char_type* from_next = nullptr;
        extern_char_type* to_next = nullptr;

        auto result = convertor.out(state,
            reinterpret_cast<const substitute_intern_char_type *>(str.data()),
            reinterpret_cast<const substitute_intern_char_type *>(str.data() + str.size()), from_next,
            external.data(), external.data() + external.size(), to_next);

        if (result != std::codecvt_base::ok) {
            return extern_string_type();
        }
        external.resize(to_next - external.data());
        return external;
    }
};

} // namespace utils4cpp::str

#endif // UTILS4CPP_USTRINGCONVERT_HPP