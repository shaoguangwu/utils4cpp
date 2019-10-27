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

#ifndef UTILS4CPP_STR_STRINGUTILS_HPP
#define UTILS4CPP_STR_STRINGUTILS_HPP

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
namespace str {

/*! StringVector is a sequence container that encapsulates strings. */
template<class StringT>
using StringVector = std::vector<StringT>;


/*****************************************************************************
    declaration
 *****************************************************************************/

template<class StringT>
void removeCharacterSelf(StringT& str, typename StringT::value_type ch, int option = 0);
template<class StringT>
StringT removeCharacter(const StringT& str, typename StringT::value_type ch, int option = 0);

template<class StringT>
void removeSubstrSelf(StringT& str, const StringT& sub, int option = 0);
template<class StringT>
StringT removeSubstr(const StringT& str, const StringT& sub, int option = 0);

template<class StringT>
bool containsCharacter(const StringT& str, typename StringT::value_type ch, CaseSensitivity cs = CaseSensitive, const std::locale& loc = std::locale());
template<class StringT>
bool containsSubstr(const StringT& str, const StringT& sub, CaseSensitivity cs = CaseSensitive, const std::locale& loc = std::locale());

template<class StringT>
void replaceStringSelf(StringT& str, const StringT& before, const StringT& after);
template<class StringT>
StringT replaceString(const StringT& str, const StringT& before, const StringT& after);

template<class StringT>
StringVector<StringT> splitString(const StringT& str, typename StringT::value_type delim);
template<class StringT>
StringVector<StringT> splitString(const StringT& str, const StringT& delim);

template<class StringT, class DelimT>
StringT joinString(const StringVector<StringT>& strs, const DelimT& delim);

template<class StringT>
void toLowerSelf(StringT& str, const std::locale& loc = std::locale());
template<class StringT>
StringT toLower(const StringT& str, const std::locale& loc = std::locale());

template<class StringT>
void toUpperSelf(StringT& str, const std::locale& loc = std::locale());
template<class StringT>
StringT toUpper(const StringT& str, const std::locale& loc = std::locale());

template<class StringT>
bool isLower(const StringT& str, const std::locale& loc = std::locale());
template<class StringT>
bool isUpper(const StringT& str, const std::locale& loc = std::locale());

template<class StringT>
void capitalizedSelf(StringT& str, const std::locale& loc = std::locale());
template<class StringT>
StringT capitalized(const StringT& str, const std::locale& loc = std::locale());

template<class StringT>
void capitalizedWordsSelf(StringT& str, const std::locale& loc = std::locale());
template<class StringT>
StringT capitalizedWords(const StringT& str, const std::locale& loc = std::locale());

template<class StringT>
void uncapitalizedWordsSelf(StringT& str, const std::locale& loc = std::locale());
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

template<class StringT>
bool startsWith(const StringT& str, typename StringT::value_type starts, CaseSensitivity cs = CaseSensitive, const std::locale& loc = std::locale());
template<class StringT>
bool startsWith(const StringT& str, const StringT& starts, CaseSensitivity cs = CaseSensitive, const std::locale& loc = std::locale());

template<class StringT>
bool endsWith(const StringT& str, typename StringT::value_type ends, CaseSensitivity cs = CaseSensitive, const std::locale& loc = std::locale());
template<class StringT>
bool endsWith(const StringT& str, const StringT& ends, CaseSensitivity cs = CaseSensitive, const std::locale& loc = std::locale());

template<class StringT>
bool compareString(const StringT& str1, const StringT& str2, CaseSensitivity cs = CaseSensitive, const std::locale& loc = std::locale());

template<class StringT>
void truncateStringSelf(StringT& str, typename StringT::size_type pos);
template<class StringT>
StringT truncateString(const StringT& str, typename StringT::size_type pos);

template<class StringT>
void reverseStringSelf(StringT& str);
template<class StringT>
StringT reverseString(const StringT& str);

template<typename NumT, class StringT>
NumT toNumber(const StringT& str, std::size_t* pos, int base, bool noexception = true);
template<typename NumT, class StringT>
NumT toNumber(const StringT& str, std::size_t* pos, bool noexception = true);
template<typename NumT, class StringT>
NumT toNumber(const StringT& str, bool noexception = true);

template<typename ... Args>
std::string formatString(const std::string& format, Args ... args);
template<typename ... Args>
std::wstring formatString(const std::wstring& format, Args ... args);


/*****************************************************************************
    implementation
 *****************************************************************************/

/*!
    Remove character \a ch from string \a str.

    The \a option :
    \li negative (  < 0) : Remove the first character equal to \a ch in the given string.
    \li positive (  > 0) : Remove the last character equal to \a ch in the given string.
    \li     zero ( == 0) : Remove all the characters equal to \a ch in the given string.

    \sa removeSubstr(), removeCharacter()
*/
template<class StringT>
void removeCharacterSelf(StringT& str, typename StringT::value_type ch, int option)
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
    }
    else { // option == 0
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

    \sa removeSubstr(), removeCharacterSelf()
*/
template<class StringT>
inline StringT removeCharacter(const StringT& str, typename StringT::value_type ch, int option)
{
    StringT result(str);
    removeCharacterSelf(str, ch, option);
    return result;
}

/*!
    Remove substring \a sub from string \a str.

    The \a option :
    \li negative (  < 0) : Remove the first substring equal to \a sub in the given string.
    \li positive (  > 0) : Remove the last substring equal to \a sub in the given string.
    \li     zero ( == 0) : Remove all the substrings equal to \a sub in the given string.

    \sa removeCharacter(), removeSubstr()
*/
template<class StringT>
void removeSubstrSelf(StringT& str, const StringT& sub, int option)
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
    }
    else { // option == 0
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

    \sa removeCharacter(), removeSubstrSelf()
*/
template<class StringT>
inline StringT removeSubstr(const StringT& str, const StringT& sub, int option)
{
    StringT result(str);
    removeSubstr(result, sub, option);
    return result;
}

/*!
    Returns \c true if \a str contains \a ch, otherwise returns \c false.

    \sa containsSubstr()
*/
template<class StringT>
bool containsCharacter(const StringT& str, typename StringT::value_type ch, CaseSensitivity cs, const std::locale& loc)
{
    if (!str.empty()) {
        if (cs == CaseSensitive) {
            return str.find(ch) != StringT::npos;
        }
        else {
            using CharT = typename StringT::value_type;
            CharT chl = std::tolower(ch, loc);
            CharT chu = std::toupper(ch, loc);
            for (const auto& c : str) {
                if (c == chl || c == chu) {
                    return true;
                }
            }
        }
    }
    return false;
}

/*!
    Returns \c true if \a str contains \a sub, otherwise returns \c false.

    \sa containsCharacter()
*/
template<class StringT>
bool containsSubstr(const StringT& str, const StringT& sub, CaseSensitivity cs, const std::locale& loc)
{
    if (!str.empty() && !sub.empty()) {
        if (cs == CaseSensitive) {
            return str.find(sub) != StringT::npos;
        } else {
            StringT temp = toLower(str, loc);
            return temp.find(toLower(sub, loc)) != StringT::npos;
        }
    }
    return false;
}

/*!
    Replaces all part strings (\a before) in this string (\a str) with \a after.

    \sa replaceString()
*/
template<class StringT>
void replaceStringSelf(StringT& str, const StringT& before, const StringT& after)
{
    if (!str.empty() && !before.empty()) {
        auto pos = str.find(before);
        while (pos != StringT::npos) {
            str.replace(pos, before.size(), after);
            pos = str.find(before, pos + after.size());
        }
    }
}

template<class StringT>
inline StringT replaceString(const StringT& str, const StringT& before, const StringT& after)
{
    StringT result(str);
    replaceStringSelf(result);
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

/*!
    Joins \a strs with delimiter (\a delim).

    \sa splitString()
*/
template<class StringT, class DelimT>
StringT joinString(const StringVector<StringT>& strs, const DelimT& delim)
{
    StringT result;
    for (auto it = strs.begin(); it != strs.end(); ++it) {
        if (it != strs.begin()) {
            result += delim;
        }
        result += *it;
    }
    return result;
}

/*!
    Converts the given string (\a str) to lowercase, if possible.

    \sa toLower(), toUpperSelf(), isLower()
*/
template<class StringT>
inline void toLowerSelf(StringT& str, const std::locale& loc)
{
    using CharT = typename StringT::value_type;
    std::transform(str.begin(), str.end(), str.begin(),
        [&](const CharT& c) -> CharT { return std::tolower(c, loc); });
}

/*!
    Converts the given string (\a str) to lowercase, if possible.

    \sa toLowerSelf(), toUpper(), isLower()
*/
template<class StringT>
inline StringT toLower(const StringT& str, const std::locale& loc)
{
    std::string result(str);
    toLowerSelf(result, loc);
    return result;
}

/*!
    Converts the given string (\a str) to uppercase, if possible.

    \sa toUpper(), toLower(), isUpper()
*/
template<class StringT>
inline void toUpperSelf(StringT& str, const std::locale& loc)
{
    using CharT = typename StringT::value_type;
    std::transform(str.begin(), str.end(), str.begin(),
        [&](const CharT& c) -> CharT { return std::toupper(c, loc); });
}

/*!
    Converts the given string (\a str) to uppercase, if possible.

    \sa toUpperSelf(), toLower(), isUpper()
*/
template<class StringT>
inline StringT toUpper(const StringT& str, const std::locale& loc)
{
    std::string result(str);
    toUpperSelf(result);
    return result;
}

/*!
    Returns \c true if the string only contains lowercase letters,
    otherwise returns \c false.

    \sa isUpper(), toLower()
 */
template<class StringT>
bool isLower(const StringT& str, const std::locale& loc)
{
    if (str.empty()) {
        return false;
    }
    for (const auto& c : str) {
        if (!std::islower(c, loc)) {
            return false;
        }
    }
    return true;
}

/*!
    Returns \c true if the string only contains uppercase letters,
    otherwise returns \c false.

    \sa isLower(), toUpper()
*/
template<class StringT>
bool isUpper(const StringT& str, const std::locale& loc)
{
    if (str.empty()) {
        return false;
    }
    for (const auto& c : str) {
        if (!std::isupper(c, loc)) {
            return false;
        }
    }
    return true;
}

/*!
    Capitalized string (i.e the first letter is uppercased, all other are lowercased).

    \sa capitalized()
*/
template<class StringT>
inline void capitalizedSelf(StringT& str, const std::locale& loc)
{
    if (!str.empty()) {
        toLower(str, loc);
        *str.begin() = std::toupper(*str.begin(), loc);
    }
}

/*!
    Return a capitalized string (i.e the first letter is uppercased, all other are lowercased).

    \sa capitalizedSelf()
*/
template<class StringT>
inline StringT capitalized(const StringT& str, const std::locale& loc)
{
    std::string result(str);
    capitalized(result, loc);
    return result;
}

/*!
    Return a 'capitalized words' string (i.e the first letter of each word
    is uppercased all other are left untouched though).

    \sa capitalizedWords(), uncapitalizedWordsSelf()
*/
template<class StringT>
void capitalizedWordsSelf(StringT& str, const std::locale& loc)
{
    using SizeT = typename StringT::size_type;

    for (SizeT i = 0; i < str.size(); ++i) {
        if (std::isalpha(str[i], loc) && (i == 0 || std::isspace(str[i - 1], loc))) {
            str[i] = std::toupper(str[i], loc);
        }
    }
    return result;
}

/*!
    Return a 'capitalized words' string (i.e the first letter of each word
    is uppercased all other are left untouched though).

    \sa capitalizedWordsSelf(), uncapitalizedWords()
*/
template<class StringT>
inline StringT capitalizedWords(const StringT& str, const std::locale& loc)
{
    StringT result(str);
    capitalizedWords(str, loc);
    return result;
}

/*!
    Uncapitalized string's words (i.e the first letter of each word
    is lowercased all other are left untouched though).

    \sa uncapitalizedWords(), capitalizedWords()
*/
template<class StringT>
void uncapitalizedWordsSelf(StringT& str, const std::locale& loc)
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

    \sa uncapitalizedWordsSelf(), capitalizedWords()
*/
template<class StringT>
inline StringT uncapitalizedWords(const StringT& str, const std::locale& loc)
{
    StringT result(str);
    uncapitalizedWordsSelf(str, loc);
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
    std::string ctype_locale;
    auto prev_ctype_loc = std::setlocale(LC_CTYPE, locale);
    if (prev_ctype_loc) {
        ctype_locale = prev_ctype_loc;
    }

    std::string result;
    std::mbstate_t state = std::mbstate_t();
    const wchar_t* wstr = str.c_str();

#ifdef _MSC_VER
#   pragma warning(push)
#   pragma warning(disable:4996)
#endif // _MSC_VER
    auto len = std::wcsrtombs(nullptr, &wstr, 0, &state) + 1;
    if (len > 1) {
        std::unique_ptr<char[]> buf(new char[len]);
        std::wcsrtombs(buf.get(), &wstr, len, &state);
        result = std::string(buf.get(), len - 1);
    }

#ifdef _MSC_VER
#   pragma warning(pop)
#endif // _MSC_VER

    std::setlocale(LC_CTYPE, ctype_locale.c_str()); // restore locale-ctype
    return result;
}

/*!
    Converts SrcStringT to DstStringT.
    Template function specialization.
*/
template<>
std::wstring convertString(const std::string& str, const char* locale)
{
    std::string ctype_locale;
    auto prev_ctype_loc = std::setlocale(LC_CTYPE, locale);
    if (prev_ctype_loc) {
        ctype_locale = prev_ctype_loc;
    }

    std::wstring result;
    std::mbstate_t state = std::mbstate_t();
    const char* mbstr = str.c_str();

#ifdef _MSC_VER
#   pragma warning(push)
#   pragma warning(disable:4996)
#endif
    auto len = std::mbsrtowcs(nullptr, &mbstr, 0, &state) + 1;
    if (len > 1) {
        std::unique_ptr<wchar_t[]> buf(new wchar_t[len]);
        std::mbsrtowcs(buf.get(), &mbstr, len, &state);
        result = std::wstring(buf.get(), len - 1);
    }
#ifdef _MSC_VER
#   pragma warning(pop)
#endif

    std::setlocale(LC_CTYPE, ctype_locale.c_str()); // restore locale-ctype
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

/*!
    Returns true if \a str starts with \a starts.
    parameter \a cs indicates case sensitivity.

    \sa endsWith()
*/
template<class StringT>
bool startsWith(const StringT& str, typename StringT::value_type starts, CaseSensitivity cs, const std::locale& loc)
{
    if (str.empty()) {
        return false;
    }

    if (CaseSensitivity::CaseInsensitive == cs) {
        return std::tolower(starts, loc) == std::tolower(str.front(), loc);
    }
    else {
        return starts == str.front();
    }
}

/*!
    Returns true if \a str starts with \a starts.
    parameter \a cs indicates case sensitivity.

    \sa endsWith()
*/
template<class StringT>
bool startsWith(const StringT& str, const StringT& starts, CaseSensitivity cs, const std::locale& loc)
{
    using CharT = typename StringT::value_type;

    if (str.empty() || starts.empty() || starts.size() > str.size()) {
        return false;
    }

    if (CaseSensitivity::CaseInsensitive == cs) {
        return std::equal(starts.begin(), starts.end(), str.begin(),
            [&](const CharT& a, const CharT& b) {
                return std::tolower((a, loc) == std::tolower(b, loc);
                    });
    }
    else {
        return std::equal(starts.begin(), starts.end(), str.begin());
    }
}

/*!
    Returns true if \a str ends with \a starts.
    parameter \a cs indicates case sensitivity.

    \sa startsWith()
*/
template<class StringT>
bool endsWith(const StringT& str, typename StringT::value_type ends, CaseSensitivity, const std::locale& loc)
{
    if (str.empty()) {
        return false;
    }

    if (CaseSensitivity::CaseInsensitive == cs) {
        return std::towlower(ends, loc) == std::towlower(str.front(), loc);
    }
    else {
        return ends == str.front();
    }
}

/*!
    Returns true if \a str ends with \a starts.
    parameter \a cs indicates case sensitivity.

    \sa startsWith()
*/
template<class StringT>
bool endsWith(const StringT& str, const StringT& ends, CaseSensitivity cs, const std::locale& loc)
{
    using CharT = typename StringT::value_type;

    if (str.empty() || ends.empty() || ends.size() > str.size()) {
        return false;
    }

    if (CaseSensitivity::CaseInsensitive == cs) {
        return std::equal(ends.rbegin(), ends.rend(), str.rbegin(),
            [&](const CharT& a, const CharT& b) {
                return std::tolower(a, loc) == std::tolower(b, loc);
            });
    }
    else {
        return std::equal(ends.rbegin(), ends.rend(), str.rbegin());
    }
}

/*!
    Compares s1 with s2 and returns an integer less than, equal to, or greater than zero if s1 is less than,
    equal to, or greater than s2.

    If cs is CaseSensitive, the comparison is case sensitive; otherwise the comparison is case insensitive.
*/
template<class StringT>
inline bool compareString(const StringT& str1, const StringT& str2, CaseSensitivity cs, const std::locale& loc)
{
    if (cs == CaseInsensitive) {
        return toLower(str1, loc).compare(toLower(str2, loc));
    }
    else {
        return str1.compare(str2);
    }
}

/*!
    Truncates the string at the given \a pos index.
    If the specified position index is beyond the end of the string, nothing happens.

    \sa truncateString()
*/
template<class StringT>
inline void truncateStringSelf(StringT& str, typename StringT::size_type pos)
{
    str = str.substr(0, pos);
}

/*!
    Returns a substring that contains the [0, pos) characters of the string.
    If the specified position index is beyond the end of the string, returns [o, str.size()).

    \sa truncateStringSelf()
*/
template<class StringT>
inline StringT truncateString(const StringT& str, typename StringT::size_type pos)
{
    return str.substr(0, pos);
}

/*!
    Reverse string \a str.

    \sa reverseString()
*/
template<class StringT>
inline void reverseStringSelf(StringT& str)
{
    using SizeT = typename StringT::size_type;
    for (SizeT i = 0; i < str.size() / 2; ++i) {
        swapChar(str[i], str[str.size() - i - 1]);
    }
}

/*!
    Reverse string \a str.

    \sa reverseStringSelf()
*/
template<class StringT>
inline StringT reverseString(const StringT& str)
{
    return { str.rbegin(), str.rend() };
}

/*!
    Interprets an integer value in the string \a str.

    \param str the string to convert.
    \param pos address of an integer to store the number of characters processed.
    \param base the number base.
    \param noexception indicates whether an exception is thrown.

    \exception  std::invalid_argument if no conversion could be performed and noexception is set to false.
    \exception  std::out_of_range if the converted value would fall out of the range of the result type.

    \note If param \a noexception set to true and exceptions are performed, return zero.
*/
template<typename NumT, class StringT>
NumT toNumber(const StringT& str, std::size_t* pos, int base, bool noexception)
{
    if (noexception) {
        try {
            return inc::stringToNumber<NumT>(str, pos, base);
        }
        catch (const std::exception& e) {
            return NumT(0);
        }
    }
    else {
        return inc::stringToNumber<NumT>(str, pos, base);
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
template<typename NumT, class StringT>
NumT toNumber(const StringT& str, std::size_t* pos, bool noexception)
{
    if (noexception) {
        try {
            return inc::stringToNumber<NumT>(str, pos);
        }
        catch (const std::exception& e) {
            return NumT(0);
        }
    }
    else {
        return inc::stringToNumber<NumT>(str, pos);
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
template<typename NumT, class StringT>
NumT toNumber(const StringT& str, bool noexception)
{
    if (noexception) {
        try {
            return inc::stringToNumber<NumT>(str);
        }
        catch (const std::exception& e) {
            return NumT(0);
        }
    }
    else {
        return inc::stringToNumber<NumT>(str);
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
    if (size > 1) {
        std::unique_ptr<char[]> buf(new char[size]);
        std::snprintf(buf.get(), size, format.c_str(), args ...);
        return { buf.get(), buf.get() + size - 1 }; // We don't want the '\0' inside
    }
    return std::string();

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
    if (size > 1) {
        std::unique_ptr<wchar_t[]> buf(new wchar_t[size]);
        std::swprintf(buf.get(), size, format.c_str(), args ...);
        return { buf.get(), buf.get() + size - 1 }; // We don't want the '\0' inside
    }
    return std::wstring();
}

} // namespace str
} // namespace utils4cpp

#endif // UTILS4CPP_STR_STRINGUTILS_HPP