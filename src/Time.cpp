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
#include <cstdio>
#include <iomanip>

#ifdef UTILS4CPP_OS_UNIX
#   include <sys/time.h>
#endif
#include <sys/timeb.h>

#include "utils4cpp/datetime/Time.hpp"

namespace utils4cpp {
namespace datetime {

enum {
    SECS_PER_DAY    = 86400,
    MSECS_PER_DAY   = 86400000,
    SECS_PER_HOUR   = 3600,
    MSECS_PER_HOUR  = 3600000,
    SECS_PER_MIN    = 60,
    MSECS_PER_MIN   = 60000
};

Time::Time()
    : m_msecs(NullTime), m_isdst(-1)
{
}

Time::Time(milliseconds_t msecs, int dst)
    : m_msecs(msecs), m_isdst(dst)
{
}

Time::Time(int h, int m, int s, int ms, int dst)
{
    setTime(h, m, s, ms, dst);
}

bool Time::isNull() const
{
    return m_msecs == NullTime;
}

bool Time::isValid() const
{
    return isValid(m_msecs);
}

bool Time::isValid(milliseconds_t msecs)
{
    return msecs >= 0 && msecs < MSECS_PER_DAY;
}

bool Time::isValid(int h, int m, int s, int ms)
{
    return (unsigned int)h < 24 && (unsigned int)m < 60 && (unsigned int)s < 60 && (unsigned int)ms < 1000;
}

int Time::hour() const
{
    if (!isValid())
        return -1;

    return m_msecs / MSECS_PER_HOUR;
}

int Time::minute() const
{
    if (!isValid())
        return -1;

    return (m_msecs % MSECS_PER_HOUR) / MSECS_PER_MIN;
}

int Time::second() const
{
    if (!isValid())
        return -1;

    return (m_msecs / 1000) % SECS_PER_MIN;
}

int Time::msec() const
{
    if (!isValid())
        return -1;

    return m_msecs % 1000;
}

bool Time::setTime(int h, int m, int s, int ms, int dst)
{
    m_isdst = dst;
    if (!isValid(h, m, s, ms)) {
        m_msecs = NullTime;    // make this invalid
        return false;
    }
    m_msecs = (h * SECS_PER_HOUR + m * SECS_PER_MIN + s) * 1000 + ms;
    return true;
}

Time Time::addSecs(int secs) const
{
    secs %= SECS_PER_DAY;
    return addMSecs(secs * 1000);
}
int Time::secsTo(const Time& t) const
{
    if (!isValid() || !t.isValid())
        return 0;

    // Truncate milliseconds as we do not want to consider them.
    return (t.toMilliseconds() / 1000) - (toMilliseconds() / 1000);
}
Time Time::addMSecs(milliseconds_t ms) const
{
    Time result;
    if (isValid()) {
        if (ms < 0) {
            // %,/ not well-defined for -ve, so always work with +ve.
            int negdays = (MSECS_PER_DAY - ms) / MSECS_PER_DAY;
            result.m_msecs = (toMilliseconds() + ms + negdays * MSECS_PER_DAY) % MSECS_PER_DAY;
        } else {
            result.m_msecs = (toMilliseconds() + ms) % MSECS_PER_DAY;
        }
    }
    return result;
}
int Time::msecsTo(const Time& t) const
{
    if (!isValid() || !t.isValid())
        return 0;
    return t.toMilliseconds() - toMilliseconds();
}

std::string Time::toString(const char* format) const
{
    std::size_t buff_size = 1024;
    std::string result;
    result.resize(buff_size);

    std::tm tm{ 0 };
    tm.tm_hour = hour();
    tm.tm_min = minute();
    tm.tm_sec = second();
    tm.tm_isdst = m_isdst;
    std::strftime(&result.front(), buff_size, format, &tm);

    return result;
}

std::wstring Time::toWString(const wchar_t* format) const
{
    std::size_t buff_size = 1024;
    std::wstring result;
    result.resize(buff_size);

    std::tm tm{ 0 };
    tm.tm_hour = hour();
    tm.tm_min = minute();
    tm.tm_sec = second();
    tm.tm_isdst = m_isdst;
    std::wcsftime(&result.front(), buff_size, format, &tm);

    return result;
}

std::string Time::sprintfTime(const char* format) const
{
    
}

std::wstring Time::sprintfTime(const wchar_t* format) const
{

}

bool Time::operator==(const Time& other) const
{
    return m_msecs == other.m_msecs;
}

bool Time::operator!=(const Time& other) const
{
    return m_msecs != other.m_msecs;
}
bool Time::operator< (const Time& other) const
{
    return m_msecs < other.m_msecs;
}
bool Time::operator<=(const Time& other) const
{
    return m_msecs <= other.m_msecs;
}
bool Time::operator> (const Time& other) const
{
    return m_msecs > other.m_msecs;
}
bool Time::operator>=(const Time& other) const
{
    return m_msecs >= other.m_msecs;
}

/*!
    Returns \c true if daylight savings time flag is same to \a other's daylight savings time flag,
    otherwise returns \c false.

    \sa dst()
*/
bool Time::isDstFlagEqual(const Time& other) const
{
    if (m_isdst < 0) {
        return other.m_isdst < 0;
    } 
    else if (m_isdst == 0) {
        return other.m_isdst == 0;
    }
    else {
        return other.m_isdst > 0;
    }
}

Time Time::fromMilliseconds(milliseconds_t ms, int dst)
{
    return Time(ms, dst);
}

inline Time::milliseconds_t Time::toMilliseconds() const
{
    return m_msecs == NullTime ? 0 : m_msecs;
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

    return { tm.tm_hour, tm.tm_min, tm.tm_sec, tb.millitm, tb.dstflag };
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

    return { tm.tm_hour, tm.tm_min, tm.tm_sec, tb.millitm, tb.dstflag };
}

/*!
    Writes the \a time to stream \a out.
*/
UTILS4CPP_EXPORT std::ostream& operator<<(std::ostream& out, const Time& time)
{
    out << "Time(\""
        << std::setw(2) << std::setfill('0') << time.hour() << ":"
        << std::setw(2) << std::setfill('0') << time.minute() << ":"
        << std::setw(2) << std::setfill('0') << time.second() << "."
        << std::setw(2) << std::setfill('0') << time.msec() << ")\"";
    return out;
}


} // namespace datetime
} // namespace utils4cpp