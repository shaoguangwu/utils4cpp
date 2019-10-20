/************************************************************************************
**
**  BSD 3-Clause License
**
**  Copyright (c) 2019 Simon Wu. All rights reserved.
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

#ifndef UTILS4CPP_STR_STRINGUTILSEXT_HPP
#define UTILS4CPP_STR_STRINGUTILSEXT_HPP

#include <clocale>

#include <vector>
#include <locale>
#include <algorithm>
#include <memory>
#include <typeinfo>
#include <type_traits>

#include "utils4cpp/str/StringToNumber.inc"
#include "utils4cpp/str/StringGlobal.hpp"

namespace utils4cpp {
namespace str_tem {

/*! StringVector is a sequence container that encapsulates strings. */
template<class StringT>
using StringVector = std::vector<StringT>;

template<class StringT>
void removeCharacter(StringT& str, typename StringT::value_type ch, int option = 0);
template<class StringT>
StringT removeCharacter(const StringT& str, typename StringT::value_type ch, int option = 0);

template<class StringT>
void removeSubstr(StringT& str, const StringT& sub, int option = 0);
template<class StringT>
StringT removeSubstr(const StringT& str, const StringT& sub, int option = 0);

template<class StringT>
void replaceString(StringT& str, const StringT& before, const StringT& after);

template<class StringT>
StringVector<StringT> splitString(const StringT& str, typename StringT::value_type delim);
template<class StringT>
StringVector<StringT> splitString(const StringT& str, const StringT& delim);

template<class StringT, class DelimT>
StringT joinString(const StringVector<StringT>& strs, const DelimT& delim);

template<class StringT>
void toLower(StringT& str, const std::locale& loc = std::locale());
template<class StringT>
StringT toLower(const StringT& str, const std::locale& loc = std::locale());

template<class StringT>
void toUpper(StringT& str, const std::locale& loc = std::locale());
template<class StringT>
StringT toUpper(const StringT& str, const std::locale& loc = std::locale());

template<class StringT>
void capitalized(StringT& str, const std::locale& loc = std::locale());
template<class StringT>
StringT capitalized(const StringT& str, const std::locale& loc = std::locale());

template<class StringT>
void capitalizedWords(StringT& str, const std::locale& loc = std::locale());
template<class StringT>
StringT capitalizedWords(const StringT& str, const std::locale& loc = std::locale());

template<class StringT>
void uncapitalizedWords(StringT& str, const std::locale& loc = std::locale());
template<class StringT>
StringT uncapitalizedWords(const StringT& str, const std::locale& loc = std::locale());

template<class DstStringT, class SrcStringT>
DstStringT convertString(const SrcStringT& str, const char* locale);
template<> // template specialization
std::string convertString(const std::wstring& str, const char* locale);
template<> // template specialization
std::wstring convertString(const std::string& str, const char* locale);

template<class DstStringT, class SrcStringT>
DstStringT convertString(const SrcStringT& str);
template<> // template specialization
std::string convertString(const std::wstring& str);
template<> // template specialization
std::wstring convertString(const std::string& str);



/*!
    Remove character \a ch from string \a str.

    The \a option :
    \li negative (  < 0) : Remove the first character equal to \a ch in the given string.
    \li positive (  > 0) : Remove the last character equal to \a ch in the given string.
    \li     zero ( == 0) : Remove all the characters equal to \a ch in the given string.

    \sa removeSubstr()
*/
template<class StringT>
void removeCharacter(StringT& str, typename StringT::value_type ch, int option)
{
    using CharT = typename StringT::value_type;
    using SizeT = typename StringT::size_type;

    if (str.empty()) {
        return;
    }

    if (option != 0) {
        auto pos = option < 0 ? str.find(ch) : str.rfind(ch);
        if (pos != StringT::npos) {
            str.erase(pos, 1);
            return;
        }
    } else { // option == 0
        auto pos = str.find(ch);
        if (pos != StringT::npos) {
            std::unique_ptr<CharT[]> buff(new CharT[str.size() + 1]);
            SizeT len = 0;
            SizeT pos1 = 0;
            while (pos != StringT::npos) {
                std::copy_n(str.begin() + pos1, pos - pos1, buff.get() + len);
                len += pos - pos1;
                pos1 = ++pos;
                pos = str.find(ch, pos1);
            }
            std::copy_n(str.begin() + pos1, str.size() - pos1, buff.get() + len);
            len += str.size() - pos1;
            str = StringT(buff.get(), len);
        }   
    }
}

/*!
    Remove character \a ch from string \a str.

    The \a option :
    \li negative (  < 0) : Remove the first character equal to \a ch in the given string.
    \li positive (  > 0) : Remove the last character equal to \a ch in the given string.
    \li     zero ( == 0) : Remove all the characters equal to \a ch in the given string.

    \sa removeSubstr()
*/
template<class StringT>
StringT removeCharacter(const StringT& str, typename StringT::value_type ch, int option)
{
    using CharT = typename StringT::value_type;
    using SizeT = typename StringT::size_type;

    if (str.empty()) {
        return str;
    }

    if (option != 0) {
        auto pos = option < 0 ? str.find(ch) : str.rfind(ch);
        if (pos != StringT::npos) {
            StringT result(str);
            result.erase(pos, 1);
            return result;
        }
    } else { // option == 0
        auto pos = str.find(ch);
        if (pos != StringT::npos) {
            std::unique_ptr<CharT[]> buff(new CharT[str.size() + 1]);
            SizeT len = 0;
            SizeT pos1 = 0;
            while (pos != StringT::npos) {
                std::copy_n(str.begin() + pos1, pos - pos1, buff.get() + len);
                len += pos - pos1;
                pos1 = ++pos;
                pos = str.find(ch, pos1);
            }
            std::copy_n(str.begin() + pos1, str.size() - pos1, buff.get() + len);
            len += str.size() - pos1;
            return StringT(buff.get(), len);
        }       
    }
    return str;
}

/*!
    Remove substring \a sub from string \a str.

    The \a option :
    \li negative (  < 0) : Remove the first substring equal to \a sub in the given string.
    \li positive (  > 0) : Remove the last substring equal to \a sub in the given string.
    \li     zero ( == 0) : Remove all the substrings equal to \a sub in the given string.

    \sa removeCharacter()
*/
template<class StringT>
void removeSubstr(StringT& str, const StringT& sub, int option = 0)
{
    using CharT = typename StringT::value_type;
    using SizeT = typename StringT::size_type;

    if (str.empty() || sub.empty()) {
        return;
    }

    if (option != 0) {
        auto pos = option < 0 ? str.find(sub) : str.rfind(sub);
        if (pos != StringT::npos) {
            str.erase(pos, sub.size());
        }
    } else { // option == 0
        auto pos = str.find(sub);
        if (pos != StringT::npos) {
            std::unique_ptr<CharT[]> buff(new CharT[str.size() + 1]);
            SizeT len = 0;
            SizeT pos1 = 0;
            while (pos != StringT::npos) {
                std::copy_n(str.begin() + pos1, pos - pos1, buff.get() + len);
                len += pos - pos1;
                pos1 = pos + sub.size();
                pos = str.find(sub, pos1);
            }
            std::copy_n(str.begin() + pos1, str.size() - pos1, buff.get() + len);
            len += str.size() - pos1;
            str = StringT(buff.get(), len);
        }
    }
}

/*!
    Remove substring \a sub from string \a str.

    The \a option :
    \li negative (  < 0) : Remove the first substring equal to \a sub in the given string.
    \li positive (  > 0) : Remove the last substring equal to \a sub in the given string.
    \li     zero ( == 0) : Remove all the substrings equal to \a sub in the given string.

    \sa removeCharacter()
*/
template<class StringT>
StringT removeSubstr(const StringT& str, const StringT& sub, int option = 0)
{
    using CharT = typename StringT::value_type;
    using SizeT = typename StringT::size_type;

    if (sub.empty() || sub.empty()) {
        return str;
    }

    if (option != 0) {
        auto pos = option < 0 ? str.find(sub) : str.rfind(sub);
        if (pos != StringT::npos) {
            StringT result(str);
            result.erase(pos, sub.size());
            return result;
        }
    } else { // option == 0
        auto pos = str.find(sub);
        if (pos != StringT::npos) {
            std::unique_ptr<CharT[]> buff(new CharT[str.size() + 1]);
            SizeT len = 0;
            SizeT pos1 = 0;
            while (pos != StringT::npos) {
                std::copy_n(str.begin() + pos1, pos - pos1, buff.get() + len);
                len += pos - pos1;
                pos1 = pos + sub.size();
                pos = str.find(sub, pos1);
            }
            std::copy_n(str.begin() + pos1, str.size() - pos1, buff.get() + len);
            len += str.size() - pos1;
            return StringT(buff.get(), len);
        }
    }
    return str;
}

/*!
    Replaces all part strings (\a before) in this string (\a str) with \a after.
*/
template<class StringT>
void replaceString(StringT& str, const StringT& before, const StringT& after)
{
    if (!str.empty() && !before.empty()) {
        auto pos = str.find(before);
        while (pos != StringT::npos) {
            str.replace(pos, before.size(), after);
            pos = str.find(before, pos + after.size());
        }
    } 
}

/*!
    Splits this string (\a str) with delimiter (\a delim).

    \note
        - If there is no delimiter in this string, returns an empty string-vector.
        - If a delimiter exists at the end of this string, the end element of the string-vector will be an empty string.

    \sa joinString()
*/
template<class StringT>
StringVector<StringT> splitString(const StringT& str, typename StringT::value_type delim)
{
    using SizeT = typename StringT::size_type;
    StringVector<StringT> result;
    if (!str.empty()) {
        SizeT beg = 0;
        SizeT pos = str.find(delim);
        while (pos != StringT::npos) {
            result.emplace_back(str.substr(beg, pos - beg));
            beg = ++pos;
            pos = str.find(delim, beg);
        }
        if (beg > 0) {
            result.emplace_back(str.substr(beg));
        }
    }

    return result;
}

/*!
    Splits this string (\a str) with delimiter (\a delim).

    \note
        - If there is no delimiter in this string, returns an empty string-vector.
        - If a delimiter exists at the end of this string, the end element of the string-vector will be an empty string.

    \sa joinString()
*/
template<class StringT>
StringVector<StringT> splitString(const StringT& str, const StringT& delim)
{
    using SizeT = typename StringT::size_type;
    StringVector<StringT> result;

    if (!str.empty() && !delim.empty()) {
        SizeT beg = 0;
        SizeT pos = str.find(delim);
        while (pos != StringT::npos) {
            result.emplace_back(str.substr(beg, pos - beg));
            beg = pos + delim.length();
            pos = str.find(delim, beg);
        }
        if (beg > 0) {
            result.emplace_back(str.substr(beg));
        }
    }

    return result;
}

/*ив
    Joins \a strs with delimiter (\a delim).

    \sa splitString()
*/
template<class StringT, class DelimT>
StringT joinString(const StringVector<StringT>& strs, const DelimT& delim)
{
    StringT result;
    for (auto it = strs.begin(); it != strs.end(); ++it)
    {
        if (it != strs.begin()) {
            result += delim;
        }
        result += *it;
    }
    return result;
}

/*!
    Converts the given string (\a str) to lowercase, if possible.

    \sa toUpper()
*/
template<class StringT>
void toLower(StringT& str, const std::locale& loc)
{
    using CharT = typename StringT::value_type;
    std::transform(str.begin(), str.end(), str.begin(),
        [&](const CharT& c) -> CharT { return std::tolower(c, loc); });
}

/*!
    Converts the given string (\a str) to lowercase, if possible.

    \sa toUpper()
*/
template<class StringT>
StringT toLower(const StringT& str, const std::locale& loc)
{
    using CharT = typename StringT::value_type;
    std::string result(str);
    std::transform(result.begin(), result.end(), result.begin(),
        [&](const CharT& c) -> CharT { return std::tolower(c, loc); });
    return result;
}

/*!
    Converts the given string (\a str) to uppercase, if possible.

    \sa toLower()
*/
template<class StringT>
void toUpper(StringT& str, const std::locale& loc)
{
    using CharT = typename StringT::value_type;
    std::transform(str.begin(), str.end(), str.begin(),
        [&](const CharT& c) -> CharT { return std::toupper(c, loc); });
}

/*!
    Converts the given string (\a str) to uppercase, if possible.

    \sa toLower()
*/
template<class StringT>
StringT toUpper(const StringT& str, const std::locale& loc)
{
    using CharT = typename StringT::value_type;
    std::string result(str);
    std::transform(result.begin(), result.end(), result.begin(),
        [&](const CharT& c) -> CharT { return std::toupper(c, loc); });
    return result;
}

/*!
    Capitalized string (i.e the first letter is uppercased, all other are lowercased).
*/
template<class StringT>
void capitalized(StringT& str, const std::locale& loc)
{
    if (!str.empty()) {
        toLower(str, loc);
        *str.begin() = std::toupper(*str.begin(), loc);
    }
}

/*!
    Return a capitalized string (i.e the first letter is uppercased, all other are lowercased).
*/
template<class StringT>
StringT capitalized(const StringT& str, const std::locale& loc)
{
    std::string result(str);
    capitalized(result, loc);
    return result;
}

/*!
    Return a 'capitalized words' string (i.e the first letter of each word
    is uppercased all other are left untouched though).

    \sa uncapitalizedWords()
*/
template<class StringT>
void capitalizedWords(StringT& str, const std::locale& loc)
{
    using SizeT = typename StringT::size_type;

    for (SizeT i = 0; i < str.size(); ++i) {
        if (std::isalpha(str[i], loc) && (i == 0 || std::isspace(str[i - 1], loc))) {
            str[i] = std::toupper(str[i], loc);
        }
    }
    return result;
}

template<class StringT>
StringT capitalizedWords(const StringT& str, const std::locale& loc)
{
    using SizeT = typename StringT::size_type;
    StringT result(str);

    for (SizeT i = 0; i < str.size(); ++i) {
        if (std::isalpha(str[i], loc) && (i == 0 || std::isspace(str[i - 1], loc))) {
            result[i] = std::toupper(str[i], loc);
        }
    }
    return result;
}

/*!
    Uncapitalized string's words (i.e the first letter of each word
    is lowercased all other are left untouched though).

    \sa capitalizedWords()
*/
template<class StringT>
void uncapitalizedWords(StringT& str, const std::locale& loc)
{
    using SizeT = typename StringT::size_type;

    for (SizeT i = 0; i < str.size(); ++i) {
        if (std::isalpha(str[i], loc) && (i == 0 || std::isspace(str[i - 1], loc))) {
            str[i] = std::tolower(str[i], loc);
        }
    }
    return result;
}

/*!
    Return a 'uncapitalized words' string (i.e the first letter of each word
    is lowercased all other are left untouched though).

    \sa capitalizedWords()
*/
template<class StringT>
StringT uncapitalizedWords(const StringT& str, const std::locale& loc)
{
    using SizeT = typename StringT::size_type;
    StringT result(str);

    for (SizeT i = 0; i < str.size(); ++i) {
        if (std::isalpha(str[i], loc) && (i == 0 || std::isspace(str[i - 1], loc))) {
            result[i] = std::tolower(str[i], loc);
        }
    }
    return result;
}

/*!
    Converts SrcStringT to DstStringT.
*/
template<class DstStringT, class SrcStringT>
DstStringT convertString(const SrcStringT& str, const char* locale)
{
    return DstStringT();
}

/*!
    Converts SrcStringT to DstStringT.
    Template function specialization.
*/
template<>
std::string convertString(const std::wstring& str, const char* locale)
{
    std::setlocale(LC_CTYPE, locale);
    std::mbstate_t state = std::mbstate_t();
    const wchar_t* wstr = str.c_str();

#ifdef _MSC_VER
#   pragma warning(push)
#   pragma warning(disable:4996)
#endif // _MSC_VER
    auto len = std::wcsrtombs(nullptr, &wstr, 0, &state) + 1;
    if (len <= 1) {
        return std::string();
    }
    std::unique_ptr<char[]> buf(new char[len]);
    //char* mbstr = new char[len];
    std::wcsrtombs(buf.get(), &wstr, len, &state);
#ifdef _MSC_VER
#   pragma warning(pop)
#endif // _MSC_VER

    std::string result(buf.get(), len - 1);
    return result;
}

/*!
    Converts SrcStringT to DstStringT.
    Template function specialization.
*/
template<>
std::wstring convertString(const std::string& str, const char* locale)
{
    std::setlocale(LC_CTYPE, locale);
    std::mbstate_t state = std::mbstate_t();
    const char* mbstr = str.c_str();

#ifdef _MSC_VER
#   pragma warning(push)
#   pragma warning(disable:4996)
#endif
    auto len = std::mbsrtowcs(nullptr, &mbstr, 0, &state) + 1;
    if (len <= 1) {
        return std::wstring();
    }
    std::unique_ptr<wchar_t[]> buf(new wchar_t[len]);
    std::mbsrtowcs(buf.get(), &mbstr, len, &state);
#ifdef _MSC_VER
#   pragma warning(pop)
#endif

    std::wstring result(buf.get(), len - 1);
    return result;
}

/*!
    Converts SrcStringT to DstStringT.
*/
template<class DstStringT, class SrcStringT>
DstStringT convertString(const SrcStringT& tr)
{
    return DstStringT();
}

/*!
    Converts SrcStringT to DstStringT.
    Template function specialization.
*/
template<>
std::string convertString(const std::wstring& str)
{
    return convertString<std::string, std::wstring>(str, "");
}

/*!
    Converts SrcStringT to DstStringT.
    Template function specialization.
*/
template<>
std::wstring convertString(const std::string& str)
{
    return convertString<std::wstring, std::string>(str, "");
}

} // namespace str_tem
} // namespace utils4cpp

#endif // UTILS4CPP_STR_STRINGUTILSEXT_HPP