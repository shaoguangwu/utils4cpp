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

#ifndef UTILS4CPP_FILESYSTEM_UPATH_HPP
#define UTILS4CPP_FILESYSTEM_UPATH_HPP

#include <utility>

#include "utils4cpp/filesystem/UFileSystemGlobal.hpp"
#include "utils4cpp/filesystem/UPathToString.inl"

namespace utils4cpp {
namespace filesystem {

/*!
    \class UPath
    \brief Objects of type path represent paths on a filesystem. 
    \since v0.0
    
    Only syntactic aspects of paths are handled: the pathname may represent a non-existing
    path or even one that is not allowed to exist on the current file system or OS.
*/
template<class StringT>
class UPath
{
public:
    /*! Typedef for StringT::value_type. Provided for STL compatibility. */
    using valu_type = typename StringT::value_type;
    /*! Typedef for StringT. Provided for STL compatibility. */
    using string_type = StringT;
    /*! Typedef for StringT::size_type. Provided for STL compatibility. */
    using size_type = typename StringT::size_type;

public:
    /*! 
        Constructs an empty path.
    */
    UPath() noexcept(std::is_nothrow_default_constructible_v<StringT>) = default;

    /*!
        Destroys the path object.
    */
    ~UPath() = default;

    UPath(const StringT& str) : m_data(str)
    {}

    UPath(StringT&& str) noexcept : m_data(std::move(str))
    {}

    UPath(const UPath& other) : m_data(other.m_data)
    {}

    UPath(UPath&& other) noexcept : m_data(std::move(other.m_data))
    {}

    UPath& operator=(const StringT& str)
    {
        m_data = str;
        return *this;
    }
    UPath& operator=(StringT& str) noexcept
    {
        m_data = std::move(str);
        return *this;
    }
    UPath& operator=(const UPath& other)
    {
        if (&other != this) {
            m_data = other.m_data;
        }
        return *this;
    }

#if UTILS4CPP_HAS_CPP17
    UPath& operator=(UPath&& other) noexcept
    {
        if (&other != this) {
            m_data = std::move(other.m_data);
        }
        return *this;
    }
#else
    UPath& operator=(UPath&& other)
    {
        if (&other != this) {
            m_data = std::move(other.m_data);
        }
        return *this;
    }
#endif

#if UTILS4CPP_HAS_STDFILESYSTEM
    UPath(const std::filesystem::path& path) : m_data(impl::pathToString<StringT>(path))
    {}
    UPath& operator=(const std::filesystem::path& path)
    {
        m_data = impl::pathToString<StringT>(path);
        return *this;
    }
#endif

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

    StringT toInputString() const
    {
        return m_data;
    }


    StringT moveToInputString() noexcept
    {
        return std::move(m_data);
    }

    bool empty() const noexcept
    {
        return m_data.empty();
    }

    void clear() noexcept
    {
        m_data.clear();
    }

#if UTILS4CPP_HAS_CPP17
    void swap(UPath& other) noexcept
    {
        m_data.swap(other.m_data);
    }
#else
    void swap(UPath& other)
    {
        m_data.swap(other.m_data);
    }
#endif


private:
    StringT m_data;
};

} // namespace filesystem
} // namespace utils4cpp

#endif // UTILS4CPP_FILESYSTEM_UPATH_HPP