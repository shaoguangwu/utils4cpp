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

#ifndef UTILS4CPP_CORE_UVERSION_HPP
#define UTILS4CPP_CORE_UVERSION_HPP

/*! The major version of utils4cpp library. */
#define UTILS4CPP_VERSION_MAJOR         0
/*! The minor version of utils4cpp library. */
#define UTILS4CPP_VERSION_MINOR         0
/*! The revision of utils4cpp library. */
#define UTILS4CPP_VERSION_REVISION      0
/*! The build status of utils4cpp library. */
#define UTILS4CPP_VERSION_STATUS        "Building"

/*! Transform expression \a __A to string format. */
#define UTILS4CPP_AUX_STR_EXP(__A)      #__A
/*! Transform \a __A to string format. */
#define UTILS4CPP_AUX_STR(__A)          UTILS4CPP_AUX_STR_EXP(__A)

/*! Transform expression \a __A to wide string format. */
#define UTILS4CPP_AUX_WSTR_EXP(__A)     L ## #__A
/*! Transform \a __A to wide string format. */
#define UTILS4CPP_AUX_WSTR(__A)         UTILS4CPP_AUX_WSTR_EXP(__A)

/*! Transform expression \a __A to u16string format. */
#define UTILS4CPP_AUX_U16STR_EXP(__A)   u ## #__A
/*! Transform \a __A to u16string format. */
#define UTILS4CPP_AUX_U16STR(__A)       UTILS4CPP_AUX_U16STR_EXP(__A)

/*! Transform expression \a __A to u32string format. */
#define UTILS4CPP_AUX_U32STR_EXP(__A)   U ## #__A
/*! Transform \a __A to u32string format. */
#define UTILS4CPP_AUX_U32STR(__A)       UTILS4CPP_AUX_U32STR_EXP(__A)

/*! The version of utils4cpp library in string format. */
#define UTILS4CPP_VERSION_STR           UTILS4CPP_AUX_STR(UTILS4CPP_VERSION_MAJOR) "."      \
                                        UTILS4CPP_AUX_STR(UTILS4CPP_VERSION_MINOR) "."      \
                                        UTILS4CPP_AUX_STR(UTILS4CPP_VERSION_REVISION) " "   \
                                        UTILS4CPP_VERSION_STATUS

/*! The version of utils4cpp library in wide string format. */
#define UTILS4CPP_VERSION_WSTR          UTILS4CPP_AUX_WSTR(UTILS4CPP_VERSION_MAJOR) "."     \
                                        UTILS4CPP_AUX_WSTR(UTILS4CPP_VERSION_MINOR) "."     \
                                        UTILS4CPP_AUX_WSTR(UTILS4CPP_VERSION_REVISION) " "  \
                                        UTILS4CPP_VERSION_STATUS

/*! The version of utils4cpp library in u16string format. */
#define UTILS4CPP_VERSION_U16STR        UTILS4CPP_AUX_U16STR(UTILS4CPP_VERSION_MAJOR) "."     \
                                        UTILS4CPP_AUX_U16STR(UTILS4CPP_VERSION_MINOR) "."     \
                                        UTILS4CPP_AUX_U16STR(UTILS4CPP_VERSION_REVISION) " "  \
                                        UTILS4CPP_VERSION_STATUS

/*! The version of utils4cpp library in u32string format. */
#define UTILS4CPP_VERSION_U32STR        UTILS4CPP_AUX_U32STR(UTILS4CPP_VERSION_MAJOR) "."     \
                                        UTILS4CPP_AUX_U32STR(UTILS4CPP_VERSION_MINOR) "."     \
                                        UTILS4CPP_AUX_U32STR(UTILS4CPP_VERSION_REVISION) " "  \
                                        UTILS4CPP_VERSION_STATUS

#endif // UTILS4CPP_CORE_UVERSION_HPP