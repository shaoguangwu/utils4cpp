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

namespace utils4cpp {
namespace str {

template<class StringT>
class UString
{
    StringT m_data;
public:
    using value_type = typename StringT::value_type;
    using string_type = StringT;
    using size_type = typename StringT::size_type;

public:

    UString() noexcept(std::is_nothrow_default_constructible_v<StringT>) = default;
    ~UString() = default;

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

    UString& operator=(const StringT& str) noexcept(std::is_nothrow_copy_constructible_v<StringT>)
    {
        m_data = str;
        return *this;
    }
    UString& operator=(StringT&& str) noexcept(std::is_nothrow_move_constructible_v<StringT>)
    {
        m_data = std::move(str);
        return *this;
    }
    UString& operator=(const UString& other) noexcept(std::is_nothrow_copy_constructible_v<StringT>)
    {
        if (this != &other) {
            m_data = other.m_data;
        }
        return *this;
    }
    UString& operator=(UString& other) noexcept(std::is_nothrow_move_constructible_v<StringT>)
    {
        if (this != &other) {
            m_data = std::move(other.m_data);
        }
        return *this;
    }

    bool empty() const noexcept
    {
        return m_data.empty();
    }

    size_type size() const noexcept
    {
        return m_data.size();
    }

    size_type length() const noexcept
    {
        return m_data.length();
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

    void clear() noexcept
    {
        return m_data.clear();
    }

    StringT toInputString() noexcept(std::is_nothrow_copy_constructible_v<StringT>)
    {
        return m_data;
    }

    StringT moveToInputString() noexcept(std::is_nothrow_move_constructible_v<StringT>)
    {
        return std::move(m_data);
    }
};


} // namespace str
} // namespace utils4cpp 

#endif // UTILS4CPP_STR_USTRING_HPP