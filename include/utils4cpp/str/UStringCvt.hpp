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

// for msvc std::codecvt error (error LNK1120).
#if defined(UTILS4CPP_OS_WIN) && UTILS4CPP_CC_MSVC && UTILS4CPP_CC_MSVC >= 1900 && UTILS4CPP_CC_MSVC < 1920
#   define __HAS_MSVC_STDCODECVT_ERROR
#endif

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

namespace detail {

template<class InternStringT, class ExternStringT,
    class = std::enable_if_t<u_and<
    is_std_basic_string<InternStringT>, 
    is_std_basic_string<ExternStringT>>::value>>
class _UInternExternStringIsh
{ };

/**
    \class UStringCvtBase
    \since v0.0
    \brief code conversion base template class.
*/
template<class InternStringT, class ExternStringT>
class _UStringCvtBase : public _UInternExternStringIsh<InternStringT, ExternStringT>
{
public:
    /** Intern string type */
    using intern_string_type = InternStringT;
    /** Extern string type */
    using extern_string_type = ExternStringT;
    /** Intern char type */
    using intern_char_type = typename intern_string_type::value_type;
    /** Extern char type */
    using extern_char_type = typename extern_string_type::value_type;

    static intern_string_type in(const extern_string_type& str,
        const std::locale& loc = std::locale())
    {
        if (str.empty()) {
            return intern_string_type();
        }

        auto& convertor = std::use_facet<
            std::codecvt<intern_char_type, extern_char_type, std::mbstate_t>>(loc);
        std::mbstate_t state{};
        intern_string_type intern(str.size(), '\0');
        const extern_char_type* from_next = nullptr;
        intern_char_type* to_next = nullptr;

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

        auto& convertor = std::use_facet<
            std::codecvt<intern_char_type, extern_char_type, std::mbstate_t>>(loc);
        std::mbstate_t state{};
        extern_string_type external(str.size() * convertor.max_length(), '\0');
        const intern_char_type* from_next = nullptr;
        extern_char_type* to_next = nullptr;

        auto result = convertor.out(state,
            str.data(), str.data() + str.size(), from_next,
            external.data(), external.data() + external.size(), to_next);

        if (result != std::codecvt_base::ok) {
            return extern_string_type();
        }
        external.resize(to_next - external.data());
        return external;
    }
};

/**
    \class UStringCvtBaseExt
    \since v0.0
    \brief code conversion base template class for msvc std::codecvt error (error LNK1120).
*/
template<class InternStringT, class ExternStringT, 
    class SubstituteInternCharType, class = if_integral<SubstituteInternCharType>>
class _UStringCvtBaseExt : public _UInternExternStringIsh<InternStringT, ExternStringT>
{
public:
    /** \see UStringCvtBase::intern_string_type */
    using intern_string_type = InternStringT;
    /** \see UStringCvtBase::extern_string_type */
    using extern_string_type = ExternStringT;
    /** \see UStringCvtBase::intern_char_type */
    using intern_char_type = typename intern_string_type::value_type;
    /** \see UStringCvtBase::extern_char_type */
    using extern_char_type = typename extern_string_type::value_type;

    static intern_string_type in(const extern_string_type& str,
        const std::locale& loc = std::locale())
    {
        if (str.empty()) {
            return intern_string_type();
        }

        auto& convertor = std::use_facet<
            std::codecvt<SubstituteInternCharType, extern_char_type, std::mbstate_t>>(loc);
        std::mbstate_t state{};
        intern_string_type intern(str.size(), '\0');
        const extern_char_type* from_next = nullptr;
        SubstituteInternCharType* to_next = nullptr;

        auto result = convertor.in(state, str.data(), str.data() + str.size(), from_next,
            reinterpret_cast<SubstituteInternCharType*>(intern.data()),
            reinterpret_cast<SubstituteInternCharType*>(intern.data() + intern.size()), 
            to_next);

        if (result != std::codecvt_base::ok) {
            return intern_string_type();
        }
        intern.resize(to_next - reinterpret_cast<const SubstituteInternCharType*>(intern.data()));
        return intern;
    }

    static extern_string_type out(const intern_string_type& str,
        const std::locale& loc = std::locale())
    {
        if (str.empty()) {
            return extern_string_type();
        }

        auto& convertor = std::use_facet<
            std::codecvt<SubstituteInternCharType, extern_char_type, std::mbstate_t>>(loc);
        std::mbstate_t state{};
        extern_string_type external(str.size() * convertor.max_length(), '\0');
        const SubstituteInternCharType* from_next = nullptr;
        extern_char_type* to_next = nullptr;

        auto result = convertor.out(state,
            reinterpret_cast<const SubstituteInternCharType*>(str.data()),
            reinterpret_cast<const SubstituteInternCharType*>(str.data() + str.size()), from_next,
            external.data(), external.data() + external.size(), to_next);

        if (result != std::codecvt_base::ok) {
            return extern_string_type();
        }
        external.resize(to_next - external.data());
        return external;
    }
};

} // namespace detail

/**
    \class UStringCvt
    \since v0.0
*/
template<class InternStringT, class ExternStringT>
class UStringCvt
    : public detail::_UInternExternStringIsh<InternStringT, ExternStringT>
{
public:
    using intern_string_type = InternStringT;
    using extern_string_type = ExternStringT;
    using intern_char_type = typename intern_string_type::value_type;
    using extern_char_type = typename extern_string_type::value_type;

    static intern_string_type in(UTILS4CPP_ATTR_MAYBE_UNUSED const extern_string_type& str,
        UTILS4CPP_ATTR_MAYBE_UNUSED const std::locale& loc = std::locale())
    {
        return intern_string_type();
    }

    static extern_string_type out(UTILS4CPP_ATTR_MAYBE_UNUSED const intern_string_type& str,
        UTILS4CPP_ATTR_MAYBE_UNUSED const std::locale& loc = std::locale())
    {
        return extern_string_type();
    }
};

template<class StringT>
class UStringCvt<StringT, StringT>
    : public detail::_UInternExternStringIsh<StringT, StringT>
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

template<>
class UStringCvt<std::wstring, std::string>
    : public detail::_UStringCvtBase<std::wstring, std::string>
{ };

#if UTILS4CPP_HAS_CHAR8T

template<>
class UStringCvt<std::u16string, std::u8string>
    : public detail::_UStringCvtBase<std::u16string, std::u8string>
{ };

template<>
class UStringCvt<std::u32string, std::u8string>
    : public detail::_UStringCvtBase<std::u32string, std::u8string>
{ };

#else

template<>
class UStringCvt<std::u16string, std::string>
#ifdef __HAS_MSVC_STDCODECVT_ERROR
    : public detail::_UStringCvtBaseExt<std::u16string, std::string, std::int16_t>
#else
    : public detail::_UStringCvtBase<std::u16string, std::string>
#endif
{ };

template<>
class UStringCvt<std::u32string, std::string>
#ifdef __HAS_MSVC_STDCODECVT_ERROR
    : public detail::_UStringCvtBaseExt<std::u32string, std::string, std::int32_t>
#else
    : public detail::_UStringCvtBase<std::u16string, std::string>
#endif
{ };

#endif // UTILS4CPP_HAS_CHAR8T

} // namespace utils4cpp::str

#endif // UTILS4CPP_USTRINGCONVERT_HPP
