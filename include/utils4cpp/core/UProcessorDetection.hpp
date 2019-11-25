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

#ifndef UTILS4CPP_CORE_UPROCESSORDETECTION_HPP
#define UTILS4CPP_CORE_UPROCESSORDETECTION_HPP

/*
    ARM family, known revisions: V5, V6, V7, V8.

    ARM is bi-endian, detect using __ARMEL__ or __ARMEB__.
*/
#if defined(__arm__) || defined(__TARGET_ARCH_ARM) || defined(_M_ARM) || defined(_M_ARM64) || defined(__aarch64__) || defined(__ARM64__)
#   if defined(__aarch64__) || defined(__ARM64__) || defined(_M_ARM64)
#       define UTILS4CPP_PROCESSOR_ARM_64
#       define UTILS4CPP_PROCESSOR_WORDSIZE 8
#   else
#       define UTILS4CPP_PROCESSOR_ARM_32
#   endif
#
#   if defined(__ARM_ARCH) && __ARM_ARCH > 1
#       define UTILS4CPP_PROCESSOR_ARM __ARM_ARCH
#   elif defined(__TARGET_ARCH_ARM) && __TARGET_ARCH_ARM > 1
#       define UTILS4CPP_PROCESSOR_ARM __TARGET_ARCH_ARM
#   elif defined(_M_ARM) && _M_ARM > 1
#       define UTILS4CPP_PROCESSOR_ARM _M_ARM
#   elif defined(__ARM64_ARCH_8__) \
        || defined(__aarch64__) \
        || defined(__ARMv8__) \
        || defined(__ARMv8_A__) \
        || defined(_M_ARM64)
#       define UTILS4CPP_PROCESSOR_ARM 8
#   elif defined(__ARM_ARCH_7__) \
        || defined(__ARM_ARCH_7A__) \
        || defined(__ARM_ARCH_7R__) \
        || defined(__ARM_ARCH_7M__) \
        || defined(__ARM_ARCH_7S__) \
        || defined(_ARM_ARCH_7) \
        || defined(__CORE_CORTEXA__)
#       define UTILS4CPP_PROCESSOR_ARM 7
#   elif defined(__ARM_ARCH_6__) \
        || defined(__ARM_ARCH_6J__) \
        || defined(__ARM_ARCH_6T2__) \
        || defined(__ARM_ARCH_6Z__) \
        || defined(__ARM_ARCH_6K__) \
        || defined(__ARM_ARCH_6ZK__) \
        || defined(__ARM_ARCH_6M__)
#       define UTILS4CPP_PROCESSOR_ARM 6
#   elif defined(__ARM_ARCH_5TEJ__) \
        || defined(__ARM_ARCH_5TE__)
#       define UTILS4CPP_PROCESSOR_ARM 5
#   else
#       define UTILS4CPP_PROCESSOR_ARM 0
#   endif
#   if UTILS4CPP_PROCESSOR_ARM >= 8
#       define UTILS4CPP_PROCESSOR_ARM_V8
#   endif
#   if UTILS4CPP_PROCESSOR_ARM >= 7
#       define UTILS4CPP_PROCESSOR_ARM_V7
#   endif
#   if UTILS4CPP_PROCESSOR_ARM >= 6
#       define UTILS4CPP_PROCESSOR_ARM_V6
#   endif
#   if UTILS4CPP_PROCESSOR_ARM >= 5
#       define UTILS4CPP_PROCESSOR_ARM_V5
#   endif

/*
    X86 family, known variants: 32- and 64-bit.

    X86 is little-endian.
*/
#elif defined(__i386) || defined(__i386__) || defined(_M_IX86)
#   define UTILS4CPP_PROCESSOR_X86_32
#   define UTILS4CPP_PROCESSOR_WORDSIZE   4

#   if defined(_M_IX86)
#       define UTILS4CPP_PROCESSOR_X86      (_M_IX86/100)
#   elif defined(__i686__) || defined(__athlon__) || defined(__SSE__) || defined(__pentiumpro__)
#       define UTILS4CPP_PROCESSOR_X86      6
#   elif defined(__i586__) || defined(__k6__) || defined(__pentium__)
#       define UTILS4CPP_PROCESSOR_X86      5
#   elif defined(__i486__) || defined(__80486__)
#       define UTILS4CPP_PROCESSOR_X86      4
#   else
#       define UTILS4CPP_PROCESSOR_X86      3
#   endif

#elif defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(_M_X64)
#   define UTILS4CPP_PROCESSOR_X86          6
#   define UTILS4CPP_PROCESSOR_X86_64
#   define UTILS4CPP_PROCESSOR_WORDSIZE     8

/*
    Itanium (IA-64) family, no revisions or variants.
*/
#elif defined(__ia64) || defined(__ia64__) || defined(_M_IA64)
#   define UTILS4CPP_PROCESSOR_IA64
#   define UTILS4CPP_PROCESSOR_WORDSIZE   8

/*
    MIPS family, known revisions: I, II, III, IV, 32, 64
*/
#elif defined(__mips) || defined(__mips__) || defined(_M_MRX000)
#   define UTILS4CPP_PROCESSOR_MIPS
#   if defined(_MIPS_ARCH_MIPS1) || (defined(__mips) && __mips - 0 >= 1)
#       define UTILS4CPP_PROCESSOR_MIPS_I
#   endif
#   if defined(_MIPS_ARCH_MIPS2) || (defined(__mips) && __mips - 0 >= 2)
#       define UTILS4CPP_PROCESSOR_MIPS_II
#   endif
#   if defined(_MIPS_ARCH_MIPS3) || (defined(__mips) && __mips - 0 >= 3)
#       define UTILS4CPP_PROCESSOR_MIPS_III
#   endif
#   if defined(_MIPS_ARCH_MIPS4) || (defined(__mips) && __mips - 0 >= 4)
#       define UTILS4CPP_PROCESSOR_MIPS_IV
#   endif
#   if defined(_MIPS_ARCH_MIPS5) || (defined(__mips) && __mips - 0 >= 5)
#       define UTILS4CPP_PROCESSOR_MIPS_V
#   endif
#   if defined(_MIPS_ARCH_MIPS32) || defined(__mips32) || (defined(__mips) && __mips - 0 >= 32)
#       define UTILS4CPP_PROCESSOR_MIPS_32
#   endif
#   if defined(_MIPS_ARCH_MIPS64) || defined(__mips64)
#       define UTILS4CPP_PROCESSOR_MIPS_64
#       define UTILS4CPP_PROCESSOR_WORDSIZE 8
#   endif

/*
    Power family, known variants: 32- and 64-bit.

    See http://en.wikipedia.org/wiki/Power_Architecture
    and http://en.wikipedia.org/wiki/File:PowerISA-evolution.svg
*/
#elif defined(__ppc__) || defined(__ppc) || defined(__powerpc__) \
      || defined(_ARCH_COM) || defined(_ARCH_PWR) || defined(_ARCH_PPC)  \
      || defined(_M_MPPC) || defined(_M_PPC)
#   define UTILS4CPP_PROCESSOR_POWER
#   if defined(__ppc64__) || defined(__powerpc64__) || defined(__64BIT__)
#       define UTILS4CPP_PROCESSOR_POWER_64
#       define UTILS4CPP_PROCESSOR_WORDSIZE 8
#   else
#       define UTILS4CPP_PROCESSOR_POWER_32
#   endif

/*
    S390 family, known variant: S390X (64-bit)
*/
#elif defined(__s390__)
#   define UTILS4CPP_PROCESSOR_S390
#   if defined(__s390x__)
#       define UTILS4CPP_PROCESSOR_S390_X
#   endif

/*
    SPARC family, optional revision: V9.
*/
#elif defined(__sparc__)
#   define UTILS4CPP_PROCESSOR_SPARC
#   if defined(__sparc_v9__)
#       define UTILS4CPP_PROCESSOR_SPARC_V9
#   endif
#   if defined(__sparc64__)
#       define UTILS4CPP_PROCESSOR_SPARC_64
#   endif

/*
    Web Assembly.
*/
#elif defined(__EMSCRIPTEN__)
#   define UTILS4CPP_PROCESSOR_WASM
#   define UTILS4CPP_PROCESSOR_WORDSIZE 8

#endif

#endif // UTILS4CPP_CORE_UPROCESSORDETECTION_HPP