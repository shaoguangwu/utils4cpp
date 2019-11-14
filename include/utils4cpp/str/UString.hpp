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

#ifndef UTILS4CPP_STR_USTRING_HPP
#define UTILS4CPP_STR_USTRING_HPP

#include <type_traits>
#include "utils4cpp/str/UStringUtils.hpp"
#include "utils4cpp/str/UStringView.hpp"

namespace utils4cpp {
namespace str {

template<class StringT>
class UString
{
    StringT m_data;
public:
    using value_type = typename StringT::value_type;
    using input_string_type = StringT;
    using size_type = typename StringT::size_type;
    using reference = typename StringT::reference; 
    using const_reference = typename StringT::const_reference;

public:

    UString() noexcept(std::is_nothrow_default_constructible_v<StringT>) = default;
    ~UString() = default;

    UString(value_type ch)
        : m_data(1, ch) {}
    UString(size_type count, value_type ch)
        : m_data(count, ch) {}
    UString(const StringT& str, size_type pos)
        : m_data(str, pos) {}
    UString(const StringT& str, size_type pos, size_type count)
        : m_data(str, pos, count){}
    UString(const value_type* s, size_type count)
        : m_data(s, count) {}
    UString(const value_type* s)
        : m_data(s) {}

    template<class InputIterator>
    UString(InputIterator first, InputIterator last)
        : m_data(first, last) {}

    UString(const StringT& str) noexcept(std::is_nothrow_copy_constructible_v<StringT>)
        : m_data(str)
    {}

    UString(StringT&& str) noexcept(std::is_nothrow_move_constructible_v<StringT>)
        : m_data(std::move(str))
    {}

    UString(const UString& other) noexcept(std::is_nothrow_copy_constructible_v<StringT>)
        : m_data(other.m_data)
    {}

    UString(UString&& other) noexcept(std::is_nothrow_move_constructible_v<StringT>)
        : m_data(std::move(other.m_data))
    {}

    UString(std::initializer_list<value_type> list)
        : m_data(list) {}

#ifdef UTILS4CPP_HAS_CPP17
    // string_view支持
    template<class T>
    explicit UString(const T& t)
        : m_data(t) {}
    template<class T>
    UString(const T& t, size_type pos, size_type n)
        : m_data(t, n) {}
#endif // UTILS4CPP_HAS_CPP17

    UString& operator=(value_type ch) noexcept
    {
        m_data.assign(1, ch);
    }
    UString& operator=(const StringT& str)
    {
        m_data = str;
        return *this;
    }
    UString& operator=(StringT&& str) noexcept
    {
        m_data = std::move(str);
        return *this;
    }
    UString& operator=(const UString& other)
    {
        if (this != &other) {
            m_data = other.m_data;
        }
        return *this;
    }
    UString& operator=(UString&& other) noexcept
    {
        if (this != &other) {
            m_data = std::move(other.m_data);
        }
        return *this;
    }

    size_type size() const noexcept
    {
        return m_data.size();
    }

    size_type count() const noexcept
    {
        return m_data.size();
    }

    size_type length() const noexcept
    {
        return m_data.length();
    }

    bool empty() const noexcept
    {
        return m_data.empty();
    }

    StringT& data() noexcept
    {
        return m_data;
    }
    const StringT& data() const noexcept
    {
        return m_data;
    }
    const StringT& constData() const noexcept
    {
        return m_data;
    }

    StringT toInputString()
    {
        return m_data;
    }

    StringT moveToInputString() noexcept
    {
        return std::move(m_data);
    }

    reference operator[](size_type pos)
    {
        return m_data[pos];
    }
    const_reference operator[](size_type pos) const
    {
        return m_data[pos];
    }

    const value_type* c_str() const noexcept
    {
        return m_data.c_str();
    }

    UString substr(size_type pos = 0, size_type count = StringT::npos) const
    {
        return m_data.substr(pos, count);
    }

    bool startsWith(value_type c, UCaseSensitivity cs = UCaseSensitive, const std::locale& loc = std::locale) const
    {
        return endsWith(c, cs, loc);
    }

    bool startsWith(const StringT& s, UCaseSensitivity cs = UCaseSensitive) const
    {

    }

    bool startsWith(const UString& s, UCaseSensitivity cs = UCaseSensitive)
    {

    }

    bool startsWith(UBasicStringView<value_type> str, UCaseSensitivity cs = UCaseSensitive) const noexcept
    {

    }
    bool endsWith();

    UString& fill(value_type ch) noexcept
    {
        std::fill(m_data.begin(), m_data.end(), ch);
        return *this;
    }

    void clear() noexcept
    {
        return m_data.clear();
    }

    void swap(UString& other) noexcept(
        std::allocator_traits<StringT::Allocator>::propagate_on_container_swap::value ||
        std::allocator_traits<StringT::Allocator>::is_always_equal::value)
    {
        m_data.swap(other.m_data);
    }

    void swap(StringT& str) noexcept(
        std::allocator_traits<StringT::Allocator>::propagate_on_container_swap::value ||
        std::allocator_traits<StringT::Allocator>::is_always_equal::value)
    {
        m_data.swap(str);
    }

    UString& reverse()
    {
        reverseStringSelf(m_data);
        return *this;
    }

    UString reversed() const
    {
        return UString(reverseString(m_data));
    }

    UString& remove(size_type pos, size_type count)
    {

    }

};
} // namespace str
} // namespace utils4cpp 

#endif // UTILS4CPP_STR_USTRING_HPP