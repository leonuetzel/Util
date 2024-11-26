#include <ITN/util.hpp>

#include <algorithm>





namespace ITN
{
	namespace util
	{
		//	String
		namespace string
		{
			std::vector<std::string> explode(const std::string& string, const char delimiter)
			{
				std::vector<std::string> elements;
				if(string.length() == 0)
				{
					return(elements);
				}
				
				uint32 numberOfElements = std::count(string.begin(), string.end(), delimiter) + 1;
				elements.reserve(numberOfElements);
				
				std::size_t start = 0;
				for(uint32 i = 0; i < numberOfElements; i++)
				{
					std::size_t end = string.find(delimiter, start);
					elements.push_back(string.substr(start, end - start));
					start = end + 1;
				}
				if(elements.at(elements.size() - 1).length() == 0)
				{
					elements.erase(elements.begin() + elements.size() - 1);
				}
				return(elements);
			}
			
			
			std::vector<std::string> explodeIfNotInStringQuotes(const std::string& string, const char delimiter)
			{
				std::vector<std::string> elements;
				if(string.length() == 0)
				{
					return(elements);
				}
				
				const uint32 numberOfCharacters = string.length();
				bool isString = false;
				uint32 start = 0;
				for(uint32 i = 0; i < numberOfCharacters; i++)
				{
					const char& character(string.at(i));
					
					if(character == '\"')
					{
						if(isString == false)
						{
							isString = true;
						}
						else
						{
							isString = false;
						}
					}
					else
					{
						if(isString == false)
						{
							if(character == delimiter)
							{
								elements.push_back(string.substr(start, i - start));
								start = i + 1;
							}
						}
					}
				}
				if(start != numberOfCharacters)
				{
					elements.push_back(string.substr(start));
				}
				
				if(elements.at(elements.size() - 1).length() == 0)
				{
					elements.erase(elements.begin() + elements.size() - 1);
				}
				return(elements);
			}
			
			
			std::vector<std::string> explode(const std::string& string, const std::vector<char>& delimiter)
			{
				std::vector<std::string> elements;
				uint32 numberOfDelimiters = delimiter.size();
				
				uint32 numberOfElements = 0;
				for(uint32 i = 0; i < numberOfDelimiters; i++)
				{
					numberOfElements += std::count(string.begin(), string.end(), delimiter.at(i));
				}
				numberOfElements++;
				
				elements.reserve(numberOfElements);
				
				std::size_t start = 0;
				for(uint32 i = 0; i < numberOfElements; i++)
				{
					std::vector<std::size_t> end;
					for(uint32 j = 0; j < numberOfDelimiters; j++)
					{
						end.push_back(string.find(delimiter.at(j), start));
					}
					std::size_t end_min = *std::min(end.begin(), end.end());
					
					elements.push_back(string.substr(start, end_min - start));
					start = end_min + 1;
				}
				if(elements.at(elements.size() - 1).length() == 0)
				{
					elements.erase(elements.begin() + elements.size() - 1);
				}
				return(elements);
			}
			
			
			bool isDigit(const std::string& string)
			{
				uint32 numberOfCharacters = string.length();
				for(uint32 i = 0; i < numberOfCharacters; i++)
				{
					if(std::isdigit(string.at(i)) == false)
					{
						return(false);
					}
				}
				return(true);
			}
			
			
			std::string to_string(float value, uint32 decimalPlaces, char decimalPoint)
			{
				std::ostringstream stringStream;
				stringStream.precision(decimalPlaces);
				stringStream << std::fixed << value;
				
				std::string string(stringStream.str());
				if(decimalPoint != '.')
				{
					std::replace(string.begin(), string.end(), '.', decimalPoint);
				}
				return(string);
			}
			
			
			uint32 findMatchingBracket(const std::string& string, uint32 startPosition, char bracketOpening, char bracketClosing)
			{
				uint32 bracketCounter = 0;
				
				const uint32 numberOfCharacters = string.length();
				for(uint32 i = startPosition; i < numberOfCharacters; i++)
				{
					const char& character(string.at(i));
					if(character == bracketOpening)
					{
						bracketCounter++;
					}
					if(character == bracketClosing)
					{
						bracketCounter--;
						if(bracketCounter == 0)
						{
							return(i);
						}
					}
				}
				return(numberOfCharacters);
			}
			
			
			void eraseAllOccurences(std::string& string, char character)
			{
				string.erase(std::remove(string.begin(), string.end(), character), string.end());
			}
			
			
			std::string to_hexString(uint64 value, uint32 numberOfDigits)
			{
				if(numberOfDigits == 0)
				{
					numberOfDigits = std::log(value) / std::log(16);
				}
				
				std::stringstream stringStream;
				stringStream << std::uppercase << std::setfill('0') << std::setw(numberOfDigits) << std::hex << value;
				return("0x" + stringStream.str());
			}
		};
		
		
		//	Filesystem
		namespace filesystem
		{
			void deleteOnlyFilesRecursive(const std::filesystem::path& path)
			{
				for(auto& i: std::filesystem::directory_iterator(path))
				{
					if(i.is_directory() == false)
					{
						std::filesystem::remove(i.path());
					}
					else
					{
						deleteOnlyFilesRecursive(path / i.path());
					}
				}
			}
			
			
			void deleteWholeFolderContent(const std::filesystem::path& path)
			{
				deleteOnlyFilesRecursive(path);
				for(auto& i: std::filesystem::directory_iterator(path))
				{
					std::filesystem::remove(i.path());
				}
			}
			
			
			void copyWholeFolderContent(const std::filesystem::path& source, const std::filesystem::path& destination)
			{
				//	Create Folders first
				for(auto& i: std::filesystem::directory_iterator(source))
				{
					if(i.is_directory() == true)
					{
						const std::filesystem::path path_relative = std::filesystem::relative(i.path(), source);
						const std::filesystem::path subFolderPath = destination / path_relative;
						std::filesystem::create_directory(subFolderPath);
						
						
						//	Recursive Call for Subfolder
						copyWholeFolderContent(i.path(), subFolderPath);
					}
				}
				
				
				//	Copy Files after
				for(auto& i: std::filesystem::directory_iterator(source))
				{
					if(i.is_regular_file() == true)
					{
						std::filesystem::copy_file(i, destination / i.path().filename());
					}
				}
			}
		};
	};
};