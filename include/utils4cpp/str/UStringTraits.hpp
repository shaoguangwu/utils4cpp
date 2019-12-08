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

#include <algorithm>
#include <charconv>
#include <list>
#include <vector>

#include "utils4cpp/str/UStringGlobal.hpp"
#include "utils4cpp/str/UStringToNumber.hpp"

namespace utils4cpp::str {

template<class StringT>
class UStringTraits
{
public:
    static_assert(is_std_basic_string_v<StringT>,
        "template parameter StringT must be std_basic_string");

    using value_type = typename StringT::value_type;
    using char_type = typename StringT::value_type;
    using char_traits_type = typename StringT::traits_type;
    using string_type = StringT;
    using string_view_type = std::basic_string_view<char_type>;
    using reference = StringT &;
    using const_reference = const StringT&;
    using size_type = typename StringT::size_type;
    using iterator = typename StringT::iterator;
    using const_iterator = typename StringT::const_iterator;
    using reverse_iterator = typename StringT::reverse_iterator;
    using const_reverse_iterator = typename StringT::const_reverse_iterator;
    static constexpr size_type nth_begin = 0;

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

    //
    // compare
    //

    template<UCaseSensitivity CS = UCaseSensitive>
    static int compare(const StringT& str1, string_view_type str2,
        const std::locale& loc = std::locale())
    {
        size_type lhs_sz = str1.size();
        size_type rhs_sz = str2.size();
        if constexpr (CS == UCaseSensitive) {
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

    template<UCaseSensitivity CS = UCaseSensitive>
    static int compare(const StringT& str1, const char_type* str2,
        const std::locale& loc = std::locale())
    {
        return compare<CS>(str1, string_view_type(str2), loc);
    }

    template<UCaseSensitivity CS = UCaseSensitive>
    static int compare(const StringT& str1, const StringT& str2,
        const std::locale& loc = std::locale())
    {
        if constexpr (CS == UCaseSensitive) {
            return str1.compare(str2);
        }
        else {
            size_type lhs_sz = str1.size();
            size_type rhs_sz = str2.size();
            if (int result = _strucmp(str1.data(), str2.data(), std::min(lhs_sz, rhs_sz), loc)) {
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

    //
    // append
    //

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

    static StringT& append(StringT& str, string_view_type s)
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

    //
    // starts with
    //

    template<UCaseSensitivity CS = UCaseSensitive>
    static bool startsWith(const StringT& str, char_type ch, 
        const std::locale& loc = std::locale()) noexcept
    {
        if (str.empty()) {
            return false;
        }
        return _equal<CS>(ch, str.front(), loc);
    }

    template<UCaseSensitivity CS = UCaseSensitive>
    static bool startsWith(const StringT& str, string_view_type starts,
        const std::locale& loc = std::locale())
    {
        if (str.empty() || starts.empty() || starts.size() > str.size()) {
            return false;
        }
        return std::equal(starts.begin(), starts.end(), str.begin(),
            [&](const char_type& a, const char_type& b) {
                return _equal<CS>(a, b, loc);
            });
    }

    template<UCaseSensitivity CS = UCaseSensitive>
    static bool startsWith(const StringT& str, const char_type* starts,
        const std::locale& loc = std::locale())
    {
        return startsWith<CS>(str, string_view_type(starts), loc);
    }

    template<UCaseSensitivity CS = UCaseSensitive>
    static bool startsWith(const StringT& str, const StringT& starts,
        const std::locale& loc = std::locale())
    {
        return startsWith<CS>(str, string_view_type(starts.c_str(), starts.size()), loc);
    }

    //
    // ends with
    //

    template<UCaseSensitivity CS = UCaseSensitive>
    static bool endsWith(const StringT& str, char_type ch,
        const std::locale& loc = std::locale())
    {
        if (str.empty()) {
            return false;
        }
        return _equal<CS>(ch, str.back(), loc);
    }

    template<UCaseSensitivity CS = UCaseSensitive>
    static bool endsWith(const StringT& str, string_view_type ends,
        const std::locale& loc = std::locale())
    {
        if (str.empty() || ends.empty() || ends.size() > str.size()) {
            return false;
        }

        return std::equal(ends.rbegin(), ends.rend(), str.rbegin(),
            [&](const char_type& a, const char_type& b) {
                return _equal<CS>(a, b, loc);
            });
    }
    
    template<UCaseSensitivity CS = UCaseSensitive>
    static bool endsWith(const StringT& str, const char_type* ends,
        const std::locale& loc = std::locale())
    {
        return endsWith<CS>(str, string_view_type(ends), loc);
    }

    template<UCaseSensitivity CS = UCaseSensitive>
    static bool endsWith(const StringT& str, const StringT& ends,
        const std::locale& loc = std::locale())
    {
        return endsWith<CS>(str, string_view_type(ends.c_str(), ends.size()), loc);
    }

    //
    // contains
    //

    // todo
    static bool contains(const StringT& str, char_type ch,
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale())
    {

    }

    // todo
    static bool contains(const StringT& str, const StringT& substr,
        UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale())
    {

    }

    //
    // reverse
    //

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

    //
    // remove
    //

    template<UCaseSensitivity CS = UCaseSensitive>
    static StringT& removeFirst(StringT& str, char_type ch,
        const std::locale& loc = std::locale())
    {
        if (!str.empty()) {
            ch = _toLowerIf<CS == UCaseInsensitive>(ch, loc);
            auto it = str.cbegin();
            while (it != str.cend()) {
                if (_equalTransOneIf<CS == UCaseInsensitive>(ch, *it, loc)) {
                    str.erase(it);
                    return str;
                }
                ++it;
            }
        }
        return str;
    }

    template<UCaseSensitivity CS = UCaseSensitive>
    static StringT& removeFirst(StringT& str, const StringT& sub,
        const std::locale& loc = std::locale())
    {
        if (!str.empty() && !sub.empty() && sub.size() <= str.size()) {
            if constexpr (CS == UCaseSensitive) {
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

    template<UCaseSensitivity CS = UCaseSensitive>
    static StringT removeLast(StringT& str, char_type ch, 
        const std::locale& loc = std::locale)
    {
        if (!str.empty()) {
            ch = _toLowerIf<CS == UCaseInsensitive>(ch, loc);
            size_type pos = str.size() - 1;
            auto it = str.crbegin();
            while (it != str.crend()) {
                if (_equalTransOneIf<CS == UCaseInsensitive>(ch, *it, loc)) {
                    str.erase(pos, 1);
                    return str;
                }
                --pos;
                ++it;
            }
        }
        return str;
    }

    template<UCaseSensitivity CS = UCaseSensitive>
    static StringT& removeLast(StringT& str, const StringT& sub,
        const std::locale& loc = std::locale())
    {
        if (!str.empty() && !sub.empty() && sub.size() <= str.size()) {
            if constexpr (CS == UCaseSensitive) {
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

    template<UCaseSensitivity CS = UCaseSensitive>
    static StringT& removeAll(StringT& str, char_type ch,
        const std::locale& loc = std::locale())
    {
        if (!str.empty()) {
            ch = _toLowerIf<CS == UCaseInsensitive>(ch, loc);
            auto it = str.cbegin();
            while (it != str.cend()) {
                if (_equalTransOneIf<CS == UCaseInsensitive>(ch, *it, loc)) {
                    str.erase(it);
                    continue;
                }
                ++it;
            }
        }
        return str;
    }

    template<UCaseSensitivity CS = UCaseSensitive>
    static StringT& removeAll(StringT& str, const StringT& sub,
        const std::locale& loc = std::locale())
    {
        if (!str.empty() && !sub.empty() && sub.size() <= str.size()) {
            if constexpr (CS == UCaseSensitive) {
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

    template<UCaseSensitivity CS = UCaseSensitive>
    static StringT& removeNth(StringT& str, char_type ch, size_type nth,
        const std::locale& loc = std::locale())
    {
        if (str.empty()) {
            return str;
        }
        size_type pos = (CS == UCaseSensitive ? _nthFinder(str, ch, nth) : _nthFinderIns(str, ch, loc));
        if (pos != StringT::npos) {
            str.erase(pos, 1);
        }
        return str;
    }

    template<UCaseSensitivity CS = UCaseSensitive>
    static StringT& removeNth(StringT& str, const StringT& substr, size_type nth,
        const std::locale& loc = std::locale())
    {
        if (str.empty() || substr.empty() || substr.size() > str.size()) {
            return str;
        }
        size_type pos = (CS == UCaseSensitive ? _nthFinder(str, substr, nth) : _nthFinderIns(str, substr, loc));
        if (pos != StringT::npos) {
            str.erase(pos, substr.size());
        }
        return str;
    }

    //
    // toNumber
    //

    template<class NumberT, bool Except = true>
    static NumberT toNumber(const StringT& str, std::size_t* pos = 0, int base = 10) noexcept(!Except)
    {
        return stringToNumber<StringT, NumberT, Except>(str, pos, base);
    }

    template<typename NumberT, bool Except = true>
    NumberT toNumber(const StringT& str, std::size_t* pos = 0) noexcept(!Except)
    {
        return stringToNumber<StringT, NumberT, Except>(str, pos);
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

    //
    // split
    //

    template<UCaseSensitivity CS = UCaseSensitive>
    static std::list<StringT> split(const StringT& str, char_type sep, 
        bool keepEmptyParts = true, const std::locale& loc = std::locale())
    {
        std::list<StringT> string_list;
        if (str.empty()) {
            return string_list;
        }

        sep = _toLowerIf<CS == UCaseInsensitive>(sep, loc);
        auto begin = str.begin();
        size_type size = str.size();
        size_type pos_prev = 0;
        size_type pos_curr = 0;

        for ( ; pos_curr < size; ++pos_curr) {
            if (_equalTransOneIf<CS == UCaseInsensitive>(sep, str[pos_curr], loc)) {
                if (keepEmptyParts || (!keepEmptyParts && pos_prev != pos_curr)) {
                    string_list.emplace_back(begin + pos_prev, begin + pos_curr);   
                }  
                pos_prev = pos_curr + 1;
            }
        }

        if (pos_prev == 0) {
            string_list.emplace_back(str);
            return string_list;
        }

        if (keepEmptyParts || (!keepEmptyParts && pos_prev != pos_curr)) {
            string_list.emplace_back(begin + pos_prev, str.end());
        }
        return string_list;
    }

    template<UCaseSensitivity CS = UCaseSensitive>
    static std::list<StringT> split(const StringT& str, string_view_type sep,
        bool keepEmptyParts = true, const std::locale& loc = std::locale())
    {
        std::list<StringT> string_list;
        if (str.empty() || sep.empty() || sep.size() > str.size()) {
            return string_list;
        }

        if constexpr (CS == UCaseSensitive) {
            _split(string_list, str, sep, keepEmptyParts);
        }
        else {
            StringT sep_str(sep);  
            _split(string_list, toLower(str, loc), lower(sep_str, loc), keepEmptyParts);
        }
        return string_list;
    }

    template<UCaseSensitivity CS = UCaseSensitive>
    inline static std::list<StringT> split(const StringT& str, const char_type* sep,
        bool keepEmptyParts = true, const std::locale& loc = std::locale())
    {
        if (!sep) {
            return std::list<StringT>();
        }
        return split<CS>(str, string_view_type(sep), keepEmptyParts, loc);
    }

    template<UCaseSensitivity CS = UCaseSensitive>
    inline static std::list<StringT> split(const StringT& str, const StringT& sep,
        bool keepEmptyParts = true, const std::locale& loc = std::locale())
    {
        return split<CS>(str, (string_view_type)sep, keepEmptyParts, loc);
    }

    inline static std::list<StringT> split(const StringT& str, const std::vector<char_type>& seps,
        bool keepEmptyParts = true)
    {
        std::list<StringT> string_list;
        _split(string_list, str, seps, keepEmptyParts);
        return string_list;
    }

    //
    // replace
    //

    template<UCaseSensitivity CS = UCaseSensitive>
    static StringT& replaceFirst(StringT& str, char_type before, char_type after,
        UTILS4CPP_ATTR_MAYBE_UNUSED const std::locale& loc = std::locale())
    {
        auto pos = ( CS == UCaseSensitive ? _nthFinder(str, before, nth_begin) :
            _nthFinderIns(str, before, nth_begin, loc));
        if (pos != StringT::npos) {
            str[pos] = after;
        }
        return str;
    }

    template<UCaseSensitivity CS = UCaseSensitive>
    static StringT& replaceFirst(StringT& str, const StringT& before, const StringT& after,
        UTILS4CPP_ATTR_MAYBE_UNUSED const std::locale& loc = std::locale())
    {
        auto pos = (CS == UCaseSensitive ? _nthFinder(str, before, nth_begin) :
            _nthFinderIns(str, before, nth_begin, loc));
        if (pos != StringT::npos) {
            str.replace(pos, before.size(), after);
        }
        return str;
    }

    template<UCaseSensitivity CS = UCaseSensitive>
    static StringT& replaceLast(StringT& str, char_type before, char_type after,
        UTILS4CPP_ATTR_MAYBE_UNUSED const std::locale& loc = std::locale())
    {
        auto pos = (CS == UCaseSensitive ? _rNthFinder(str, before, nth_begin) :
            _rNthFinderIns(str, before, nth_begin, loc));
        if (pos != StringT::npos) {
            str[pos] = after;
        }
        return str;
    }

    template<UCaseSensitivity CS = UCaseSensitive>
    static StringT& replaceNth(StringT& str, char_type before, char_type after,
        UTILS4CPP_ATTR_MAYBE_UNUSED const std::locale& loc = std::locale())
    {
        auto pos = (CS == UCaseSensitive ? _rNthFinder(str, before, nth_begin) :
            _rNthFinderIns(str, before, nth_begin, loc));
        if (pos != StringT::npos) {
            str[pos] = after;
        }
        return str;
    }

    template<UCaseSensitivity CS = UCaseSensitive>
    static StringT& replaceNth(StringT& str, const StringT& before, const StringT& after,
        size_type nth, UTILS4CPP_ATTR_MAYBE_UNUSED const std::locale& loc = std::locale())
    {
        auto pos = (CS == UCaseSensitive ? _rNthFinder(str, before, nth) :
            _rNthFinderIns(str, before, nth, loc));
        if (pos != StringT::npos) {
            str.replace(pos, before.size(), after);
        }
        return str;
    }

    template<UCaseSensitivity CS = UCaseSensitive>
    static StringT& replaceRnth(StringT& str, char_type before, char_type after,
        size_type nth, UTILS4CPP_ATTR_MAYBE_UNUSED const std::locale& loc = std::locale())
    {
        auto pos = (CS == UCaseSensitive ? _rNthFinder(str, before, nth) :
            _rNthFinderIns(str, before, nth, loc));
        if (pos != StringT::npos) {
            str[pos] = after;
        }
        return str;
    }

    template<UCaseSensitivity CS = UCaseSensitive>
    static StringT& replaceRnth(StringT& str, const StringT& before, const StringT& after,
        size_type nth, UTILS4CPP_ATTR_MAYBE_UNUSED const std::locale& loc = std::locale())
    {
        auto pos = (CS == UCaseSensitive ? _rNthFinder(str, before, nth) :
            _rNthFinderIns(str, before, nth, loc));
        if (pos != StringT::npos) {
            str.replace(pos, before.size(), after);
        }
        return str;
    }

    template<UCaseSensitivity CS = UCaseSensitive>
    static StringT& replace(StringT& str, char_type before, char_type after,
        UTILS4CPP_ATTR_MAYBE_UNUSED const std::locale& loc = std::locale())
    {
        before = _toLowerIf<CS == UCaseInsensitive>(before, loc);
        for (auto& c : str) {
            if (_equalTransOneIf<CS == UCaseInsensitive>(before, c, loc)) {
                c = after;
            }
        }
        return str;
    }

    template<UCaseSensitivity CS = UCaseSensitive>
    static StringT& replace(StringT& str, const StringT& before, const StringT& after,
        UTILS4CPP_ATTR_MAYBE_UNUSED const std::locale& loc = std::locale())
    {
        if (str.empty() || before.empty() || str.size() < before.size()) {
            return str;
        }
        return (CS == UCaseSensitive ? _replace(str, before, after) :
            _replaceIns(str, before, after, loc));
    }

    //
    // repeated
    //

    static StringT& repeat(const StringT& str, size_type times)
    {
        if (str.empty() || times == 0) {
            return StringT();
        }
        string_view_type sv = str;
        str.reserve(str.size() * times);
        while (--times > 0) {
            str += sv;
        }
        return str;
    }

    inline static StringT repeated(const StringT& str, size_type times)
    {
        StringT result;
        return repeat(result, times);
    }

    //
    // trim
    //

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
    inline static bool _isLower(char_type ch, const std::locale& loc)
    {
        return std::use_facet<std::ctype<char_type>>(loc).is(std::ctype_base::lower, ch);
    }

    inline static bool _isUpper(char_type ch, const std::locale& loc)
    {
        return std::use_facet<std::ctype<char_type>>(loc).is(std::ctype_base::upper, ch);
    }

    inline static char_type _toLower(char_type ch, const std::locale& loc)
    {
        return std::use_facet<std::ctype<char_type>>(loc).tolower(ch);
    }

    inline static const char_type* _toLower(char_type* first, char_type* end, 
        const std::locale& loc)
    {
        return std::use_facet<std::ctype<char_type>>(loc).tolower(first, end);
    }

    inline static char_type _toUpper(char_type ch, const std::locale& loc)
    {
        return std::use_facet<std::ctype<char_type>>(loc).toupper(ch);
    }

    inline static const char_type* _toUpper(char_type* first, char_type* end, 
        const std::locale& loc)
    {
        return std::use_facet<std::ctype<char_type>>(loc).toupper(first, end);
    }

    template<bool Condition>
    inline static char_type _toLowerIf(char_type ch, 
        UTILS4CPP_ATTR_MAYBE_UNUSED const std::locale& loc)
    {
        return Condition ? _toLower(ch, loc) : ch;
    }

    template<bool Condition>
    inline static char_type _toUpperIf(char_type ch, 
        UTILS4CPP_ATTR_MAYBE_UNUSED const std::locale& loc)
    {
        return Condition ? _toUpper(ch, loc) : ch;
    }

    inline static bool _equalNoTrans(char_type ch1, char_type ch2)
    {
        return ch1 == ch2;
    }

    inline static bool _equalTransOne(char_type ch1, char_type ch2,
        const std::locale& loc)
    {
        return ch1 == std::tolower(ch2, loc);
    }

    template<bool Condition>
    inline static bool _equalTransOneIf(char_type ch1, char_type ch2, 
        UTILS4CPP_ATTR_MAYBE_UNUSED const std::locale& loc)
    {
        return Condition ? _equalTransOne(ch1, ch2, loc) : _equalNoTrans(ch1, ch2);
    }

    inline static bool _equalTransTwo(char_type ch1, char_type ch2,
        const std::locale& loc)
    {
        return _toLower(ch1, loc) == _toLower(ch2, loc);
    }

    template<bool Condition>
    inline static bool _equalTransTwoIf(char_type ch1, char_type ch2,
        UTILS4CPP_ATTR_MAYBE_UNUSED const std::locale& loc)
    {
        return Condition ? _equalTransTwo(ch1, ch2, loc) : _equalNoTrans(ch1, ch2);
    }

    template<UCaseSensitivity CS>
    inline static bool _equal(char_type ch1, char_type ch2,
        UTILS4CPP_ATTR_MAYBE_UNUSED const std::locale& loc = std::locale())
    {
        return CS == UCaseSensitive ? _equalNoTrans(ch1, ch2) : _equalTransTwo(ch1, ch2, loc);
    }

    inline static bool _equal(char_type ch1, char_type ch2, UCaseSensitivity cs,
        UTILS4CPP_ATTR_MAYBE_UNUSED const std::locale& loc = std::locale())
    {
        return cs == UCaseSensitive ? _equalNoTrans(ch1, ch2) : _equalTransTwo(ch1, ch2, loc);
    }

    static size_type _nthFinder(const StringT& str, char_type ch, size_type nth) noexcept
    {
        size_type count = nth_begin;
        auto pos = str.find(ch);
        while (pos != StringT::npos) {
            if (count++ == nth) {
                return pos;
            }
            pos = str.find(ch, pos + 1);
        }
        return StringT::npos;
    }

    static size_type _nthFinderIns(const StringT& str, char_type ch, size_type nth,
        const std::locale& loc)
    {
        size_type count = nth_begin;
        ch = _toLower(ch, loc);
        for (size_type i = 0; i < str.size(); ++i) {
            if (_equalTransOne(ch, str[i], loc)) {
                if (count++ == nth) {
                    return i;
                }
            }
        }
        return StringT::npos;
    }

    static size_type _rNthFinder(const StringT& str, char_type ch, size_type nth)
    {
        size_type count = nth_begin;
        auto pos = str.rfind(ch);
        while (pos != StringT::npos) {
            if (count++ == nth) {
                return pos;
            }
            pos = str.rfind(ch, pos + 1);
        }
        return StringT::npos;
    }

    static size_type _rNthFinderIns(const StringT& str, char_type ch, size_type nth,
        const std::locale& loc)
    {
        size_type count = nth_begin;
        ch = _toLower(ch, loc);
        auto it = str.rbegin();
        while (it != str.rend()) {
            if (_equalTransOne(ch, *it, loc)) {
                if (count++ == nth) {
                    return static_cast<size_type>(it - str.rbegin() - 1);
                }
            }
            ++it;
        }
        return StringT::npos;
    }

    static size_type _nthFinder(const StringT& str, const StringT& sub, size_type nth) noexcept
    {
        size_type count = nth_begin;
        size_type sub_size = sub.size();
        auto pos = str.find(sub);
        while (pos != StringT::npos) {
            if (count++ == nth) {
                return pos;
            }
            pos = str.find(sub, pos + sub_size);
        }
        return StringT::npos;
    }

    static size_type _nthFinderIns(const StringT& str, const StringT& sub, size_type nth,
        const std::locale& loc)
    {
        StringT lowstr = toLower(str, loc);
        StringT lowsub = toLower(sub, loc);
        return _nthFinder(lowstr, lowsub, nth);
    }

    static size_type _rNthFinder(const StringT& str, const StringT& sub, size_type nth)
    {
        size_type count = nth_begin;
        string_view_type sv = str;
        auto pos = sv.rfind(sub);
        while (pos != string_view_type::npos) {
            if (nth == count++) {
                return pos;
            }
            sv = sv.substr(0, pos);
            pos = sv.rfind(sub);
        }
        return StringT::npos;
    }

    static size_type _rNthFinderIns(const StringT& str, const StringT& sub, size_type nth,
        const std::locale& loc)
    {
        StringT lowstr = toLower(str, loc);
        StringT lowsub = toLower(sub, loc);
        return _rNthFinder(lowstr, lowsub, nth);
    }

    static StringT& _replace(StringT& str, const StringT& before, const StringT& after)
    {
        auto pos = str.find(before);
        while (pos != StringT::npos) {
            str.replace(pos, before.size(), after);
            pos = str.find(before, pos + after.size());
        }
        return str;
    }

    static StringT& _replaceIns(StringT& str, const StringT& before, const StringT& after,
        const std::locale& loc = std::locale())
    {
        auto bsz = before.size();
        auto asz = after.size();
        auto s = toLower(str, loc);
        auto sub = toLower(before, loc);
        auto pos = s.find(before);
        auto offset = pos;
        while (pos != StringT::npos) {
            str.replace(offset, bsz, after);
            pos = str.find(before, pos + bsz);
            offset += pos + asz - bsz;
        }
        return str;
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
        const std::locale& loc)
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

    static void _split(std::list<StringT>& list, const string_view_type& str,
        const string_view_type& sep, bool keepEmptyParts)
    {
        size_type sep_size = sep.size();
        size_type pos_prev = 0;
        size_type pos_curr = str.find(sep);
        while (pos_curr != StringT::npos) {
            if (keepEmptyParts || (!keepEmptyParts && pos_prev != pos_curr)) {
                list.emplace_back(str.substr(pos_prev, pos_curr - pos_prev));
            }
            pos_prev = pos_curr + sep_size;
            pos_curr = str.find(sep, pos_prev);
        }

        if (keepEmptyParts || (!keepEmptyParts && pos_prev != pos_curr)) {
            list.emplace_back(str.substr(pos_prev));
        }
    }

    inline static void _split(std::list<StringT>& list, const StringT& str, 
        const string_view_type& sep, bool keepEmptyParts)
    {
        _split(list, string_view_type(str.data(), str.size()), sep, keepEmptyParts);
    }

    inline static void _split(std::list<StringT>& list, const StringT& str,
        const StringT& sep, bool keepEmptyParts)
    {
        _split(list, string_view_type(str.data(), str.size()), 
            string_view_type(sep.data(), sep.size()), keepEmptyParts);
    }

    static void _split(std::list<StringT>& list, const StringT& str,
        const std::vector<char_type>& seps, bool keepEmptyParts)
    {
        auto begin = str.begin();
        size_type size = str.size();
        size_type pos_prev = 0;
        size_type pos_curr = 0;

        for (; pos_curr < size; ++pos_curr) {
            for (auto& sep : seps) {
                if (_equalNoTrans(sep, str[pos_curr])) {
                    if (keepEmptyParts || (!keepEmptyParts && pos_prev != pos_curr)) {
                        list.emplace_back(begin + pos_prev, begin + pos_curr);
                    }
                    pos_prev = pos_curr + 1;
                    continue;
                }
            }
        }

        //if (pos_prev == 0) {
        //    list.emplace_back(str);
        //    return;
        //}

        if (keepEmptyParts || (!keepEmptyParts && pos_prev != pos_curr)) {
            list.emplace_back(begin + pos_prev, str.end());
        }
    }

};

} // namespace utils4cpp::str

#endif // UTILS4CPP_STR_USTRINGALGORITHM_HPP