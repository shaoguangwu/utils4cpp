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

#ifndef UTILS4CPP_STR_STRINGUTILS_HPP
#define UTILS4CPP_STR_STRINGUTILS_HPP

#include <string>
#include <vector>

#include "utils4cpp/str/StringToNumber.hpp"
#include "utils4cpp/core/Core.hpp"

namespace utils4cpp {
/*!
    \brief String utility library.
    \since v0.0
*/
namespace str {

/*! Indicates case sensitive or not. */
enum CaseSensitivity {
    CaseInsensitive,                ///< Case insensitive.  (no)
    CaseSensitive                   ///< Case sensitive.    (yes)
};

UTILS4CPP_EXPORT std::string removeCharacter(const std::string& str, char ch,  int option = 0);
UTILS4CPP_EXPORT std::wstring removeCharacter(const std::wstring& str, wchar_t ch, int option = 0);

UTILS4CPP_EXPORT std::string removeSubstr(const std::string& str, const std::string& sub, int option = 0);
UTILS4CPP_EXPORT std::wstring removeSubstr(const std::wstring& str, const std::wstring& sub, int option = 0);

UTILS4CPP_EXPORT void replaceString(std::string& str, const std::string& before, const std::string& after);
UTILS4CPP_EXPORT void replaceString(std::wstring& str, const std::wstring& before, const std::wstring& after);

UTILS4CPP_EXPORT std::vector<std::string> splitString(const std::string& str, char delim);
UTILS4CPP_EXPORT std::vector<std::string> splitString(const std::string& str, const std::string& delim);
UTILS4CPP_EXPORT std::vector<std::wstring> splitString(const std::wstring& str, wchar_t delim);
UTILS4CPP_EXPORT std::vector<std::wstring> splitString(const std::wstring& str, const std::wstring& delim);

UTILS4CPP_EXPORT std::string joinString(const std::vector<std::string>& strs, char delim);
UTILS4CPP_EXPORT std::string joinString(const std::vector<std::string>& strs, const std::string& delim);
UTILS4CPP_EXPORT std::wstring joinString(const std::vector<std::wstring>& strs, char delim);
UTILS4CPP_EXPORT std::wstring joinString(const std::vector<std::wstring>& strs, const std::wstring& delim);
 
UTILS4CPP_EXPORT std::string toLower(const std::string& str);
UTILS4CPP_EXPORT std::string toUpper(const std::string& str);
UTILS4CPP_EXPORT std::wstring toLower(const std::wstring& str);
UTILS4CPP_EXPORT std::wstring toUpper(const std::wstring& str);

UTILS4CPP_EXPORT std::string capitalized(const std::string& str);
UTILS4CPP_EXPORT std::wstring capitalized(const std::wstring& str);
UTILS4CPP_EXPORT std::string capitalizedWords(const std::string& str);
UTILS4CPP_EXPORT std::wstring capitalizedWords(const std::wstring& str);
UTILS4CPP_EXPORT std::string uncapitalizedWords(const std::string& str);
UTILS4CPP_EXPORT std::wstring uncapitalizedWords(const std::wstring& str);

UTILS4CPP_EXPORT std::wstring toWstring(const std::string& str);
UTILS4CPP_EXPORT std::string toString(const std::wstring& wstr);

template<typename DstT, class StringT>
DstT toNumber(const StringT& str, std::size_t* pos, int base, bool noexception = false);

template<typename DstT, class StringT>
DstT toNumber(const StringT& str, std::size_t* pos, bool noexception = false);

template<typename DstT, class StringT>
DstT toNumber(const StringT& str, bool noexception = false);

UTILS4CPP_EXPORT bool startsWith(const std::string& str, char starts, CaseSensitivity cs = CaseSensitive);
UTILS4CPP_EXPORT bool startsWith(const std::string& str, const std::string& starts, CaseSensitivity cs = CaseSensitive);
UTILS4CPP_EXPORT bool startsWith(const std::wstring& str, wchar_t starts, CaseSensitivity cs = CaseSensitive);
UTILS4CPP_EXPORT bool startsWith(const std::wstring& str, const std::wstring& starts, CaseSensitivity cs = CaseSensitive);

UTILS4CPP_EXPORT bool endsWith(const std::string& str, char ends, CaseSensitivity cs = CaseSensitive);
UTILS4CPP_EXPORT bool endsWith(const std::string& str, const std::string& ends, CaseSensitivity cs = CaseSensitive);
UTILS4CPP_EXPORT bool endsWith(const std::wstring& str, wchar_t ends, CaseSensitivity cs = CaseSensitive);
UTILS4CPP_EXPORT bool endsWith(const std::wstring& str, const std::wstring& ends, CaseSensitivity cs = CaseSensitive);

template<typename ... Args>
std::string formatString(const std::string& format, Args ... args);

template<typename ... Args>
std::wstring formatString(const std::wstring& format, Args ... args);





/*! 
    \fn template<typename DstT, class StringT> DstT toNumber(const StringT& str, std::size_t* pos, int base, bool noexception)
    Interprets an integer value in the string \a str.

    \param str the string to convert.
    \param pos address of an integer to store the number of characters processed.
    \param base the number base.
    \param noexception indicates whether an exception is thrown.

    \exception  std::invalid_argument if no conversion could be performed and noexception is set to false.
    \exception  std::out_of_range if the converted value would fall out of the range of the result type.

    \note If param \a noexception set to true and exceptions are performed, return zero.
*/
template<typename DstT, class StringT>
DstT toNumber(const StringT& str, std::size_t* pos, int base, bool noexception)
{
    if (noexception) {
        try {
            return internal::stringToNumber<DstT>(str, pos, base);
        } catch(const std::exception& e) {
            return DstT(0);
        }
    } else {
        return internal::stringToNumber<DstT>(str, pos, base);
    }
}

/*!
    Interprets an integer value or a floating point value in the string \a str.

    \param str the string to convert.
    \param pos address of an integer to store the number of characters processed.
    \param noexception indicates whether an exception is thrown.

    \exception  std::invalid_argument if no conversion could be performed and noexception is set to false.
    \exception  std::out_of_range if the converted value would fall out of the range of the result type.

    \note If param \a noexception set to true and exceptions are performed, return zero.
    \note Converses to decimal base integer by default.
*/
template<typename DstT, class StringT>
DstT toNumber(const StringT& str, std::size_t* pos, bool noexception)
{
    if (noexception) {
        try {
            return internal::stringToNumber<DstT>(str, pos);
        } catch(const std::exception& e) {
            return DstT(0);
        }
    } else {
        return internal::stringToNumber<DstT>(str, pos);
    }
}

/*!
    Interprets an integer value a floating point value in the string \a str.

    \param str the string to convert.
    \param noexception indicates whether an exception is thrown.

    \exception  std::invalid_argument if no conversion could be performed and noexception is set to false.
    \exception  std::out_of_range if the converted value would fall out of the range of the result type.

    \note If param \a noexception set to true and exceptions are performed, return zero.
    \note Converses to decimal base integer by default.
*/
template<typename DstT, class StringT>
DstT toNumber(const StringT& str, bool noexception)
{
    if (noexception) {
        try {
            return internal::stringToNumber<DstT>(str);
        } catch(const std::exception& e) {
            return DstT(0);
        }
    } 
    else {
        return internal::stringToNumber<DstT>(str);
    }
}

/*!
    Format string in a specified \a format by \a args.
    The format specifiers can reference snprintf()'s format specifiers.
*/
template<typename ... Args>
std::string formatString(const std::string& format, Args ... args)
{
    auto size = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    if (size <= 0) {
        return std::string();
    }
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args ...);
    return { buf.get(), buf.get() + size - 1 }; // We don't want the '\0' inside
}

/*!
    Format wide string in a specified \a format by \a args.
    The format specifiers can reference swprintf()'s format specifiers.

    \warning If \a args contains string, use wide string form. 
*/
template<typename ... Args>
std::wstring formatString(const std::wstring& format, Args ... args)
{
    auto size = std::swprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    if (size <= 0) {
        return std::wstring();
    }
    std::unique_ptr<wchar_t[]> buf(new wchar_t[size]);
    std::swprintf(buf.get(), size, format.c_str(), args ...);
    return { buf.get(), buf.get() + size - 1 }; // We don't want the '\0' inside
}

} // namespace str
} // namespace utils4cpp

#endif // UTILS4CPP_STR_STRINGUTILS_HPP