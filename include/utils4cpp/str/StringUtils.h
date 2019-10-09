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

#ifndef UTILS4CPP_STR_STRINGUTILS_H_
#define UTILS4CPP_STR_STRINGUTILS_H_

#include <vector>

#include "utils4cpp/str/StringToNumber.h"

namespace utils4cpp {
namespace str {

/*!
    \enum Indicates case sensitive or not.
*/
enum CaseSensitivity {
    CaseInsensitive,                ///< Case insensitive.  (no)
    CaseSensitive                   ///< Case sensitive.    (yes)
};

void replaceString(std::string& str, const std::string& before, const std::string& after);
void replaceString(std::wstring& str, const std::wstring& before, const std::wstring& after);

std::vector<std::string> splitString(const std::string& str, char delim);
std::vector<std::string> splitString(const std::string& str, const std::string& delim);
std::vector<std::wstring> splitString(const std::wstring& str, wchar_t delim);
std::vector<std::wstring> splitString(const std::wstring& str, const std::wstring& delim);

std::string joinString(const std::vector<std::string>& strs, char delim);
std::string joinString(const std::vector<std::string>& strs, const std::string& delim);
std::wstring joinString(const std::vector<std::wstring>& strs, char delim);
std::wstring joinString(const std::vector<std::wstring>& strs, const std::wstring& delim);

std::string toLower(const std::string& str);
std::string toUpper(const std::string& str);
std::wstring toLower(const std::wstring& str);
std::wstring toUpper(const std::wstring& str);

std::string capitalized(const std::string& str);
std::wstring capitalized(const std::wstring& str);
std::string capitalizedWords(const std::string& str);
std::wstring capitalizedWords(const std::wstring& str);
std::string unCapitalizedWords(const std::string& str);
std::wstring unCapitalizedWords(const std::wstring& str);

std::wstring toWstring(const std::string& str);
std::string toString(const std::wstring& wstr);

template<typename DstT, class StringT>
DstT toNumber(const StringT& str, std::size_t* pos, int base, bool noexception = false);

template<typename DstT, class StringT>
DstT toNumber(const StringT& str, std::size_t* pos, bool noexception = false);

template<typename DstT, class StringT>
DstT toNumber(const StringT& str, bool noexception = false);

} // namespace str
} // namespace utils4cpp

#endif // UTILS4CPP_STR_STRINGUTILS_H_