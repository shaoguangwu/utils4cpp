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

#ifndef UTILS4CPP_STR_USTRINGVIEW_HPP
#define UTILS4CPP_STR_USTRINGVIEW_HPP

#include "utils4cpp/str/UStringGlobal.hpp"
#include "utils4cpp/str/UOstreamString.inl"

namespace utils4cpp {
namespace str {

#if UTILS4CPP_HAS_STDSTRINGVIEW
    template<typename charT, class Traits = std::char_traits<charT>>
    using UBasicStringView = std::basic_string_view<charT, Traits>;
#else
    // forward declaration for UBasicStringView
    template<typename charT, class Traits = std::char_traits<charT>>
    class UBasicStringView;
#endif // UTILS4CPP_HAS_STDSTRINGVIEW

/*! string view */
using UStringView = UBasicStringView<char>;
/*! wide string view */
using UWStringView = UBasicStringView<wchar_t>;
/*! u16string view */
using U16StringView = UBasicStringView<char16_t>;
/*! u32string view */
using U32StringView = UBasicStringView<char32_t>;
#if UTILS4CPP_HAS_CHAR8T
/*! u8string view */
using U8StringView = UBasicStringView<char8_t, std::char_traits<char8_t>>;
#endif // UTILS4CPP_HAS_CHAR8T

#if !UTILS4CPP_HAS_STDSTRINGVIEW

/*!
    \class UBasicStringView
    \since v0.0

    \brief The template class UBasicStringView describes an object that can refer to a constant
    contiguous sequence of char-like objects with the first element of the sequence at position zero.

    If has std::string_view, The template class UBasicStringView is same as std::string_view,
    otherwise, we define it.
*/
template<typename charT, class Traits = std::char_traits<charT>>
class UBasicStringView
{
public:
    using traits_type = Traits;
    using value_type = charT;
    using pointer = charT*;
    using const_pointer = const charT*;
    using reference = charT&;
    using const_reference = const charT&;
    using const_iterator = const_pointer;
    using iterator = const_iterator;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using reverse_iterator = const_reverse_iterator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    static constexpr size_type npos = size_type(-1);

    /*!
         Default constructor. Constructs an empty basic_string_view.
         After construction, data() is equal to nullptr, and size() is equal to 0.
    */
    constexpr UBasicStringView() noexcept
        : m_ptr(nullptr), m_len(0) {}

    /*!
        Copy constructor. Constructs a view of the same content as other. 
        After construction, data() is equal to other.data(), and size() is equal to other.size().
    */
    constexpr UBasicStringView(const UBasicStringView& other) noexcept = default;

    /*!
        Constructs a view of the null-terminated character string pointed to by \a str,
        not including the terminating null character.

        The length of the view is determined as if by Traits::length(str).
        The behavior is undefined if [str, str+Traits::length(str)) is not a valid range.
        After construction, data() is equal to \a str, and size() is equal to Traits::length(str).
    */
    constexpr UBasicStringView(const CharT* str)
        : m_ptr(), m_len(traits::length(str)) {}

    /*!
        Constructs a view of the first count characters of the character array starting with the 
        element pointed by \a str. \a str can contain null characters. 
        
        The behavior is undefined if [str, str+len) is not a valid range (even though the constructor
        may not access any of the elements of this range). After construction, data() is equal to \a str, 
        and size() is equal to \a len.
    */
    constexpr UBasicStringView(const CharT* str, size_type len)
        : m_ptr(str), m_len(len) {}

    /*!
        Replaces the view with that of \a view.
    */
    constexpr UBasicStringView& operator=(const UBasicStringView& view) noexcept = default;

    /*!
        Returns an iterator to the first character of the view.

        \sa end(), cbegin(), rbegin()
    */
    constexpr const_iterator begin() const noexcept { return m_ptr; }
    /*!
        Returns an iterator to the first character of the view.

        \sa cend(), begin(), crbegin()
    */
    constexpr const_iterator cbegin() const noexcept { return m_ptr; }
    /*!
        Returns an iterator to the character following the last character of the view. 
        This character acts as a placeholder, attempting to access it results in undefined behavior.

        \sa begin(), cend(), rend()
    */
    constexpr const_iterator end() const noexcept { return m_ptr + m_len; }
    /*!
        Returns an iterator to the character following the last character of the view.
        This character acts as a placeholder, attempting to access it results in undefined behavior.

        \sa cbegin(), end(), crend()
    */
    constexpr const_iterator cend() const noexcept { return m_ptr + m_len; }
    /*!
        Returns a reverse iterator to the first character of the reversed view. 
        It corresponds to the last character of the non-reversed view.

        \sa rend(), begin(), crbegin(), 
    */
    constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    /*!
        Returns a reverse iterator to the first character of the reversed view.
        It corresponds to the last character of the non-reversed view.

        \sa crend(), rbegin(), cbegin(), 
    */
    constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }
    /*!
        Returns a reverse iterator to the character following the last character of the reversed view. 
        It corresponds to the character preceding the first character of the non-reversed view. 
        This character acts as a placeholder, attempting to access it results in undefined behavior.

        \sa rbegin(), crend(), end()
    */
    constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
    /*!
        Returns a reverse iterator to the character following the last character of the reversed view.
        It corresponds to the character preceding the first character of the non-reversed view.
        This character acts as a placeholder, attempting to access it results in undefined behavior.

        \sa crbegin(), rend(), cend(), 
    */
    constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

    /*!
        Returns the number of CharT elements in the view, i.e. std::distance(begin(), end()).

        \sa length(), max_size(), empty()
    */
    constexpr size_type size() const noexcept { return m_len; }
    /*!
        Returns the number of CharT elements in the view, i.e. std::distance(begin(), end()).

        \sa size(), max_size(), empty()
    */
    constexpr size_type length() const noexcept { return m_len; }
    /*!
        The largest possible number of char-like objects that can be referred to by a view.

        \sa size(), length(), empty()
    */
    constexpr size_type max_size() const noexcept { return m_len; }
    /*!
        Checks if the view has no characters, i.e. whether size() == 0.

        \sa size(), length(), max_size()
    */
    constexpr bool empty() const noexcept { return m_len == 0; }

    /*!
        Returns a const reference to the character at specified location \a pos.
        No bounds checking is performed: the behavior is undefined if pos >= size().

        \note Unlike std::basic_string::operator[], UBasicStringView::operator[](size()) 
            has undefined behavior instead of returning CharT().
        \sa at()
    */
    constexpr const_reference operator[](size_type pos) const noexcept { return m_ptr[pos]; }

    /*!
        Returns a reference to the character at specified location \a pos with bounds checking. 

        \exception std::out_of_range will be thrown on invalid access.
        \sa operator[]()
    */
    constexpr const_reference at(size_t pos) const 
    {
        return pos >= m_len ? 
            throw std::out_of_range("utils4cpp::str::UBasicStringView::at") : m_ptr[pos];
    }

    /*!
        Returns reference to the first character in the view. 
        The behavior is undefined if empty() == true.

        \sa back(), empty()
    */
    constexpr const_reference front() const { return m_ptr[0]; }
    /*!
        Returns reference to the last character in the view. 
        The behavior is undefined if empty() == true.

        \sa front(), empty()
    */
    constexpr const_reference back() const { return m_ptr[m_len - 1]; }
    /*!
        Returns a pointer to the underlying character array. 
        The pointer is such that the range [data(); data() + size()) is valid and the values 
        in it correspond to the values of the view.

        \note Unlike std::basic_string::data() and string literals, data() may return a pointer 
                to a buffer that is not null-terminated. Therefore it is typically a mistake to pass data() 
                to a routine that takes just a const CharT* and expects a null-terminated string.
        \sa front(), back()
    */
    constexpr const_pointer data() const noexcept { return m_ptr; }

    /*!
        Moves the start of the view forward by \a n characters.
        The behavior is undefined if n > size().

        \sa remove_suffix()
    */
    constexpr void remove_prefix(size_type n) 
    {
        if (n > m_len) {
            n = m_len;
        }
        m_ptr += n;
        m_len -= n;
    }
    /*!
        Moves the end of the view back by \a n characters.
        The behavior is undefined if n > size().

        \sa remove_prefix()
    */
    constexpr void remove_suffix(size_type n) 
    {
        if (n > m_len) {
            n = m_len;
        }
        m_len -= n;
    }

    /*!
        Exchanges the view with that of \a other.
    */
    constexpr void swap(UBasicStringView& other) noexcept
    {
        std::swap(m_ptr, other.m_ptr);
        std::swap(m_len, other.m_len);
    }

    /*!
        Copies the substring [pos, pos + rcount) to the character array pointed to by \a dest, 
        where rcount is the smaller of \a count and size() - pos.
        Equivalent to:
        \code
            Traits::copy(dest, data() + pos, rcount).
        \endcode

        \param dest     pointer to the destination character string.
        \param count    requested substring length.
        \param pos      position of the first character

        \return Number of characters copied.
        \exception std::out_of_range if \a pos > size().
        \note std::basic_string_view::copy() has no constexpr specifier before c++20.

        \sa substr()
    */
    constexpr size_type copy(charT* dest, size_type count, size_type pos = 0) const 
    {
        if (pos > size()) {
            throw std::out_of_range("utils4cpp::str::UBasicStringView::copy");
        }
        size_type rlen = std::min(count, m_len - pos);
        traits_type::copy(dest, data() + pos, rlen);
        return rlen;
    }

    /*!
        Returns a view of the substring [pos, pos + rcount), 
        where rcount is the smaller of \a count and size() - pos.

        \sa copy(), find()
    */
    constexpr UBasicStringView substr(size_type pos, size_type count = npos) const 
    {
        if (pos > size()) {
            throw std::out_of_range("utils4cpp::str::UBasicStringView::substr");
        }
        return UBasicStringView(data() + pos, std::min(size() - pos, count));
    }

    /*!
        The length rlen of the sequences to compare is the smaller of size() and v.size(). 
        The function compares the two views by calling traits::compare(data(), v.data(), rlen), 
        and returns a value according to the following table:

        <table>
            <tr><th rowspan="1" colspan="2">Condition                                                            <th> Result                 <th> Retuen Value
            <tr><td rowspan="1" colspan="2">Traits::compare(data(), v.data(), rlen)  < 0                         <td> this is less than v    <td> <0
            <tr><td rowspan="3" colspan="1">Traits::compare(data(), v.data(), rlen) == 0 <td> size()  < v.size() <td> this is less than v    <td> <0
            <tr>                                                                         <td> size() == v.size() <td> this is equal to v     <td>  0
            <tr>                                                                         <td> size()  > v.size() <td> this is greater than v <td> >0
            <tr><td rowspan="1" colspan="2">Traits::compare(data(), v.data(), rlen)  > 0                         <td> this is greater than v <td> >0
        </table>

        \return negative value if this view is less than the other character sequence, 
                zero if the both character sequences are equal, positive value if this view is 
                greater than the other character sequence.

        \sa operator==(), operator!=(), operator<(), operator>(), operator<=(), operator>=()
    */
    constexpr int compare(UBasicStringView v) const noexcept
    {
        const int cmp = traits::compare(m_ptr, v.m_ptr, std::min(m_len, v.m_len));
        return cmp != 0 ? cmp : (m_len == v.m_len ? 0 : m_len < v.m_len ? -1 : 1);
    }

    /*!
        Equivalent to:
        \code
            substr(pos1, count1).compare(v);
        \endcode

        \return negative value if this view is less than the other character sequence,
                zero if the both character sequences are equal, positive value if this view is 
                greater than the other character sequence.

        \sa substr(), operator==(), operator!=(), operator<(), operator>(), operator<=(), operator>=()
    */
    constexpr int compare(size_type pos1, size_type count1, UBasicStringView v) const noexcept
    {
        return substr(pos1, count1).compare(v);
    }

    /*!
        Equivalent to:
        \code
            substr(pos1, count1).compare(v.substr(pos2, count2));
        \endcode

        \return negative value if this view is less than the other character sequence,
                zero if the both character sequences are equal, positive value if this view is 
                greater than the other character sequence.

        \sa substr(), operator==(), operator!=(), operator<(), operator>(), operator<=(), operator>=()
    */
    constexpr int compare(size_type pos1, size_type count1,
        UBasicStringView v, size_type pos2, size_type count2) const
    {
        return substr(pos1, count1).compare(v.substr(pos2, count2));
    }

    /*!
        Equivalent to:
        \code
            compare(UBasicStringView(s)).
        \endcode

        \return negative value if this view is less than the other character sequence,
                zero if the both character sequences are equal, positive value if this view is 
                greater than the other character sequence.

        \sa operator==(), operator!=(), operator<(), operator>(), operator<=(), operator>=()
    */
    constexpr int compare(const charT* s) const 
    {
        return compare(UBasicStringView(s));
    }

    /*!
        Equivalent to:
        \code
            substr(pos1, count1).compare(UBasicStringView(s));
        \endcode

        \return negative value if this view is less than the other character sequence,
                zero if the both character sequences are equal, positive value if this view is 
                greater than the other character sequence.

        \sa substr(), operator==(), operator!=(), operator<(), operator>(), operator<=(), operator>=()
    */
    constexpr int compare(size_type pos1, size_type count1, const charT* s) const 
    {
        return substr(pos1, count1).compare(UBasicStringView(s));
    }

    /*!
        Equivalent to:
        \code
            substr(pos1, count1).compare(UBasicStringView(s, count2));
        \endcode

        \return negative value if this view is less than the other character sequence,
                zero if the both character sequences are equal, positive value if this view is 
                greater than the other character sequence.

        \sa substr(), operator==(), operator!=(), operator<(), operator>(), operator<=(), operator>=()
    */
    constexpr int compare(size_type pos1, size_type count1,
        const charT* s, size_type count2) const 
    {
        return substr(pos1, count1).compare(UBasicStringView(s, count2));
    }

    /*!
        Checks if the string view begins with the given prefix.
        Effectively returns:
        \code
            size() >= x.size() && compare(0, x.size(), x) == 0;
        \endcode

        \note std::basic_string_view provides this function since from c++20, use it carefully.
        \sa ends_with(), compare()
    */
    constexpr bool starts_with(UBasicStringView x) const noexcept
    {
        return size() >= x.size() && compare(0, x.size(), x) == 0;
        return m_len >= x.m_len && traits::compare(m_ptr, x.m_ptr, x.m_len) == 0;
    }

    /*!
        Checks if the string view begins with the given prefix.
        Effectively returns:
        \code
            !empty() && Traits::eq(front(), x);
        \endcode

        \note std::basic_string_view provides this function since from c++20, use it carefully.
        \sa ends_with(), compare()
    */
    constexpr bool starts_with(charT x) const noexcept 
    {
        return !empty() && traits::eq(x, front());
    }

    /*!
        Checks if the string view begins with the given prefix.
        Effectively returns:
        \code
            starts_with(UBasicStringView(x));
        \endcode

        \note std::basic_string_view provides this function since from c++20, use it carefully.
        \sa ends_with(), compare()
    */
    constexpr bool starts_with(const charT* x) const noexcept
    {
        return starts_with(UBasicStringView(x));
    }

    /*!
        Checks if the string view ends with the given suffix.
        Effectively returns:
        \code
            size() >= x.size() && compare(size() - x.size(), npos, x) == 0;
        \endcode

        \note std::basic_string_view provides this function since from c++20, use it carefully.
        \sa starts_with(), compare()
    */
    constexpr bool ends_with(UBasicStringView x) const noexcept
    {
        return m_len >= x.m_len &&
            traits::compare(m_ptr + m_len - x.m_len, x.m_ptr, x.m_len) == 0;
    }

    /*!
        Checks if the string view ends with the given suffix.
        Effectively returns:
        \code
            !empty() && Traits::eq(back(), x);
        \endcode

        \note std::basic_string_view provides this function since from c++20, use it carefully.
        \sa starts_with(), compare()
    */
    constexpr bool ends_with(charT x) const noexcept
    {
        return !empty() && traits::eq(x, back());
    }

    /*!
        Checks if the string view ends with the given suffix.
        Effectively returns:
        \code
            ends_with(UBasicStringView(x)).
        \endcode

        \note std::basic_string_view provides this function since from c++20, use it carefully.
        \sa starts_with(), compare()
    */
    constexpr bool ends_with(const charT* x) const noexcept
    {
        return ends_with(UBasicStringView(x));
    }

    /*!
        Finds the first substring equal to the given character sequence.
        Finds the first occurence of \a v in this view, starting at position \a pos.

        \return Position of the first character of the found substring, or npos if no such substring is found.
        \sa rfind(), find_first_of(), find_last_of(), find_first_not_of(), find_last_not_of()
    */
    constexpr size_type find(UBasicStringView v, size_type pos = 0) const noexcept
    {
        if (pos > size() || v.empty() || v.size() > size() - pos) {
            return npos;
        }
        const charT* cur = m_ptr + pos;
        const charT* last = cend() - v.size() + 1;
        for ( ; cur != last; ++cur) {
            cur = traits::find(cur, last - cur, v[0]);
            if (!cur) {
                return npos;
            }       
            if (traits::compare(cur, v.cbegin(), v.size()) == 0) {
                return cur - m_ptr;
            }
        }
        return npos;
    }
    /*!
        Finds the first substring equal to the given character sequence.
        Equivalent to:
        \code
            find(UBasicStringView(std::addressof(ch), 1), pos);
        \endcode

        \return Position of the first character of the found substring, or npos if no such substring is found.
        \sa rfind(), find_first_of(), find_last_of(), find_first_not_of(), find_last_not_of()
    */
    constexpr size_type find(charT ch, size_type pos = 0) const noexcept 
    {
        if (pos <= size()) {
            const charT* ret_ptr = traits::find(m_ptr + pos, m_len - pos, ch);
            if (ret_ptr) {
                return ret_ptr - m_ptr;
            }        
        }
        return npos;
    }
    /*!
        Finds the first substring equal to the given character sequence.
        Equivalent to:
        \code
            find(UBasicStringView(s, count), pos).
        \endcode

        \return Position of the first character of the found substring, or npos if no such substring is found.
        \sa rfind(), find_first_of(), find_last_of(), find_first_not_of(), find_last_not_of()
    */
    constexpr size_type find(const charT* s, size_type pos, size_type count) const noexcept
    {
        return find(UBasicStringView(s, count), pos);
    }
    /*!
        Finds the first substring equal to the given character sequence.
        Equivalent to:
        \code
            find(UBasicStringView(s), pos);
        \endcode
        
        \return Position of the first character of the found substring, or npos if no such substring is found.
        \sa rfind(), find_first_of(), find_last_of(), find_first_not_of(), find_last_not_of()
    */
    constexpr size_type find(const charT* s, size_type pos = 0) const noexcept
    {
        return find(UBasicStringView(s), pos);
    }

    /*!
        Finds the last substring equal to the given character sequence.
        Finds the last occurence of \a v in this view, starting at position \a pos.

        \return Position of the first character of the found substring or npos if no such substring is found.
        \sa find(), find_first_of(), find_last_of(), find_first_not_of(), find_last_not_of()
    */
    constexpr size_type rfind(UBasicStringView v, size_type pos = npos) const noexcept
    {
        if (m_len < v.m_len) {
            return npos;
        }    
        if (pos > m_len - v.m_len) {
            pos = m_len - v.m_len;
        }    
        if (v.m_len == 0u) {     // an empty string is always found
            return pos;
        }
        for (const charT* cur = m_ptr + pos; ; --cur) {
            if (traits::compare(cur, v.m_ptr, v.m_len) == 0) {
                return cur - m_ptr;
            }
            if (cur == m_ptr) {
                return npos;
            }
        }
    }
    /*!
        Finds the last substring equal to the given character sequence.
        Equivalent to:
        \code
            rfind(UBasicStringView(std::addressof(c), 1), pos);
        \endcode

        \return Position of the first character of the found substring or npos if no such substring is found.
        \sa find(), find_first_of(), find_last_of(), find_first_not_of(), find_last_not_of()
    */
    constexpr size_type rfind(charT c, size_type pos = npos) const noexcept
    {
        return rfind(UBasicStringView(&c, 1), pos);
    }
    /*!
        Finds the last substring equal to the given character sequence.
        Equivalent to:
        \code
            rfind(UBasicStringView(s, count), pos);
        \endcode

        \return Position of the first character of the found substring or npos if no such substring is found.
        \sa find(), find_first_of(), find_last_of(), find_first_not_of(), find_last_not_of()
    */
    constexpr size_type rfind(const charT* s, size_type pos, size_type count) const noexcept
    {
        return rfind(UBasicStringView(s, count), pos);
    }
    /*!
        Finds the last substring equal to the given character sequence.
        Equivalent to:
        \code
            rfind(basic_string_view(s), pos);
        \endcode

        \return Position of the first character of the found substring or npos if no such substring is found.
        \sa find(), find_first_of(), find_last_of(), find_first_not_of(), find_last_not_of()
    */
    constexpr size_type rfind(const charT* s, size_type pos = npos) const noexcept
    {
        return rfind(UBasicStringView(s), pos);
    }

    /*!
        Finds the first character equal to any of the characters in the given character sequence.
        Finds the first occurence of any of the characters of \a v in this view, starting at position \a pos.

        \return Position of the first occurrence of any character of the substring, or npos if no such character is found.
        \sa find(), rfind(), find_last_of(), find_first_not_of(), find_last_not_of()
    */
    constexpr size_type find_first_of(UBasicStringView v, size_type pos = 0) const noexcept 
    {
        if (pos >= m_len || v.m_len == 0) {
            return npos;
        }     
        const_iterator iter = std::find_first_of
        (this->cbegin() + pos, this->cend(), v.cbegin(), v.cend(), traits::eq);
        return iter == this->cend() ? npos : std::distance(this->cbegin(), iter);
    }
    /*!
        Finds the first character equal to any of the characters in the given character sequence.
        Equivalent to:
        \code
            find_first_of(UBasicStringView(std::addressof(c), 1), pos);
        \endcode

        \return Position of the first occurrence of any character of the substring, or npos if no such character is found.
        \sa find(), rfind(), find_last_of(), find_first_not_of(), find_last_not_of()
    */
    constexpr size_type find_first_of(charT c, size_type pos = 0) const noexcept
    {
        return find(c, pos);
    }
    /*!
        Finds the first character equal to any of the characters in the given character sequence.
        Equivalent to:
        \code
            find_first_of(UBasicStringView(s, count), pos);
        \endcode

        \return Position of the first occurrence of any character of the substring, or npos if no such character is found.
        \sa find(), rfind(), find_last_of(), find_first_not_of(), find_last_not_of()
    */
    constexpr size_type find_first_of(const charT* s, size_type pos, size_type count) const noexcept
    {
        return find_first_of(UBasicStringView(s, count), pos);
    }
    /*!
        Finds the first character equal to any of the characters in the given character sequence.
        Equivalent to:
        \code
            find_first_of(UBasicStringView(s), pos);
        \endcode

        \return Position of the first occurrence of any character of the substring, or npos if no such character is found.
        \sa find(), rfind(), find_last_of(), find_first_not_of(), find_last_not_of()
    */
    constexpr size_type find_first_of(const charT* s, size_type pos = 0) const noexcept
    {
        return find_first_of(UBasicStringView(s), pos);
    }

    /*!
        Finds the last character equal to one of characters in the given character sequence. 
        Exact search algorithm is not specified. The search considers only the interval [0; pos]. 
        If the character is not present in the interval, npos will be returned.
        Finds the last occurence of any of the characters of v in this view, ending at position pos.

        \return Position of the last occurrence of any character of the substring, or npos if no such character is found.
        \sa find(), rfind(), find_first_of(), find_first_not_of(), find_last_not_of()
    */
    constexpr size_type find_last_of(UBasicStringView v, size_type pos = npos) const noexcept
    {
        if (v.m_len == 0u) {
            return npos;
        }
        if (pos >= m_len) {
            pos = 0;
        } else {
            pos = m_len - (pos + 1);
        }
        const_reverse_iterator iter = std::find_first_of
        (this->crbegin() + pos, this->crend(), v.cbegin(), v.cend(), traits::eq);
        return iter == this->crend() ? npos : reverse_distance(this->crbegin(), iter);
    }
    /*!
        Finds the last character equal to one of characters in the given character sequence.
        Exact search algorithm is not specified. The search considers only the interval [0; pos].
        If the character is not present in the interval, npos will be returned.
        Equivalent to:
        \code
            find_last_of(UBasicStringView(std::addressof(c), 1), pos);
        \endcode

        \return Position of the last occurrence of any character of the substring, or npos if no such character is found.
        \sa find(), rfind(), find_first_of(), find_first_not_of(), find_last_not_of()
    */
    constexpr size_type find_last_of(charT c, size_type pos = npos) const noexcept
    {
        return find_last_of(UBasicStringView(&c, 1), pos);
    }
    /*!
        Finds the last character equal to one of characters in the given character sequence.
        Exact search algorithm is not specified. The search considers only the interval [0; pos].
        If the character is not present in the interval, npos will be returned.
        Equivalent to:
        \code
            find_last_of(UBasicStringView(s, count), pos);
        \endcode

        \return Position of the last occurrence of any character of the substring, or npos if no such character is found.
        \sa find(), rfind(), find_first_of(), find_first_not_of(), find_last_not_of()
    */
    constexpr size_type find_last_of(const charT* s, size_type pos, size_type count) const noexcept
    {
        return find_last_of(UBasicStringView(s, count), pos);
    }
    /*!
        Finds the last character equal to one of characters in the given character sequence.
        Exact search algorithm is not specified. The search considers only the interval [0; pos].
        If the character is not present in the interval, npos will be returned.
        Equivalent to:
        \code
            find_last_of(UBasicStringView(s), pos);
        \endcode

        \return Position of the last occurrence of any character of the substring, or npos if no such character is found.
        \sa find(), rfind(), find_first_of(), find_first_not_of(), find_last_not_of()
    */
    constexpr size_type find_last_of(const charT* s, size_type pos = npos) const noexcept
    {
        return find_last_of(UBasicStringView(s), pos);
    }

    /*!
        Finds the first character not equal to any of the characters in the given character sequence.
        Finds the first character not equal to any of the characters of \a v in this view, starting at position \a pos.

        \return Position of the first character not equal to any of the characters in the given string, 
                or npos if no such character is found.
        \sa find(), rfind(), find_first_of(), find_last_of(), find_last_not_of()
    */
    constexpr size_type find_first_not_of(UBasicStringView v, size_type pos = 0) const noexcept
    {
        if (pos >= m_len) {
            return npos;
        }
        if (v.m_len == 0) {
            return pos;
        }
        const_iterator iter = find_not_of(this->cbegin() + pos, this->cend(), v);
        return iter == this->cend() ? npos : std::distance(this->cbegin(), iter);
    }
    /*!
        Finds the first character not equal to any of the characters in the given character sequence.
        Equivalent to:
        \code
            find_first_not_of(UBasicStringView(std::addressof(c), 1), pos);
        \endcode

        \return Position of the first character not equal to any of the characters in the given string, 
                or npos if no such character is found.
        \sa find(), rfind(), find_first_of(), find_last_of(), find_last_not_of()
    */
    constexpr size_type find_first_not_of(charT c, size_type pos = 0) const noexcept
    {
        return find_first_not_of(UBasicStringView(&c, 1), pos);
    }
    /*!
        Finds the first character not equal to any of the characters in the given character sequence.
        Equivalent to:
        \code
            find_first_not_of(UBasicStringView(s, count), pos);
        \endcode

        \return Position of the first character not equal to any of the characters in the given string,
                or npos if no such character is found.
        \sa find(), rfind(), find_first_of(), find_last_of(), find_last_not_of()
    */
    constexpr size_type find_first_not_of(const charT* s, size_type pos, size_type count) const noexcept
    {
        return find_first_not_of(UBasicStringView(s, count), pos);
    }
    /*!
        Finds the first character not equal to any of the characters in the given character sequence.
        Equivalent to:
        \code 
            find_first_not_of(UBasicStringView(s), pos);
        \endcode

        \return Position of the first character not equal to any of the characters in the given string,
                or npos if no such character is found.
        \sa find(), rfind(), find_first_of(), find_last_of(), find_last_not_of()
    */
    constexpr size_type find_first_not_of(const charT* s, size_type pos = 0) const noexcept
    {
        return find_first_not_of(UBasicStringView(s), pos);
    }

    /*!
        Finds the last character not equal to any of the characters in the given character sequence.
        Finds the last character not equal to any of the characters of \a v in this view, starting at position \a pos.

        \return Position of the last character not equal to any of the characters in the given string, 
                or npos if no such character is found.
        \sa find(), rfind(), find_first_of(), find_last_of(), find_first_not_of()
    */
    constexpr size_type find_last_not_of(UBasicStringView v, size_type pos = npos) const noexcept
    {
        if (pos >= m_len) {
            pos = m_len - 1;
        }      
        if (v.m_len == 0u) {
            return pos;
        }      
        pos = m_len - (pos + 1);
        const_reverse_iterator iter = find_not_of(this->crbegin() + pos, this->crend(), v);
        return iter == this->crend() ? npos : reverse_distance(this->crbegin(), iter);
    }
    /*!
        Finds the last character not equal to any of the characters in the given character sequence.
        Equivalent to:
        \code 
            find_last_not_of(UBasicStringView(std::addressof(c), 1), pos);
        \endcode

        \return Position of the last character not equal to any of the characters in the given string, 
                or npos if no such character is found.
        \sa find(), rfind(), find_first_of(), find_last_of(), find_first_not_of()
    */
    constexpr size_type find_last_not_of(charT c, size_type pos = npos) const noexcept
    {
        return find_last_not_of(UBasicStringView(&c, 1), pos);
    }
    /*!
        Finds the last character not equal to any of the characters in the given character sequence.
        Equivalent to:
        \code
            find_last_not_of(UBasicStringView(s, count), pos);
        \endcode

        \return Position of the last character not equal to any of the characters in the given string,
                or npos if no such character is found.
        \sa find(), rfind(), find_first_of(), find_last_of(), find_first_not_of()
    */
    constexpr size_type find_last_not_of(const charT* s, size_type pos, size_type count) const noexcept
    {
        return find_last_not_of(UBasicStringView(s, count), pos);
    }
    /*!
        Finds the last character not equal to any of the characters in the given character sequence.
        Equivalent to:
        \code
            find_last_not_of(UBasicStringView(s), pos);
        \endcode

        \return Position of the last character not equal to any of the characters in the given string,
                or npos if no such character is found.
        \sa find(), rfind(), find_first_of(), find_last_of(), find_first_not_of()
    */
    constexpr size_type find_last_not_of(const charT* s, size_type pos = npos) const noexcept
    {
        return find_last_not_of(UBasicStringView(s), pos);
    }
private:
    template <typename r_iter>
    size_type reverse_distance(r_iter first, r_iter last) const noexcept 
    {
        // Portability note here: std::distance is not NOEXCEPT, but calling it with a string_view::reverse_iterator will not throw.
        return m_len - 1 - std::distance(first, last);
    }

    template <typename Iterator>
    Iterator find_not_of(Iterator first, Iterator last, basic_string_view v) const noexcept
    {
        for (; first != last; ++first) {
            if (0 == traits::find(v.ptr_, v.m_len, *first)) {
                return first;
            }
        }
        return last;
    }

private:
    const charT* m_ptr;
    std::size_t m_len;
}; // class UBasicStringView

/*!
    Compares two views.

    \li All comparisons are done via the compare() member function (which itself is defined in terms of Traits::compare()):
        Two views are equal if both the size of lhs and rhs are equal and each character in \a x has an equivalent character 
        in \a y at the same position.
    \li The ordering comparisons are done lexicographically -- the comparison is performed by a function equivalent to 
        std::lexicographical_compare.

    \return \c true if the corresponding comparison holds, \c false otherwise.
*/
template<typename charT, typename traits>
inline constexpr bool operator==(UBasicStringView<charT, traits> x, UBasicStringView<charT, traits> y) noexcept 
{
    if (x.size() != y.size()) {
        return false;
    }
    return x.compare(y) == 0;
}

/*!
    Compares two views.

    \li All comparisons are done via the compare() member function (which itself is defined in terms of Traits::compare()):
        Two views are equal if both the size of lhs and rhs are equal and each character in \a x has an equivalent character
        in \a y at the same position.
    \li The ordering comparisons are done lexicographically -- the comparison is performed by a function equivalent to
        std::lexicographical_compare.

    \return \c true if the corresponding comparison holds, \c false otherwise.
*/
template<typename charT, typename traits>
inline constexpr bool operator!=(UBasicStringView<charT, traits> x, UBasicStringView<charT, traits> y) noexcept 
{
    if (x.size() != y.size()) {
        return true;
    }
    return x.compare(y) != 0;
}

/*!
    Compares two views.

    \li All comparisons are done via the compare() member function (which itself is defined in terms of Traits::compare()):
        Two views are equal if both the size of lhs and rhs are equal and each character in \a x has an equivalent character
        in \a y at the same position.
    \li The ordering comparisons are done lexicographically -- the comparison is performed by a function equivalent to
        std::lexicographical_compare.

    \return \c true if the corresponding comparison holds, \c false otherwise.
*/
template<typename charT, typename traits>
inline constexpr bool operator<(UBasicStringView<charT, traits> x, UBasicStringView<charT, traits> y) noexcept 
{
    return x.compare(y) < 0;
}

/*!
    Compares two views.

    \li All comparisons are done via the compare() member function (which itself is defined in terms of Traits::compare()):
        Two views are equal if both the size of lhs and rhs are equal and each character in \a x has an equivalent character
        in \a y at the same position.
    \li The ordering comparisons are done lexicographically -- the comparison is performed by a function equivalent to
        std::lexicographical_compare.

    \return \c true if the corresponding comparison holds, \c false otherwise.
*/
template<typename charT, typename traits>
inline constexpr bool operator>(UBasicStringView<charT, traits> x, UBasicStringView<charT, traits> y) noexcept 
{
    return x.compare(y) > 0;
}

/*!
    Compares two views.

    \li All comparisons are done via the compare() member function (which itself is defined in terms of Traits::compare()):
        Two views are equal if both the size of lhs and rhs are equal and each character in \a x has an equivalent character
        in \a y at the same position.
    \li The ordering comparisons are done lexicographically -- the comparison is performed by a function equivalent to
        std::lexicographical_compare.

    \return \c true if the corresponding comparison holds, \c false otherwise.
*/
template<typename charT, typename traits>
inline constexpr bool operator<=(UBasicStringView<charT, traits> x, UBasicStringView<charT, traits> y) noexcept
{
    return x.compare(y) <= 0;
}

/*!
    Compares two views.

    \li All comparisons are done via the compare() member function (which itself is defined in terms of Traits::compare()):
        Two views are equal if both the size of lhs and rhs are equal and each character in \a x has an equivalent character
        in \a y at the same position.
    \li The ordering comparisons are done lexicographically -- the comparison is performed by a function equivalent to
        std::lexicographical_compare.

    \return \c true if the corresponding comparison holds, \c false otherwise.
*/
template<typename charT, typename traits>
inline constexpr bool operator>=(UBasicStringView<charT, traits> x, UBasicStringView<charT, traits> y) noexcept 
{
    return x.compare(y) >= 0;
}

/*!
    Equivalent to:
    \code
        x == UBasicStringView<charT, traits>(y);
    \endcode
*/
template<typename charT, typename traits, typename Allocator>
inline constexpr bool operator==(UBasicStringView<charT, traits> x,
    const std::basic_string<charT, traits, Allocator>& y) noexcept 
{
    return x == UBasicStringView<charT, traits>(y);
}

/*!
    Equivalent to:
    \code
        UBasicStringView<charT, traits>(x) == y;
    \endcode
*/
template<typename charT, typename traits, typename Allocator>
inline constexpr bool operator==(const std::basic_string<charT, traits, Allocator>& x,
    UBasicStringView<charT, traits> y) noexcept 
{
    return UBasicStringView<charT, traits>(x) == y;
}

/*!
    Equivalent to:
    \code
        x == UBasicStringView<charT, traits>(y);
    \endcode
*/
template<typename charT, typename traits>
inline constexpr bool operator==(UBasicStringView<charT, traits> x, const charT* y) noexcept 
{
    return x == UBasicStringView<charT, traits>(y);
}

/*!
    Equivalent to:
    \code
        UBasicStringView<charT, traits>(x) == y;
    \endcode
*/
template<typename charT, typename traits>
inline constexpr bool operator==(const charT* x, UBasicStringView<charT, traits> y) noexcept 
{
    return UBasicStringView<charT, traits>(x) == y;
}

/*!
    Equivalent to:
    \code
        x != UBasicStringView<charT, traits>(y);
    \endcode
*/
template<typename charT, typename traits, typename Allocator>
inline constexpr bool operator!=(UBasicStringView<charT, traits> x,
    const std::basic_string<charT, traits, Allocator>& y) noexcept 
{
    return x != UBasicStringView<charT, traits>(y);
}

/*!
    Equivalent to:
    \code
        UBasicStringView<charT, traits>(x) != y;
    \endcode
*/
template<typename charT, typename traits, typename Allocator>
inline constexpr bool operator!=(const std::basic_string<charT, traits, Allocator>& x,
    UBasicStringView<charT, traits> y) noexcept 
{
    return UBasicStringView<charT, traits>(x) != y;
}

/*!
    Equivalent to:
    \code
        x != UBasicStringView<charT, traits>(y);
    \endcode
*/
template<typename charT, typename traits>
inline constexpr bool operator!=(UBasicStringView<charT, traits> x, const charT* y) noexcept 
{
    return x != UBasicStringView<charT, traits>(y);
}

/*!
    Equivalent to:
    \code
        UBasicStringView<charT, traits>(x) != y;
    \endcode
*/
template<typename charT, typename traits>
inline constexpr bool operator!=(const charT* x, UBasicStringView<charT, traits> y) noexcept 
{
    return UBasicStringView<charT, traits>(x) != y;
}

/*!
    Equivalent to:
    \code
        x < basic_string_view<charT, traits>(y);
    \endcode
*/
template<typename charT, typename traits, typename Allocator>
inline constexpr bool operator<(UBasicStringView<charT, traits> x,
    const std::basic_string<charT, traits, Allocator>& y) noexcept 
{
    return x < basic_string_view<charT, traits>(y);
}

/*!
    Equivalent to:
    \code
        UBasicStringView<charT, traits>(x) < y;
    \endcode
*/
template<typename charT, typename traits, typename Allocator>
inline constexpr bool operator<(const std::basic_string<charT, traits, Allocator>& x,
    UBasicStringView<charT, traits> y) noexcept 
{
    return UBasicStringView<charT, traits>(x) < y;
}

/*!
    Equivalent to:
    \code
        x < UBasicStringView<charT, traits>(y);
    \endcode
*/
template<typename charT, typename traits>
inline constexpr bool operator<(UBasicStringView<charT, traits> x, const charT* y) noexcept
{
    return x < UBasicStringView<charT, traits>(y);
}

/*!
    Equivalent to:
    \code
        UBasicStringView<charT, traits>(x) < y;
    \endcode
*/
template<typename charT, typename traits>
inline constexpr bool operator<(const charT* x, UBasicStringView<charT, traits> y) noexcept
{
    return UBasicStringView<charT, traits>(x) < y;
}

/*!
    Equivalent to:
    \code
        x > UBasicStringView<charT, traits>(y);
    \endcode
*/
template<typename charT, typename traits, typename Allocator>
inline constexpr bool operator>(UBasicStringView<charT, traits> x,
    const std::basic_string<charT, traits, Allocator>& y) noexcept 
{
    return x > UBasicStringView<charT, traits>(y);
}

/*!
    Equivalent to:
    \code
        UBasicStringView<charT, traits>(x) > y;
    \endcode
*/
template<typename charT, typename traits, typename Allocator>
inline constexpr bool operator>(const std::basic_string<charT, traits, Allocator>& x,
    UBasicStringView<charT, traits> y) noexcept 
{
    return UBasicStringView<charT, traits>(x) > y;
}

/*!
    Equivalent to:
    \code
        x > UBasicStringView<charT, traits>(y);
    \endcode
*/
template<typename charT, typename traits>
inline constexpr bool operator>(UBasicStringView<charT, traits> x,
    const charT* y) noexcept 
{
    return x > UBasicStringView<charT, traits>(y);
}

/*!
    Equivalent to:
    \code
        UBasicStringView<charT, traits>(x) > y;
    \endcode
*/
template<typename charT, typename traits>
inline constexpr bool operator>(const charT* x, UBasicStringView<charT, traits> y) noexcept 
{
    return UBasicStringView<charT, traits>(x) > y;
}

/*!
    Equivalent to:
    \code
        x <= UBasicStringView<charT, traits>(y);
    \endcode
*/
template<typename charT, typename traits, typename Allocator>
inline constexpr bool operator<=(UBasicStringView<charT, traits> x,
    const std::basic_string<charT, traits, Allocator>& y) noexcept 
{
    return x <= UBasicStringView<charT, traits>(y);
}

/*!
    Equivalent to:
    \code
        UBasicStringView<charT, traits>(x) <= y;
    \endcode
*/
template<typename charT, typename traits, typename Allocator>
inline constexpr bool operator<=(const std::basic_string<charT, traits, Allocator>& x,
    UBasicStringView<charT, traits> y) noexcept 
{
    return UBasicStringView<charT, traits>(x) <= y;
}

/*!
    Equivalent to:
    \code
        x <= UBasicStringView<charT, traits>(y);
    \endcode
*/
template<typename charT, typename traits>
inline constexpr bool operator<=(UBasicStringView<charT, traits> x, const charT* y) noexcept
{
    return x <= UBasicStringView<charT, traits>(y);
}

/*!
    Equivalent to:
    \code
        UBasicStringView<charT, traits>(x) <= y;
    \endcode
*/
template<typename charT, typename traits>
inline constexpr bool operator<=(const charT* x, UBasicStringView<charT, traits> y) noexcept
{
    return UBasicStringView<charT, traits>(x) <= y;
}

/*!
    Equivalent to:
    \code
        x >= UBasicStringView<charT, traits>(y);
    \endcode
*/
template<typename charT, typename traits, typename Allocator>
inline constexpr bool operator>=(UBasicStringView<charT, traits> x,
    const std::basic_string<charT, traits, Allocator>& y) noexcept 
{
    return x >= UBasicStringView<charT, traits>(y);
}

/*!
    Equivalent to:
    \code
        UBasicStringView<charT, traits>(x) >= y;
    \endcode
*/
template<typename charT, typename traits, typename Allocator>
inline constexpr bool operator>=(const std::basic_string<charT, traits, Allocator>& x,
    UBasicStringView<charT, traits> y) noexcept 
{
    return UBasicStringView<charT, traits>(x) >= y;
}

/*!
    Equivalent to:
    \code
        x >= UBasicStringView<charT, traits>(y);
    \endcode
*/
template<typename charT, typename traits>
inline constexpr bool operator>=(UBasicStringView<charT, traits> x, const charT* y) noexcept 
{
    return x >= UBasicStringView<charT, traits>(y);
}

/*!
    Equivalent to:
    \code
        UBasicStringView<charT, traits>(x) >= y;
    \endcode
*/
template<typename charT, typename traits>
inline constexpr bool operator>=(const charT* x, UBasicStringView<charT, traits> y) noexcept 
{
    return UBasicStringView<charT, traits>(x) >= y;
}

/*!
    Behaves as a FormattedOutputFunction. 
    After constructing and checking the sentry object, determines the output format padding as follows:

    \li If v.size() is not less than os.width(), uses the range [v.begin(), v.end()) as-is.
    \li Otherwise, if (os.flags() & ios_base::adjustfield) == ios_base::left, places os.width()-v.size() 
        copies of the os.fill() character after the character sequence.
    \li Otherwise, places os.width()-v.size() copies of the os.fill() character before the character sequence.
    
    Then stores each character from the resulting sequence (the contents of v plus padding) to the output 
    stream os as if by calling os.rdbuf()->sputn(seq, n), where n=std::max(os.width(), str.size()).
    Finally, calls os.width(0) to cancel the effects of std::setw, if any.

    \exception May throw \c std::ios_base::failure if an exception is thrown during output.
*/
template<class charT, class traits>
inline std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& os, 
    const UBasicStringView<charT, traits> str) 
{
    return detail::ostream_string(os, str.data(), str.size());
}

inline namespace string_view_literals {

/*!
    Forms a string view of a character literal.
    \return The string_view literal.
*/
UTILS4CPP_NODISCARD constexpr UStringView operator "" sv(const char* str, std::size_t len) noexcept
{
    return (UStringView(str, len));
}

/*!
    Forms a string view of a character literal.
    \return The string_view literal.
*/
UTILS4CPP_NODISCARD constexpr UWStringView operator "" sv(const wchar_t* str, std::size_t len) noexcept
{
    return (UWStringView(str, len));
}

/*!
    Forms a string view of a character literal.
    \return The string_view literal.
*/
UTILS4CPP_NODISCARD constexpr U16StringView operator "" sv(const char16_t* str, std::size_t len) noexcept
{
    return (U16StringView(str, len));
}

/*!
    Forms a string view of a character literal.
    \return The string_view literal.
*/
UTILS4CPP_NODISCARD constexpr U32StringView operator "" sv(const char32_t* str, std::size_t len) noexcept
{
    return (U32StringView(str, len));
}

#if UTILS4CPP_HAS_CHAR8T

/*!
    Forms a string view of a character literal.
    \return The string_view literal.
*/
UTILS4CPP_NODISCARD constexpr U8StringView operator "" sv(const char8_t* str, std::size_t len) noexcept
{
    return (U8StringView(str, len));
}

#endif // UTILS4CPP_HAS_CHAR8T

} // inline namespace string_view_literals

#endif // !UTILS4CPP_HAS_STDSTRINGVIEW

} // namespace str
} // namespace utils4cpp

#endif // UTILS4CPP_STR_USTRINGVIEW_HPP