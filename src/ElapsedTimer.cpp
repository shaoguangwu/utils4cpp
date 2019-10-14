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

#include "utils4cpp/datetime/ElapsedTimer.hpp"

namespace utils4cpp {
namespace datetime {

/*!
    \var ElapsedTimer::chrono_clock_type

    The type of std::chrono clock.
*/

/*!
    \var ElapsedTimer::chrono_days

    std::chrono::days defines in c++20 standard, define it before that.
*/

/*!
    \var ElapsedTimer::elapsed_time_floating_t

    The floating type of elapsed time.
*/

/*!
    \fn ElapsedTimer::ElapsedTimer()

    Constructs a elapsed timer, and start timing.

    \sa reset()
*/
ElapsedTimer::ElapsedTimer()
    : m_tp(chrono_clock_type::now())
{
}

/*!
    \fn void ElapsedTimer::restart()

    Restart timing.
*/
void ElapsedTimer::restart()
{
    m_tp = chrono_clock_type::now();
}

/*!
    \fn std::chrono::milliseconds::rep ElapsedTimer::elapsed() const

    Returns the elapsed time in milliseconds with integer value.

    \sa elapsedFloating()
*/
std::chrono::milliseconds::rep ElapsedTimer::elapsed() const
{
    return elapsedMilliseconds();
}

/*!
    \fn std::chrono::milliseconds::rep ElapsedTimer::elapsedNanoseconds() const

    Returns the elapsed time in nanoseconds with integer value.

    \sa elapsedNanosecondsFloating()
*/
std::chrono::nanoseconds::rep ElapsedTimer::elapsedNanoseconds() const
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(chrono_clock_type::now() - m_tp).count();
}

/*!
    \fn std::chrono::milliseconds::rep ElapsedTimer::elapsedMicroseconds() const

    Returns the elapsed time in microseconds with integer value.

    \sa elapsedMicrosecondsFloating()
*/
std::chrono::microseconds::rep ElapsedTimer::elapsedMicroseconds() const
{
    return std::chrono::duration_cast<std::chrono::microseconds>(chrono_clock_type::now() - m_tp).count();
}

/*!
    \fn std::chrono::milliseconds::rep ElapsedTimer::elapsedMilliseconds() const

    Returns the elapsed time in milliseconds with integer value.

    \sa elapsedMillisecondsFloating()
*/
std::chrono::milliseconds::rep ElapsedTimer::elapsedMilliseconds() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(chrono_clock_type::now() - m_tp).count();
}

/*!
    \fn std::chrono::milliseconds::rep ElapsedTimer::elapsedSeconds() const

    Returns the elapsed time in seconds with integer value.

    sa elapsedSecondsFloating()
*/
std::chrono::seconds::rep ElapsedTimer::elapsedSeconds() const
{
    return std::chrono::duration_cast<std::chrono::seconds>(chrono_clock_type::now() - m_tp).count();
}

/*!
    \fn std::chrono::milliseconds::rep ElapsedTimer::elapsedMinutes() const

    Returns the elapsed time in minutes with integer value.

    \sa elapsedMinutesFloating()
*/
std::chrono::minutes::rep ElapsedTimer::elapsedMinutes() const
{
    return std::chrono::duration_cast<std::chrono::minutes>(chrono_clock_type::now() - m_tp).count();
}

/*!
    \fn std::chrono::milliseconds::rep ElapsedTimer::elapsedHours() const

    Returns the elapsed time in hours with integer value.

    \sa elapsedHoursFloating()
*/
std::chrono::hours::rep ElapsedTimer::elapsedHours() const
{
    return std::chrono::duration_cast<std::chrono::hours>(chrono_clock_type::now() - m_tp).count();
}

/*!
    \fn ElapsedTimer::chrono_days::rep ElapsedTimer::elapsedDays() const

    Returns the elapsed time in days with integer value.

    \sa elapsedHDaysFloating()
*/
ElapsedTimer::chrono_days::rep ElapsedTimer::elapsedDays() const
{
    return std::chrono::duration_cast<chrono_days>(chrono_clock_type::now() - m_tp).count();
}

/*!
    \fn ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsedFloating() const

    Returns the elapsed time in milliseconds with floating value.

    \sa elapsed()
*/
ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsedFloating() const
{
    return elapsedMillisecondsFloating();
}

/*!
    \fn ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsedNanosecondsFloating() const

    Returns the elapsed time in nanoseconds with floating value.

    \sa elapsedNanoseconds()
*/
ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsedNanosecondsFloating() const
{
    return static_cast<nanoseconds_floating_t>(chrono_clock_type::now() - m_tp).count();
}

/*!
    \fn ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsedMicrosecondsFloating() const

    Returns the elapsed time in microseconds with floating value.

    \sa elapsedMicroseconds()
*/
ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsedMicrosecondsFloating() const
{
    return static_cast<microseconds_floating_t>(chrono_clock_type::now() - m_tp).count();
}

/*!
    \fn ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsedMillisecondsFloating() const

    Returns the elapsed time in milliseconds with floating value.

    \sa elapsedMilliseconds()
*/
ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsedMillisecondsFloating() const
{
    return static_cast<milliseconds_floating_t>(chrono_clock_type::now() - m_tp).count();
}

/*!
    \fn ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsedSecondsFloating() const

    Returns the elapsed time in seconds with floating value.

    \sa elapsedSeconds()
*/
ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsedSecondsFloating() const
{
    return static_cast<seconds_floating_t>(chrono_clock_type::now() - m_tp).count();
}

/*!
    \fn ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsedMinutesFloating() const

    Returns the elapsed time in minutes with floating value.

    \sa elapsedMinutes()
*/
ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsedMinutesFloating() const
{
    return static_cast<minutes_floating_t>(chrono_clock_type::now() - m_tp).count();
}

/*!
    \fn ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsedHoursFloating() const

    Returns the elapsed time in hours with floating value.

    \sa elapsedHours()
*/
ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsedHoursFloating() const
{
    return static_cast<hours_floating_t>(chrono_clock_type::now() - m_tp).count();
}

/*!
    \fn ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsedDaysFloating() const

    Returns the elapsed time in days with floating value.

    \sa elapsedDays()
*/
ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsedDaysFloating() const
{
    return static_cast<days_floating_t>(chrono_clock_type::now() - m_tp).count();
}

} }// namespace