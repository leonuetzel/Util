#include <ITN/base64.hpp>

#include <algorithm>





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

const std::map<uint8, char> ITN::BASE64::c_encodingTable = 
{
	{ 0,	'A'},
	{ 1,	'B'},
	{ 2,	'C'},
	{ 3,	'D'},
	{ 4,	'E'},
	{ 5,	'F'},
	{ 6,	'G'},
	{ 7,	'H'},
	{ 8,	'I'},
	{ 9,	'J'},
	{10,	'K'},
	{11,	'L'},
	{12,	'M'},
	{13,	'N'},
	{14,	'O'},
	{15,	'P'},
	{16,	'Q'},
	{17,	'R'},
	{18,	'S'},
	{19,	'T'},
	{20,	'U'},
	{21,	'V'},
	{22,	'W'},
	{23,	'X'},
	{24,	'Y'},
	{25,	'Z'},
	{26,	'a'},
	{27,	'b'},
	{28,	'c'},
	{29,	'd'},
	{30,	'e'},
	{31,	'f'},
	{32,	'g'},
	{33,	'h'},
	{34,	'i'},
	{35,	'j'},
	{36,	'k'},
	{37,	'l'},
	{38,	'm'},
	{39,	'n'},
	{40,	'o'},
	{41,	'p'},
	{42,	'q'},
	{43,	'r'},
	{44,	's'},
	{45,	't'},
	{46,	'u'},
	{47,	'v'},
	{48,	'w'},
	{49,	'x'},
	{50,	'y'},
	{51,	'z'},
	{52,	'0'},
	{53,	'1'},
	{54,	'2'},
	{55,	'3'},
	{56,	'4'},
	{57,	'5'},
	{58,	'6'},
	{59,	'7'},
	{60,	'8'},
	{61,	'9'},
	{62,	'+'},
	{63,	'/'},
	{64,	'='}
};

const std::map<char, uint8> ITN::BASE64::c_decodingTable = 
{
	{'A',  0},
	{'B',  1},
	{'C',  2},
	{'D',  3},
	{'E',  4},
	{'F',  5},
	{'G',  6},
	{'H',  7},
	{'I',  8},
	{'J',  9},
	{'K', 10},
	{'L', 11},
	{'M', 12},
	{'N', 13},
	{'O', 14},
	{'P', 15},
	{'Q', 16},
	{'R', 17},
	{'S', 18},
	{'T', 19},
	{'U', 20},
	{'V', 21},
	{'W', 22},
	{'X', 23},
	{'Y', 24},
	{'Z', 25},
	{'a', 26},
	{'b', 27},
	{'c', 28},
	{'d', 29},
	{'e', 30},
	{'f', 31},
	{'g', 32},
	{'h', 33},
	{'i', 34},
	{'j', 35},
	{'k', 36},
	{'l', 37},
	{'m', 38},
	{'n', 39},
	{'o', 40},
	{'p', 41},
	{'q', 42},
	{'r', 43},
	{'s', 44},
	{'t', 45},
	{'u', 46},
	{'v', 47},
	{'w', 48},
	{'x', 49},
	{'y', 50},
	{'z', 51},
	{'0', 52},
	{'1', 53},
	{'2', 54},
	{'3', 55},
	{'4', 56},
	{'5', 57},
	{'6', 58},
	{'7', 59},
	{'8', 60},
	{'9', 61},
	{'+', 62},
	{'/', 63},
	{'=', 64}
};



const std::map<uint8, char> ITN::BASE64::c_encodingTable_url = 
{
	{ 0,	'A'},
	{ 1,	'B'},
	{ 2,	'C'},
	{ 3,	'D'},
	{ 4,	'E'},
	{ 5,	'F'},
	{ 6,	'G'},
	{ 7,	'H'},
	{ 8,	'I'},
	{ 9,	'J'},
	{10,	'K'},
	{11,	'L'},
	{12,	'M'},
	{13,	'N'},
	{14,	'O'},
	{15,	'P'},
	{16,	'Q'},
	{17,	'R'},
	{18,	'S'},
	{19,	'T'},
	{20,	'U'},
	{21,	'V'},
	{22,	'W'},
	{23,	'X'},
	{24,	'Y'},
	{25,	'Z'},
	{26,	'a'},
	{27,	'b'},
	{28,	'c'},
	{29,	'd'},
	{30,	'e'},
	{31,	'f'},
	{32,	'g'},
	{33,	'h'},
	{34,	'i'},
	{35,	'j'},
	{36,	'k'},
	{37,	'l'},
	{38,	'm'},
	{39,	'n'},
	{40,	'o'},
	{41,	'p'},
	{42,	'q'},
	{43,	'r'},
	{44,	's'},
	{45,	't'},
	{46,	'u'},
	{47,	'v'},
	{48,	'w'},
	{49,	'x'},
	{50,	'y'},
	{51,	'z'},
	{52,	'0'},
	{53,	'1'},
	{54,	'2'},
	{55,	'3'},
	{56,	'4'},
	{57,	'5'},
	{58,	'6'},
	{59,	'7'},
	{60,	'8'},
	{61,	'9'},
	{62,	'-'},
	{63,	'_'},
	{64,	'\0'}
};

const std::map<char, uint8> ITN::BASE64::c_decodingTable_url = 
{
	{'A',  0},
	{'B',  1},
	{'C',  2},
	{'D',  3},
	{'E',  4},
	{'F',  5},
	{'G',  6},
	{'H',  7},
	{'I',  8},
	{'J',  9},
	{'K', 10},
	{'L', 11},
	{'M', 12},
	{'N', 13},
	{'O', 14},
	{'P', 15},
	{'Q', 16},
	{'R', 17},
	{'S', 18},
	{'T', 19},
	{'U', 20},
	{'V', 21},
	{'W', 22},
	{'X', 23},
	{'Y', 24},
	{'Z', 25},
	{'a', 26},
	{'b', 27},
	{'c', 28},
	{'d', 29},
	{'e', 30},
	{'f', 31},
	{'g', 32},
	{'h', 33},
	{'i', 34},
	{'j', 35},
	{'k', 36},
	{'l', 37},
	{'m', 38},
	{'n', 39},
	{'o', 40},
	{'p', 41},
	{'q', 42},
	{'r', 43},
	{'s', 44},
	{'t', 45},
	{'u', 46},
	{'v', 47},
	{'w', 48},
	{'x', 49},
	{'y', 50},
	{'z', 51},
	{'0', 52},
	{'1', 53},
	{'2', 54},
	{'3', 55},
	{'4', 56},
	{'5', 57},
	{'6', 58},
	{'7', 59},
	{'8', 60},
	{'9', 61},
	{'-', 62},
	{'_', 63},
	{'\0', 64}
};



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

std::string ITN::BASE64::encode(std::vector<uint8> input, const std::map<uint8, char>& table)
{
	std::string output;
	
	uint32 numberOfBytes = input.size();
	uint32 numberOfBlocks = numberOfBytes / 3;
	
	//	Calculate Number of Output Characters needed for Padding with '=' before padding input Data with 0
	uint32 numberOfOutputCharacters = numberOfBlocks * 4;
	switch(numberOfBytes % 3)
	{
		case 1:
			numberOfOutputCharacters += 2;
			break;
			
		case 2:
			numberOfOutputCharacters += 3;
			break;
			
		default:
			break;
	}
	
	if(numberOfBytes % 3 != 0)
	{
		numberOfBlocks++;
		while(numberOfBytes % 3 != 0)
		{
			input.push_back(0);
			numberOfBytes = input.size();
		}
	}
	
	for(uint32 i = 0; i < numberOfBlocks; i++)
	{
		uint8 bytes[3] =
		{
			input.at(i * 3 + 0),
			input.at(i * 3 + 1),
			input.at(i * 3 + 2)
		};
		
		uint8 chunks[4];
		chunks[0] = ( bytes[0] & 0xFC) >> 2;
		chunks[1] = ((bytes[0] & 0x03) << 4) | ((bytes[1] & 0xF0) >> 4);
		chunks[2] = ((bytes[1] & 0x0F) << 2) | ((bytes[2] & 0xC0) >> 6);
		chunks[3] =   bytes[2] & 0x3F;
		
		for(uint32 j = 0; j < 4; j++)
		{
			output += table.at(chunks[j]);
		}
	}
	
	for(uint32 i = numberOfOutputCharacters; i < output.length(); i++)
	{
		output.at(i) = table.at(64);
	}
	
	if(table.at(64) == '\0')
	output.erase(numberOfOutputCharacters);
	
	return(output);
}


std::vector<uint8> ITN::BASE64::decode(std::string input, const std::map<char, uint8>& table)
{
	std::vector<uint8> output;
	
	if(is_validCode(input, table) == false)
	{
		return(output);
	}
	
	//	Find padding Character in decoding Table
	char padding;
	{
		bool found = false;
		for(auto& i: table)
		{
			if(i.second == 64)
			{
				padding = i.first;
				found = true;
				break;
			}
		}
		if(found == false)
		{
			padding = '\0';
		}
	}
	
	
	uint32 numberOfCharacters = input.length();
	while(numberOfCharacters % 4 != 0)
	{
		input += padding;
	}
	
	
	
	//	Count Padding Characters needed to shorten the Output String later
	uint32 numberOfPaddingCharacters = std::count(input.begin(), input.end(), padding);
	
	
	
	const uint32 numberOfBlocks = numberOfCharacters / 4;
	for(uint32 i = 0; i < numberOfBlocks; i++)
	{
		char encoded[4] =
		{
			input.at(i * 4 + 0),
			input.at(i * 4 + 1),
			input.at(i * 4 + 2),
			input.at(i * 4 + 3)
		};
		
		uint8 decoded[4] =
		{
			table.at(encoded[0]),
			table.at(encoded[1]),
			table.at(encoded[2]),
			table.at(encoded[3]),
		};
		
		uint8 bytes[3];
		
		bytes[0] = ((decoded[0] & 0x3F) << 2) | ((decoded[1] & 0x30) >> 4);
		bytes[1] = ((decoded[1] & 0x0F) << 4) | ((decoded[2] & 0x3C) >> 2);
		bytes[2] = ((decoded[2] & 0x03) << 6) | ((decoded[3] & 0x3F) >> 0);
		
		output.push_back(bytes[0]);
		output.push_back(bytes[1]);
		output.push_back(bytes[2]);
	}
	
	switch(numberOfPaddingCharacters)
	{
		case 1:
			output.pop_back();
			break;
			
		case 2:
			output.pop_back();
			output.pop_back();
			break;
			
		default:
			break;
	}
	return(output);
}







bool ITN::BASE64::is_validCode(const std::string code, const std::map<char, uint8>& table)
{
	char padding;
	{
		bool found = false;
		for(auto& i: table)
		{
			if(i.second == 64)
			{
				padding = i.first;
				found = true;
				break;
			}
		}
		if(found == false)
		{
			return(false);
		}
	}
	
	uint32 numberOfPaddingCharacters = 0;
	const uint32 numberOfCharacters = code.length();
	for(uint32 i = 0; i < numberOfCharacters; i++)
	{
		if(table.find(code.at(i)) == table.end())
		{
			return(false);
		}
		if(code.at(i) == padding)
		{
			numberOfPaddingCharacters++;
			if(numberOfPaddingCharacters > 2)
			{
				return(false);
			}
		}
		else
		{
			if(numberOfPaddingCharacters > 0)
			{
				return(false);
			}
		}
	}
	return(true);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

std::string ITN::BASE64::encode(std::string input)
{
	std::vector<uint8> bytes;
	const uint32 numberOfCharacters = input.length();
	for(uint32 i = 0; i < numberOfCharacters; i++)
	{
		bytes.push_back((uint8) input.at(i));
	}
	
	return(encode(bytes, c_encodingTable));
}


std::string ITN::BASE64::encode_url(std::string input)
{
	std::vector<uint8> bytes;
	const uint32 numberOfCharacters = input.length();
	for(uint32 i = 0; i < numberOfCharacters; i++)
	{
		bytes.push_back((uint8) input.at(i));
	}
	
	return(encode(bytes, c_encodingTable_url));
}







std::string ITN::BASE64::encode(const std::vector<uint8>& input)
{
	return(encode(input, c_encodingTable));
}


std::string ITN::BASE64::encode_url(const std::vector<uint8>& input)
{
	return(encode(input, c_encodingTable_url));
}







std::vector<uint8> ITN::BASE64::decode(const std::string& input)
{
	return(decode(input, c_decodingTable));
}


std::vector<uint8> ITN::BASE64::decode_url(const std::string& input)
{
	return(decode(input, c_decodingTable_url));
}