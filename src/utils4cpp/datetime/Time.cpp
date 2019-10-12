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

#include <time.h>

#include <ctime>
#include <cstring>

#ifdef UTILS4CPP_OS_UNIX
#   include <sys/time.h>
#endif
#include <sys/timeb.h>

#include "utils4cpp/datetime/Time.h"

namespace utils4cpp {
namespace datetime {

enum {
    SECS_PER_DAY    = 86400,
    MSECS_PER_DAY   = 86400000,
    SECS_PER_HOUR   = 3600,
    MSECS_PER_HOUR  = 3600000,
    SECS_PER_MIN    = 60
};

void Time::makeInvalid()
{
    std::memset(&m_tm, -1, sizeof(m_tm));
}

Time::Time()
{
    makeInvalid();
}

Time::Time(int h, int m, int s, int ms, int dst)
{
    setTime(h, m, s, ms, dst);
}

int Time::hour() const
{
    return m_tm.hour;
}

int Time::minute() const
{
    return m_tm.min;
}

int Time::second() const
{
    return m_tm.sec;
}

int Time::msec() const
{
    return m_tm.msec;
}

bool Time::isValid()
{
    return isValid(m_tm.hour, m_tm.min, m_tm.sec, m_tm.msec);
}

bool Time::setTime(int h, int m, int s, int ms, int dst)
{
    if (!isValid(h,m,s,ms)) {
        makeInvalid();
        return false;
    }

    m_tm.hour = h;
    m_tm.min = m;
    m_tm.sec = s;
    m_tm.msec = ms;
    m_tm.isdst = dst;

    return true;
}

Time Time::currentLocalTime()
{
    struct timeb tb;
    ftime(&tb);
    std::tm tm;

#if defined(UTILS4CPP_OS_WIN)
    localtime_s(&tm, &tb.time);
#elif defined(UTILS4CPP_OS_UNIX)
    localtime_r(&tb.time, &tm);
#else
    tm = *std::localtime(&tb.time);
#endif

    return {tm.tm_hour, tm.tm_min, tm.tm_sec, tb.millitm, tb.dstflag};
}

Time Time::currentGmTime()
{
    struct timeb tb;
    ftime(&tb);
    std::tm tm;

#if defined(UTILS4CPP_OS_WIN)
    gmtime_s(&tm, &tb.time);
#elif defined(UTILS4CPP_OS_UNIX)
    gmtime_r(&tb.time, &tm);
#else
    tm = *std::gmtime(&tb.time);
#endif

    return {tm.tm_hour, tm.tm_min, tm.tm_sec, tb.millitm};
}

bool Time::isValid(int h, int m, int s, int ms)
{
    return (unsigned int)h < 24 && (unsigned int)m < 60 && (unsigned int)s < 60 && (unsigned int)ms < 1000;
}


} // namespace datetime
} // namespace utils4cpp