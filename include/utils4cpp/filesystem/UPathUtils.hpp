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

#ifndef UTILS4CPP_FILESYSTEM_UPATHUTILS_HPP
#define UTILS4CPP_FILESYSTEM_UPATHUTILS_HPP

#include <string>
#include <vector>

#include "utils4cpp/filesystem/UFileSystemGlobal.hpp"

namespace utils4cpp {
namespace filesystem {

/*****************************************************************************
    declaration
 *****************************************************************************/

template<class StringT>
void convertToUnixSlashesSelf(StringT& path);

template<class StringT>
StringT convertToUnixSlashes(const StringT& path);

template<class StringT>
void convertToWindowsSlashesSelf(StringT& path);

template<class StringT>
StringT convertToWindowsSlashes(const StringT& path);

template<class StringT>
void convertToNativeSlashesSelf(StringT& path);

template<class StringT>
StringT convertToNativeSlashes(const StringT& path);

/*****************************************************************************
    implementation
 *****************************************************************************/

template<class StringT>
inline void convertToUnixSlashesSelf(StringT& path)
{
    for (auto& c : path) {
        if (c == '\\') {
            c = '/';
        }
    }
}

template<class StringT>
inline StringT convertToUnixSlashes(const StringT& path)
{
    StringT result(path);
    convertToUnixSlashesSelf(result);
    return result;
}

template<class StringT>
inline void convertToWindowsSlashesSelf(StringT& path)
{
    for (auto& c : path) {
        if (c == '/') {
            c = '\\';
        }
    }
}

template<class StringT>
inline StringT convertToWindowsSlashes(const StringT& path)
{
    StringT result(path);
    convertToWindowsSlashesSelf(result);
    return result;
}

template<class StringT>
inline void convertToNativeSlashesSelf(StringT& path)
{
#ifdef UTILS4CPP_OS_WIN
    return convertToWindowsSlashesSelf(path);
#else
    return convertToUnixSlashesSelf(path);
#endif

}

template<class StringT>
inline StringT convertToNativeSlashes(const StringT& path)
{
    StringT result(path);
    convertToNativeSlashesSelf(result);.
    return result;
}

template<class StringT>
StringT fileName(const StringT& path)
{
    auto rit = path.rbegin();
    while (rit != path.rend()) {
        if (*rit == '/' || *rit == '\\') {

        }
    }
}

#if UTILS4CPP_HAS_STDFILESYSTEM

template<>
inline void convertToUnixSlashesSelf(std::filesystem::path& path)
{

}

template<>
std::filesystem::path fileName(const std::filesystem::path& path)
{
    return path.filename();
}


#endif /* UTILS4CPP_HAS_STDFILESYSTEM */

} // namespace filesystem
} // namespace utils4cpp

#endif // UTILS4CPP_FILESYSTEM_UPATHUTILS_HPP