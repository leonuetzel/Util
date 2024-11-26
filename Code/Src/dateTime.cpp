#include <ITN/dateTime.hpp>
#include <ITN/util.hpp>

#include <vector>





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

ITN::DateTime::DateTime()
{
	
}


ITN::DateTime::DateTime(uint8 second, uint8 minute, uint8 hour, uint8 day, uint8 month, uint16 year)
	:	m_date(day, month, year),
		m_time(second, minute, hour)
{
	
}


ITN::DateTime::DateTime(std::time_t timeStamp)
	:	m_date(timeStamp),
		m_time(timeStamp)
{
	
}


ITN::DateTime::DateTime(const std::string& dateTimeString)
{
	std::vector strings(util::string::explode(dateTimeString, '-'));
	
	uint32 numberOfStrings = strings.size();
	if(numberOfStrings != 2)
	{
		*this = DateTime();
		return;
	}
	strings.at(0).erase(strings.at(0).length() - 1);
	strings.at(1).erase(0, 1);
	
	m_date = Date(strings.at(0));
	m_time = Time(strings.at(1));
}







const ITN::Date& ITN::DateTime::get_date() const
{
	return(m_date);
}


const ITN::Time& ITN::DateTime::get_time() const
{
	return(m_time);
}







void ITN::DateTime::set_date(const Date& date)
{
	m_date = date;
}


void ITN::DateTime::set_time(const Time& time)
{
	m_time = time;
}







bool ITN::DateTime::is_validDateTime() const
{
	if(m_date.is_validDate() == true && m_time.is_validTime() == true)
	{
		return(true);
	}
	return(false);
}







std::string ITN::DateTime::to_string() const
{
	if(is_validDateTime() == true)
	{
		return(m_date.to_string() + " - " + m_time.to_string());
	}
	return("");
}


std::tm ITN::DateTime::to_tm() const
{
	std::tm tm{};
	tm.tm_sec		= m_time.get_second();
	tm.tm_min		= m_time.get_minute();
	tm.tm_hour	= m_time.get_hour();
	tm.tm_mday	= m_date.get_day();
	tm.tm_mon		= m_date.get_month() - 1;
	tm.tm_year	= m_date.get_year() - 1900;
	
	return(tm);
}







void ITN::DateTime::add_seconds(uint32 seconds)
{
	m_time.add_seconds(seconds);
}


void ITN::DateTime::add_days(uint32 days)
{
	m_date.add_days(days);
}







ITN::DateTime ITN::DateTime::operator+(const Time& time) const
{
	DateTime dateTime(*this);
	
	const Time timeTemp(dateTime.m_time);
	
	dateTime.m_time += time;
	if(dateTime.m_time < timeTemp)
	{
		dateTime.m_date++;
	}
	return(dateTime);
}


ITN::DateTime& ITN::DateTime::operator+=(const Time& time)
{
	*this = *this + time;
	return(*this);
}







bool ITN::DateTime::operator<(const ITN::DateTime& dateTime) const
{
	if(m_date < dateTime.m_date)
	{
		return(true);
	}
	if(m_date == dateTime.m_date)
	{
		if(m_time < dateTime.m_time)
		{
			return(true);
		}
		return(false);
	}
	return(false);
}


bool ITN::DateTime::operator<=(const ITN::DateTime& dateTime) const
{
	if(*this < dateTime || *this == dateTime)
	{
		return(true);
	}
	return(false);
}


bool ITN::DateTime::operator==(const ITN::DateTime& dateTime) const
{
	if(m_date == dateTime.m_date && m_time == dateTime.m_time)
	{
		return(true);
	}
	return(false);
}


bool ITN::DateTime::operator>=(const ITN::DateTime& dateTime) const
{
	if(dateTime < *this || *this == dateTime)
	{
		return(true);
	}
	return(false);
}


bool ITN::DateTime::operator>(const ITN::DateTime& dateTime) const
{
	if(dateTime < *this)
	{
		return(true);
	}
	return(false);
}







ITN::DateTime ITN::DateTime::now()
{
	std::time_t timeType_now(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
	std::tm tm_now(*localtime(&timeType_now));
	
	return(DateTime(tm_now.tm_sec, tm_now.tm_min, tm_now.tm_hour, tm_now.tm_mday, tm_now.tm_mon + 1, tm_now.tm_year + 1900));
}