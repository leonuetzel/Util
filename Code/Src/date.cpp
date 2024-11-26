#include <ITN/date.hpp>
#include <ITN/util.hpp>

#include <vector>





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

const uint8 ITN::Date::c_daysPerMonth[c_monthsPerYear] =
{
	31,
	28,
	31,
	30,
	31,
	30,
	31,
	31,
	30,
	31,
	30,
	31
};



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

ITN::Date::Date()
	:	m_day(1),
		m_month(1),
		m_year(2000)
{
	
}


ITN::Date::Date(uint8 day, uint8 month, uint16 year)
	:	m_day(day),
		m_month(month),
		m_year(year)
{
	
}


ITN::Date::Date(std::time_t timeStamp)
{
	std::tm tm(*localtime(&timeStamp));
	
	m_day		= tm.tm_mday;
	m_month	= tm.tm_mon + 1;
	m_year	= tm.tm_year + 1900;
}


ITN::Date::Date(const std::string& dateString)
{
	const std::vector strings(util::string::explode(dateString, '.'));
	
	uint32 numberOfStrings = strings.size();
	if(numberOfStrings != 3)
	{
		*this = Date();
		return;
	}
	for(uint32 i = 0; i < numberOfStrings; i++)
	{
		if(util::string::isDigit(strings.at(i)) == false)
		{
			*this = Date();
			return;
		}
	}
	
	m_day		= std::stoi(strings.at(0));
	m_month = std::stoi(strings.at(1));
	m_year	= std::stoi(strings.at(2));
}







const uint8& ITN::Date::get_day() const
{
	return(m_day);
}


const uint8& ITN::Date::get_month() const
{
	return(m_month);
}


const uint16& ITN::Date::get_year() const
{
	return(m_year);
}







void ITN::Date::set_day(uint8 day)
{
	m_day = day;
}


void ITN::Date::set_month(uint8 month)
{
	m_month = month;
}


void ITN::Date::set_year(uint16 year)
{
	m_year = year;
}







bool ITN::Date::is_validDate() const
{
	if(m_month > c_monthsPerYear || m_month == 0 || m_day == 0)
	{
		return(false);
	}
	if(m_day > c_daysPerMonth[m_month - 1])
	{
		if(m_month != 2)
		{
			return(false);
		}
		
		if(is_leapYear() == false)
		{
			return(false);
		}
		if(m_day > c_daysPerMonth[m_month - 1] + 1)
		{
			return(false);
		}
	}
	return(true);
}


bool ITN::Date::is_leapYear() const
{
	if(m_year % 4 == 0)
	{
		if(m_year % 100 == 0)
		{
			if(m_year % 400 == 0)
			{
				return(true);
			}
		}
		else
		{
			return(true);
		}
	}
	return(false);
}


ITN::Date::e_weekday ITN::Date::get_weekday() const
{
	static const uint8 c_arrMonthOffset[12] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
	
	if(is_validDate() == false)
	{
		return(e_weekday::INVALID);
	}
	
	uint8 temp_day			= m_day % 7;
	uint8 temp_month		= c_arrMonthOffset[m_month - 1];
	uint8 temp					= m_year % 100;
	uint8 temp_year			= (temp + temp / 4) % 7;
	uint8 temp_century	= (3 - ((m_year / 100) % 4)) * 2;
	
	if(m_month <= 2 && is_leapYear() == true)
	{
		temp_day += 6;
	}
	uint8 result = (temp_day + temp_month + temp_year + temp_century) % 7;
	return((e_weekday) result);
}







std::string ITN::Date::to_string() const
{
	if(is_validDate() == true)
	{
		std::string dateString;
		if(m_day < 10)
		{
			dateString += "0";
		}
		dateString += std::to_string(m_day) + ".";
		
		if(m_month < 10)
		{
			dateString += "0";
		}
		dateString += std::to_string(m_month) + "." + std::to_string(m_year);
		return(dateString);
	}
	return("");
}


std::tm ITN::Date::to_tm() const
{
	std::tm tm{};
	tm.tm_mday	= m_day;
	tm.tm_mon		= m_month - 1;
	tm.tm_year	= m_year - 1900;
	
	return(tm);
}







void ITN::Date::add_days(uint32 days)
{
	for(uint32 i = 0; i < days; i++)
	{
		operator++(1);
	}
}







ITN::Date ITN::Date::operator++(int inc)
{
	if(is_validDate() == true)
	{
		m_day++;
		if(m_day > c_daysPerMonth[m_month - 1])
		{
			if(m_month == 2)
			{
				if(is_leapYear() == true)
				{
					return(*this);
				}
			}
			m_day = 1;
			m_month++;
			if(m_month >= c_monthsPerYear)
			{
				m_month = 1;
				m_year++;
			}
		}
	}
	return(*this);
}


ITN::Date ITN::Date::operator--(int inc)
{
	if(m_day == 1)
	{
		if(m_month == 1)
		{
			m_month = c_monthsPerYear;
			if(m_year > 0)
			{
				m_year--;
			}
		}
		else
		{
			m_month--;
		}
		m_day = c_daysPerMonth[m_month];
		if(m_month == 2 && is_leapYear() == true)
		{
			m_day++;
		}
	}
	else
	{
		m_day--;
	}
	return(*this);
}







bool ITN::Date::operator<(const ITN::Date& date) const
{
	if(m_year < date.m_year)																																																			//	Year Comparison
	{
		return(true);
	}
	if(m_year > date.m_year)
	{
		return(false);
	}
	
	if(m_month < date.m_month)																																																		//	Month Comparison
	{
		return(true);
	}
	if(m_month > date.m_month)
	{
		return(false);
	}
	
	if(m_day < date.m_day)																																																				//	Day Comparison
	{
		return(true);
	}
	if(m_day > date.m_day)
	{
		return(false);
	}
	return(false);																																																								//	Equal
}


bool ITN::Date::operator<=(const ITN::Date& date) const
{
	if(*this < date || *this == date)
	{
		return(true);
	}
	return(false);
}


bool ITN::Date::operator==(const ITN::Date& date) const
{
	if(m_year == date.m_year && m_month == date.m_month && m_day == date.m_day)
	{
		return(true);
	}
	return(false);
}


bool ITN::Date::operator>=(const ITN::Date& date) const
{
	if(date < *this || *this == date)
	{
		return(true);
	}
	return(false);
}


bool ITN::Date::operator>(const ITN::Date& date) const
{
	if(date < *this)
	{
		return(true);
	}
	return(false);
}







ITN::Date ITN::Date::now()
{
	return(Date(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())));
}