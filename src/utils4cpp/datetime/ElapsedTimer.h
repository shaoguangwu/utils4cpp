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

#ifndef UTILS4CPP_DATETIME_ELAPSEDTIMER_H_
#define UTILS4CPP_DATETIME_ELAPSEDTIMER_H_

#include <chrono>

#include "utils4cpp/core/Core.h"

namespace utils4cpp {
namespace datetime {

/*!
	\class ElapsedTimer
    \since 0.0

	\brief Defines a elapsed timer.
*/
class UTILS4CPP_EXPORT ElapsedTimer
{
public:
	using elapsed_time_floating_t = double;

	ElapsedTimer();
	void reset();

	std::chrono::milliseconds::rep elapsed() const;
	std::chrono::nanoseconds::rep elapsedNanoseconds() const;
	std::chrono::microseconds::rep elapsedMicroseconds() const;
	std::chrono::milliseconds::rep elapsedMilliseconds() const;
	std::chrono::seconds::rep elapsedSeconds() const;
	std::chrono::minutes::rep elapsedMinutes() const;
	std::chrono::hours::rep elapsedHours() const;

	elapsed_time_floating_t elapsedFloating() const;
	elapsed_time_floating_t elapsedNanosecondsFloating() const;
	elapsed_time_floating_t elapsedMicrosecondsFloating() const;
	elapsed_time_floating_t elapsedMillisecondsFloating() const;
	elapsed_time_floating_t elapsedSecondsFloating() const;
	elapsed_time_floating_t elapsedMinutesFloating() const;
	elapsed_time_floating_t elapsedHoursFloating() const;

private:
	using nanoseconds_floating_t = std::chrono::duration<elapsed_time_floating_t, std::chrono::nanoseconds::period>;
	using microseconds_floating_t = std::chrono::duration<elapsed_time_floating_t, std::chrono::microseconds::period>;
	using milliseconds_floating_t = std::chrono::duration<elapsed_time_floating_t, std::chrono::milliseconds::period>;
	using seconds_floating_t = std::chrono::duration<elapsed_time_floating_t, std::chrono::seconds::period>;
	using minutes_floating_t = std::chrono::duration<elapsed_time_floating_t, std::chrono::minutes::period>;
	using hours_floating_t = std::chrono::duration<elapsed_time_floating_t, std::chrono::hours::period>;

#if UTILS4CPP_HAS_CPP20
	using days_floating_t = std::chrono::duration<elapsed_time_floating_t, std::chrono::days::period>;
#else
	using days_floating_t = std::chrono::duration<elapsed_time_floating_t, std::ratio<86400>>;
#endif

	std::chrono::time_point<std::chrono::high_resolution_clock> m_tp;
};

} // namespace datetime
} // namespace utils4cpp

#endif // UTILS4CPP_DATETIME_ELAPSEDTIMER_H_