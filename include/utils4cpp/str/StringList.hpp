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
#include <set>
#include <utility>

#include "utils4cpp/str/StringGlobal.hpp"
#include "utils4cpp/str/StringUtils.hpp"

namespace utils4cpp {
namespace str {

/*!
    \class BasicStringList
    \since v0.0

    \brief The string list template class.
*/
template<class StringT>
class UTILS4CPP_EXPORT BasicStringList : public std::list<StringT>
{
private:
    /*! This structure is used to compare two strings in case insensitive. 
    */
    struct CaseInsensitiveLessThan {
        using result_type = bool;

        /*! Returns \c true if StringT \a s1 is less than StringT \a s2 in case insensitive.
            Otherwise returns \c false.
        */
        result_type operator()(const StringT& s1, const StringT& s2) const
        {
            return compareString(s1, s2, CaseInsensitive) < 0;
        }
    };

public:
    /*! Typedef for StringT. Provided for STL compatibility. */
    using value_type = StringT;
    /*! Typedef for std::list<T>::size_type. Provided for STL compatibility. */
    using size_type = typename std::list<StringT>::size_type;
    /*! Typedef for std::list<T>::iterator. Provided for STL compatibility. */
    using iterator = typename std::list<StringT>::iterator;
    /*! Typedef for std::list<T>::const_iterator. Provided for STL compatibility. */
    using const_iterator = typename std::list<StringT>::const_iterator;

public:
    using std::list<StringT>::list;

    StringT& at(size_type index)
    {
        if (index < 0 || index >= this->size()) {
            throw std::out_of_range("out of range");
        }
        auto it = this->begin();
        while (index > 0) {
            ++it;
            --index;
        }
        return *it;
    }

    const StringT& at(size_type index) const
    {
        if (index < 0 || index >= this->size()) {
            throw std::out_of_range("out of range");
        }
        auto it = this->begin();
        while (index > 0) {
            ++it;
            --index;
        }
        return *it;
    }

    StringT& operator[](size_type index)
    {
        auto it = this->begin();
        while (index > 0) {
            ++it;
            --index;
        }
        return *it;
    }
    const StringT operator[](size_type index) const
    {
        auto it = this->begin();
        while (index > 0) {
            ++it;
            --index;
        }
        return *it;
    }

    iterator iteratorAt(size_type index)
    {
        if (index < 0 || index >= this->size()) {
            return this->end();
        }
        auto it = this->begin();
        while (--index >= 0) {
            ++it;
        }
        return it;
    }

    void swapItems(size_type i, size_type j)
    {
        auto& self = *this;
        std::swap(self[i], self[j]);
    }

    void swapItemsAt(size_type i, size_type j)
    {
        auto& self = *this;
        if (i < 0 || i >= self.size() || j < 0 || j >= self.size()) {
            throw std::out_of_range("out_of_range");
        }
        std::swap(self[i], self[j]);
    }

    bool contains(const StringT& str, CaseSensitivity cs = CaseSensitive, const std::locale& loc = std::locale()) const
    {
        for (const auto& string : *this) {
            if (string.size() == str.size() && compareString(string, str, cs, loc) == 0) {
                return true;
            }
        }
        return false;
    }   
    size_type indexOf(const StringT& str, size_type from = 0) const
    {
        if (from < 0) {
            from = 0;
        }
        const auto& self = *this;
        for (size_type i = from; i < self.size(); ++i) {
            if (self[i] == str) {
                return i;
            }
        }
        return -1;
    }
    size_type lastIndexOf(const StringT& str, size_type from = -1) const
    {
        const auto& self = *this;
        if (from < 0) {
            from += this->size();
        }

        if (from < self.size()) {
            for (size_type i = from; i >= 0; --i) {
                if (self[i] == str) {
                    return i;
                }
            }
        }        
        return -1;
    }

    StringT join(typename StringT::value_type delim) const
    {
        StringT result;
        for (auto it = this->begin(); it != this->end(); ++it) {
            if (it != this->begin()) {
                result += delim;
            }
            result += *it;
        }
        return result;
    }

    StringT join(const StringT& delim) const
    {
        StringT result;
        for (auto it = this->begin(); it != this->end(); ++it) {
            if (it != this->begin()) {
                result += delim;
            }
            result += *it;
        }
        return result;
    }

    int removeDuplicates()
    {
        auto& self = *this;
        size_type n = self.size();
        size_type j = 0;
        std::set<StringT> seen;
        size_type setSize = 0;
        for (size_type i = 0; i < n; ++i) {
            const StringT& str = self[i];
            seen.insert(str);
            if (setSize == seen.size()) {
                continue;
            }
            ++setSize;
            if (j != i) {
                self.swapItems(i, j);
            }
            ++j;
        }
        if (n != j) {
            self.erase(self.iteratorAt(j), self.end());
        }
        return n - j;
    }
    static BasicStringList removeDuplicates(const BasicStringList& list)
    {
        BasicStringList result(list);
        result.removeDuplicates();
        return result;
    }

    void sort(CaseSensitivity cs = CaseSensitive)
    {
        if (cs = CaseSensitive) {
            return std::sort(this->begin(), this->end());
        } else {
            return std::sort(this->begin(), this->end(), CaseInsensitiveLessThan());
        }
    }

    BasicStringList filter(const StringT& str, CaseSensitivity cs = CaseSensitive, const std::locale& loc = std::locale()) const
    {
        const auto& self = *this;
        BasicStringList result;
        for (const auto& s : self) {
            if (containsSubstr(s, str, cs, loc)) {
                result << s;
            }
        }
        return result;
    }

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

    BasicStringList& operator+=(const StringT& str)
    {
        this->emplace_back(str);
        return *this;
    }

    BasicStringList& operator+=(const BasicStringList& other)
    {
        for (const auto& str : other) {
            this->emplace_back(str);
        }
        return *this;
    }

    BasicStringList& operator+=(const std::list<StringT>& other)
    {
        for (const auto& str : other) {
            this->emplace_back(str);
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

/*! The std::string list. */
using StringList = BasicStringList<std::string>;
/*! The std::wstring list. */
using WStringList = BasicStringList<std::wstring>;
/*! The std::u16string list. */
using U16StringList = BasicStringList<std::u16string>;
/*! The std::u32string list. */
using U32StringList = BasicStringList<std::u32string>;

} // namespace str
} // namespace utils4cpp

#endif // UTILS4CPP_STR_STRINGLIST_HPP