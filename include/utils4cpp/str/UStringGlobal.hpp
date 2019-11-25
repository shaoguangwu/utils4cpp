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

#ifndef UTILS4CPP_STR_USTRINGGLOBAL_HPP
#define UTILS4CPP_STR_USTRINGGLOBAL_HPP

#include <cwchar>
#include <cuchar>

#include <locale>
#include <string>

#include "utils4cpp/core/UCore.hpp"
#include "utils4cpp/core/UTypeTraits.hpp"

namespace utils4cpp::str {

/*! Indicates case sensitive or not. */
enum UCaseSensitivity {
    UCaseInsensitive,                ///< Case insensitive.  (no)
    UCaseSensitive                   ///< Case sensitive.    (yes)
};

/*!
    Swap char \a a and \a b with no intermediate variable.
*/
template<typename CharT>
inline void uSwapChar(CharT &a, CharT& b) noexcept
{
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

namespace detail {

template<class StringT, class CharT>
using _is_std_basic_string = u_and<
    std::is_same<typename StringT::value_type, CharT>,
    std::is_convertible<const StringT&,
    std::basic_string<CharT, typename StringT::traits_type, typename StringT::allocator_type>>,
    u_not<std::is_convertible<const StringT&, const CharT *>>>;

template<class StringT, class CharT>
struct _std_basic_string_traits
{
    using is = _is_std_basic_string<StringT, CharT>;
    using type = typename std::enable_if_t<is::value, StringT>;
};

} // namespace utils4cpp::str::detail

//
// std_basic_string_traits
//

template<class StringT>
using std_basic_string_traits = detail::_std_basic_string_traits<StringT, typename StringT::value_type>;

template<class StringT>
using is_std_basic_string = typename std_basic_string_traits<StringT>::is;

template<class StringT>
inline constexpr bool is_std_basic_string_v = is_std_basic_string<StringT>::value;

template<class StringT>
using if_std_basic_string = typename std_basic_string_traits<StringT>::type;

//
// std_string_traits
//

template<class StringT>
using std_string_traits = detail::_std_basic_string_traits<StringT, typename std::string::value_type>;

template<class StringT>
using is_std_string = typename std_string_traits<StringT>::is;

template<class StringT>
inline constexpr bool is_std_string_v = is_std_string<StringT>::value;

template<class StringT>
using if_std_string = typename std_string_traits<StringT>::type;

//
// std_wstring_traits
//

template<class StringT>
using std_wstring_traits = detail::_std_basic_string_traits<StringT, typename std::wstring::value_type>;

template<class StringT>
using is_std_wstring = typename std_wstring_traits<StringT>::is;

template<class StringT>
inline constexpr bool is_std_wstring_v = is_std_wstring<StringT>::value;

template<class StringT>
using if_std_wstring = typename std_wstring_traits<StringT>::type;

//
// std_u16string_traits
//

template<class StringT>
using std_u16string_traits = detail::_std_basic_string_traits<StringT, typename std::u16string::value_type>;

template<class StringT>
using is_std_u16string = typename std_u16string_traits<StringT>::is;

template<class StringT>
inline constexpr bool is_std_u16string_v = is_std_u16string<StringT>::value;

template<class StringT>
using if_std_u16string = typename std_u16string_traits<StringT>::type;

//
// std_u32string_traits
//

template<class StringT>
using std_u32string_traits = detail::_std_basic_string_traits<StringT, typename std::u32string::value_type>;

template<class StringT>
using is_std_u32string = typename std_u32string_traits<StringT>::is;

template<class StringT>
inline constexpr bool is_std_u32string_v = is_std_u32string<StringT>::value;

template<class StringT>
using if_std_u32string = typename std_u32string_traits<StringT>::type;

#if UTILS4CPP_HAS_U8STRING

//
// std_u8string_traits
//

template<class StringT>
using std_u8string_traits = detail::_std_basic_string_traits<StringT, typename std::u8string::value_type>;

template<class StringT>
using is_std_u8string = typename std_u8string_traits<StringT>::is;

template<class StringT>
inline constexpr bool is_std_u8string_v = is_std_u8string<StringT>::value;

template<class StringT>
using if_std_u8string = typename std_u8string_traits<StringT>::type;

#endif // UTILS4CPP_HAS_U8STRING

//
// std_string_or_wstring_traits
//

template<class StringT>
using is_std_string_or_wstring = u_or<is_std_string<StringT>, is_std_wstring<StringT>>;

template<class StringT>
inline constexpr bool is_std_string_or_wstring_v = is_std_string_or_wstring<StringT>::value;

template<class StringT>
using if_std_string_or_wstring = std::enable_if_t<is_std_string_or_wstring_v<StringT>, StringT>;

} // namespace utils4cpp::global

#endif // UTILS4CPP_STR_USTRINGGLOBAL_HPP