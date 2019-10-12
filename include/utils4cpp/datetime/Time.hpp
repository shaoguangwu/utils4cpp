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

#ifndef UTILS4CPP_DATETIME_TIME_HPP
#define UTILS4CPP_DATETIME_TIME_HPP

#include "utils4cpp/core/Core.hpp"

namespace utils4cpp {
namespace datetime {

class UTILS4CPP_EXPORT Time
{
    struct tms
    {
        int hour;       //!< hours since midnight - [0, 23]
        int min;        //!< minutes after the hour - [0, 59]
        int sec;        //!< seconds after the minute - [0, 60], including leap second
        int msec;       //!< milliseconds sfter the second - [0, 999]
        int isdst;      //!< daylight savings time flag. The value is positive if DST is in effect, zero if not and negative if no information is available
    };
    tms m_tm;

public:
    Time();
    Time(int h, int m, int s, int ms = 0, int dst = -1);

    int hour() const;
    int minute() const;
    int second() const;
    int msec() const;

    bool isValid();

    bool setTime(int h, int m, int s, int ms = 0, int dst = -1);

    static Time currentLocalTime();
    static Time currentGmTime();

    static bool isValid(int h, int m, int s, int ms = 0);

private:
    void makeInvalid();

    // int m_hour;
    // int m_min;
    // int m_sec;
    // int m_msec;
};

} // namespace datetime
} // namespace utils4cpp

#endif // UTILS4CPP_DATETIME_TIME_HPP