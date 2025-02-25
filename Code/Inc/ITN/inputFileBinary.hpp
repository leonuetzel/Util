#pragma once

#include <ITN/defines.hpp>

#include <string>
#include <fstream>
#include <filesystem>
#include <iterator>
#include <vector>

#include "windows.h"





namespace ITN
{
	class InputFileBinary
	{
		public:
			
			
			
			
			
			
			
		private:
			
			std::filesystem::path m_path;
			std::ifstream m_file;
			std::vector<uint8> m_data;
			bool m_valid;
			uint32 m_size;
			
			std::filesystem::path openFileDialog(std::string title, std::filesystem::path initialPath, std::string extensionFilter, HWND hWnd);
			
			
			
			
			
		public:
			
			InputFileBinary(std::filesystem::path path);
			InputFileBinary(std::string title, std::filesystem::path initialPath, std::string extensionFilter, HWND hWnd = NULL);
			~InputFileBinary();
			
			std::filesystem::path get_path() const;
			bool is_valid() const;
			const std::vector<uint8>& get_data() const;
			uint32 get_size() const;
	};
};