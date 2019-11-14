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

#ifndef UTILS4CPP_STR_USTRINGLIST_HPP
#define UTILS4CPP_STR_USTRINGLIST_HPP

#include <list>
#include <set>
#include <utility>

#include "utils4cpp/str/UStringGlobal.hpp"
#include "utils4cpp/str/UStringUtils.hpp"

namespace utils4cpp {
namespace str {

// forward declaration for UBasicStringView
template<class StringT>
class UBasicStringList;

/*! The std::string list. */
using UStringList = UBasicStringList<std::string>;
/*! The std::wstring list. */
using UWStringList = UBasicStringList<std::wstring>;
/*! The std::u16string list. */
using U16StringList = UBasicStringList<std::u16string>;
/*! The std::u32string list. */
using U32StringList = UBasicStringList<std::u32string>;

#if UTILS4CPP_HAS_U8STRING
/*! The std::u8string list. (if c++20 enabled) */
using U8StringList = UBasicStringList<std::u8string>;
#endif

/*!
    \class UBasicStringList
    \since v0.0

    \brief The string list template class.
*/
template<class StringT>
class UBasicStringList : public std::list<StringT>
{
public:
    /*! Typedef for StringT. Provided for STL compatibility. */
    using value_type = StringT;
    /*! Typedef for std::list<T>::size_type. Provided for STL compatibility. */
    using size_type = typename std::list<StringT>::size_type;
    /*! Typedef for std::list<T>::iterator. Provided for STL compatibility. */
    using iterator = typename std::list<StringT>::iterator;
    /*! Typedef for std::list<T>::const_iterator. Provided for STL compatibility. */
    using const_iterator = typename std::list<StringT>::const_iterator;

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
            return compareString(s1, s2, UCaseInsensitive) < 0;
        }
    };

    /*!
        Returns the iterator at index position in the list.

        \li If (\a index < 0), return begin().
        \li If (\a idnex == size()), return end().
        \li If (\a index > size()), reurn unexpected result.

        \note No bounds checking is performed.
        \sa constItr()
    */
    iterator itr(size_type index)
    {
        auto it = this->begin();
        while (--index >= 0) {
            ++it;
        }
        return it;
    }

    /*!
        Returns the constant iterator at index position in the list, same as constItr().

        \li If (\a index < 0), return cbegin().
        \li If (\a idnex == size()), return cend().
        \li If (\a index > size()), reurn unexpected result.

        \note No bounds checking is performed.
        \sa constItr()
    */
    const_iterator itr(size_type index) const
    {
        auto it = this->cbegin();
        while (--index >= 0) {
            ++it;
        }
        return it;
    }

    /*!
        Returns the constant iterator at index position in the list.

        \li If (\a index < 0), return cbegin().
        \li If (\a idnex == size()), return cend().
        \li If (\a index > size()), reurn unexpected result.

        \note No bounds checking is performed.
        \sa itr()
    */
    const_iterator constItr(size_type index) const
    {
        auto it = this->cbegin();
        while (--index >= 0) {
            ++it;
        }
        return it;
    }

public:
    using std::list<StringT>::list;

    //BasicStringList(const std::list<StringT>& list)
    //    : std::list<StringT>(list)
    //{
    //}

    //BasicStringList(std::list<StringT>&& list)
    //    : std::list<StringT>(std::move(list))
    //{
    //}

    /*!
        Returns the iterator at index position in the list.

        \li If (\a index < 0), return begin().
        \li If (\a index >= size()), return end().

        \sa constIteratorAt()
    */
    iterator iteratorAt(size_type index)
    {
        if (index >= this->size()) {
            return this->end();
        }
        return itr(index);
    }

    /*!
        Returns the constant iterator at index position in the list, Same as constIteratorAt().
        
        \li If (\a index < 0), return begin().
        \li If (\a index >= size()), return end().

        \sa constIteratorAt()
    */
    const_iterator iteratorAt(size_type index) const
    {
        if (index >= this->size()) {
            return this->end();
        }
        return itr(index);
    }

    /*!
        Returns the constant iterator at index position in the list.

        \li If (\a index < 0), return begin().
        \li If (\a index >= size()), return end().

        \sa iteratorAt()
    */
    const_iterator constIteratorAt(size_type index) const
    {
        return iteratorAt(index);
    }

    /*!
        Returns the item at index position in the list, with bounds checking.

        \note If \a index is not within the range of the list, an exception of type std::out_of_range is thrown.
        \exception std::out_of_range if (index < 0 || index >= size())
        \sa operator[]()
    */
    const StringT& at(size_type index) const
    {
        if (index < 0 || index >= this->size()) {
            throw std::out_of_range("out of range");
        }
        return *constItr(index);
    }

    /*!
        Returns the item at index position as a modifiable reference. 
        The \a index must be a valid index position in the list (i.e., 0 <= i < size()).
        otherwise return unexpected result.

        \note No bounds checking is performed.
        \sa at()
    */
    StringT& operator[](size_type index)
    {
        return *itr(index);
    }

    /*!
        Returns the item at index position as a constant reference. 
        The \a index must be a valid index position in the list (i.e., 0 <= i < size()).
        otherwise return unexpected result.

        \note No bounds checking is performed.
        \sa at()
    */
    const StringT& operator[](size_type index) const
    {
        return *constItr(index);
    }

    /*!
        Exchange the item at index position \a i with the item at index position \a j.
        The \a index must be a valid index position in the list (i.e., 0 <= i < size()),
        otherwise the behavior is undefined.

        \note No bounds checking is performed.
        \sa swapItemsAt()
    */
    void swapItems(size_type i, size_type j)
    {
        auto& self = *this;
        std::swap(self[i], self[j]);
    }

    /*!
        Exchange the item at index position \a i with the item at index position \a j, with bounds checking.

        \exception std::out_of_range if (i < 0 || index >= size() || j < 0 || j >= size()).
        \sa swapItems()
    */
    void swapItemsAt(size_type i, size_type j)
    {
        auto& self = *this;
        if (i < 0 || i >= self.size() || j < 0 || j >= self.size()) {
            throw std::out_of_range("out_of_range");
        }
        std::swap(self[i], self[j]);
    }

    /*!
        Returns true if the list contains the string \a str, otherwise returns \a false. 
        The search is case insensitive if \a cs is CaseInsensitive; the search is case sensitive by default.

        \sa indexOf()
    */
    bool contains(const StringT& str, CaseSensitivity cs = UCaseSensitive, 
        const std::locale& loc = std::locale()) const
    {
        for (const auto& string : *this) {
            if (string.size() == str.size() && compareString(string, str, cs, loc) == 0) {
                return true;
            }
        }
        return false;
    }   

    /*!
        Returns the index position of the first occurrence of \a str in the list, 
        searching forward from index position \a from. Returns -1 if no item matched.

        Example:
        \code
              BasicStringList<std::string> list;
              list << "A" << "B" << "C" << "B" << "A";
              list.indexOf("B");          // returns 1
              list.indexOf("B", 1);       // returns 1
              list.indexOf("B", 2);       // returns 3
              list.indexOf("X");          // returns -1
        \endcode

        \note If (\a from < 0), searching at the first.
        \sa lastIndexOf(), contains()
    */
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

    /*!
        Returns the index position of the last occurrence of \a str in the list, 
        searching backward from index position \a from. If \a from is -1 (the default), 
        the search starts at the last item. Returns -1 if no item matched.

        Example:
        \code
            BasicStringList<std::string> list;
            list << "A" << "B" << "C" << "B" << "A";
            list.lastIndexOf("B");      // returns 3
            list.lastIndexOf("B", 3);   // returns 3
            list.lastIndexOf("B", 2);   // returns 1
            list.lastIndexOf("X");      // returns -1
        \endcode

        \sa indexOf(), contains()
    */
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

    /*!
        Joins all the string list's strings into a single character with each element
        separated by the given \a delim.
    */
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

    /*!
        Joins all the string list's strings into a single string with each element 
        separated by the given \a delim (which can be an empty string).
    */
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

    /*!
        Removes duplicate entries. The entries do not have to be sorted. 
        They will retain their original order. Returns the number of removed entries.
    */
    size_type removeDuplicates()
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

    /*!
        Returns a new string list which removes duplicate entries from a \a list. 
        The entries do not have to be sorted. They will retain their original order.
    */
    static UBasicStringList removeDuplicates(const UBasicStringList& list)
    {
        UBasicStringList result(list);
        result.removeDuplicates();
        return result;
    }

    /*!
        Sorts the list of strings in ascending order. If \a cs is CaseSensitive (the default), 
        the string comparison is case sensitive; otherwise the comparison is case insensitive.
        
        \note Sorting is performed using the STL's std::sort() algorithm, 
            which averages linear-logarithmic time, i.e. O(n log n). 
    */
    void sort(CaseSensitivity cs = UCaseSensitive)
    {
        if (cs = UCaseSensitive) {
            return std::sort(this->begin(), this->end());
        } else {
            return std::sort(this->begin(), this->end(), CaseInsensitiveLessThan());
        }
    }

    /*!
        Returns a list of all the strings containing the substring \a str.
        If \a cs is CaseSensitive (the default), the string comparison is case sensitive; 
        otherwise the comparison is case insensitive.

        Example:
        \code
            BasicStringList<std::string> list;
            list << "Beijing, China" << "London, England" << "Chongqing, China";

            BasicStringList<std::string>  result;
            result = list.filter("China"); // result: ["Beijing, China", "Chongqing, China"]
        \endcode

        \sa contains()
    */
    UBasicStringList filter(const StringT& str, CaseSensitivity cs = UCaseSensitive, 
        const std::locale& loc = std::locale()) const
    {
        const auto& self = *this;
        UBasicStringList result;
        for (const auto& s : self) {
            if (containsSubstr(s, str, cs, loc)) {
                result << s;
            }
        }
        return result;
    }

    /*!
        Returns a BasicStringList object with the string contained in \a list. 
        The order of the elements in the BasicStringList is the same as in \a list.

        \sa toStdList(), fromStdVector()
    */
    static UBasicStringList fromStdList(const std::list<StringT>& list)
    {
        UBasicStringList result;
        for (const auto& str : list) {
            result << str;
        }
        return result;
    }

    /*!
        Returns a std::list object with the strings contained in this list.

        \sa fromStdList(), toStdVector()
    */
    std::list<StringT> toStdList() const
    {
        std::list<StringT> result;
        for (const auto& str : *this) {
            result.emplace_back(str);
        }
        return result;
    }

    std::list<StringT> moveToStringList()
    {
        std::list<StringT> result;
        for (auto& str : *this) {
            return.emplace_back(std::move(str));
        }
        return result;
    }

    /*!
        Returns a BasicStringList object with the string contained in std::vector \a vec.
        The order of the elements in the BasicStringList is the same as in vector.

        \sa toStdVector(), fromStdList()
    */
    static UBasicStringList fromStdVector(const std::vector<StringT>& vec)
    {
        UBasicStringList result;
        for (const auto& str : vec) {
            result << str;
        }
        return result;
    }

    /*!
        Returns a std::vector object with the strings contained in this list.

        \sa fromStdVector(), toStdList()
    */
    std::vector<StringT> toStdVector()
    {
        std::vector<StringT> result;
        for (const auto& str : *this) {
            result.emplace_back(str);
        }
        return result;
    }

    /*!
        Appends the given string \a str to this string list and returns a reference to this string list.

        \sa operator<<()
    */
    UBasicStringList& operator+=(const StringT& str)
    {
        this->emplace_back(str);
        return *this;
    }

    /*!
        Appends the strings of the other string list to this list and returns a reference to this list.

        \sa operator+(), operator<<()
    */
    UBasicStringList& operator+=(const UBasicStringList& list)
    {
        for (const auto& str : list) {
            this->emplace_back(str);
        }
        return *this;
    }

    /*!
        Appends the strings of the std::list \a list to this list and returns a reference to this list.

        \sa operator+(), operator<<()
    */
    UBasicStringList& operator+=(const std::list<StringT>& list)
    {
        for (const auto& str : list) {
            this->emplace_back(str);
        }
        return *this;
    }

    /*!
        Returns a string list that is the concatenation of this string list with the other string list.

        \sa operator+=()
    */
    UBasicStringList operator+(const UBasicStringList& list) const
    {
        UBasicStringList result(*this);
        result += list;
        return result;
    }

    /*!
        Appends the given string \a str to this string list and returns a reference to this string list.

        \sa operator+=()
    */
    UBasicStringList& operator<<(const StringT& str)
    {
        *this += str;
        return *this;
    }

    /*!
        Appends the strings of the other string \a list to this list and returns a reference to this list.

        \sa operator+=()
    */
    UBasicStringList& operator<<(const UBasicStringList& list)
    {
        *this += list;
        return *this;
    }

    /*!
        Appends the strings of the std::list \a list to this list and returns a reference to this list.

        \sa operator+=()
    */
    UBasicStringList& operator<<(const std::list<StringT>& list)
    {
        *this += list;
        return *this;
    }
};

} // namespace str
} // namespace utils4cpp

#endif // UTILS4CPP_STR_USTRINGLIST_HPP