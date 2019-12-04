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

#ifndef UTILS4CPP_CORE_UCPPFEATURES_HPP
#define UTILS4CPP_CORE_UCPPFEATURES_HPP

#include "utils4cpp/core/UCppStandardDetection.hpp"
#include "utils4cpp/core/UCompilerDetection.hpp"

//
// C++17 features
//

// std::string_view
#define UTILS4CPP_USE_STD_STRIING_VIEW      // enabled: msvc - 1910, gcc - 7, clang-libstdc++ - 4
// [[maybe_unused]]
#define UTILS4CPP_USE_ATTR_MAYBE_UNUSED     // enabled: msvc - 1911, gcc - 7, clang-libstdc++ - 3.9
// if constexpr
#define UTILS4CPP_USE_IF_CONSTEXPR          // enabled: msvc - 1911, gcc - 7, clang-libstdc++ - 3.9
// std::bool_constant
#define UTILS4CPP_USE_STD_BOOL_CONSTANT     // enabled: msvc - 1900, gcc - 6, clang-libstdc++ - 3.7
// std::optional
#define UTILS4CPP_USE_STD_OPTIONAL          // enabled: msvc - 1910, gcc - 7, clang-libstdc++ - 4
// std::conjunction
#define UTILS4CPP_USE_STD_CONJUNCTION       // enabled: msvc - 1900, gcc - 6, clang-libstdc++ - 3.8
// std::disjunction
#define UTILS4CPP_USE_STD_DISJUNCTION       // enabled: msvc - 1900, gcc - 6, clang-libstdc++ - 3.8
// std::negation
#define UTILS4CPP_USE_STD_NEGATION          // enabled: msvc - 1900, gcc - 6, clang-libstdc++ - 3.8
// inline variable
#define UTILS4CPP_USE_INLINE_VARIABLE       // enabled: msvc - 1912, gcc - 7, clang-libstdc++ - 3.9
// nested namespace
#define UTILS4CPP_USE_NESTED_NAMESPACE      // enabled: msvc - 1900, gcc - 6, clang-libstdc++ - 3.6
// __has_include
//#define UTILS4CPP_USE_HAS_INCLUDE           // enabled: msvc - 1911, gcc - 5, clang-libstdc++ - 3.6

#define UTILS4CPP_MSVC_MINVER_REQUIRE               1912
#define UTILS4CPP_GNU_MINVER_REQUIRE                7
#define UTILS4CPP_CLANG_LIBSTD_MINVER_REQUIRE       4

/*  Only the following compilers are supported currently:
    msvc, gnu-c++, clang-libstdc++
*/
#if ( defined(UTILS4CPP_CC_MSVC) && UTILS4CPP_CC_MSVC < UTILS4CPP_MSVC_MINVER_REQUIRE )     || \
    ( defined(UTILS4CPP_CC_GNU) && UTILS4CPP_CC_GNU < UTILS4CPP_GNU_MINVER_REQUIRE * 100 )  || \
    ( defined(UTILS4CPP_CC_CLANG) && UTILS4CPP_CC_CLANG < UTILS4CPP_CLANG_LIBSTD_MINVER_REQUIRE * 100 )
#error Unsupported compiler or compiler version is too low.
#endif

//
// C++20 features
// 

/** indicates that char8_t type. */
#if UTILS4CPP_HAS_CPP2A
#   if  ( defined(UTILS4CPP_CC_MSVC) && UTILS4CPP_CC_MSVC >= 1922 ) || \
        ( defined(UTILS4CPP_CC_GNU) && UTILS4CPP_CC_GNU >= 900 )    || \
        ( defined(UTILS4CPP_CC_CLANG) && UTILS4CPP_CC_CLANG >= 700 )
#       define UTILS4CPP_HAS_CHAR8T                 1
#   endif
#else
#   define UTILS4CPP_HAS_CHAR8T                     0
#endif

/** indicates that <version> header file. */
#if UTILS4CPP_HAS_CPP2A
#   if  ( defined(UTILS4CPP_CC_MSVC) && UTILS4CPP_CC_MSVC >= 1922 ) || \
        ( defined(UTILS4CPP_CC_GNU) && UTILS4CPP_CC_GNU >= 900 )    || \
        ( defined(UTILS4CPP_CC_CLANG) && UTILS4CPP_CC_CLANG >= 700 )
#       define UTILS4CPP_HAS_VERSION_HEADER         1
#   elif __has_include(<version>)
#           define UTILS4CPP_HAS_VERSION_HEADER     1
#   endif
#else
#   define UTILS4CPP_HAS_VERSION_HEADER             0
#endif

#endif // UTILS4CPP_CORE_UCPPFEATURES_HPP
