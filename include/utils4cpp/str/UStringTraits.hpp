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

#ifndef UTILS4CPP_STR_USTRINGALGORITHM_HPP
#define UTILS4CPP_STR_USTRINGALGORITHM_HPP

//#include <memory>
#include <algorithm>
#include <charconv>
#include <list>

#include "utils4cpp/str/UStringGlobal.hpp"
#include "utils4cpp/str/UStringToNumber.hpp"

namespace utils4cpp::str {

template<class StringT, class = if_std_basic_string<StringT>>
class UStringTraits
{
public:
    using char_type = typename StringT::value_type;
    using char_traits_type = typename StringT::traits_type;
    using string_type = StringT;
    using reference = StringT &;
    using const_reference = const StringT&;
    using size_type = typename StringT::size_type;
    using iterator = typename StringT::iterator;
    using const_iterator = typename StringT::const_iterator;
    using reverse_iterator = typename StringT::reverse_iterator;
    using const_reverse_iterator = typename StringT::const_reverse_iterator;

    // upper and lower

    static StringT& lower(StringT& str, const std::locale& loc = std::locale())
    {
        for (auto& c : str) {
            c = _toLower(c, loc);
        }
        return str;
    }

    static StringT toLower(const StringT& str, const std::locale& loc = std::locale())
    {
        StringT result;
        result.resize(str.size());
        std::transform(str.begin(), str.end(), result.begin(), [&](const auto& ch)->char_type {
            return _toLower(ch, loc);
        });
        return result;
    }

    static StringT& upper(StringT& str, const std::locale& loc = std::locale())
    {
        for (auto& c : str) {
            c = _toUpper(c, loc);
        }
        return str;
    }

    static StringT toUpper(const StringT& str, const std::locale& loc = std::locale())
    {
        StringT result;
        result.resize(str.size());
        std::transform(str.begin(), str.end(), result.begin(), [&](const auto& ch)->char_type {
            return _toUpper(ch, loc);
        });
        return result;
    }

    static bool isLower(const StringT& str, const std::locale& loc = std::locale())
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

    static bool isUpper(const StringT& str, const std::locale& loc = std::locale())
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

    // compare

    static int compare(const StringT& str1, UBasicStringView<char_type> str2,
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale())
    {
        size_type lhs_sz = str1.size();
        size_type rhs_sz = str2.size();
        if (cs == UCaseSensitive) {
            if (int result = char_traits_type::compare(str1.data(), str2.data(), std::min(lhs_sz, rhs_sz))) {
                return result;
            }
        }
        else {
            if (int result = _strucmp(str1.data(), str2.data(), std::min(lhs_sz, rhs_sz))) {
                return result;
            }
        }

        if (lhs_sz < rhs_sz) {
            return -1;
        }
        if (lhs_sz > rhs_sz) {
            return 1;
        }

        return 0;
    }

    static int compare(const StringT& str1, const char_type* str2,
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale())
    {
        return compare(str1, UBasicStringView<char_type>(str2), cs, loc);
    }

    static int compare(const StringT& str1, const StringT& str2,
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale())
    {
        if (cs == UCaseSensitive) {
            return str1.compare(str2);
        }
        else {
            size_type lhs_sz = str1.size();
            size_type rhs_sz = str2.size();
            if (int result = _strucmp(str1.data(), str2.data(), std::min(lhs_sz, rhs_sz))) {
                return result;
            }
            if (lhs_sz < rhs_sz) {
                return -1;
            }
            if (lhs_sz > rhs_sz) {
                return 1;
            }
        }
           
        return 0;
    }

    // append

    static StringT& append(StringT& str, char_type ch)
    {
        str.push_back(ch);
        return str;
    }

    static StringT& append(StringT& str, char_type ch, size_type count)
    {
        str.append(count, ch);
        return str;
    }

    static StringT& append(StringT& str, UBasicStringView<char_type> s)
    {
        str.append(s.data(), s.size());
        return str;
    }

    static StringT& append(StringT& str, const char_type* s)
    {
        str.append(s);
        return str;
    }

    static StringT& append(StringT& str, const char_type* s, size_type count)
    {
        str.append(s, count);
        return str;
    }

    static StringT& append(StringT& str, const StringT& s)
    {
        str.append(s);
        return str;
    }

    // starts and ends

    static bool startsWith(const StringT& str, char_type ch, 
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale()) noexcept
    {
        if (str.empty()) {
            return false;
        }
        return _equalTranstwo(ch, str.front(), cs, loc);
    }

    static bool startsWith(const StringT& str, UBasicStringView<char_type> starts,
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale())
    {
        if (str.empty() || starts.empty() || starts.size() > str.size()) {
            return false;
        }

        if (UCaseSensitivity::UCaseInsensitive == cs) {
            return std::equal(starts.begin(), starts.end(), str.begin(),
                [&](const char_type& a, const char_type& b) {
                    return _toLower(a, loc) == _toLower(b, loc);
                }
            );
        }
        else {
            return std::equal(starts.begin(), starts.end(), str.begin());
        }
    }

    static bool startsWith(const StringT& str, const char_type* starts,
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale())
    {
        return startsWith(str, UBasicStringView<char_type>(starts), cs, loc);
    }

    static bool startsWith(const StringT& str, const StringT& starts,
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale())
    {
        return startsWith(str, UBasicStringView<char_type>(starts.c_str(), starts.size()), cs, loc);
    }

    static bool endsWith(const StringT& str, char_type ch,
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale()) noexcept
    {
        if (str.empty()) {
            return false;
        }
        return _equalTranstwo(ch, str.back(), cs, loc);
    }

    static bool endsWith(const StringT& str, UBasicStringView<char_type> ends,
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale())
    {
        if (str.empty() || ends.empty() || ends.size() > str.size()) {
            return false;
        }

        if (UCaseSensitivity::UCaseInsensitive == cs) {
            return std::equal(ends.rbegin(), ends.rend(), str.rbegin(),
                [&](const char_type& a, const char_type& b) {
                    return _toLower(a, loc) == _toLower(b, loc);
                });
        }
        else {
            return std::equal(ends.rbegin(), ends.rend(), str.rbegin());
        }
    }
    
    static bool endsWith(const StringT& str, const char_type* ends,
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale())
    {
        return endsWith(str, UBasicStringView<char_type>(ends), cs, loc);
    }

    static bool endsWith(const StringT& str, const StringT& ends,
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale())
    {
        return endsWith(str, UBasicStringView<char_type>(ends.c_str(), ends.size()), cs, loc);
    }

    // contains

    // todo
    static bool contains(const StringT& str, char_type ch,
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale())
    {

    }

    // todo
    static bool contains(const StringT& str, const String& substr, 
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale())
    {

    }

    // reverse

    static StringT& reverse(StringT& str) noexcept
    {
        size_type len = str.size();
        for (size_type i = 0; i < len / 2; ++i) {
            std::swap(str[i], str[len - i - 1]);
        }
        return str;
    }

    static StringT reversed(const StringT& str)
    {
        return {str.rbegin(), str.rend()};
    }

    // remove

    static StringT& removeFirst(StringT& str, char_type ch,
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale())
    {
        if (!str.empty()) {
            ch = (cs == UCaseSensitive ? ch : std::tolower(ch, loc));
            auto it = str.cbegin();
            while (it != str.cend()) {
                if (_equalTransone(ch, *it)) {
                    str.erase(it);
                    return str;
                }
            }
        }
        return str;
    }

    static StringT& removeFirst(StringT& str, const StringT& sub,
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale())
    {
        if (!str.empty() && !sub.empty() && sub.size() <= str.size()) {
            if (cs == UCaseSensitive) {
                auto pos = str.find(sub);
                if (pos != StringT::npos) {
                    str.erase(pos, sub.size());
                }
            }
            else {
                auto s = toLower(str, loc);
                auto l = toLower(sub, loc);
                auto pos = s.find(l);
                if (pos != StringT::npos) {
                    str.erase(pos, sub.size());
                }
            }
        }
        return str;
    }

    static StringT removeLast(StringT& str, char_type ch, 
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale)
    {
        if (!str.empty()) {
            ch = (cs == UCaseSensitive ? ch : std::tolower(ch, loc));
            size_type pos = str.size() - 1;
            auto it = str.crbegin();
            while (it != str.crend()) {
                if (_equalTransone(ch, *it)) {
                    str.erase(pos, 1);
                    return str;
                }
                --pos;
                ++it;
            }
        }
        return str;
    }

    static StringT& removeLast(StringT& str, const StringT& sub,
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale())
    {
        if (!str.empty() && !sub.empty() && sub.size() <= str.size()) {
            if (cs == UCaseSensitive) {
                auto pos = str.rfind(sub);
                if (pos != StringT::npos) {
                    str.erase(pos, sub.size());
                }
            }
            else {
                auto s = toLower(str, loc);
                auto l = toLower(sub, loc);
                auto pos = s.rfind(l);
                if (pos != StringT::npos) {
                    str.erase(pos, sub.size());
                }
            }
        }
        return str;
    }

    static StringT& removeAll(StringT& str, char_type ch,
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale())
    {
        if (!str.empty()) {
            ch = (cs == UCaseSensitive ? ch : std::tolower(ch, loc));
            auto it = str.cbegin();
            while (it != str.cend()) {
                if (_equalTransone(ch, *it)) {
                    str.erase(it);
                    continue;
                }
                ++it;
            }
        }
        return str;
    }

    static StringT& removeAll(StringT& str, const StringT& sub,
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale())
    {
        if (!str.empty() && !sub.empty() && sub.size() <= str.size()) {
            if (cs == UCaseSensitive) {
                auto pos = str.find(sub);
                while (pos != StringT::npos) {
                    str.erase(pos, sub.size());
                    pos = str.find(sub);
                }
            }
            else {
                auto s = toLower(str, loc);
                auto l = toLower(sub, loc);
                auto pos = s.find(l);
                while (pos != StringT::npos) {
                    str.erase(pos, sub.size());
                    pos = str.find(sub);
                }
            }
        }
        return str;
    }

    static StringT& removeHead(StringT& str, size_type count)
    {
        str.erase(0, count);
        return str;
    }

    static StringT& removeTail(StringT& str, size_type count)
    {
        if (count > str.size()) {
            str.erase();
        }
        else {
            str.erase(str.size() - count);
        } 
        return str;
    }
    
    static StringT& removeRange(StringT& str, size_type pos1, size_type pos2)
    {
        auto range = std::minmax(pos1, pos2);
        if (range.first < str.size()) {
            str.erase(range.first, range.second - range.first);
        }
        return str;
    }

    static StringT& removeNth(StringT& str, char_type ch, size_type nth,
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale())
    {
        if (nth > 0) {
            if (cs == UCaseSensitive) {
                auto pos = _nthFinder(str, ch, nth);
                if (pos != StringT::npos) {
                    str.erase(pos, 1);
                }
            }
            else {
                StringT s = toUpper(str, loc);
                auto pos = _nthFinder(s, ch, nth);
                if (pos != StringT::npos) {
                    str.erase(pos, 1);
                }
            }
        }
        return str;
    }

    static StringT& removeNth(StringT& str, const StringT& substr, size_type nth,
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale())
    {
        if (nth > 0) {
            if (cs == UCaseSensitive) {
                auto pos = _nthFinder(str, substr, nth);
                if (pos != StringT::npos) {
                    str.erase(pos, substr.size());
                }
            }
            else {
                StringT s = toLower(str, loc);
                StringT sub = toLower(substr, loc);
                auto pos = _nthFinder(s, sub, nth);
                if (pos != StringT::npos) {
                    str.erase(pos, substr.size());
                }
            }
        }
        return str;
    }

    // toNumber

    template<class NumberT, bool Exception = true>
    static NumberT toNumber(const StringT& str, std::size_t* pos = 0, int base = 10)
    {
        return stringToNumber<StringT, NumberT, Exception>(str, pos, base)
    }

    template<typename NumberT, bool Exception = true>
    NumberT toNumber(const StringT& str, std::size_t* pos = 0)
    {
        return stringToNumber<StringT, NumberT, Exception>(str, pos);
    }

    // number

    // TODO
    template<class NumberT, class = if_integral_not_bool<NumberT>>
    static StringT number(NumberT n, int base = 10)
    {
        std::to_chars_result res = std::to_chars();
    }

    // TODO
    template<class NumberT, class = if_floating_point<NumberT>>
    static StringT number(NumberT n, char format = 'g', int precision = 6)
    {
        switch (format)
        {
        case 'f':
            break;
        case 'e':
            break;
        case 'g':
            break;
        default:
            return StringT();
            break;
        }
    }

    // TODO
    template<class NumberT, class = if_bool<NumberT>>
    static StringT number(NumberT n, bool boolalpha = false)
    {
        if (boolalpha) {
            return number(static_cast<int>(n));
        }
        else {
            // TODO
        }
    }

    // split

    // trim

    static StringT& trimLeft(StringT& str, const std::locale& loc = std::locale())
    {
        auto it = str.cbegin();
        while (it != str.cend()) {
            if (!std::isspace(*it, loc)) {
                break;
            }
            ++it;
        }
        str.erase(str.cbegin(), it);
        return str;
    }

    static StringT& trimRight(StringT& str, const std::locale& loc = std::locale())
    {
        size_type sz = str.size();
        auto it = str.crbegin();
        while (it != str.crend()) {
            if (!std::isspace(*it, loc)) {
                break;
            }
            ++it;
        }
        str.erase(sz - (it - str.crbegin()));
        return str;
    }

    static StringT& trim(StringT& str, const std::locale& loc = std::locale())
    {
        return trimLeft(trimRight(str, loc));
    }

    static StringT& trimAll(StringT& str, const std::locale& loc = std::locale())
    {
        size_type offset = 0;
        for (size_type i = 0; i < str.size(); ++i) {
            if (!std::isspace(str[i], loc)) {
                str[offset++] = str[i];
            }
        }
        str.resize(offset);
        return str;
    }

    static StringT trimmedLeft(const StringT& str, const std::locale& loc = std::locale())
    {
        auto it = str.cbegin();
        while (it != str.cend()) {
            if (!std::isspace(*it, loc)) {
                break;
            }
            ++it;
        }
        return { it , str.cend() };
    }

    static StringT trimmedRight(const StringT& str, const std::locale& loc = std::locale())
    {
        size_type sz = str.size();
        auto it = str.crbegin();
        while (it != str.crend()) {
            if (!std::isspace(*it, loc)) {
                break;
            }
            ++it;
        }
        return StringT(str, 0, sz - (it - str.crbegin()));
    }

    static StringT trimmed(const StringT& str, const std::locale& loc = std::locale())
    {
        StringT result = trimmedLeft(str, loc);
        return trimRight(result, loc);
    }

    static StringT trimmedAll(const StringT& str, const std::locale& loc = std::locale())
    {
        StringT result;
        result.resize(str.size());
        size_type sz = 0;
        for (auto ch : str) {
            if (!std::isspace(ch, loc)) {
                result[sz++] = ch;
            }
        }

        result.resize(sz);
        if (sz < str.size() / 2) {
            result.shrink_to_fit();
        }
        return result;
    }

private:
    inline static bool _isLower(char_type ch, const std::locale& loc = std::locale())
    {
        return std::use_facet<std::ctype<char_type>>(loc).is(std::ctype_base::lower, ch);
    }

    inline static bool _isUpper(char_type ch, const std::locale& loc = std::locale())
    {
        return std::use_facet<std::ctype<char_type>>(loc).is(std::ctype_base::upper, ch);
    }

    inline static char_type _toLower(char_type ch, const std::locale& loc = std::locale())
    {
        return std::use_facet<std::ctype<char_type>>(loc).tolower(ch);
    }

    inline static const char_type* _toLower(char_type* first, char_type* end, 
        const std::locale& loc = std::locale())
    {
        return std::use_facet<std::ctype<char_type>>(loc).tolower(first, end);
    }

    inline static char_type _toUpper(char_type ch, const std::locale& loc = std::locale())
    {
        return std::use_facet<std::ctype<char_type>>(loc).toupper(ch);
    }

    inline static const char_type* _toUpper(char_type* first, char_type* end, 
        const std::locale& loc = std::locale())
    {
        return std::use_facet<std::ctype<char_type>>(loc).toupper(first, end);
    }

    inline static bool _equal(const char_type& ch1, const char_type& ch2)
    {
        return ch1 == ch2;
    }

    inline static bool _equalTransone(const char_type& ch1, const char_type& ch2,
        const UCaseSensitivity& cs = UCaseSensitive,
        const std::locale& loc = std::locale())
    {
        return (cs == UCaseSensitive ? ch1 == ch2 : ch1 == std::tolower(ch2, loc));
    }

    inline static bool _equalTranstwo(const char_type& ch1, const char_type& ch2,
        const UCaseSensitivity& cs = UCaseSensitive,
        const std::locale& loc = std::locale())
    {
        return (cs == UCaseSensitive ? ch1 == ch2 : _toLower(ch1, loc) == _toLower(ch2, loc));
    }

    static size_type _nthFinder(const StringT& str, char_type ch, size_type nth) noexcept
    {
        size_type count = 1;
        auto pos = str.find(ch);
        while (pos != StringT::npos) {
            if (count++ == nth) {
                return pos;
            }
            pos = str.find(ch, pos + 1);
        }
        return StringT::npos;
    }

    static size_type _nthFinder(const StringT& str, const StringT& sub, size_type nth) noexcept
    {
        size_type count = 1;
        size_type sub_size = sub.size();
        if (!str.empty() && !sub.empty() && str.size() >= sub_size) {
            auto pos = str.find(sub);
            while (pos != StringT::npos) {
                if (count++ == nth) {
                    return pos;
                }
                pos = str.find(sub, pos + sub_size);
            }
        }
        return StringT::npos;
    }

    static int _strcmp(const char_type* s1, const char_type* s2, size_type len)
    {
        while (len > 0 && *s1 == *s1) {
            s1++;
            s2++;
            len--;
        }
        return static_cast<int>(*s1 - *s1);
    }

    /**
        Perform a case-independent string comparison.
    */
    static int _strucmp(const char_type* s1, const char_type* s2, size_type len, 
        const std::locale& loc = std::locale())
    {
        char_type lc = 0;
        char_type rc = 0;
        while (len > 0 && lc == rc) {
            lc = _toLower(*s1++, loc);
            rc = _toLower(*s2++, loc);
            len--;
        }
        return static_cast<int>(lc - rc);
    }

};

} // namespace utils4cpp::str

#endif // UTILS4CPP_STR_USTRINGALGORITHM_HPP