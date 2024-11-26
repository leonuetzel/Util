#pragma once

#include <ITN/defines.hpp>

#include <string>
#include <vector>
#include <map>





namespace ITN
{
	class BASE64
	{
		public:
			
			
			
			
			
			
			
		private:
			
			static const std::map<uint8, char> c_encodingTable;
			static const std::map<char, uint8> c_decodingTable;
			
			static const std::map<uint8, char> c_encodingTable_url;
			static const std::map<char, uint8> c_decodingTable_url;
			
			static std::string encode(std::vector<uint8> input, const std::map<uint8, char>& table);
			static std::vector<uint8> decode(std::string input, const std::map<char, uint8>& table);
			
			static bool is_validCode(const std::string code, const std::map<char, uint8>& table);
			
			
			
			
			
		public:
			
			static std::string encode(std::string input);
			static std::string encode_url(std::string input);
			
			static std::string encode(const std::vector<uint8>& input);
			static std::string encode_url(const std::vector<uint8>& input);
			
			
			
			static std::vector<uint8> decode(const std::string& input);
			static std::vector<uint8> decode_url(const std::string& input);
	};
};