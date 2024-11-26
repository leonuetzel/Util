#pragma once

#include <ITN/defines.hpp>

#include <string>
#include <ctime>





namespace ITN
{
	class Date
	{
		public:
			
			static constexpr uint8 c_monthsPerYear = 12;
			
			enum class e_weekday
			{
				SUNDAY 		= 0,
				MONDAY 		= 1,
				TUESDAY		= 2,
				WEDNESDAY	= 3,
				THURSDAY	= 4,
				FRIDAY		= 5,
				SATURDAY	= 6,
				INVALID		= 7
			};
			
			
			
			
			
		private:
			
			uint8 m_day;
			uint8 m_month;
			uint16 m_year;
			
			static const uint8 c_daysPerMonth[c_monthsPerYear];
			
			
			
			
			
		public:
			
			Date();
			Date(uint8 day, uint8 month, uint16 year);
			Date(std::time_t timeStamp);
			Date(const std::string& dateString);
			
			const uint8& get_day() const;
			const uint8& get_month() const;
			const uint16& get_year() const;
			
			void set_day(uint8 day);
			void set_month(uint8 month);
			void set_year(uint16 year);
			
			bool is_validDate() const;
			bool is_leapYear() const;
			e_weekday get_weekday() const;
			
			std::string to_string() const;
			std::tm to_tm() const;
			
			void add_days(uint32 days);
			
			Date operator++(int inc);
			Date operator--(int inc);
			
			bool operator<(const Date& date) const;
			bool operator<=(const Date& date) const;
			bool operator==(const Date& date) const;
			bool operator>=(const Date& date) const;
			bool operator>(const Date& date) const;
			
			static Date now();
	};
};