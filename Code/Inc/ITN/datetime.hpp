#pragma once

#include <ITN/defines.hpp>
#include <ITN/date.hpp>
#include <ITN/time.hpp>

#include <string>
#include <ctime>





namespace ITN
{
	class DateTime
	{
		public:
			
			
			
			
			
			
			
		private:
			
			Date m_date;
			Time m_time;
			
			
			
			
			
		public:
			
			DateTime();
			DateTime(uint8 second, uint8 minute, uint8 hour, uint8 day, uint8 month, uint16 year);
			DateTime(std::time_t timeStamp);
			DateTime(const std::string& dateTimeString);
			
			const Date& get_date() const;
			const Time& get_time() const;
			
			void set_date(const Date& date);
			void set_time(const Time& time);
			
			bool is_validDateTime() const;
			
			std::string to_string() const;
			std::tm to_tm() const;
			
			void add_seconds(uint32 seconds);
			void add_days(uint32 days);
			
			DateTime operator+(const Time& time) const;
			DateTime& operator+=(const Time& time);
			
			bool operator<(const DateTime& dateTime) const;
			bool operator<=(const DateTime& dateTime) const;
			bool operator==(const DateTime& dateTime) const;
			bool operator>=(const DateTime& dateTime) const;
			bool operator>(const DateTime& dateTime) const;
			
			static DateTime now();
	};
};