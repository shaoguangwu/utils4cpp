/************************************************************************************
**
**  BSD 3-Clause License
**
**  Copyright (c) 2019, shaoguang
**  All rights reserved.
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

#ifndef UTILS4CPP_CORE_CPPSTANDARDDETECTION_H_
#define UTILS4CPP_CORE_CPPSTANDARDDETECTION_H_

#ifdef _MSVC_LANG

#   if _MSVC_LANG > 201703L
#       define UTILS4CPP_CPP20_SUPPORT
#   endif

#   if _MSVC_LANG > 201402L
#       define UTILS4CPP_CPP17STANDARD
#   endif

#   if _MSVC_LANG > 201103L
#       define UTILS4CPP_CPP14STANDARD
#   endif

#   if _MSVC_LANG > 199711L
#       define UTILS4CPP_CPP11STANDARD
#   endif

#else // !_MSVC_LANG

#   if __cplusplus > 201703L
#       define UTILS4CPP_CPP17STANDARD
#   endif

#   if __cplusplus > 201402L
#       define UTILS4CPP_CPP17STANDARD
#   endif

#   if __cplusplus > 201103L
#       define UTILS4CPP_CPP14STANDARD
#   endif

#   if __cplusplus > 199711L
#       define UTILS4CPP_CPP11STANDARD
#   endif

#endif // _MSVC_LANG

#endif // UTILS4CPP_CORE_CPPSTANDARDDETECTION_H_