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

#ifndef UTILS4CPP_STR_STRINGLIST_HPP
#define UTILS4CPP_STR_STRINGLIST_HPP

#include <list>

#include "utils4cpp/str/StringGlobal.hpp"
#include "utils4cpp/str/StringUtils.hpp"

namespace utils4cpp {
namespace str {

template<class StringT>
class UTILS4CPP_EXPORT BasicStringList : public std::list<StringT>
{
public:
    using value_type = StringT;
    using size_type = typename std::list<StringT>::size_type;

public:
    using std::list<StringT>::list;

    bool contains(const StringT& str, CaseSensitivity cs = CaseSensitive) const
    {

    }
    size_type indexOf(const StringT& str, int from = 0) const;
    size_type lastIndexOf(const StringT& str, int from = -1) const;

    StringT join(StringT::value_type delim);
    StringT join(const StringT& delim);

    // 删除重复项， 利用std::set
    void removeDuplicates();
    static BasicStringList removeDuplicates(const BasicStringList& list);

    BasicStringList& replaceInStrings(const StringT& before, const StringT& other, CaseSensitivity cs = CaseSensitive);
    static BasicStringList replaceInStrings(const BasicStringList& list, const StringT& before, const StringT& other, CaseSensitivity cs = CaseSensitive);

    void sort(CaseSensitivity cs = CaseSensitive);
    BasicStringList filter(const StringT& str, CaseSensitivity cs = CaseSensitive) const;

    // BasicStringList(const BasicStringList& other)
    // {
    // }
    // BasicStringList(BasicStringList&& other);
    // BasicStringList& operator=(const BasicStringList& other);
    // BasicStringList& operator=(BasicStringList&& other);

    void fromStdList(const std::list<StringT>& strs)
    {
        *this << strs;
    }

    std::list<StringT> toStdList() const
    {
        std::list<StringT> result;
        for (const auto& str : *this) {
            result.emplace_back(str);
        }
        return result;
    }

    BasicStringList& operator+=(const StringT& str) const
    {
        emplace_back(str);
        return *this;
    }

    BasicStringList& operator+=(const BasicStringList& other) const
    {
        for (const auto& str :other) {
            emplace_back(str);
        }
        return *this;
    }

    BasicStringList& operator+=(const std::list<StringT>& other) const
    {
        for (const auto& str :other) {
            emplace_back(str);
        }
        return *this;
    }

    BasicStringList operator+(const BasicStringList& other) const
    {
        BasicStringList result(*this);
        result += other;
        return result;
    }

    BasicStringList& operator<<(const StringT& str)
    {
        *this += str;
        return *this;
    }
    BasicStringList& operator<<(const BasicStringList& other)
    {
        *this += other;
        return *this;
    }
    BasicStringList& operator<<(const std::list<StringT>& other)
    {
        *this += other;
        return *this;
    }
};

// template<class StringT>
// BasicStringList<StringT> BasicStringList<StringT>::operator+(const BasicStringList<StringT>& other) const
// {

// }
// BasicStringList& operator<<(const StringT& str);
// BasicStringList& operator<<(const BasicStringList& other);
// BasicStringList& operator<<(const std::list<StringT>& other);

} // namespace str
} // namespace utils4cpp

#endif // UTILS4CPP_STR_STRINGLIST_HPP