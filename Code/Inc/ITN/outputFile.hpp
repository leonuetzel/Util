#pragma once

#include <ITN/defines.hpp>

#include <string>
#include <fstream>
#include <filesystem>





namespace ITN
{
	class OutputFile: public std::string
	{
		public:
			
			
			
			
			
			
			
		private:
			
			std::filesystem::path m_path;
			std::ofstream m_outputStream;
			
			
			
			
			
		public:
			
			OutputFile(std::filesystem::path path);
			~OutputFile();
			
			std::filesystem::path get_path() const;
			bool is_valid() const;
			void clear();
			void save();
			OutputFile& operator=(const std::string& string);
	};
};