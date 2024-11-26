#pragma once

#include <ITN/defines.hpp>

#include <string>
#include <vector>





namespace ITN
{
	class SHA256
	{
		public:
			
			
			
			
			
			
			
		private:
			
			static constexpr uint32 c_blockSizeInBits		= 512;
			static constexpr uint32 c_blockSizeInBytes	= c_blockSizeInBits / 8;
			
			static const uint32 c_hashValues[8];
			static const uint32 c_roundConstants[64];
			
			const std::vector<uint8> m_input;
			std::vector<uint8> m_output;
			
			
			
			
			
		public:
			
			SHA256(const std::string& input);
			SHA256(const std::vector<uint8>& input);
			
			const std::vector<uint8>& get_input();
			const std::vector<uint8>& get_hash();
	};
};