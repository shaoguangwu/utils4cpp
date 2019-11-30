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

#ifndef UTILS4CPP_CORE_UCOMPILERDETECTION_HPP
#define UTILS4CPP_CORE_UCOMPILERDETECTION_HPP

/**
    The compiler, must mbe one of: (UTILS4CPP_CC_x)

    \li SYM     - Digital Mars C/C++ (used to be Symantec C++)
    \li MSVC    - Microsoft Visual C/C++, Intel C++ for Windows
    \li CLANG   - C++ front-end for the LLVM compiler
    \li INTEL   - Intel C++ for Linux, Intel C++ for Windows
    \li BOR     - Borland/Turbo C++
    \li WAT     - Watcom C++
    \li RVCT    - ARM Realview Compiler Suite
    \li GNU     - GNU C++
    \li MINGW   - MinGW Compiler for Windows (_GNU)
    \li MINGW64 - MinGW64 Compiler for Windows (_GNU)
    \li PGI     - Portland Group C++
    \li EDG     - Edison Design Group C++
    \li COMEAU  - Comeau C++
    \li KAI     - KAI C++
    \li GHS     - Green Hills Optimizing C++ Compilers
    \li USLC    - SCO OUDK and UDK
    \li OC      - CenterLine C++
    \li CDS     - Reliant C++
    \li MIPS    - MIPSpro C++
    \li HIGHC   - MetaWare High C/C++
    \li SUN     - Forte Developer, or Sun Studio C++
    \li HPACC   - HP aC++
*/

#if defined(__DMC__) || defined(__SC__)
#   define UTILS4CPP_CC_SYM

#elif defined(_MSC_VER)
#   define UTILS4CPP_CC_MSVC        (_MSC_VER)
#   ifdef __clang__
#       define UTILS4CPP_CC_CLANG  ((__clang_major__ * 100) + __clang_minor__)
#   endif // __clang__
#   ifdef __INTEL_COMPILER
#       define UTILS4CPP_CC_INTEL   __INTEL_COMPILER
#   endif // __INTEL_COMPILER

#elif defined(__BORLANDC__) || defined(__TURBOC__)
#   define UTILS4CPP_CC_BOR

#elif defined(__WATCOMC__)
#   define UTILS4CPP_CC_WAT

#elif defined(__ARMCC__) || defined(__CC_ARM)
#   define UTILS4CPP_CC_RVCT

#elif defined(__GNUC__)
#   define UTILS4CPP_CC_GNU    ((__GNUC__ * 100) + __GNUC_MINOR__)
#   if defined(__MINGW64__)
#       define UTILS4CPP_CC_MINGW64 (__MINGW64_VERSION_MAJOR * 100) + __MINGW64_VERSION_MINOR)
#   endif // __MINGW64__
#   if defined(__MINGW32__)
#       define UTILS4CPP_CC_MINGW ((__MINGW32_MAJOR_VERSION * 100) + __MINGW32_MINOR_VERSION)
#   endif // __MINGW32__
#   if defined(__INTEL_COMPILER)
/* Intel C++ also masquerades as GCC */
#       define UTILS4CPP_CC_INTEL   __INTEL_COMPILER
#       if defined(__clang__)
/* Intel C++ masquerades as Clang masquerading as GCC */
#           define UTILS4CPP_CC_CLANG ((__clang_major__ * 100) + __clang_minor__)
#       endif // __clang__
#   endif // __INTEL_COMPILER

#elif defined(__PGI)
#   define UTILS4CPP_CC_PGI

#elif defined(__EDG) || defined(__EDG__)
#   define UTILS4CPP_CC_EDG
#   if defined(__COMO__)
/* The Comeau compiler is based on EDG and does define __EDG__ */
#       define UTILS4CPP_COMEAU
#   elif defined(__KCC)
#        define UTILS4CPP_CC_KAI
#   elif defined(__INTEL_COMPILER)
#       define UTILS4CPP_CC_INTEL   (__INTEL_COMPILER)
#   elif defined(__ghs)
#       define UTILS4CPP_CC_GHS
#   elif defined(__USLC__) && defined(__SCO_VERSION__)
#       define UTILS4CPP_CC_USLC
#   elif defined(CENTERLINE_CLPP) || defined(OBJECTCENTER)
#       define UTILS4CPP_CC_OC
#   elif defined(sinix)
#       define UTILS4CPP_CC_CDS
#   elif defined(__sgi)
#       define UTILS4CPP_CC_MIPS
#   endif

#elif defined(_DIAB_TOOL)
#   define UTILS4CPP_CC_DIAB

#elif defined(__HIGHC__)
#   define UTILS4CPP_CC_HIGHC

#elif defined(__SUNPRO_CC) || defined(__SUNPRO_C)
#   define UTILS4CPP_CC_SUN

#elif defined(sinix)
#   define UTILS4CPP_CC_EDG
#   define UTILS4CPP_CC_CDS

#elif defined(__HP_aCC)
#   define UTILS4CPP_CC_HPACC

#endif

#endif // UTILS4CPP_CORE_UCOMPILERDETECTION_HPP