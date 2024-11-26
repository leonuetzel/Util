#include <ITN/inputFileBinary.hpp>





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

std::filesystem::path ITN::InputFileBinary::openFileDialog(std::string title, std::filesystem::path initialPath, std::string extensionFilter, HWND hWnd)
{
	char filename[MAX_PATH];
	std::string initialPath_string(initialPath.string());
	initialPath_string += "\\*";
	uint32_t initialPath_stringLength = initialPath_string.length();
	if(initialPath_stringLength >= MAX_PATH)
	{
		return("");
	}
	
	for(uint32_t i = 0; i < initialPath_stringLength; i++)
	{
		filename[i] = initialPath_string.at(i);
	}
	filename[initialPath_stringLength] = '\0';
	
	
	
  OPENFILENAME ofn;
	ZeroMemory(&ofn,      sizeof(ofn));
	ofn.lStructSize  		= sizeof(ofn);
	ofn.hwndOwner    		= hWnd;
	ofn.lpstrFilter  		= extensionFilter.c_str();
	ofn.lpstrFile    		= filename;
	ofn.nMaxFile     		= MAX_PATH;
	ofn.lpstrTitle   		= title.c_str();
	ofn.Flags        		= OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
  
	if(GetOpenFileNameA(&ofn))
  {
		return(filename);
	}
	else
	{
		return("");
	}
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

ITN::InputFileBinary::InputFileBinary(std::filesystem::path path)
	:	m_valid(false)
{
	if(std::filesystem::exists(path) == false)
	{
		return;
	}
	
	m_file.open(path, std::ios::in | std::ios::binary);
	if(m_file.good() == false)
	{
		return;
	}
	m_path = path;
	m_size = std::filesystem::file_size(path);
	
	m_data = std::vector<uint8>(std::istreambuf_iterator<char>(m_file), std::istreambuf_iterator<char>());
	m_valid = true;
}


ITN::InputFileBinary::InputFileBinary(std::string title, std::filesystem::path initialPath, std::string extensionFilter, HWND hWnd)
	:	InputFileBinary(openFileDialog(title, initialPath, extensionFilter, hWnd))
{
	
}


ITN::InputFileBinary::~InputFileBinary()
{
	if(m_file.is_open() == true)
	{
		m_file.close();
	}
}







std::filesystem::path ITN::InputFileBinary::get_path() const
{
	return(m_path);
}


bool ITN::InputFileBinary::is_valid() const
{
	return(m_valid);
}


const std::vector<uint8>& ITN::InputFileBinary::get_data() const
{
	return(m_data);
}


uint32 ITN::InputFileBinary::get_size() const
{
	return(m_size);
}