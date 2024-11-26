#include <ITN/time.hpp>
#include <ITN/util.hpp>

#include <chrono>





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

ITN::Time::Time()
	:	m_second(0),
		m_minute(0),
		m_hour(0)
{
	
}


ITN::Time::Time(uint8 second, uint8 minute, uint8 hour)
	:	m_second(second),
		m_minute(minute),
		m_hour(hour)
{
	
}


ITN::Time::Time(std::time_t timeStamp)
{
	std::tm tm(*localtime(&timeStamp));
	
	m_second	= tm.tm_sec;
	m_minute	= tm.tm_min;
	m_hour		= tm.tm_hour;
}


ITN::Time::Time(const std::string& timeString)
{
	const std::vector strings(util::string::explode(timeString, ':'));
	
	uint32 numberOfStrings = strings.size();
	if(numberOfStrings != 3)
	{
		*this = Time();
		return;
	}
	for(uint32 i = 0; i < numberOfStrings; i++)
	{
		if(util::string::isDigit(strings.at(i)) == false)
		{
			*this = Time();
			return;
		}
	}
	
	m_hour = std::stoi(strings.at(0));
	m_minute = std::stoi(strings.at(1));
	m_second = std::stoi(strings.at(2));
}







const uint8& ITN::Time::get_second() const
{
	return(m_second);
}


const uint8& ITN::Time::get_minute() const
{
	return(m_minute);
}


const uint8& ITN::Time::get_hour() const
{
	return(m_hour);
}







void ITN::Time::set_second(uint8 second)
{
	m_second = second;
}


void ITN::Time::set_minute(uint8 minute)
{
	m_minute = minute;
}


void ITN::Time::set_hour(uint8 hour)
{
	m_hour = hour;
}







bool ITN::Time::is_validTime() const
{
	if(m_second >= c_secondsPerMinute || m_minute >= c_minutesPerHour || m_hour >= c_hoursPerDay)
	{
		return(false);
	}
	return(true);
}







std::string ITN::Time::to_string() const
{
	if(is_validTime() == true)
	{
		std::string timeString;
		if(m_hour < 10)
		{
			timeString += "0";
		}
		timeString += std::to_string(m_hour) + ":";
		
		if(m_minute < 10)
		{
			timeString += "0";
		}
		timeString += std::to_string(m_minute) + ":";
		
		if(m_second < 10)
		{
			timeString += "0";
		}
		timeString += std::to_string(m_second);
		return(timeString);
	}
	return("");
}


std::tm ITN::Time::to_tm() const
{
	std::tm tm{};
	tm.tm_sec		= m_second;
	tm.tm_min		= m_minute;
	tm.tm_hour	= m_hour;
	
	return(tm);
}







void ITN::Time::add_seconds(uint32 seconds)
{
	seconds	+= m_second;
	uint32 minutes	= (uint32) m_minute;
	uint32 hours		= (uint32) m_hour;
	
	minutes += seconds / c_secondsPerMinute;
	hours		+= minutes / c_minutesPerHour;
	
	seconds	%= c_secondsPerMinute;
	minutes	%= c_minutesPerHour;
	hours		%= c_hoursPerDay;
	
	m_second	= seconds;
	m_minute	= minutes;
	m_hour		= hours;
}







ITN::Time ITN::Time::operator+(const Time& time) const
{
	uint16 seconds	= (uint16) m_second	+ (uint16) time.m_second;
	uint16 minutes	= (uint16) m_minute	+ (uint16) time.m_minute;
	uint16 hours		= (uint16) m_hour		+ (uint16) time.m_hour;
	
	minutes += seconds / c_secondsPerMinute;
	hours		+= minutes / c_minutesPerHour;
	
	seconds	%= c_secondsPerMinute;
	minutes	%= c_minutesPerHour;
	hours		%= c_hoursPerDay;
	
	return(Time(seconds, minutes, hours));
}


ITN::Time& ITN::Time::operator+=(const Time& time)
{
	*this = *this + time;
	return(*this);
}







ITN::Time ITN::Time::operator++(int inc)
{
	m_second++;
	if(m_second >= c_secondsPerMinute)
	{
		m_second = 0;
		m_minute++;
		if(m_minute >= c_minutesPerHour)
		{
			m_minute = 0;
			m_hour++;
			if(m_hour >= c_hoursPerDay)
			{
				m_hour = 0;
			}
		}
	}
	return(*this);
}


ITN::Time ITN::Time::operator--(int inc)
{
	if(m_second == 0)
	{
		m_second = c_secondsPerMinute - 1;
		if(m_minute == 0)
		{
			m_minute = c_minutesPerHour - 1;
			if(m_hour == 0)
			{
				m_hour = c_hoursPerDay - 1;
			}
			else
			{
				m_hour--;
			}
		}
		else
		{
			m_minute--;
		}
	}
	else
	{
		m_second--;
	}
	return(*this);
}







bool ITN::Time::operator<(const Time& time) const
{
	if(m_hour < time.m_hour)																																																			//	Hour Comparison
	{
		return(true);
	}
	if(m_hour > time.m_hour)
	{
		return(false);
	}
	
	if(m_minute < time.m_minute)																																																	//	Minute Comparison
	{
		return(true);
	}
	if(m_minute > time.m_minute)
	{
		return(false);
	}
	
	if(m_second < time.m_second)																																																	//	Second Comparison
	{
		return(true);
	}
	if(m_second > time.m_second)
	{
		return(false);
	}
	return(false);																																																								//	Equal
}


bool ITN::Time::operator<=(const Time& time) const
{
	if(*this < time || *this == time)
	{
		return(true);
	}
	return(false);
}


bool ITN::Time::operator==(const Time& time) const
{
	if(m_hour == time.m_hour && m_minute == time.m_minute && m_second == time.m_second)
	{
		return(true);
	}
	return(false);
}


bool ITN::Time::operator>=(const ITN::Time& time) const
{
	if(time < *this || *this == time)
	{
		return(true);
	}
	return(false);
}


bool ITN::Time::operator>(const ITN::Time& time) const
{
	if(time < *this)
	{
		return(true);
	}
	return(false);
}







ITN::Time ITN::Time::now()
{
	return(Time(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())));
}