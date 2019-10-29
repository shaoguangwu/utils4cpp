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

#ifndef UTILS4CPP_CORE_UCPPSTANDARDDETECTION_HPP
#define UTILS4CPP_CORE_UCPPSTANDARDDETECTION_HPP

/*! cplusplus-standard version number. */
#ifdef _MSVC_LANG
#   define UTILS4CPP_CPLUSPLUS      _MSVC_LANG
#else
#   define UTILS4CPP_CPLUSPLUS      __cplusplus
#endif /* _MSVC_LANG */

/*! Compiler enabled c++20 standard or not. */
#if UTILS4CPP_CPLUSPLUS > 201703L
#   define UTILS4CPP_HAS_CPP20      1
#else
#   define UTILS4CPP_HAS_CPP20      0
#endif

/*! Compiler enabled c++17 standard or not. */
#if UTILS4CPP_CPLUSPLUS > 201402L
#    define UTILS4CPP_HAS_CPP17     1
#else
#    define UTILS4CPP_HAS_CPP17     0
#endif

/*! Compiler enabled c++14 standard or not. */
#if UTILS4CPP_CPLUSPLUS > 201103L
#    define UTILS4CPP_HAS_CPP14     1
#else
#    define UTILS4CPP_HAS_CPP14     0
#endif

/*! Compiler enabled c++11 standard or not. */
#if UTILS4CPP_CPLUSPLUS > 199711L
#    define UTILS4CPP_HAS_CPP11     1
#else
#    define UTILS4CPP_HAS_CPP11     0
#endif

#if !UTILS4CPP_HAS_CPP11
#   error "utils4cpp requires enabled c++11 support."
#endif

#endif // UTILS4CPP_CORE_UCPPSTANDARDDETECTION_HPP
