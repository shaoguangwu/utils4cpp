/************************************************************************************
**
**  BSD 3-Clause License
**  
**  Copyright (c) 2019, shaoguang
**  All rights reserved.
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

#include <utils4cpp/datetime/ElapsedTimer.h>

namespace utils4cpp {

/*!
	\var ElapsedTimer::elapsed_time_floating_t

	The floating type of elapsed time.
*/

/*!
	\fn ElapsedTimer::ElapsedTimer()
	
	Constructs a elapsed timer, then start timing.

	\sa reset()
*/
ElapsedTimer::ElapsedTimer()
	: start_time(std::chrono::high_resolution_clock::now())
{
}

/*!
	\fn void ElapsedTimer::reset()

	Restart timing.
*/
void ElapsedTimer::reset()
{
	start_time = std::chrono::high_resolution_clock::now();
}

/*!
	\fn std::chrono::milliseconds::rep ElapsedTimer::elapsed() const

	Returns the elapsed time in milliseconds with integer value.
	
	\sa elapsed_floating()
*/
std::chrono::milliseconds::rep ElapsedTimer::elapsed() const
{
	return elapsed_milliseconds();
}

/*!
	\fn std::chrono::milliseconds::rep ElapsedTimer::elapsed_nanoseconds() const

	Returns the elapsed time in nanoseconds with integer value.
	
	\sa elapsed_nanoseconds_floating()
*/
std::chrono::nanoseconds::rep ElapsedTimer::elapsed_nanoseconds() const
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>(
		std::chrono::high_resolution_clock::now() - start_time).count();
}

/*!
	\fn std::chrono::milliseconds::rep ElapsedTimer::elapsed_microseconds() const

	Returns the elapsed time in microseconds with integer value.
	
	\sa elapsed_microseconds_floating()
*/
std::chrono::microseconds::rep ElapsedTimer::elapsed_microseconds() const
{
	return std::chrono::duration_cast<std::chrono::microseconds>(
		std::chrono::high_resolution_clock::now() - start_time).count();
}

/*!
	\fn std::chrono::milliseconds::rep ElapsedTimer::elapsed_milliseconds() const

	Returns the elapsed time in milliseconds with integer value.
	
	\sa elapsed_milliseconds_floating()
*/
std::chrono::milliseconds::rep ElapsedTimer::elapsed_milliseconds() const
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::high_resolution_clock::now() - start_time).count();
}

/*!
	\fn std::chrono::milliseconds::rep ElapsedTimer::elapsed_seconds() const

	Returns the elapsed time in seconds with integer value.
	
	sa elapsed_seconds_floating()
*/
std::chrono::seconds::rep ElapsedTimer::elapsed_seconds() const
{
	return std::chrono::duration_cast<std::chrono::seconds>(
		std::chrono::high_resolution_clock::now() - start_time).count();
}

/*!
	\fn std::chrono::milliseconds::rep ElapsedTimer::elapsed_minutes() const

	Returns the elapsed time in minutes with integer value.
	
	\sa elapsed_minutes_floating()
*/
std::chrono::minutes::rep ElapsedTimer::elapsed_minutes() const
{
	return std::chrono::duration_cast<std::chrono::minutes>(
		std::chrono::high_resolution_clock::now() - start_time).count();
}

/*!
	\fn std::chrono::milliseconds::rep ElapsedTimer::elapsed_hours() const

	Returns the elapsed time in hours with integer value.
	
	\sa elapsed_hours_floating()
*/
std::chrono::hours::rep ElapsedTimer::elapsed_hours() const
{
	return std::chrono::duration_cast<std::chrono::hours>(
		std::chrono::high_resolution_clock::now() - start_time).count();
}

/*!
	\fn ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsed_floating() const

	Returns the elapsed time in milliseconds with floating value.
	
	\sa elapsed()
*/
ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsed_floating() const
{
	return elapsed_milliseconds_floating();
}

/*!
	\fn ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsed_nanoseconds_floating() const

	Returns the elapsed time in nanoseconds with floating value.
	
	\sa elapsed_nanoseconds()
*/
ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsed_nanoseconds_floating() const
{
	return static_cast<nanoseconds_floating_t>(
		std::chrono::high_resolution_clock::now() - start_time).count();
}

/*!
	\fn ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsed_microseconds_floating() const

	Returns the elapsed time in microseconds with floating value.
	
	\sa elapsed_microseconds()
*/
ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsed_microseconds_floating() const
{
	return static_cast<microseconds_floating_t>(
		std::chrono::high_resolution_clock::now() - start_time).count();
}

/*!
	\fn ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsed_milliseconds_floating() const

	Returns the elapsed time in milliseconds with floating value.
	
	\sa elapsed_milliseconds()
*/
ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsed_milliseconds_floating() const
{
	return static_cast<milliseconds_floating_t>(
		std::chrono::high_resolution_clock::now() - start_time).count();
}

/*!
	\fn ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsed_seconds_floating() const

	Returns the elapsed time in seconds with floating value.
	
	\sa elapsed_seconds()
*/
ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsed_seconds_floating() const
{
	return static_cast<seconds_floating_t>(
		std::chrono::high_resolution_clock::now() - start_time).count();
}

/*!
	\fn ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsed_minutes_floating() const

	Returns the elapsed time in minutes with floating value.
	
	\sa elapsed_minutes()
*/
ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsed_minutes_floating() const
{
	return static_cast<minutes_floating_t>(
		std::chrono::high_resolution_clock::now() - start_time).count();
}

/*!
	\fn ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsed_hours_floating() const

	Returns the elapsed time in hours with floating value.
	
	\sa elapsed_hours()
*/
ElapsedTimer::elapsed_time_floating_t ElapsedTimer::elapsed_hours_floating() const
{
	return static_cast<hours_floating_t>(
		std::chrono::high_resolution_clock::now() - start_time).count();
}

} // namespace utils4cpp