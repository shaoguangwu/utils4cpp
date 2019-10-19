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

#include "utils4cpp/str/StringUtils.hpp"

#include <clocale>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include <cwctype>
#include <memory>

namespace utils4cpp {
namespace str {

/*!
    Remove character \a ch from string \a str. 
    
    The \a option : 
    \li negative (  < 0) : Remove the first character equal to \a ch in the given string.
    \li positive (  > 0) : Remove the last character equal to \a ch in the given string.
    \li     zero ( == 0) : Remove all the characters equal to \a ch in the given string.

    \sa removeSubstr()
*/
UTILS4CPP_EXPORT std::string removeCharacter(const std::string& str, char ch,  int option)
{
    if (str.empty()) {
        return str;
    }

    if (option != 0) {
        auto pos = option < 0 ? str.find(ch) : str.rfind(ch);
        if (pos != std::string::npos) {
            std::string result(str);
            result.erase(pos, 1);
            return result;
        }
        return str;
    } else { // option == 0
        auto pos = str.find(ch);
        if (pos == std::string::npos)  {
            return str;
        }

        std::unique_ptr<char[]> buff(new char[str.size() + 1]);
        std::size_t len = 0;
        std::string::size_type pos1 = 0;
        while (pos != std::string::npos) {
            std::copy_n(str.begin() + pos1, pos - pos1, buff.get() + len);
            len += pos - pos1;
            pos1 = ++pos;
            pos = str.find(ch, pos1);
        }
        std::copy_n(str.begin() + pos1, str.size() - pos1, buff.get() + len);
        len += str.size() - pos1;
        return std::string(buff.get(), len);
    }
}

/*!
    Remove character \a ch from wide string \a str. 
    
    The \a option : 
    \li negative (  < 0) : Remove the first character equal to \a ch in the given wide string.
    \li positive (  > 0) : Remove the last character equal to \a ch in the given wide string.
    \li     zero ( == 0) : Remove all the characters equal to \a ch in the given wide string.

    \sa removeSubstr()
*/
UTILS4CPP_EXPORT std::wstring removeCharacter(const std::wstring& str, wchar_t ch, int option)
{
    if (str.empty()) {
        return str;
    }

    if (option != 0) {
        auto pos = option < 0 ? str.find(ch) : str.rfind(ch);
        if (pos != std::wstring::npos) {
            std::wstring result(str);
            result.erase(pos, 1);
            return result;
        }
        return str;
    } else { // option == 0
        auto pos = str.find(ch);
        if (pos == std::wstring::npos)  {
            return str;
        }

        std::unique_ptr<wchar_t[]> buff(new wchar_t[str.size() + 1]);
        std::size_t len = 0;
        std::wstring::size_type pos1 = 0;
        while (pos != std::wstring::npos) {
            std::copy_n(str.begin() + pos1, pos - pos1, buff.get() + len);
            len += pos - pos1;
            pos1 = ++pos;
            pos = str.find(ch, pos1);
        }
        std::copy_n(str.begin() + pos1, str.size() - pos1, buff.get() + len);
        len += str.size() - pos1;
        return std::wstring(buff.get(), len);
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
UTILS4CPP_EXPORT std::string removeSubstr(const std::string& str, const std::string& sub, int option)
{
    if (str.empty()) {
        return str;
    }

    if (option != 0) {
        auto pos = option < 0 ? str.find(sub) : str.rfind(sub);
        if (pos != std::string::npos) {
            std::string result(str);
            result.erase(pos, sub.size());
            return result;
        }
        return str;
    } else { // option == 0
        auto pos = str.find(sub);
        if (pos == std::string::npos)  {
            return str;
        }

        std::unique_ptr<char[]> buff(new char[str.size() + 1]);
        std::size_t len = 0;
        std::string::size_type pos1 = 0;
        while (pos != std::string::npos) {
            std::copy_n(str.begin() + pos1, pos - pos1, buff.get() + len);
            len += pos - pos1;
            pos1 = pos + sub.size();
            pos = str.find(sub, pos1);
        }
        std::copy_n(str.begin() + pos1, str.size() - pos1, buff.get() + len);
        len += str.size() - pos1;
        return std::string(buff.get(), len);
    }
}

/*!
    Remove substring \a sub from wide string \a str. 
    
    The \a option : 
    \li negative (  < 0) : Remove the first substring equal to \a sub in the given wide string.
    \li positive (  > 0) : Remove the last substring equal to \a sub in the given wide string.
    \li     zero ( == 0) : Remove all the substrings equal to \a sub in the given wide string.

    \sa removeCharacter()
*/
UTILS4CPP_EXPORT std::wstring removeSubstr(const std::wstring& str, const std::wstring& sub, int option)
{
    if (str.empty()) {
        return str;
    }

    if (option != 0) {
        auto pos = option < 0 ? str.find(sub) : str.rfind(sub);
        if (pos != std::wstring::npos) {
            std::wstring result(str);
            result.erase(pos, sub.size());
            return result;
        }
        return str;
    } else { // option == 0
        auto pos = str.find(sub);
        if (pos == std::wstring::npos)  {
            return str;
        }
        
        std::unique_ptr<wchar_t[]> buff(new wchar_t[str.size() + 1]);
        std::size_t len = 0;
        std::wstring::size_type pos1 = 0;
        while (pos != std::wstring::npos) {
            std::copy_n(str.begin() + pos1, pos - pos1, buff.get() + len);
            len += pos - pos1;
            pos1 = pos + sub.size();
            pos = str.find(sub, pos1);
        }
        std::copy_n(str.begin() + pos1, str.size() - pos1, buff.get() + len);
        len += str.size() - pos1;
        return std::wstring(buff.get(), len);
    }
}

/*!
    Replaces all part strings (\a before) in this string (\a str) with \a after.
*/
UTILS4CPP_EXPORT void replaceString(std::string& str, const std::string& before, const std::string& after)
{
    auto pos = str.find(before);
    while (pos != std::string::npos)
    {
        str.replace(pos, before.size(), after);
        pos = str.find(before, pos + after.size());
    }
}

/*!
    Replaces all part strings (\a before) in this wstring (\a str) with \a after.
*/
UTILS4CPP_EXPORT void replaceString(std::wstring& str, const std::wstring& before, const std::wstring& after)
{
    auto pos = str.find(before);
    while (pos != std::wstring::npos)
    {
        str.replace(pos, before.size(), after);
        pos = str.find(before, pos + after.size());
    }
}

/*!
    Splits this string (\a str) with delimiter (\a delim).

    \note
        - If there is no delimiter in this string, returns an empty string-vector.
        - If a delimiter exists at the end of this string, the end element of the string-vector will be an empty string.

    \sa joinString()
*/
UTILS4CPP_EXPORT StringVector splitString(const std::string& str, char delim)
{
    StringVector result;
    std::size_t beg = 0;
    std::size_t pos = str.find(delim);
    while (pos != std::string::npos)
    {
        result.emplace_back(str.substr(beg, pos - beg));
        beg = ++pos;
        pos = str.find(delim, beg);
    }
    if (beg > 0) {
        result.emplace_back(str.substr(beg));
    }

    return result;
}

/*!
    \fn std::vector<std::string> splitString(const std::string& str, const std::string& delim)
    
    Splits this string (\a str) with delimiter (\a delim).

    \note
        - If there is no delimiter in this string, returns an empty string-vector.
        - If a delimiter exists at the end of this string, the end element of the string-vector will be an empty string.

    \sa joinString()
*/
UTILS4CPP_EXPORT StringVector splitString(const std::string& str, const std::string& delim)
{
    StringVector result;
    std::size_t beg = 0;
    std::size_t pos = str.find(delim);
    while (pos != std::string::npos)
    {
        result.emplace_back(str.substr(beg, pos - beg));
        beg = pos + delim.length();
        pos = str.find(delim, beg);
    }
    if (beg > 0) {
        result.emplace_back(str.substr(beg));
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
UTILS4CPP_EXPORT WStringVector splitString(const std::wstring& str, wchar_t delim)
{
    WStringVector result;
    std::size_t beg = 0;
    std::size_t pos = str.find(delim);
    while (pos != std::wstring::npos)
    {
        result.emplace_back(str.substr(beg, pos - beg));
        beg = ++pos;
        pos = str.find(delim, beg);
    }
    if (beg > 0) {
        result.emplace_back(str.substr(beg));
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
UTILS4CPP_EXPORT WStringVector splitString(const std::wstring& str, const std::wstring& delim)
{
    WStringVector result;
    std::size_t beg = 0;
    std::size_t pos = str.find(delim);
    while (pos != std::wstring::npos)
    {
        result.emplace_back(str.substr(beg, pos - beg));
        beg = pos + delim.length();
        pos = str.find(delim, beg);
    }
    if (beg > 0) {
        result.emplace_back(str.substr(beg));
    }

    return result;
}

/*á
    Joins \a strs with delimiter (\a delim).

    \sa splitString()
*/
UTILS4CPP_EXPORT std::string joinString(const StringVector& strs, char delim)
{
    std::string result;
    for (auto it = strs.cbegin(); it != strs.cend(); ++it)
    {
        if (it != strs.cbegin()) {
            result += delim;
        }
        result += *it;
    }
    return result;
}

/*á
    Joins \a strs with delimiter (\a delim).

    \sa splitString()
*/
UTILS4CPP_EXPORT std::string joinString(const StringVector& strs, const std::string& delim)
{
    std::string result;
    for (auto it = strs.cbegin(); it != strs.cend(); ++it)
    {
        if (it != strs.cbegin()) {
            result += delim;
        }
        result += *it;
    }
    return result;
}

/*á
    Joins \a strs with delimiter (\a delim).

    \sa splitString()
*/
UTILS4CPP_EXPORT std::wstring joinString(const WStringVector& strs, char delim)
{
    std::wstring result;
    for (auto it = strs.cbegin(); it != strs.cend(); ++it)
    {
        if (it != strs.cbegin()) {
            result += delim;
        }
        result += *it;
    }
    return result;
}

/*á
    Joins \a strs with delimiter (\a delim).

    \sa splitString()
*/
UTILS4CPP_EXPORT std::wstring joinString(const WStringVector& strs, const std::wstring& delim)
{
    std::wstring result;
    for (auto it = strs.cbegin(); it != strs.cend(); ++it)
    {
        if (it != strs.cbegin()) {
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
UTILS4CPP_EXPORT std::string toLower(const std::string& str)
{
    std::string result(str);
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) -> char { return std::tolower((int)c); });
    return result;
}

/*!
    Converts the given string (\a str) to uppercase, if possible.

    \sa toLower()
*/
UTILS4CPP_EXPORT std::string toUpper(const std::string& str)
{
    std::string result(str);
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) -> char { return std::toupper((int)c); });
    return result;
}

/*!
    Converts the given wide string (\a str) to lowercase, if possible.

    \sa toUpper()
*/
UTILS4CPP_EXPORT std::wstring toLower(const std::wstring& str)
{
    std::wstring result(str);
    std::transform(result.begin(), result.end(), result.begin(),
        [](wchar_t c) -> wchar_t { return std::towlower((std::wint_t)c); });
    return result;
}

/*!
    Converts the given wide string (\a str) to uppercase, if possible.

    \sa toLower()
*/
UTILS4CPP_EXPORT std::wstring toUpper(const std::wstring& str)
{
    std::wstring result(str);
    std::transform(result.begin(), result.end(), result.begin(),
        [](wchar_t c) -> wchar_t { return std::towupper((std::wint_t)c); });
    return result;
}

/*!
    Return a capitalized string (i.e the first letter is uppercased, all other are lowercased).
*/
UTILS4CPP_EXPORT std::string capitalized(const std::string& str)
{
    std::string result(toLower(str));
    auto it = result.begin();
    if (it != result.end()) {
        *it = (char)std::toupper((int)*it);
    }
    return result;
}

/*!
    Return a capitalized wide string (i.e the first letter is uppercased, all other are lowercased).
*/
UTILS4CPP_EXPORT std::wstring capitalized(const std::wstring& str)
{
    std::wstring result(toLower(str));
    auto it = result.begin();
    if (it != result.end()) {
        *it = (wchar_t)std::towupper((std::wint_t)*it);
    }
    return result;
}

/*!
    Return a 'capitalized words' string (i.e the first letter of each word
    is uppercased all other are left untouched though).

    \sa uncapitalizedWords()
*/
UTILS4CPP_EXPORT std::string capitalizedWords(const std::string& str)
{
    std::string result(str);

    for (std::size_t i = 0; i < str.size(); ++i) {
#if defined(_MSC_VER) && defined(_MT) && defined(_DEBUG)
        // MS has an assert that will fail if s[i] < 0; 
        // setting LC_CTYPE using setlocale() does *not* help.
        if ((int)str[i] >= 0 && std::isalpha((int)str[i]) &&
            (i == 0 || ((int)str[i - 1] >= 0 && std::isspace((int)str[i - 1]))))
#else
        if (std::isalpha((int)str[i]) && (i == 0 || std::isspace((int)str[i - 1])))
#endif
        {
            result[i] = static_cast<std::string::value_type>(std::toupper((int)str[i]));
        }
    }
    return result;
}

/*!
    Return a 'capitalized words' wide string (i.e the first letter of each word
    is uppercased all other are left untouched though).

    \sa uncapitalizedWords()
*/
UTILS4CPP_EXPORT std::wstring capitalizedWords(const std::wstring& str)
{
    std::wstring result(str);

    for (std::size_t i = 0; i < str.size(); ++i) {
        if (std::iswalpha((std::wint_t)str[i]) && (i == 0 || std::iswspace((std::wint_t)str[i - 1])))
            result[i] = static_cast<std::string::value_type>(std::towupper((std::wint_t)str[i]));
    }
    return result;
}

/*!
    Return a 'uncapitalized words' string (i.e the first letter of each word
    is lowercased all other are left untouched though).

    \sa capitalizedWords()
*/
UTILS4CPP_EXPORT std::string uncapitalizedWords(const std::string& str)
{
    std::string result(str);

    for (std::size_t i = 0; i < str.size(); ++i) {
#if defined(_MSC_VER) && defined(_MT) && defined(_DEBUG)
        // MS has an assert that will fail if s[i] < 0; 
        // setting LC_CTYPE using setlocale() does *not* help.
        if ((int)str[i] >= 0 && std::isalpha((int)str[i]) &&
            (i == 0 || ((int)str[i - 1] >= 0 && std::isspace((int)str[i - 1]))))
#else
        if (std::isalpha((int)str[i]) && (i == 0 || std::isspace((int)str[i - 1])))
#endif
        {
            result[i] = static_cast<std::string::value_type>(std::tolower((int)str[i]));
        }
    }
    return result;
}

/*!
    Return a 'uncapitalized words' wide string (i.e the first letter of each word
    is lowercased all other are left untouched though).

    \sa capitalizedWords()
*/
UTILS4CPP_EXPORT std::wstring uncapitalizedWords(const std::wstring& str)
{
    std::wstring result(str);
    for (std::size_t i = 0; i < str.size(); ++i) {
        if (std::iswalpha((std::wint_t)str[i]) && (i == 0 || std::iswspace((std::wint_t)str[i - 1])))
            result[i] = static_cast<std::string::value_type>(std::towlower((std::wint_t)str[i]));
    }
    return result;
}

/*!
    Converts std::string to std::wstring.

    \sa toString()
*/
UTILS4CPP_EXPORT std::wstring toWString(const std::string& str)
{
    std::setlocale(LC_CTYPE, "");
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
    Converts std::wstring to std::string.

    \sa toWstring()
*/
UTILS4CPP_EXPORT std::string toString(const std::wstring& str)
{
    std::setlocale(LC_CTYPE, "");
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
    Returns true if \a str starts with \a starts.
    parameter \a cs indicates case sensitivity.

    \sa endsWith()
*/
UTILS4CPP_EXPORT bool startsWith(const std::string& str, char starts, CaseSensitivity cs)
{
    if (str.empty()) {
        return false;
    }

    if (CaseSensitivity::CaseInsensitive == cs) {
        return std::tolower((int)starts) == std::tolower((int)str.front());
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
UTILS4CPP_EXPORT bool startsWith(const std::string& str, const std::string& starts, CaseSensitivity cs)
{
    if (str.empty() || starts.empty() || starts.size() > str.size()) {
        return false;
    }

    if (CaseSensitivity::CaseInsensitive == cs) {
        return std::equal(starts.begin(), starts.end(), str.begin(),
            [](char a, char b) {
                return std::tolower((int)a) == std::tolower((int)b);
            });
    }
    else {
        return std::equal(starts.begin(), starts.end(), str.begin());
    }
}

/*!
    Returns true if \a str starts with \a starts.
    parameter \a cs indicates case sensitivity.

    \sa endsWith()
*/
UTILS4CPP_EXPORT bool startsWith(const std::wstring& str, wchar_t starts, CaseSensitivity cs)
{
    if (str.empty()) {
        return false;
    }

    if (CaseSensitivity::CaseInsensitive == cs) {
        return std::towlower((std::wint_t)starts) == std::towlower((std::wint_t)str.front());
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
UTILS4CPP_EXPORT bool startsWith(const std::wstring& str, const std::wstring& starts, CaseSensitivity cs)
{
    if (str.empty() || starts.empty() || starts.size() > str.size()) {
        return false;
    }

    if (CaseSensitivity::CaseInsensitive == cs) {
        return std::equal(starts.begin(), starts.end(), str.begin(),
            [](wchar_t a, wchar_t b) {
                return std::towlower((std::wint_t)a) == std::towlower((std::wint_t)b);
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
UTILS4CPP_EXPORT bool endsWith(const std::string& str, char ends, CaseSensitivity cs)
{
    if (str.empty()) {
        return false;
    }

    if (CaseSensitivity::CaseInsensitive == cs) {
        return std::towlower((int)ends) == std::towlower((int)str.front());
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
UTILS4CPP_EXPORT bool endsWith(const std::string& str, const std::string& ends, CaseSensitivity cs)
{
    if (str.empty() || ends.empty() || ends.size() > str.size()) {
        return false;
    }

    if (CaseSensitivity::CaseInsensitive == cs) {
        return std::equal(ends.rbegin(), ends.rend(), str.rbegin(),
            [](char a, char b) {
                return std::tolower((int)a) == std::tolower((int)b);
            });
    }
    else {
        return std::equal(ends.rbegin(), ends.rend(), str.rbegin());
    }
}

/*!
    Returns true if \a str ends with \a starts.
    parameter \a cs indicates case sensitivity.

    \sa startsWith()
*/
UTILS4CPP_EXPORT bool endsWith(const std::wstring& str, wchar_t ends, CaseSensitivity cs)
{
    if (str.empty()) {
        return false;
    }

    if (CaseSensitivity::CaseInsensitive == cs) {
        return std::towlower((std::wint_t)ends) == std::towlower((std::wint_t)str.front());
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
UTILS4CPP_EXPORT bool endsWith(const std::wstring& str, const std::wstring& ends, CaseSensitivity cs)
{
    if (str.empty() || ends.empty() || ends.size() > str.size()) {
        return false;
    }

    if (CaseSensitivity::CaseInsensitive == cs) {
        return std::equal(ends.rbegin(), ends.rend(), str.rbegin(),
            [](wchar_t a, wchar_t b) {
                return std::towlower((std::wint_t)a) == std::towlower((std::wint_t)b);
            });
    }
    else {
        return std::equal(ends.rbegin(), ends.rend(), str.rbegin());
    }
}

} // namespace str
} // namespace utils4cpp