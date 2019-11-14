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

#ifndef UTILS4CPP_STR_UCASECONVERSION_HPP
#define UTILS4CPP_STR_UCASECONVERSION_HPP

#include <locale>

namespace utils4cpp {
namespace str {

//
//  case conversion functors
//

/**
    \class ToLowerF
    \brief a tolower functor.

    \sa ToUpperF
*/
template<class CharT>
struct ToLowerF
{
    using argument_type = CharT;
    using result_type = CharT;

    ToLowerF(const std::locale& loc)
        : m_loc(&loc) {}

    result_type operator()(CharT ch) const
    {
        return std::tolower(ch, *m_loc);
    }
private:
    const std::locale* m_loc;
};

/**
    \class ToLowerF
    \brief a tolower functor.

    \sa ToLowerF
*/
template<class CharT>
struct ToUpperF
{
    using argument_type = CharT;
    using result_type = CharT;

    ToLowerF(const std::locale& loc)
        : m_loc(&loc) {}

    result_type operator()(CharT ch) const
    {
        return std::toupper(ch, *m_loc);
    }
private:
    const std::locale* m_loc;
};

} // namespace str
} // namespace utils4cpp

#endif // UTILS4CPP_STR_UCASECONVERSION_HPP