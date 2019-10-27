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

#ifndef UTILS4CPP_FILESYSTEM_PATHTOSTRING_INC
#define UTILS4CPP_FILESYSTEM_PATHTOSTRING_INC

#if UTILS4CPP_HAS_STDFILESYSTEM

#include <string>
#include <filesystem>
#include <stdexcept>

#include "utils4cpp/core/StlConfig.hpp"

namespace utils4cpp {
namespace filesystem {
namespace inc {

template<class StringT>
inline StringT pathToString(const std::filesystem::path& path)
{
    throw std::invalid_argument("invalid template argument");
}

template<>
inline std::string pathToString(const std::filesystem::path& path)
{
    return path.string();
}

template<>
inline std::wstring pathToString(const std::filesystem::path& path)
{
    return path.wstring();
}

template<>
inline std::u16string pathToString(const std::filesystem::path& path)
{
    return path.u16string();
}

template<>
inline std::u32string pathToString(const std::filesystem::path& path)
{
    return path.u32string();
}

#if UTILS4CPP_HAS_U8STRING

template<>
inline std::u8string pathToString(const std::filesystem::path& path)
{
    return path.u8string();
}

#endif // UTILS4CPP_HAS_U8STRING

} // namespace inc
} // namespace filesystem
} // namespace utils4cpp

#endif // UTILS4CPP_HAS_STDFILESYSTEM

#endif // UTILS4CPP_FILESYSTEM_PATHTOSTRING_INC