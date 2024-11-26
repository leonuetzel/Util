#include <ITN/executionTime.hpp>
#include <ITN/outputFile.hpp>





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

std::vector<std::chrono::_V2::system_clock::time_point> ITN::ExecutionTime::m_timePoints;



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

void ITN::ExecutionTime::add_timePoint()
{
	m_timePoints.push_back(std::chrono::high_resolution_clock::now());
}


void ITN::ExecutionTime::save(std::filesystem::path path)
{
	OutputFile file(path);
	if(file.is_valid() == false)
	{
		return;
	}
	
	uint32 numberOfTimePoints = m_timePoints.size();
	for(uint32 i = 1; i < numberOfTimePoints; i++)
	{
		file += "[" + std::to_string(i) + "] - ";
	  file += std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(m_timePoints.at(i) - m_timePoints.at(i - 1)).count());
		file += "\n";
	}
	file.save();
}


void ITN::ExecutionTime::clear()
{
	m_timePoints.clear();
}