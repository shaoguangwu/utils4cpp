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

#ifndef UTILS4CPP_CORE_USTLCONFIG_HPP
#define UTILS4CPP_CORE_USTLCONFIG_HPP

#include "utils4cpp/core/UCppStandardDetection.hpp"

/*!
    \def UTILS4CPP_HAS_STDFILESYSTEM
    \li 1 Supports std::filesystem.
    \li 0 Not supports std::filesystem.

    std::filesystem since from c++17
*/
#if UTILS4CPP_HAS_CPP17
#   /* MSVC */
#   if defined(_MSC_VER) && _MSC_VER >= 1914
#       define UTILS4CPP_HAS_STDFILESYSTEM          1
#   /* GCC */
#   elif defined(__GNUC__) && __GNUC__ >= 8
#       define UTILS4CPP_HAS_STDFILESYSTEM          1
#   /* Clang */
#   elif defined(__clang__) && __clang_major__ >= 7
#       define UTILS4CPP_HAS_STDFILESYSTEM          1
#   /* Unkown, default to not support */
#   else
#       define UTILS4CPP_HAS_STDFILESYSTEM          0
#   endif
#else /* !UTILS4CPP_HAS_CPP17 */
#   define UTILS4CPP_HAS_STDFILESYSTEM              0
#endif /* UTILS4CPP_HAS_CPP17 */

/*!
    \def UTILS4CPP_HAS_CHAR8T
    \li 1 Supports char8_t.
    \li 0 Not supports char8_t.

    char8_t since from c++20.
*/
#if UTILS4CPP_HAS_CPP20
#   if defined(_MSC_VER) && _MSC_VER >= 1922
#   /* MSVC */
#       define UTILS4CPP_HAS_CHAR8T                 1
#   /* GCC */
#   elif defined(__GNUC__) && __GNUC__ >= 9
#       define UTILS4CPP_HAS_CHAR8T                 1
#   /* Clang */
#   elif defined(__clang__) && __clang_major__ >= 7
#       define UTILS4CPP_HAS_CHAR8T                 1
#   /* Unkown, default to not support */
#   else
#       define UTILS4CPP_HAS_CHAR8T                 0
#   endif
#else /* !UTILS4CPP_HAS_CPP20 */
#   define UTILS4CPP_HAS_CHAR8T                     0
#endif /* UTILS4CPP_HAS_CPP20 */

/*!
    \def UTILS4CPP_HAS_U8STRING
    \li 1 Supports std::u8string.
    \li 0 Not supports std::u8string.

    std::u8string since from c++20.
*/
#if UTILS4CPP_HAS_CHAR8T
#   define UTILS4CPP_HAS_U8STRING                      1
#else
#   define UTILS4CPP_HAS_U8STRING                      0
#endif /* UTILS4CPP_HAS_CHAR8T */

#endif // UTILS4CPP_CORE_USTLCONFIG_HPP