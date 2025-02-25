#pragma once

#include <ITN/defines.hpp>

#include <string>
#include <vector>
#include <map>
#include <filesystem>
#include <cmath>





namespace ITN
{
	namespace util
	{
		//	String
		namespace string
		{
			std::vector<std::string> explode(const std::string& string, const char delimiter);
			std::vector<std::string> explodeIfNotInStringQuotes(const std::string& string, const char delimiter);
			std::vector<std::string> explode(const std::string& string, const std::vector<char>& delimiter);
			bool isDigit(const std::string& string);
			std::string to_string(float value, uint32 decimalPlaces = 2, char decimalPoint = '.');
			uint32 findMatchingBracket(const std::string& string, uint32 startPosition, char bracketOpening, char bracketClosing);
			void eraseAllOccurences(std::string& string, char character);
			std::string to_hexString(uint64 value, uint32 numberOfDigits = 0);
		};
		
		
		//	Filesystem
		namespace filesystem
		{
			void deleteOnlyFilesRecursive(const std::filesystem::path& path);
			void deleteWholeFolderContent(const std::filesystem::path& path);
			void copyWholeFolderContent(const std::filesystem::path& source, const std::filesystem::path& destination);
		};
		
		
		//	Bit Operations
		namespace bit
		{
			template<typename dataType>
			constexpr dataType rotate_right(dataType variable, uint32 numberOfBitsToRotate)
			{
				uint32 numberOfBitsToRotateReverse = sizeof(variable) * 8 - numberOfBitsToRotate;
				if(numberOfBitsToRotate == 0 || numberOfBitsToRotateReverse == 0)
				{
					return(variable);
				}
				return((variable >> numberOfBitsToRotate) | (variable << numberOfBitsToRotateReverse));
			}
			
			template<typename dataType>
			constexpr dataType rotate_left(dataType variable, uint32 numberOfBitsToRotate)
			{
				return(rotate_right<dataType>(variable, sizeof(variable) * 8 - numberOfBitsToRotate));
			}
			
			
			template<typename dataType>
			constexpr dataType shift_right(dataType variable, uint32 numberOfBitsToShift)
			{
				if(numberOfBitsToShift == 0)
				{
					return(variable);
				}
				return(variable >> numberOfBitsToShift);
			}
			
			
			template<typename dataType>
			constexpr dataType shift_left(dataType variable, uint32 numberOfBitsToShift)
			{
				if(numberOfBitsToShift == 0)
				{
					return(variable);
				}
				return(variable << numberOfBitsToShift);
			}
			
			
			
			
			
			
			
			template<typename dataType>
			constexpr void set(dataType& variable, uint32 bit)
			{
				variable |= (((dataType) 1) << bit);
			}
			
			
			template<typename dataType>
			constexpr void clear(dataType& variable, uint32 bit)
			{
				variable &= ~(((dataType) 1) << bit);
			}
			
			
			template<typename dataType>
			constexpr bool isSet(dataType variable, uint32 bit)
			{
				dataType test = variable & (((dataType) 1) << bit);
				
				if(test != 0)
				{
					return(true);
				}
				return(false);
			}
			
			
			template<typename dataType>
			constexpr bool isCleared(dataType variable, uint32 bit)
			{
				if(isSet<dataType>(variable, bit) == true)
				{
					return(false);
				}
				return(true);
			}
			
			
			constexpr uint8 mirror(uint8 variable)
			{
				return((variable * 0x0000000202020202ULL & 0x0000010884422010ULL) % 1023);
			}
			
			
			constexpr uint32 mirror(uint32 variable)
			{
				variable = ((variable & 0xFFFF0000) >> 16) | ((variable & 0x0000FFFF) << 16);
				variable = ((variable & 0xFF00FF00) >>  8) | ((variable & 0x00FF00FF) <<  8);
				variable = ((variable & 0xF0F0F0F0) >>  4) | ((variable & 0x0F0F0F0F) <<  4);
				variable = ((variable & 0xCCCCCCCC) >>  2) | ((variable & 0x33333333) <<  2);
				variable = ((variable & 0xAAAAAAAA) >>  1) | ((variable & 0x55555555) <<  1);
				
				return(variable);
			}
			
			
			
			
			
			
			
			namespace pack
			{
				constexpr inline uint16 _2x8Bit_to_1x16Bit(const uint8* lowestByte, bool msbFirst = true)
				{
					if(msbFirst == true)
					{
						return((lowestByte[0] << 8) + lowestByte[1]);
					}
					return((lowestByte[1] << 8) + lowestByte[0]);
				}
				
				
				inline uint16 _2x8Bit_to_1x16Bit(const std::vector<uint8>& data, uint32 startIndex = 0, bool msbFirst = true)
				{
					if(data.size() < 2 + startIndex)
					{
						return(0);
					}
					
					if(msbFirst == true)
					{
						return((data.at(0 + startIndex) << 8) + data.at(1 + startIndex));
					}
					return((data.at(1 + startIndex) << 8) + data.at(0 + startIndex));
				}
				
				
				constexpr inline uint32 _4x8Bit_to_1x32Bit(const uint8* lowestByte, bool msbFirst = true)
				{
					if(msbFirst == true)
					{
						return((lowestByte[0] << 24) + (lowestByte[1] << 16) + (lowestByte[2] << 8) + lowestByte[3]);
					}
					return((lowestByte[3] << 24) + (lowestByte[2] << 16) + (lowestByte[1] << 8) + lowestByte[0]);
				}
				
				
				inline uint32 _4x8Bit_to_1x32Bit(const std::vector<uint8>& data, uint32 startIndex = 0, bool msbFirst = true)
				{
					if(data.size() < 4 + startIndex)
					{
						return(0);
					}
					
					if(msbFirst == true)
					{
						return((data.at(0 + startIndex) << 24) + (data.at(1 + startIndex) << 16) + (data.at(2 + startIndex) << 8) + data.at(3 + startIndex));
					}
					return((data.at(3 + startIndex) << 24) + (data.at(2 + startIndex) << 16) + (data.at(1 + startIndex) << 8) + data.at(0 + startIndex));
				}
				
				
				
				
				
				
				
				constexpr inline void _1x16Bit_to_2x8Bit(uint16 data, uint8 outBuffer[2], bool msbFirst = true)
				{
					if(msbFirst == true)
					{
						outBuffer[0] = (data & 0xFF00) >> 8;
						outBuffer[1] = (data & 0x00FF) >> 0;
					}
					else
					{
						outBuffer[0] = (data & 0x00FF) >> 0;
						outBuffer[1] = (data & 0xFF00) >> 8;
					}
				}
				
				
				constexpr inline void _1x32Bit_to_4x8Bit(uint32 data, uint8 outBuffer[4], bool msbFirst = true)
				{
					if(msbFirst == true)
					{
						outBuffer[0] = (data & 0xFF000000) >> 24;
						outBuffer[1] = (data & 0x00FF0000) >> 16;
						outBuffer[2] = (data & 0x0000FF00) >> 8;
						outBuffer[3] = (data & 0x000000FF) >> 0;
					}
					else
					{
						outBuffer[0] = (data & 0x000000FF) >> 0;
						outBuffer[1] = (data & 0x0000FF00) >> 8;
						outBuffer[2] = (data & 0x00FF0000) >> 16;
						outBuffer[3] = (data & 0xFF000000) >> 24;
					}
				}
				
				
				
				
				
				
				
				constexpr inline void double_to_8x8Bit(double data, uint8 outBuffer[8], bool msbFirst = true)
				{
					union convert
					{
						double d;
						uint8 u[8];
					};
					
					convert c = {0};
					c.d = data;
					
					if(msbFirst == false)
					{
						for(uint32 i = 0; i < 8; i++)
						{
							outBuffer[i] = c.u[i];
						}
					}
					else
					{
						for(uint32 i = 0; i < 8; i++)
						{
							outBuffer[i] = c.u[7 - i];
						}
					}
				}
				
				
				constexpr inline double _8x8Bit_to_double(const uint8* lowestByte, bool msbFirst = true)
				{
					union convert
					{
						double d;
						uint8 u[8];
					};
					
					convert c = {0};
					
					if(msbFirst == false)
					{
						for(uint32 i = 0; i < 8; i++)
						{
							c.u[i] = lowestByte[i];
						}
					}
					else
					{
						for(uint32 i = 0; i < 8; i++)
						{
							c.u[i] = lowestByte[7 - i];
						}
					}
					
					return(c.d);
				}
				
				
				inline double _8x8Bit_to_double(const std::vector<uint8>& data, uint32 startIndex = 0, bool msbFirst = true)
				{
					if(data.size() < 8 + startIndex)
					{
						return(0);
					}
					
					union convert
					{
						double d;
						uint8 u[8];
					};
					
					convert c = {0};
					
					if(msbFirst == false)
					{
						for(uint32 i = 0; i < 8; i++)
						{
							c.u[i] = data.at(i + startIndex);
						}
					}
					else
					{
						for(uint32 i = 0; i < 8; i++)
						{
							c.u[i] = data.at(7 - i + startIndex);
						}
					}
					
					return(c.d);
				}
				
				
				constexpr inline void float_to_4x8Bit(float data, uint8 outBuffer[4], bool msbFirst = true)
				{
					union convert
					{
						float d;
						uint8 u[4];
					};
					
					convert c = {0};
					c.d = data;
					
					if(msbFirst == false)
					{
						for(uint32 i = 0; i < 4; i++)
						{
							outBuffer[i] = c.u[i];
						}
					}
					else
					{
						for(uint32 i = 0; i < 4; i++)
						{
							outBuffer[i] = c.u[3 - i];
						}
					}
				}
				
				
				constexpr inline float _4x8Bit_to_float(const uint8* lowestByte, bool msbFirst = true)
				{
					union convert
					{
						float d;
						uint8 u[4];
					};
					
					convert c = {0};
					
					if(msbFirst == false)
					{
						for(uint32 i = 0; i < 4; i++)
						{
							c.u[i] = lowestByte[i];
						}
					}
					else
					{
						for(uint32 i = 0; i < 4; i++)
						{
							c.u[i] = lowestByte[3 - i];
						}
					}
					
					return(c.d);
				}
				
				
				inline float _4x8Bit_to_float(const std::vector<uint8>& data, uint32 startIndex = 0, bool msbFirst = true)
				{
					if(data.size() < 4 + startIndex)
					{
						return(0);
					}
					
					union convert
					{
						float d;
						uint8 u[4];
					};
					
					convert c = {0};
					
					if(msbFirst == false)
					{
						for(uint32 i = 0; i < 4; i++)
						{
							c.u[i] = data.at(i + startIndex);
						}
					}
					else
					{
						for(uint32 i = 0; i < 4; i++)
						{
							c.u[i] = data.at(3 - i + startIndex);
						}
					}
					
					return(c.d);
				}
			};
		};
		
		
		//	std::vector Extensions
		namespace vector
		{
			template<typename dataType>
			bool contains(const std::vector<dataType>& vector, const dataType& element)
			{
				if(std::find(vector.begin(), vector.end(), element) != vector.end())
				{
					return(true);
				}
				return(false);
			}
			
			
			template<typename dataType>
			void pushBackUnique(std::vector<dataType>& vector, const dataType& element)
			{
				if(contains(vector, element) == false)
				{
					vector.push_back(element);
				}
			}
			
			
			template<typename dataType>
			std::map<dataType, uint32> distribution(const std::vector<dataType>& vector)
			{
				std::map<dataType, uint32> distribution;
				for(auto& i: vector)
				{
					distribution[i]++;
				}
				return(distribution);
			}
			
			
			template<typename dataTypeIn, typename dataTypeOut>
			std::vector<dataTypeOut> convert(const std::vector<dataTypeIn>& vectorIn)
			{
				const uint32 N = vectorIn.size();
				std::vector<dataTypeOut> vectorOut(N, dataTypeOut());
				for(uint32 i = 0; i < N; i++)
				{
					vectorOut.at(i) = vectorIn.at(i);
				}
				return(vectorOut);
			}
		};
		
		
		namespace math
		{
			constexpr double c_pi = 3.141592653589793238463;
			
			constexpr inline double radToDeg(double radiant)
			{
				return(radiant * 180.0 / c_pi);
			}
			
			
			constexpr inline double degToRad(double degree)
			{
				return(degree * c_pi / 180.0);
			}
		};
	};
}