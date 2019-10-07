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

#ifndef UTILS4CPP_CORE_SYSTEMDETECTION_H_
#define UTILS4CPP_CORE_SYSTEMDETECTION_H_

/*
   The operating system, must be one of: (UTILS4CPP_OS_x)

     DARWIN   - Any Darwin system (macOS, iOS, watchOS, tvOS)
     MACOS    - macOS
     IOS      - iOS
     WATCHOS  - watchOS
     TVOS     - tvOS
     WIN32    - Win32 (Windows and Windows Server)
     WINRT    - WinRT (Windows Runtime)
     CYGWIN   - Cygwin
     SOLARIS  - Sun Solaris
     HPUX     - HP-UX
     LINUX    - Linux [has variants]
     FREEBSD  - FreeBSD [has variants]
     NETBSD   - NetBSD
     OPENBSD  - OpenBSD
     INTERIX  - Interix
     AIX      - AIX
     HURD     - GNU Hurd
     QNX      - QNX [has variants]
     QNX6     - QNX RTP 6.1
     LYNX     - LynxOS
     BSD4     - Any BSD 4.4 system
     UNIX     - Any UNIX BSD/SYSV system
     ANDROID  - Android platform
     HAIKU    - Haiku

   The following operating systems have variants:
     LINUX    - both UTILS4CPP_OS_LINUX and UTILS4CPP_OS_ANDROID are defined when building for Android
              - only UTILS4CPP_OS_LINUX is defined if building for other Linux systems
     FREEBSD  - UTILS4CPP_OS_FREEBSD is defined only when building for FreeBSD with a BSD userland
              - UTILS4CPP_OS_FREEBSD_KERNEL is always defined on FreeBSD, even if the userland is from GNU
*/

#if defined(__APPLE__) && (defined(__GNUC__) || defined(__xlC__) || defined(__xlc__))
#
#   include <TargetConditionals.h>
#
#   if defined(TARGET_OS_MAC) && TARGET_OS_MAC
#       define UTILS4CPP_OS_DARWIN
#       define UTILS4CPP_OS_BSD4
#
#       ifdef __LP64__
#           define UTILS4CPP_OS_DARWIN64
#       else
#           define UTILS4CPP_OS_DARWIN32
#       endif /* __LP64__ */
#
#       if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#           define UTILS4CPP_PLATFORM_UIKIT
#           if defined(TARGET_OS_WATCH) && TARGET_OS_WATCH
#               define UTILS4CPP_OS_WATCHOS
#           elif defined(TARGET_OS_TV) && TARGET_OS_TV
#               define UTILS4CPP_OS_TVOS
#           else
#               define UTILS4CPP_OS_IOS
#           endif
#       else
#          define UTILS4CPP_OS_MACOS
#       endif
#
#   else
#       error "Unknown Apple platform."
#   endif
#
#elif defined(__ANDROID__) || defined(ANDROID)
#   define UTILS4CPP_OS_ANDROID
#   define UTILS4CPP_OS_LINUX
#
#elif defined(__CYGWIN__)
#   define UTILS4CPP_OS_CYGWIN
#
#elif !defined(SAG_COM) && (!defined(WINAPI_FAMILY) || WINAPI_FAMILY==WINAPI_FAMILY_DESKTOP_APP) && (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))
#   define UTILS4CPP_OS_WIN32
#   define UTILS4CPP_OS_WIN64
#
#elif !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
#   if defined(WINAPI_FAMILY)
#       ifndef WINAPI_FAMILY_PC_APP
#           define WINAPI_FAMILY_PC_APP WINAPI_FAMILY_APP
#       endif
#       if defined(WINAPI_FAMILY_PHONE_APP) && WINAPI_FAMILY==WINAPI_FAMILY_PHONE_APP
#           define UTILS4CPP_OS_WINRT
#       elif WINAPI_FAMILY==WINAPI_FAMILY_PC_APP
#           define UTILS4CPP_OS_WINRT
#       else
#           define UTILS4CPP_OS_WIN32
#       endif
#   else
#       define UTILS4CPP_OS_WIN32
#  endif
#
#elif defined(__sun) || defined(sun)
#   define UTILS4CPP_OS_SOLARIS
#
#elif defined(hpux) || defined(__hpux)
#   define UTILS4CPP_OS_HPUX
#
#elif defined(__native_client__)
#   define UTILS4CPP_OS_NACL
#
#elif defined(__EMSCRIPTEN__)
#   define UTILS4CPP_OS_WASM
#
#elif defined(__linux__) || defined(__linux)
#   define UTILS4CPP_OS_LINUX
#
#elif defined(__FreeBSD__) || defined(__DragonFly__) || defined(__FreeBSD_kernel__)
#   ifndef __FreeBSD_kernel__
#       define UTILS4CPP_OS_FREEBSD
#   endif
#   define UTILS4CPP_OS_FREEBSD_KERNEL
#   define UTILS4CPP_OS_BSD4
#
#elif defined(__NetBSD__)
#   define UTILS4CPP_OS_NETBSD
#   define UTILS4CPP_OS_BSD4
#
#elif defined(__OpenBSD__)
#   define UTILS4CPP_OS_OPENBSD
#   define UTILS4CPP_OS_BSD4
#
#elif defined(__INTERIX)
#   define UTILS4CPP_OS_INTERIX
#   define UTILS4CPP_OS_BSD4
#
#elif defined(_AIX)
#   define UTILS4CPP_OS_AIX
#
#elif defined(__Lynx__)
#   define UTILS4CPP_OS_LYNX
#
#elif defined(__GNU__)
#   define UTILS4CPP_OS_HURD
#
#elif defined(__QNXNTO__)
#   define UTILS4CPP_OS_QNX
#
#elif defined(__INTEGRITY)
#   define UTILS4CPP_OS_INTEGRITY
#
#elif defined(VXWORKS)
#   define UTILS4CPP_OS_VXWORKS
#
#elif defined(__HAIKU__)
#   define UTILS4CPP_OS_HAIKU
#
#elif defined(__MAKEDEPEND__)
#
#else
#   error "Unknown OS."
#endif




#if defined(UTILS4CPP_OS_WIN32) || defined(UTILS4CPP_OS_WIN64) || defined(UTILS4CPP_OS_WINRT)
#   define UTILS4CPP_OS_WIN
#endif /* UTILS4CPP_OS_WIN32 || UTILS4CPP_OS_WIN64 || UTILS4CPP_OS_WINRT */

#if defined(UTILS4CPP_OS_WIN)
#   undef UTILS4CPP_OS_UNIX
#elif !defined(UTILS4CPP_OS_UNIX)
#   define UTILS4CPP_OS_UNIX
#endif /* UTILS4CPP_OS_WIN */

// Compatibility synonyms
#ifdef UTILS4CPP_OS_DARWIN
#   define UTILS4CPP_OS_MAC
#endif /* UTILS4CPP_OS_DARWIN */

#ifdef UTILS4CPP_OS_DARWIN32
#   define UTILS4CPP_OS_MAC32
#endif /* UTILS4CPP_OS_DARWIN32 */

#ifdef UTILS4CPP_OS_DARWIN64
#   define UTILS4CPP_OS_MAC64
#endif /* UTILS4CPP_OS_DARWIN64 */

#ifdef UTILS4CPP_OS_MACOS
#   define UTILS4CPP_OS_MACX
#   define UTILS4CPP_OS_OSX
#endif /* UTILS4CPP_OS_MACOS */

#ifdef UTILS4CPP_OS_DARWIN
#
#   include <Availability.h>
#   include <AvailabilityMacros.h>
#
#   ifdef UTILS4CPP_OS_MACOS
#       if !defined(__MAC_OS_X_VERSION_MIN_REQUIRED) || __MAC_OS_X_VERSION_MIN_REQUIRED < __MAC_10_6
#           undef __MAC_OS_X_VERSION_MIN_REQUIRED
#           define __MAC_OS_X_VERSION_MIN_REQUIRED __MAC_10_6
#       endif
#       if !defined(MAC_OS_X_VERSION_MIN_REQUIRED) || MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_6
#           undef MAC_OS_X_VERSION_MIN_REQUIRED
#           define MAC_OS_X_VERSION_MIN_REQUIRED MAC_OS_X_VERSION_10_6
#       endif
#   endif
#
#   if !defined(__MAC_10_11)
#       define __MAC_10_11 101100
#   endif
#   if !defined(__MAC_10_12)
#       define __MAC_10_12 101200
#   endif
#   if !defined(__MAC_10_13)
#       define __MAC_10_13 101300
#   endif
#   if !defined(__MAC_10_14)
#       define __MAC_10_14 101400
#   endif
#   if !defined(MAC_OS_X_VERSION_10_11)
#       define MAC_OS_X_VERSION_10_11 101100
#   endif
#   if !defined(MAC_OS_X_VERSION_10_12)
#       define MAC_OS_X_VERSION_10_12 101200
#   endif
#   if !defined(MAC_OS_X_VERSION_10_13)
#       define MAC_OS_X_VERSION_10_13 101300
#   endif
#   if !defined(MAC_OS_X_VERSION_10_14)
#       define MAC_OS_X_VERSION_10_14 101400
#   endif
#
#   if !defined(__IPHONE_10_0)
#       define __IPHONE_10_0 100000
#   endif
#   if !defined(__IPHONE_10_1)
#       define __IPHONE_10_1 100100
#   endif
#   if !defined(__IPHONE_10_2)
#       define __IPHONE_10_2 100200
#   endif
#   if !defined(__IPHONE_10_3)
#       define __IPHONE_10_3 100300
#   endif
#   if !defined(__IPHONE_11_0)
#       define __IPHONE_11_0 110000
#   endif
#   if !defined(__IPHONE_12_0)
#       define __IPHONE_12_0 120000
#   endif
#endif /* UTILS4CPP_OS_DARWIN */

#ifdef __LSB_VERSION__
#   ifndef UTILS4CPP_LINUXBASE
#       define UTILS4CPP_LINUXBASE
#   endif
#endif /* __LSB_VERSION__ */

#endif // UTILS4CPP_CORE_SYSTEMDETECTION_H_