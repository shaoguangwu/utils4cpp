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

#ifndef UTILS4CPP_FILESYSTEM_UFILESYSTEMGLOBAL_HPP
#define UTILS4CPP_FILESYSTEM_UFILESYSTEMGLOBAL_HPP

#include <string>
#include "utils4cpp/core/UCore.hpp"

#if UTILS4CPP_HAS_STDFILESYSTEM
#   include <filesystem>
#endif /* UTILS4CPP_HAS_STDFILESYSTEM */ 

namespace utils4cpp {
/*!
    \brief file system libraries.
    \since v0.0
*/
namespace filesystem {

/*!
    Returns the path separator on native operating system.
    The template parameter \a CharT must one of char, wchar_t, char16_t, char32_t, 
    char8_t(c++20).
*/
template<typename CharT>
static constexpr CharT nativeSeparator() noexcept
{
#ifdef UTILS4CPP_OS_WIN
    return '\\';
#else
    return '/';
#endif
}

} // namespace filesystem
} // namespace utils4cpp

#endif // UTILS4CPP_FILESYSTEM_UFILESYSTEMGLOBAL_HPP
