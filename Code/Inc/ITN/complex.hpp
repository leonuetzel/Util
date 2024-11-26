#pragma once

#include <ITN/defines.hpp>

#include <cmath>





namespace ITN
{
	template<typename dataType>
	class Complex
	{
		public:
			
			dataType x;
			dataType y;
			
			
			
			
			
		private:
			
			
			
			
			
			
			
		public:
			
			constexpr Complex();
			constexpr Complex(dataType x, dataType y);
			
			
			constexpr double absolute() const;
			
			
			constexpr bool operator==(Complex& z) const;
			constexpr bool operator!=(Complex& z) const;
			
			constexpr Complex operator+(const Complex& z) const;
			constexpr Complex operator-(const Complex& z) const;
			constexpr Complex operator*(const Complex& z) const;
			constexpr Complex operator*(dataType scalar) const;
			constexpr Complex operator/(const Complex& z) const;
			constexpr Complex operator/(dataType scalar) const;
			
			constexpr Complex& operator+=(const Complex& z);
			constexpr Complex& operator-=(const Complex& z);
			constexpr Complex& operator*=(const Complex& z);
			constexpr Complex& operator*=(dataType scalar);
			constexpr Complex& operator/=(const Complex& z);
			constexpr Complex& operator/=(dataType scalar);
			constexpr Complex& operator=(const Complex& z);
	};
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

template<typename dataType>
constexpr ITN::Complex<dataType>::Complex()
	:	x(0),
		y(0)
{
	
}


template<typename dataType>
constexpr ITN::Complex<dataType>::Complex(dataType x, dataType y)
	: x(x),
		y(y)
{
	
}







template<typename dataType>
constexpr double ITN::Complex<dataType>::absolute() const
{
	return(std::sqrt((x * x) + (y * y)));
}







template<typename dataType>
constexpr bool ITN::Complex<dataType>::operator==(Complex& z) const
{
	if(x == z.x && y == z.y)
	{
		return(true);
	}
	return(false);
}


template<typename dataType>
constexpr bool ITN::Complex<dataType>::operator!=(Complex& z) const
{
	if(x != z.x || y != z.y)
	{
		return(true);
	}
	return(false);
}







template<typename dataType>
constexpr ITN::Complex<dataType> ITN::Complex<dataType>::operator+(const Complex& z) const
{
	Complex<dataType> result(x + z.x, y + z.y);
	return(result);
}


template<typename dataType>
constexpr ITN::Complex<dataType> ITN::Complex<dataType>::operator-(const Complex& z) const
{
	Complex<dataType> result(x - z.x, y - z.y);
	return(result);
}


template<typename dataType>
constexpr ITN::Complex<dataType> ITN::Complex<dataType>::operator*(const Complex& z) const
{
	Complex<dataType> result(x * z.x - y * z.y, x * z.y + y * z.x);
	return(result);
}


template<typename dataType>
constexpr ITN::Complex<dataType> ITN::Complex<dataType>::operator*(dataType scalar) const
{
	Complex<dataType> result(x * scalar, y * scalar);
	return(result);
}


template<typename dataType>
constexpr ITN::Complex<dataType> ITN::Complex<dataType>::operator/(const Complex& z) const
{
	Complex<dataType> result(x * z.x + y * z.y, y * z.x - x * z.y);
	result /= z.x * z.x + z.y * z.y;
	return(result);
}


template<typename dataType>
constexpr ITN::Complex<dataType> ITN::Complex<dataType>::operator/(dataType scalar) const
{
	Complex<dataType> result(x / scalar, y / scalar);
	return(result);
}







template<typename dataType>
constexpr ITN::Complex<dataType>& ITN::Complex<dataType>::operator+=(const Complex& z)
{
	*this = *this + z;
	return(*this);
}


template<typename dataType>
constexpr ITN::Complex<dataType>& ITN::Complex<dataType>::operator-=(const Complex& z)
{
	*this = *this - z;
	return(*this);
}


template<typename dataType>
constexpr ITN::Complex<dataType>& ITN::Complex<dataType>::operator*=(const Complex& z)
{
	*this = *this * z;
	return(*this);
}


template<typename dataType>
constexpr ITN::Complex<dataType>& ITN::Complex<dataType>::operator*=(dataType scalar)
{
	*this = *this * scalar;
	return(*this);
}


template<typename dataType>
constexpr ITN::Complex<dataType>& ITN::Complex<dataType>::operator/=(const Complex& z)
{
	*this = *this / z;
	return(*this);
}


template<typename dataType>
constexpr ITN::Complex<dataType>& ITN::Complex<dataType>::operator/=(dataType scalar)
{
	*this = *this / scalar;
	return(*this);
}


template<typename dataType>
constexpr ITN::Complex<dataType>& ITN::Complex<dataType>::operator=(const Complex& z)
{
	x = z.x;
	y = z.y;
	
	return(*this);
}