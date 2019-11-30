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

#include "utils4cpp/datetime/UElapsedTimer.hpp"

namespace utils4cpp {
namespace datetime {

/**
    \var UElapsedTimer::chrono_clock_type

    The type of std::chrono clock.
*/

/**
    \var UElapsedTimer::elapsed_time_floating_t

    The floating type of elapsed time.
*/

/**
    Constructs a elapsed timer, and start timing.

    \sa reset()
*/
UElapsedTimer::UElapsedTimer()
    : m_tp(chrono_clock_type::now())
{
}

/**
    Restart timing.
*/
void UElapsedTimer::restart()
{
    m_tp = chrono_clock_type::now();
}

/**
    Returns the elapsed time in milliseconds with integer value.

    \sa elapsedFloating()
*/
std::chrono::milliseconds::rep UElapsedTimer::elapsed() const
{
    return elapsedMilliseconds();
}

/**
    Returns the elapsed time in nanoseconds with integer value.

    \sa elapsedNanosecondsFloating()
*/
std::chrono::nanoseconds::rep UElapsedTimer::elapsedNanoseconds() const
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(chrono_clock_type::now() - m_tp).count();
}

/**
    Returns the elapsed time in microseconds with integer value.

    \sa elapsedMicrosecondsFloating()
*/
std::chrono::microseconds::rep UElapsedTimer::elapsedMicroseconds() const
{
    return std::chrono::duration_cast<std::chrono::microseconds>(chrono_clock_type::now() - m_tp).count();
}

/**
    Returns the elapsed time in milliseconds with integer value.

    \sa elapsedMillisecondsFloating()
*/
std::chrono::milliseconds::rep UElapsedTimer::elapsedMilliseconds() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(chrono_clock_type::now() - m_tp).count();
}

/**
    Returns the elapsed time in seconds with integer value.

    sa elapsedSecondsFloating()
*/
std::chrono::seconds::rep UElapsedTimer::elapsedSeconds() const
{
    return std::chrono::duration_cast<std::chrono::seconds>(chrono_clock_type::now() - m_tp).count();
}

/**
    Returns the elapsed time in minutes with integer value.

    \sa elapsedMinutesFloating()
*/
std::chrono::minutes::rep UElapsedTimer::elapsedMinutes() const
{
    return std::chrono::duration_cast<std::chrono::minutes>(chrono_clock_type::now() - m_tp).count();
}

/**
    Returns the elapsed time in hours with integer value.

    \sa elapsedHoursFloating()
*/
std::chrono::hours::rep UElapsedTimer::elapsedHours() const
{
    return std::chrono::duration_cast<std::chrono::hours>(chrono_clock_type::now() - m_tp).count();
}

/**
    Returns the elapsed time in milliseconds with floating value.

    \sa elapsed()
*/
UElapsedTimer::elapsed_time_floating_t UElapsedTimer::elapsedFloating() const
{
    return elapsedMillisecondsFloating();
}

/**
    Returns the elapsed time in nanoseconds with floating value.

    \sa elapsedNanoseconds()
*/
UElapsedTimer::elapsed_time_floating_t UElapsedTimer::elapsedNanosecondsFloating() const
{
    return static_cast<nanoseconds_floating_t>(chrono_clock_type::now() - m_tp).count();
}

/**
    Returns the elapsed time in microseconds with floating value.

    \sa elapsedMicroseconds()
*/
UElapsedTimer::elapsed_time_floating_t UElapsedTimer::elapsedMicrosecondsFloating() const
{
    return static_cast<microseconds_floating_t>(chrono_clock_type::now() - m_tp).count();
}

/**
    Returns the elapsed time in milliseconds with floating value.

    \sa elapsedMilliseconds()
*/
UElapsedTimer::elapsed_time_floating_t UElapsedTimer::elapsedMillisecondsFloating() const
{
    return static_cast<milliseconds_floating_t>(chrono_clock_type::now() - m_tp).count();
}

/**
    Returns the elapsed time in seconds with floating value.

    \sa elapsedSeconds()
*/
UElapsedTimer::elapsed_time_floating_t UElapsedTimer::elapsedSecondsFloating() const
{
    return static_cast<seconds_floating_t>(chrono_clock_type::now() - m_tp).count();
}

/**
    Returns the elapsed time in minutes with floating value.

    \sa elapsedMinutes()
*/
UElapsedTimer::elapsed_time_floating_t UElapsedTimer::elapsedMinutesFloating() const
{
    return static_cast<minutes_floating_t>(chrono_clock_type::now() - m_tp).count();
}

/**
    Returns the elapsed time in hours with floating value.

    \sa elapsedHours()
*/
UElapsedTimer::elapsed_time_floating_t UElapsedTimer::elapsedHoursFloating() const
{
    return static_cast<hours_floating_t>(chrono_clock_type::now() - m_tp).count();
}

} }// namespace