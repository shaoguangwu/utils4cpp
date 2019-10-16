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

#ifndef UTILS4CPP_GEOMETRY_GEOMETRYGLOBAL_HPP
#define UTILS4CPP_GEOMETRY_GEOMETRYGLOBAL_HPP

namespace utils4cpp {
/*!
    The geometry namespace supports for geometric data structures.
    \since v0.0
*/
namespace geometry {

/*! Defines two-dimensional plane coordinate axis. */
enum Axis2D {
    Axis2DX = 0,    //!< Two-dimensional plane coordinate axis X.
    Axis2DY = 1     //!< Two-dimensional plane coordinate axis Y.
};

/*! Defines three-dimensional space coordinate axis. */
enum Axis3D {
    Axis3DX = 0,    //!< Three-dimensional space Space coordinate axis X.
    Axis3DY = 1,    //!< Three-dimensional space coordinate axis Y.
    Axis3DZ = 2     //!< Three-dimensional space coordinate axis Z.
};

} // namespace geometry
} // namespace utils4cpp


#endif // UTILS4CPP_GEOMETRY_GEOMETRYGLOBAL_HPP