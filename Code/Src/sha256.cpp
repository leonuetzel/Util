#include <ITN/sha256.hpp>
#include <ITN/util.hpp>





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

const uint32 ITN::SHA256::c_hashValues[8] =
{
	0x6A09E667,
	0xBB67AE85,
	0x3C6EF372,
	0xA54FF53A,
	0x510E527F,
	0x9B05688C,
	0x1F83D9AB,
	0x5BE0CD19
};

const uint32 ITN::SHA256::c_roundConstants[64] =
{
	0x428A2F98,
	0x71374491,
	0xB5C0FBCF,
	0xE9B5DBA5,
  0x3956C25B,
	0x59F111F1,
	0x923F82A4,
	0xAB1C5ED5,
  0xD807AA98,
	0x12835B01,
	0x243185BE,
	0x550C7DC3,
  0x72BE5D74,
	0x80DEB1FE,
	0x9BDC06A7,
	0xC19BF174,
  0xE49B69C1,
	0xEFBE4786,
	0x0FC19DC6,
	0x240CA1CC,
  0x2DE92C6F,
	0x4A7484AA,
	0x5CB0A9DC,
	0x76F988DA,
  0x983E5152,
	0xA831C66D,
	0xB00327C8,
	0xBF597FC7,
  0xC6E00BF3,
	0xD5A79147,
	0x06CA6351,
	0x14292967,
  0x27B70A85,
	0x2E1B2138,
	0x4D2C6DFC,
	0x53380D13,
  0x650A7354,
	0x766A0ABB,
	0x81C2C92E,
	0x92722C85,
  0xA2BFE8A1,
	0xA81A664B,
	0xC24B8B70,
	0xC76C51A3,
  0xD192E819,
	0xD6990624,
	0xF40E3585,
	0x106AA070,
  0x19A4C116,
	0x1E376C08,
	0x2748774C,
	0x34B0BCB5,
  0x391C0CB3,
	0x4ED8AA4A,
	0x5B9CCA4F,
	0x682E6FF3,
  0x748F82EE,
	0x78A5636F,
	0x84C87814,
	0x8CC70208,
  0x90BEFFFA,
	0xA4506CEB,
	0xBEF9A3F7,
	0xC67178F2
};



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

ITN::SHA256::SHA256(const std::string& input)
	:	SHA256(std::vector<uint8>(input.begin(), input.end()))
{
	
}


ITN::SHA256::SHA256(const std::vector<uint8>& input)
	:	m_input(input)
{
	m_output.clear();
	std::vector<uint8> data(input);
	
	
	
	//	Append a single 1 and pad with 0 until data is multiple of 512 - 64 = (n * 512) + 448 Bits
	data.push_back(0x80);
	while(data.size() % c_blockSizeInBytes != c_blockSizeInBytes - 8)
	{
		data.push_back(0);
	}
	
	
	//	Append 64 Bits = 8 Bytes representing the Length of the Input String in !BIG ENDIAN! and Bits
	{
		uint64 length = input.size() * 8;
		for(uint32 i = 0; i < sizeof(length); i++)
		{
			const uint8 byteNumber = sizeof(length) - i - 1;
			const uint64 mask = util::bit::shift_left<uint64>(0xFF, 8 * byteNumber);
			const uint8 byte = (length & mask) >> (8 * byteNumber);
			data.push_back(byte);
		}
	}
	
	
	//	Loop over every Block
	uint32 numberOfBlocks = data.size() / c_blockSizeInBytes;
	if(data.size() % c_blockSizeInBytes != 0)
	{
		numberOfBlocks++;
	}
	for(uint32 i = 0; i < numberOfBlocks; i++)
	{
		//	Write Input Data in the first 16 Words of the Block and pad the remaining 48 Words with 0
		uint32 block[64];
		for(uint32 j = 0; j < c_blockSizeInBytes / sizeof(uint32); j++)
		{
			const uint32 index_block	= i * c_blockSizeInBytes;
			const uint32 index_word		= j * 4;
			
			const uint8 byte[sizeof(uint32)] =
			{
				data.at(index_block + index_word + 0),
				data.at(index_block + index_word + 1),
				data.at(index_block + index_word + 2),
				data.at(index_block + index_word + 3)
			};
			
			block[j] = (byte[0] << 24) | (byte[1] << 16) | (byte[2] << 8) | (byte[3] << 0);
		}
		
		for(uint32 j = c_blockSizeInBytes / sizeof(uint32); j < 64; j++)
		{
			block[j] = 0;
		}
		
		
		
		//	Modify the zero-ed 48 Words
		for(uint32 j = c_blockSizeInBytes / sizeof(uint32); j < 64; j++)
		{
			uint32 s0 = util::bit::rotate_right(block[j - 15],  7) ^ util::bit::rotate_right(block[j - 15], 18) ^ util::bit::shift_right(block[j - 15],  3);
			uint32 s1 = util::bit::rotate_right(block[j -  2], 17) ^ util::bit::rotate_right(block[j -  2], 19) ^ util::bit::shift_right(block[j -  2], 10);
			block[j] = block[j - 16] + s0 + block[j - 7] + s1;
		}
		
		
		
		//	Compression
		uint32 hashes[8] = 
		{
			c_hashValues[0],
			c_hashValues[1],
			c_hashValues[2],
			c_hashValues[3],
			c_hashValues[4],
			c_hashValues[5],
			c_hashValues[6],
			c_hashValues[7]
		};
		
		for(uint32 j = 0; j < 64; j++)
		{
			uint32 s1			= util::bit::rotate_right(hashes[4], 6) ^ util::bit::rotate_right(hashes[4], 11) ^ util::bit::rotate_right(hashes[4], 25);
			uint32 ch			= (hashes[4] & hashes[5]) ^ (~hashes[4] & hashes[6]);
			uint32 temp1	= hashes[7] + s1 + ch + c_roundConstants[j] + block[j];
			uint32 s0			= util::bit::rotate_right(hashes[0], 2) ^ util::bit::rotate_right(hashes[0], 13) ^ util::bit::rotate_right(hashes[0], 22);
			uint32 maj 		= (hashes[0] & hashes[1]) ^ (hashes[0] & hashes[2]) ^ (hashes[1] & hashes[2]);
			uint32 temp2	= s0 + maj;
			
			hashes[7] = hashes[6];
			hashes[6] = hashes[5];
			hashes[5] = hashes[4];
			hashes[4] = hashes[3] + temp1;
			hashes[3] = hashes[2];
			hashes[2] = hashes[1];
			hashes[1] = hashes[0];
			hashes[0] = temp1 + temp2;
		}
		
		uint32 hashes_final[8];
		for(uint32 j = 0; j < 8; j++)
		{
			hashes_final[j] = c_hashValues[j] + hashes[j];
		}
		
		for(uint32 j = 0; j < 8; j++)
		{
			for(uint32 k = 0; k < 4; k++)
			{
				uint32 shift = (3 - k) * 8;
				uint32 mask = util::bit::shift_left<uint32>(0xFF, shift);
				m_output.push_back((hashes_final[j] & mask) >> shift);
			}
		}
	}
}







const std::vector<uint8>& ITN::SHA256::get_input()
{
	return(m_input);
}


const std::vector<uint8>& ITN::SHA256::get_hash()
{
	return(m_output);
}