#include <ITN/outputFile.hpp>





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

ITN::OutputFile::OutputFile(std::filesystem::path path)
	:	std::string(),
		m_path(path),
		m_outputStream(path, std::ios::out)
{
	if(is_valid() == true)
	{
		m_outputStream.clear();
	}
}


ITN::OutputFile::~OutputFile()
{
	if(m_outputStream.is_open() == true)
	{
		m_outputStream.close();
	}
}







std::filesystem::path ITN::OutputFile::get_path() const
{
	return(m_path);
}


bool ITN::OutputFile::is_valid() const
{
	if(m_path.empty() == true)
	{
		return(false);
	}
	return(true);
}


void ITN::OutputFile::clear()
{
	std::string::clear();
}


void ITN::OutputFile::save()
{
	m_outputStream << *this;
}


ITN::OutputFile& ITN::OutputFile::operator=(const std::string& string)
{
	std::string::operator=(string);
	return(*this);
}