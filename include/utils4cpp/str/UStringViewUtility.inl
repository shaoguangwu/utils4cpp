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

#ifndef UTILS4CPP_STR_USTRINGVIEWUTILITY_INL
#define UTILS4CPP_STR_USTRINGVIEWUTILITY_INL

#include <ostream>

namespace utils4cpp {
namespace str {
namespace impl {
namespace detail {

template<class CharT, class Traits, class SizeT>
inline SizeT oss_put(std::basic_ostream<CharT, Traits>& os,
    const CharT* data, SizeT size)
{
    return static_cast<SizeT>(os.rdbuf()->sputn(data, size));
}

template<class CharT, class Traits, class SizeT>
inline bool oss_fill(std::basic_ostream<CharT, Traits>& os, SizeT size)
{
    CharT c = os.fill();
    CharT fill[] = { c, c, c, c, c, c, c, c };
    enum {
        chunk = sizeof fill / sizeof(CharT)
    };
    for ( ; size > chunk; size -= chunk) {
        if (oss_put(os, fill, chunk) != chunk) {
            return false;
        }
    }
    return oss_put(os, fill, size) == size;
}

template<class CharT, class Traits, class SizeT>
class oss_guard 
{
public:
    explicit oss_guard(std::basic_ostream<CharT, Traits>& os) noexcept
        : m_os(&os) { }

    ~oss_guard() noexcept(false) 
    {
        if (m_os) {
            m_os->setstate(std::basic_ostream<CharT, Traits>::badbit);
        }
    }

    void release() noexcept 
    {
        m_os = 0;
    }
private:
    oss_guard(const oss_guard&) = default;
    oss_guard& operator=(const oss_guard&) = default;
    std::basic_ostream<CharT, Traits>* m_os;
};

} // namespace detail

template<class CharT, class Traits, class SizeT>
inline std::basic_ostream<CharT, Traits>& ostream_string(std::basic_ostream<CharT, Traits>& os, 
    const CharT* data, SizeT size)
{
    using stream = std::basic_ostream<CharT, Traits>;
    oss_guard<CharT, Traits> guard(os);
    typename stream::sentry entry(os);
    if (entry) {
        SizeT width = static_cast<SizeT>(os.width());
        if (width <= size) {
            if (detail::oss_put(os, data, size) != size) {
                return os;
            }
        }
        else if ((os.flags() & stream::adjustfield) == stream::left) {
            if (detail::oss_put(os, data, size) != size ||
                !detail::oss_fill(os, width - size)) {
                return os;
            }
        }
        else if (!detail::oss_fill(os, width - size) ||
            detail::oss_put(os, data, size) != size) {
            return os;
        }
        os.width(0);
    }
    guard.release();
    return os;
}

} // namespace impl
} // namespace str
} // namespace utils4cpp

#endif // UTILS4CPP_STR_USTRINGVIEWUTILITY_INL