#pragma once

#include <ITN/defines.hpp>

#include <vector>





namespace ITN
{
	template<typename dataType>
	class Matrix
	{
		public:
			
			
			
			
			
			
		private:
			
			std::vector<std::vector<dataType>> m_matrix;
			
			
			
			
			
		protected:
			
			void enableBoundaries(uint32 numberOfColumns, uint32 numberOfRows);
			
			
			
			
			
		public:
			
			Matrix();
			Matrix(uint32 numberOfColumns, uint32 numberOfRows);
			Matrix(uint32 numberOfColumns, uint32 numberOfRows, dataType defaultValue);
			~Matrix();
			
			inline uint32 get_numberOfRows() const;
			inline uint32 get_numberOfColumns() const;
			
			dataType get_cell(uint32 columnNumber, uint32 rowNumber) const;
			dataType& cell(uint32 columnNumber, uint32 rowNumber);
			std::vector<dataType> get_row(uint32 rowNumber) const;
			std::vector<dataType>& get_row(uint32 rowNumber);
			std::vector<dataType> get_column(uint32 columnNumber) const;
			
			void insert_row(uint32 rowNumber, std::vector<dataType>& row);
			void insert_column(uint32 columnNumber, std::vector<dataType>& column);
			
			void append_row(std::vector<dataType>& row);
			void append_column(std::vector<dataType>& column);
			
			void clear();
			feedback delete_row(uint32 rowNumber);
			feedback delete_column(uint32 columnNumber);
			
			void fill(dataType fillValue);
			void set_row(uint32 rowNumber, std::vector<dataType> row);
			void set_column(uint32 columnNumber, std::vector<dataType> column);
			void set_cell(uint32 columnNumber, uint32 rowNumber, dataType value);
			
			Matrix& operator+=(const Matrix& matrix);
			Matrix operator+(const Matrix& matrix) const;
	};
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/

template<typename dataType>
void ITN::Matrix<dataType>::enableBoundaries(uint32 numberOfColumns, uint32 numberOfRows)
{
	if(numberOfRows == 0 && numberOfColumns == 0)
	{
		return;
	}
	
	if(numberOfRows == 0 && numberOfColumns > 0)
	{
		numberOfRows = 1;
	}
	
	if(m_matrix.size() < numberOfRows)
	{
		m_matrix.resize(numberOfRows);
	}
	
	if(m_matrix.at(0).size() > numberOfColumns)
	{
		numberOfColumns = m_matrix.at(0).size();
	}
	
	for(uint32 i = 0; i < m_matrix.size(); i++)
	{
		if(m_matrix.at(i).size() < numberOfColumns)
		{
			m_matrix.at(i).resize(numberOfColumns);
		}
	}
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

template<typename dataType>
ITN::Matrix<dataType>::Matrix()
{
	
}


template<typename dataType>
ITN::Matrix<dataType>::Matrix(uint32 numberOfColumns, uint32 numberOfRows)
{
	enableBoundaries(numberOfColumns, numberOfRows);
}


template<typename dataType>
ITN::Matrix<dataType>::Matrix(uint32 numberOfColumns, uint32 numberOfRows, dataType defaultValue)
{
	enableBoundaries(numberOfColumns, numberOfRows);
	fill(defaultValue);
}


template<typename dataType>
ITN::Matrix<dataType>::~Matrix()
{
	
}







template<typename dataType>
inline uint32 ITN::Matrix<dataType>::get_numberOfRows() const
{
	return(m_matrix.size());
}


template<typename dataType>
inline uint32 ITN::Matrix<dataType>::get_numberOfColumns() const
{
	if(m_matrix.size() > 0)
	{
		return(m_matrix.at(0).size());
	}
	return(0);
}







template<typename dataType>
dataType ITN::Matrix<dataType>::get_cell(uint32 columnNumber, uint32 rowNumber) const
{
	dataType cell = dataType();
	if(rowNumber < m_matrix.size())
	{
		if(columnNumber < m_matrix.at(rowNumber).size())
		{
			cell = m_matrix.at(rowNumber).at(columnNumber);
		}
	}
	return(cell);
}


template<typename dataType>
dataType& ITN::Matrix<dataType>::cell(uint32 columnNumber, uint32 rowNumber)
{
	if(rowNumber < m_matrix.size())
	{
		if(columnNumber < m_matrix.at(rowNumber).size())
		{
			return(m_matrix.at(rowNumber).at(columnNumber));
		}
	}
	return((dataType&) *((dataType*) 0));
}


template<typename dataType>
std::vector<dataType> ITN::Matrix<dataType>::get_row(uint32 rowNumber) const
{
	std::vector<dataType> row;
	if(rowNumber < m_matrix.size())
	{
		row = m_matrix.at(rowNumber);
	}
	return(row);
}


template<typename dataType>
std::vector<dataType>& ITN::Matrix<dataType>::get_row(uint32 rowNumber)
{
	if(rowNumber < m_matrix.size())
	{
		return(m_matrix.at(rowNumber));
	}
	return((std::vector<dataType>&) *((std::vector<dataType>*) 0));
}


template<typename dataType>
std::vector<dataType> ITN::Matrix<dataType>::get_column(uint32 columnNumber) const
{
	std::vector<dataType> column;
	if(get_numberOfColumns() <= columnNumber)
	{
		return(column);
	}
	
	uint32 numberOfRows = get_numberOfRows();
	for(uint32 i = 0; i < numberOfRows; i++)
	{
		column.push_back(m_matrix.at(i).at(columnNumber));
	}
	return(column);
}







template<typename dataType>
void ITN::Matrix<dataType>::insert_row(uint32 rowNumber, std::vector<dataType>& row)
{
	bool empty = false;
	if(m_matrix.size() == 0)
	{
		empty = true;
	}
	
	enableBoundaries(row.size(), 0);
	
	if(row.size() < m_matrix.at(0).size())
	{
		row.resize(m_matrix.at(0).size());
	}
	
	if(empty == false)
	{
		m_matrix.insert(m_matrix.begin() + rowNumber, row);
	}
	else
	{
		m_matrix.at(0) = row;
	}
}


template<typename dataType>
void ITN::Matrix<dataType>::insert_column(uint32 columnNumber, std::vector<dataType>& column)
{
	enableBoundaries(0, column.size());
	
	if(column.size() < m_matrix.size())
	{
		column.resize(m_matrix.size());
	}
	
	for(uint32 i = 0; i < m_matrix.size(); i++)
	{
		m_matrix.at(i).insert(m_matrix.at(i).begin() + columnNumber, column.at(i));
	}
}







template<typename dataType>
void ITN::Matrix<dataType>::append_row(std::vector<dataType>& row)
{
	bool empty = false;
	if(m_matrix.size() == 0)
	{
		empty = true;
	}
	
	enableBoundaries(row.size(), 0);
	
	if(row.size() < m_matrix.at(0).size())
	{
		row.resize(m_matrix.at(0).size());
	}
	
	if(empty == false)
	{
		m_matrix.push_back(row);
	}
	else
	{
		m_matrix.at(0) = row;
	}
}


template<typename dataType>
void ITN::Matrix<dataType>::append_column(std::vector<dataType>& column)
{
	enableBoundaries(0, column.size());
	
	if(column.size() < m_matrix.size())
	{
		column.resize(m_matrix.size());
	}
	
	for(uint32 i = 0; i < m_matrix.size(); i++)
	{
		m_matrix.at(i).push_back(column.at(i));
	}
}







template<typename dataType>
void ITN::Matrix<dataType>::clear()
{
	m_matrix.clear();
}


template<typename dataType>
ITN::feedback ITN::Matrix<dataType>::delete_row(uint32 rowNumber)
{
	if(rowNumber < m_matrix.size())
	{
		m_matrix.erase(m_matrix.begin() + rowNumber);
		return(OK);
	}
	return(FAIL);
}


template<typename dataType>
ITN::feedback ITN::Matrix<dataType>::delete_column(uint32 columnNumber)
{
	uint32 numberOfRows = get_numberOfRows();
	if(get_numberOfColumns() <= columnNumber || numberOfRows == 0)
	{
		return(FAIL);
	}
	
	for(uint32 i = 0; i < numberOfRows; i++)
	{
		std::vector<dataType>& row = m_matrix.at(i);
		row.erase(row.begin() + columnNumber);
	}
	return(OK);
}







template<typename dataType>
void ITN::Matrix<dataType>::fill(dataType fillValue)
{
	for(auto& i: m_matrix)
	{
		for(auto& j: i)
		{
			j = fillValue;
		}
	}
}


template<typename dataType>
void ITN::Matrix<dataType>::set_row(uint32 rowNumber, std::vector<dataType> row)
{
	enableBoundaries(row.size(), rowNumber + 1);
	if(row.size() < m_matrix.at(0).size())
	{
		row.resize(m_matrix.at(0).size());
	}
	m_matrix.at(rowNumber) = row;
}


template<typename dataType>
void ITN::Matrix<dataType>::set_column(uint32 columnNumber, std::vector<dataType> column)
{
	enableBoundaries(columnNumber + 1, column.size());
	if(column.size() < m_matrix.size())
	{
		column.resize(m_matrix.size());
	}
	for(uint32 i = 0; i < m_matrix.size(); i++)
	{
		m_matrix.at(i).at(columnNumber) = column.at(i);
	}
}


template<typename dataType>
void ITN::Matrix<dataType>::set_cell(uint32 columnNumber, uint32 rowNumber, dataType value)
{
	enableBoundaries(columnNumber + 1, rowNumber + 1);
	m_matrix.at(rowNumber).at(columnNumber) = value;
}







template<typename dataType>
ITN::Matrix<dataType>& ITN::Matrix<dataType>::operator+=(const Matrix& matrix)
{
	const uint32 numberOfRows = matrix.get_numberOfRows();
	for(uint32 i = 0; i < numberOfRows; i++)
	{
		std::vector row(matrix.get_row(i));
		append_row(row);
	}
	return(*this);
}


template<typename dataType>
ITN::Matrix<dataType> ITN::Matrix<dataType>::operator+(const Matrix& matrix) const
{
	Matrix matrixReturn;
	
	matrixReturn += *this;
	matrixReturn += matrix;
	
	return(matrixReturn);
}