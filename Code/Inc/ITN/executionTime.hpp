#pragma once

#include <ITN/defines.hpp>

#include <filesystem>
#include <chrono>
#include <vector>





namespace ITN
{
	class ExecutionTime
	{
		public:
			
			
			
			
			
			
			
		private:
			
			static std::vector<std::chrono::_V2::system_clock::time_point> m_timePoints;
			
			
			
			
			
		public:
			
			static void add_timePoint();
			static void save(std::filesystem::path path);
			static void clear();
	};
};