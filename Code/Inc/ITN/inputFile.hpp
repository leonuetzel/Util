#pragma once

#include <ITN/defines.hpp>

#include <string>
#include <fstream>
#include <filesystem>

#include "windows.h"





namespace ITN
{
	class InputFile
	{
		public:
			
			
			
			
			
			
			
		private:
			
			std::filesystem::path m_path;
			std::ifstream m_file;
			std::string m_data;
			bool m_valid;
			uint32 m_size;
			
			std::filesystem::path openFileDialog(std::string title, std::filesystem::path initialPath, std::string extensionFilter, HWND hWnd);
			
			
			
			
			
		public:
			
			InputFile(std::filesystem::path path);
			InputFile(std::string title, std::filesystem::path initialPath, std::string extensionFilter, HWND hWnd = NULL);
			~InputFile();
			
			std::filesystem::path get_path() const;
			bool is_valid() const;
			const std::string& get_data() const;
			uint32 get_size() const;
	};
};