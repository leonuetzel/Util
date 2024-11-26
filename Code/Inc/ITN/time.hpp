#pragma once

#include <ITN/defines.hpp>

#include <string>
#include <ctime>





namespace ITN
{
	class Time
	{
		public:
			
			static constexpr uint8 c_secondsPerMinute = 60;
			static constexpr uint8 c_minutesPerHour		= 60;
			static constexpr uint8 c_hoursPerDay			= 24;
			
			
			
			
			
		private:
			
			uint8 m_second;
			uint8 m_minute;
			uint8 m_hour;
			
			
			
			
			
		public:
			
			Time();
			Time(uint8 second, uint8 minute, uint8 hour);
			Time(std::time_t timeStamp);
			Time(const std::string& timeString);
			
			const uint8& get_second() const;
			const uint8& get_minute() const;
			const uint8& get_hour() const;
			
			void set_second(uint8 second);
			void set_minute(uint8 minute);
			void set_hour(uint8 hour);
			
			bool is_validTime() const;
			
			std::string to_string() const;
			std::tm to_tm() const;
			
			void add_seconds(uint32 seconds);
			
			Time operator+(const Time& time) const;
			Time& operator+=(const Time& time);
			
			Time operator++(int inc);
			Time operator--(int inc);
			
			bool operator<(const Time& time) const;
			bool operator<=(const Time& time) const;
			bool operator==(const Time& time) const;
			bool operator>=(const Time& time) const;
			bool operator>(const Time& time) const;
			
			static Time now();
	};
};
