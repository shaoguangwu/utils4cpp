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

#include <cwchar>
#include <cstring>
#include <iomanip>

#ifdef UTILS4CPP_OS_UNIX
#   include <sys/time.h>
#endif // UTILS4CPP_OS_UNIX

#include "utils4cpp/datetime/UDate.hpp"

namespace utils4cpp {
namespace datetime {

static const char monthDays[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

/**
    \internal
    Division, rounding down (rather than towards zero).

    From C++11 onwards, integer division is defined to round towards zero, so we
    can rely on that when implementing this.  This is only used with denominator b
    > 0, so we only have to treat negative numerator, a, specially.
*/
static inline std::int64_t floordiv(std::int64_t a, int b)
{
    return (a - (a < 0 ? b - 1 : 0)) / b;
}

static inline int floordiv(int a, int b)
{
    return (a - (a < 0 ? b - 1 : 0)) / b;
}

static std::int64_t julianDayFromDate(int year, int month, int day)
{
    // Adjust for no year 0
    if (year < 0)
        ++year;

    /*
     * Math from The Calendar FAQ at http://www.tondering.dk/claus/cal/julperiod.php
     * This formula is correct for all julian days, when using mathematical integer
     * division (round to negative infinity), not c++11 integer division (round to zero)
     */
    int a = floordiv(14 - month, 12);
    std::int64_t y = (std::int64_t)year + 4800 - a;
    int m = month + 12 * a - 3;
    return day + floordiv(153 * m + 2, 5) + 365 * y + floordiv(y, 4) - floordiv(y, 100) + floordiv(y, 400) - 32045;
}

static void getDateFromJulianDay(std::int64_t julianDay, int& year, int& month, int& day)
{
    /*
     * Math from The Calendar FAQ at http://www.tondering.dk/claus/cal/julperiod.php
     * This formula is correct for all julian days, when using mathematical integer
     * division (round to negative infinity), not c++11 integer division (round to zero)
     */
    std::int64_t a = julianDay + 32044;
    std::int64_t b = floordiv(4 * a + 3, 146097);
    std::int64_t c = a - floordiv(146097 * b, 4);

    std::int64_t d = floordiv(4 * c + 3, 1461);
    std::int64_t e = c - floordiv(1461 * d, 4);
    std::int64_t m = floordiv(5 * e + 2, 153);

    day = static_cast<int>(e - floordiv(153 * m + 2, 5) + 1);
    month = static_cast<int>(m + 3 - 12 * floordiv(m, 10));
    year = static_cast<int>(100 * b + d - 4800 + floordiv(m, 10));

    // Adjust for no year 0
    if (year <= 0)
        --year;
}

template<class T>
inline const T& min(const T& t1, const T& t2)
{
    return t1 < t2 ? t1 : t2;
}

static inline UDate fixedDate(int y, int m, int d)
{
    UDate result(y, m, 1);
    result.setDate(y, m, min(d, result.daysInMonth()));
    return result;
}

/*****************************************************************************
  Date member functions
 *****************************************************************************/

/**
    Constructs an invalid date.

    \sa isValid()
*/
UDate::UDate()
{
    makeInvalid();
}

/**
    Constructs a date with year \a y, month \a m and day \a d.

    If the specified date is invalid, the date is set to default 
    invalid date and isValid() returns \c false.

    \param y year
    \param m month
    \param d day
    \param dst Daylight saving time flag. The value is positive if DST is in effect, 
                 zero if not and negative if no information is available

    \warning Years 1 to 99 are interpreted as is. Year 0 is invalid.

    \sa isValid()
*/
UDate::UDate(int y, int m, int d, int dst)
{
    setDate(y, m, d, dst);
}

/**
    Constructs a date with std::tm structur \a tm.

    \sa isValid()
*/
UDate::UDate(const std::tm& tm)
{
    fromTm(tm);
}

/**
    Returns the year of this date. Negative numbers indicate years
    before 1 CE, such that year -44 is 44 BCE.

    Returns 0 if the date is invalid.

    \sa month(), day()
*/
int UDate::year() const
{
    return m_dt.year;
}

/**
    Returns the number corresponding to the month of this date, using
    the following convention:

    \li 1 = "January"
    \li 2 = "February"
    \li 3 = "March"
    \li 4 = "April"
    \li 5 = "May"
    \li 6 = "June"
    \li 7 = "July"
    \li 8 = "August"
    \li 9 = "September"
    \li 10 = "October"
    \li 11 = "November"
    \li 12 = "December"

    Returns 0 if the date is invalid.

    \sa year(), day()
*/
int UDate::month() const
{
    return m_dt.mon;
}

/**
    Returns the day of the month (1 to 31) of this date.

    Returns 0 if the date is invalid.

    \sa year(), month(), dayOfWeek()
*/
int UDate::day() const
{
    return m_dt.mday;
}

/**
    Returns the daylight saving time flag.

    The value is positive if DST is in effect, zero if not and negative if no information is available.
*/
int UDate::dst() const
{
    return m_dt.isdst;
}

/**
    Returns the weekday (1 = Monday to 7 = Sunday) for this date.

    Returns 0 if the date is invalid. Using the following convention:

    \li 1 - "Monday"
    \li 2 - "Tuesday"
    \li 3 - "Wednesday"
    \li 4 - "Thursday"
    \li 5 - "Friday"
    \li 6 - "Saturday"
    \li 7 - "Sunday"

    \sa day(), dayOfYear(), Date::DayOfWeek
*/
int UDate::dayOfWeek() const
{
    return m_dt.wday;
}

/**
    Returns the day of the year (1 to 365 or 366 on leap years) for
    this date.

    Returns 0 if the date is invalid.

    \sa day(), dayOfWeek()
*/
int UDate::dayOfYear() const
{
    return m_dt.yday;
}

/**
    Returns the number of days in the month (28 to 31) for this date.

    Returns 0 if the date is invalid.

    \sa day(), daysInYear()
*/
int UDate::daysInMonth() const
{
    if (m_dt.mon == 2 && isLeapYear(m_dt.year))
        return 29;
    else 
        return monthDays[m_dt.mon];
}

/**
    Returns the number of days in the year (365 or 366) for this date.

    Returns 0 if the date is invalid.

    \sa day(), daysInMonth()
*/
int UDate::daysInYear() const
{
    if (!isValid())
        return 0;

    return isLeapYear(m_dt.year) ? 366 : 365;
}

/**
    Returns \c true if this date is valid; otherwise returns \c false.
*/
bool UDate::isValid() const
{
    return UDate::isValid(m_dt.year, m_dt.mon, m_dt.mday);
}

/**
    Sets the date's year \a y, month \a m, and day \a d. Returns \c true if
    the date is valid; otherwise returns \c false.

    If the specified date is invalid, the QDate object is set to be
    invalid.

    \sa isValid()
*/
bool UDate::setDate(int y, int m, int d, int dst)
{
    if (isValid(y, m, d)) {
        m_dt.year = y;
        m_dt.mon = m;
        m_dt.mday = d;
        m_dt.wday = dayOfWeek(y, m, d);
        m_dt.yday = dayOfYear(y, m, d);
        m_dt.isdst = dst;
        return true;
    }

    makeInvalid();
    return false;
}

/**
    Extracts the date's year, month, and day, and assigns them to
    \a year, \a month, and \a day.

    \sa year(), month(), day(), isValid()
*/
void UDate::getDate(int& year, int& month, int& day) const
{
    year = m_dt.year;
    month = m_dt.mon;
    day = m_dt.mday;
}

/**
    Sets this date with a tm structur.

    \sa toTm()
*/
void UDate::fromTm(const std::tm& tm)
{
    m_dt.mday = tm.tm_mday;
    m_dt.mon = tm.tm_mon + 1;
    m_dt.year = tm.tm_year + 1900;
    m_dt.wday = tm.tm_wday ? tm.tm_wday : 7;
    m_dt.yday = tm.tm_yday + 1;
    m_dt.isdst = tm.tm_isdst;
}

/**
    Converts date to a tm struct.

    \sa fromTm()
*/
std::tm UDate::toTm()
{
    std::tm datetm;
    std::memset(&datetm, 0, sizeof(datetm));
    datetm.tm_mday = m_dt.mday;
    datetm.tm_mon = m_dt.mon - 1;
    datetm.tm_year = m_dt.year - 1900;
    datetm.tm_wday = (m_dt.wday == 7 ? 0 : m_dt.wday);
    datetm.tm_yday = m_dt.yday - 1;
    datetm.tm_isdst = m_dt.isdst;
    return datetm;
}

/**
    Converts this date to julian day.

    If this date is invalid, returns 0;
*/
std::int64_t UDate::toJulianDay() const
{
    if (isValid())
        return julianDayFromDate(m_dt.year, m_dt.mon, m_dt.mday);
    else
        return 0;
}

/**
    Converts julian day to date.
*/
UDate UDate::fromJulianDay(std::int64_t julianDay)
{
    /*
     * Math from The Calendar FAQ at http://www.tondering.dk/claus/cal/julperiod.php
     * This formula is correct for all julian days, when using mathematical integer
     * division (round to negative infinity), not c++11 integer division (round to zero)
     */
    std::int64_t a = julianDay + 32044;
    std::int64_t b = floordiv(4 * a + 3, 146097);
    std::int64_t c = a - floordiv(146097 * b, 4);

    std::int64_t d = floordiv(4 * c + 3, 1461);
    std::int64_t e = c - floordiv(1461 * d, 4);
    std::int64_t m = floordiv(5 * e + 2, 153);

    int day = static_cast<int>(e - floordiv(153 * m + 2, 5) + 1);
    int month = static_cast<int>(m + 3 - 12 * floordiv(m, 10));
    int year = static_cast<int>(100 * b + d - 4800 + floordiv(m, 10));

    // Adjust for no year 0
    if (year <= 0)
        --year;

    return UDate(year, month, day);
}

/**
    Returns the number of days from this date to \a d (which is
    negative if \a d is earlier than this date).

    Returns 0 if either date is invalid.
*/
std::int64_t UDate::daysTo(const UDate& d) const
{
    if (!isValid())
        return 0;
    else
        return toJulianDay() - d.toJulianDay();
}

/**
    Returns a Date object containing a date \a ndays later than the
    date of this object (or earlier if \a ndays is negative).

    Returns an invalid date if the current date is invalid.

    \sa addMonths(), addYears(), daysTo()
*/
UDate UDate::addDays(std::int64_t days) const
{
    if (!isValid())
        return UDate();

    if (!days)
        return *this;
    else
        return fromJulianDay(toJulianDay() + days);
}

/**
    Returns the date as a string. The \a format parameter determines
    the format of the result string.

    These expressions can refer to std::strftime.
	see https://en.cppreference.com/w/cpp/chrono/c/strftime

	\note The result is 1024 character limits.
*/
#include <iomanip>
std::string UDate::toString(const char* format)
{
	std::size_t buff_size = 1024; 
	std::string result;
	result.resize(buff_size);
	
	std::tm tm{0};
	tm.tm_year = m_dt.year - 1900;
	tm.tm_mon = m_dt.mon - 1;
	tm.tm_mday = m_dt.mday;
	std::strftime(&result.front(), buff_size, format, &tm);
	
	return result;
}

/**
    Returns the date as a wide string. The \a format parameter determines
    the format of the result string.

    These expressions can refer to std::strftime.
    see https://en.cppreference.com/w/cpp/chrono/c/wcsftime

    \note The result is 1024 character limits.
*/
std::wstring UDate::toWString(const wchar_t* format)
{
    std::size_t buff_size = 1024;
    std::wstring result;
    result.resize(buff_size);

    std::tm tm{ 0 };
    tm.tm_year = m_dt.year - 1900;
    tm.tm_mon = m_dt.mon - 1;
    tm.tm_mday = m_dt.mday;
    std::wcsftime(&result.front(), buff_size, format, &tm);

    return result;
}

/**
    Returns a Date object containing a date \a nmonths later than the
    date of this object (or earlier if \a nmonths is negative).

    \note If the ending day/month combination does not exist in the
    resulting month/year, this function will return a date that is the
    latest valid date.

    \sa addDays(), addYears()
*/
UDate UDate::addMonths(int months) const
{
    if (!isValid())
        return UDate();
    if (!months)
        return *this;

    int old_y = m_dt.year;
    int y = m_dt.year;
    int m = m_dt.mon;
    int d = m_dt.mday;

    bool increasing = months > 0;

    while (months != 0) {
        if (months < 0 && months + 12 <= 0) {
            y--;
            months += 12;
        }
        else if (months < 0) {
            m += months;
            months = 0;
            if (m <= 0) {
                --y;
                m += 12;
            }
        }
        else if (months - 12 >= 0) {
            y++;
            months -= 12;
        }
        else if (m == 12) {
            y++;
            m = 0;
        }
        else {
            m += months;
            months = 0;
            if (m > 12) {
                ++y;
                m -= 12;
            }
        }
    }

    // was there a sign change?
    if ((old_y > 0 && y <= 0) ||
        (old_y < 0 && y >= 0))
        // yes, adjust the date by +1 or -1 years
        y += increasing ? +1 : -1;

    return fixedDate(y, m, d);
}

/**
    Returns a Date object containing a date \a nyears later than the
    date of this object (or earlier if \a nyears is negative).

    \note If the ending day/month combination does not exist in the
    resulting year (i.e., if the date was Feb 29 and the final year is
    not a leap year), this function will return a date that is the
    latest valid date (that is, Feb 28).

    \sa addDays(), addMonths()
*/
UDate UDate::addYears(int nyears) const
{
    if (!isValid())
        return UDate();

    int old_y = m_dt.year;
    int y = m_dt.year;
    y += nyears;

    // was there a sign change?
    if ((old_y > 0 && y <= 0) ||
        (old_y < 0 && y >= 0))
        // yes, adjust the date by +1 or -1 years
        y += nyears > 0 ? +1 : -1;

    return fixedDate(y, m_dt.mon, m_dt.mday);
}

/**
    Sets the Date object to be default invalid state.

    \sa isValid()
*/
void UDate::makeInvalid()
{
    std::memset(&m_dt, 0, sizeof(m_dt));
    m_dt.isdst = -1;
}

/**
    Returns \c true if this date is equal to \a d; otherwise returns \c false.

    \sa operator!=()
*/
bool UDate::operator==(const UDate& other) const
{
    return m_dt.year == other.m_dt.year
        && m_dt.mon == other.m_dt.mon
        && m_dt.mday == other.m_dt.mday;
}

/**
    Returns \c true if this date is different from \a d; otherwise
    returns \c false.

    \sa operator==()
*/
bool UDate::operator!=(const UDate& other) const
{
    return m_dt.year != other.m_dt.year
        || m_dt.mon != other.m_dt.mon
        || m_dt.mday != m_dt.mday;
}

/**
    Returns \c true if this date is earlier than \a d; otherwise returns \c false.

    \sa operator>(), operator<=()
*/
bool UDate::operator<(const UDate& other) const
{
    return toJulianDay() < other.toJulianDay();
}

/**
    Returns \c true if this date is earlier than or equal to \a d;
    otherwise returns \c false.

    \sa operator>=(), operator<()
*/
bool UDate::operator<=(const UDate& other) const
{
    if (*this == other)
        return true;
    return *this < other;
}

/**
    Returns \c true if this date is later than \a d; otherwise returns \c false.

    \sa operator>=(), operator<()
*/
bool UDate::operator>(const UDate& other) const
{
    return toJulianDay() > other.toJulianDay();
}

/**
    Returns \c true if this date is later than or equal to \a d;
    otherwise returns \c false.

    \sa operator>(), operator<=()
*/
bool UDate::operator>=(const UDate& other) const
{
    if (*this == other)
        return true;
    return *this > other;
}

/**
    Returns \c true if daylight savings time flag is same to \a other's daylight savings time flag,
    otherwise returns \c false.

    \sa dst()
*/
bool UDate::isDstFlagSameTo(const UDate& other) const
{
    if (m_dt.isdst < 0) {
        return other.dst() < 0;
    } else if (m_dt.isdst == 0) {
        return other.dst() == 0;
    } else {
        return other.dst() > 0;
    }
}

/**
    Returns \c true if this month \a m has 31 days;
    otherwise returns \c false.
*/
bool UDate::is31Days(int m)
{
    return m == Month::Jan || m == Month::Feb || m == Month::May || m == Month::July
        || m == Month::Aug || m == Month::Oct || m == Month::Dec;
}

/**
    Returns \c true if this month \a m has 30 days;
    otherwise returns \c false.
*/
bool UDate::is30Days(int m)
{
    return m == Month::Apr || m == Month::June || m == Month::Sept || m == Month::Nov;
}

/**
    Returns \c true if this date (\a year, \a month, \a day) is valid;
    otherwise returns \c false.
*/
bool UDate::isValid(int y, int m, int d)
{
    using uint = unsigned int;

    if (is31Days(m))
        return (uint)d <= 31;
    else if (is30Days(m))
        return (uint)d <= 30;
    else // m == Month::Feb
        return isLeapYear(y) ? (uint)d <= 29 : (uint)d <= 28;
}

/**
    Returns \c true if the specified \a year is a leap year; otherwise
    returns \c false.
*/
bool UDate::isLeapYear(int y)
{
    // No year 0 in Gregorian calendar, so -1, -5, -9 etc are leap years
    if (y < 1)
        ++y;

    return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
}

/**
    Returns \c true if this date is earlier than Gregorian Calendar(1582.10.04);
    otherwise returns \c false.
*/
bool UDate::beforGregorianCalendar(int year, int month, int day)
{
    if (year > 1582)
        return false;
    if (month > 10)
        return false;
    if (month > 4)
        return false;
    return true;
}

/**
    Returns \c true if this date \a d is earlier than Gregorian Calendar(1582.10.04);
    otherwise returns \c false.
*/
bool UDate::beforGregorianCalendar(const UDate& d)
{
    return beforGregorianCalendar(d.m_dt.year, d.m_dt.mon, d.m_dt.mday);
}

/**
    Returns the day of the year (1 to 365 or 366 on leap years) for this date.

    Returns 0 if the date is invalid.
*/
int UDate::dayOfYear(int year, int month, int day)
{
    if (!isValid(year, month, day))
        return 0;

    int days = 0;
    for (int i = 1; i < month; ++i)
        days += monthDays[i];

    if (isLeapYear(year) && month > 2)
        return days + day + 1;
    else
        return days + day;
}

/**
    Returns the weekday (1 = Monday to 7 = Sunday) for this date (\a year, \a month, \a day).
    Using the following convention:

    \li 1 - "Monday"
    \li 2 - "Tuesday"
    \li 3 - "Wednesday"
    \li 4 - "Thursday"
    \li 5 - "Friday"
    \li 6 - "Saturday"
    \li 7 - "Sunday"

    Returns 0 if the date is invalid.
*/
int UDate::dayOfWeek(int year, int month, int day)
{
    int weekday = 0;
    if (!isValid(year, month, day))
        return weekday;

    if (beforGregorianCalendar(year, month, day))
        weekday = (day + 1 + 2 * month + 3 * (month + 1) / 5 + year + year / 4 + 5) % 7;
    else
        weekday = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400 + 1) % 7;
   
    if (weekday == 0)
        weekday = 7;

    return weekday;
}

/**
    Returns the current local date, as reported by the system clock.
*/
UDate UDate::currentLocalDate()
{
    std::time_t t = std::time(nullptr);
    std::tm tm;

#if defined(UTILS4CPP_OS_WIN)
    localtime_s(&tm, &t);
#elif defined(UTILS4CPP_OS_UNIX)
    localtime_r(&t, &tm);
#else
    tm = *std::localtime(&t);
#endif

    return UDate(tm);
}

/**
    Returns the current GM(Greenwish Mean) date, as reported by the system clock.
*/
UDate UDate::currentGmDate()
{
    std::time_t t = std::time(nullptr);
    std::tm tm;
    
#if defined(UTILS4CPP_OS_WIN)
    gmtime_s(&tm, &t);
#elif defined(UTILS4CPP_OS_UNIX)
    gmtime_r(&t, &tm);
#else
    tm = *std::gmtime(&t);
#endif

    return UDate(tm);
}

/*****************************************************************************
  Date frriend functions
 *****************************************************************************/

/**
    Writes the \a date to stream \a out.
*/
UTILS4CPP_EXPORT std::ostream& operator<<(std::ostream& out, const UDate& date)
{
    out << "Date(\""
        << std::setw(4) << std::setfill('0') << date.year() << "-"
        << std::setw(2) << std::setfill('0') << date.month() << "-"
        << std::setw(2) << std::setfill('0') << date.day() << ")\"";
    return out;
}

} // namespace datetime
} // namespace utils4cpp