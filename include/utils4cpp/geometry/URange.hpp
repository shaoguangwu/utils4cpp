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

#ifndef UTILS4CPP_GEOMETRY_URANGE_HPP
#define UTILS4CPP_GEOMETRY_URANGE_HPP

namespace utils4cpp {
namespace geometry {

template<class ElemT>
class URange
{
public:
    using value_type = ElemT;

    UInterval()
    {}
    UInterval(const ElemT& lower, const ElemT& upper)
    {}

    ElemT& lower() noexcept { return m_lowerBounds; }
    ElemT& upper() noexcept { return m_upperBounds; }
    const ElemT& lower() const noexcept { return m_lowerBounds; }
    const ElemT& upper() const noexcept { return m_upperBounds; }
    const ElemT& constLower() const noexcept { return m_lowerBounds; }
    const ElemT& constUpper() const noexcept { return m_upperBounds; }

private:
    ElemT m_lowerBounds;    //*< The lower bounds of this interval.
    ElemT m_upperBounds;    //*< The upper Bounds of this interval.
};

} // namespace geometry
} // namespace utils4cpp

#endif // UTILS4CPP_GEOMETRY_URANGE_HPP