#pragma once

#include <ITN/defines.hpp>

#include <cmath>
#include <algorithm>





namespace ITN
{
	template<typename dataType>
	class Vector3
	{
		public:
			
			dataType x;
			dataType y;
			dataType z;
			
			
			
			
			
		private:
			
			
			
			
			
			
			
		public:
			
			constexpr inline Vector3();
			constexpr inline Vector3(dataType x, dataType y, dataType z);
			constexpr inline Vector3(Vector3& start, Vector3& end);
			
			
			constexpr inline double absolute() const;
			
			
			constexpr inline bool operator==(Vector3& v) const;
			constexpr inline bool operator!=(Vector3& v) const;
			
			constexpr inline Vector3 operator+(const Vector3& v) const;
			constexpr inline Vector3 operator-(const Vector3& v) const;
			constexpr inline dataType operator*(const Vector3& v) const;
			constexpr inline Vector3 operator*(dataType scalar) const;
			constexpr inline Vector3 operator/(dataType scalar) const;
			
			constexpr inline Vector3& operator+=(const Vector3& v);
			constexpr inline Vector3& operator-=(const Vector3& v);
			constexpr inline Vector3& operator*=(dataType scalar);
			constexpr inline Vector3& operator/=(dataType scalar);
			constexpr inline Vector3& operator=(const Vector3& v);
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
constexpr inline ITN::Vector3<dataType>::Vector3()
	:	x(0),
		y(0),
		z(0)
{
	
}


template<typename dataType>
constexpr inline ITN::Vector3<dataType>::Vector3(dataType x, dataType y, dataType z)
	: x(x),
		y(y),
		z(z)
{
	
}


template<typename dataType>
constexpr inline ITN::Vector3<dataType>::Vector3(Vector3& start, Vector3& end)
	:	x(end.x - start.x),
		y(end.y - start.y),
		z(end.z - start.z)
{
	
}







template<typename dataType>
constexpr inline double ITN::Vector3<dataType>::absolute() const
{
	return(std::sqrt((x * x) + (y * y) + (z * z)));
}







template<typename dataType>
constexpr inline bool ITN::Vector3<dataType>::operator==(Vector3& v) const
{
	if(x == v.x && y == v.y && z = v.z)
	{
		return(true);
	}
	return(false);
}


template<typename dataType>
constexpr inline bool ITN::Vector3<dataType>::operator!=(Vector3& v) const
{
	if(x != v.x || y != v.y || z != v.z)
	{
		return(true);
	}
	return(false);
}







template<typename dataType>
constexpr inline ITN::Vector3<dataType> ITN::Vector3<dataType>::operator+(const Vector3& v) const
{
	Vector3<dataType> result(x + v.x, y + v.y, z + v.z);
	return(result);
}

template<typename dataType>
constexpr inline ITN::Vector3<dataType> ITN::Vector3<dataType>::operator-(const Vector3& v) const
{
	Vector3<dataType> result(x - v.x, y - v.y, z - v.z);
	return(result);
}


template<typename dataType>
constexpr inline dataType ITN::Vector3<dataType>::operator*(const Vector3& v) const
{
	dataType result = x * v.x + y * v.y + z * v.z;
	return(result);
}


template<typename dataType>
constexpr inline ITN::Vector3<dataType> ITN::Vector3<dataType>::operator*(dataType scalar) const
{
	Vector3<dataType> result(x * scalar, y * scalar, z * scalar);
	return(result);
}


template<typename dataType>
constexpr inline ITN::Vector3<dataType> ITN::Vector3<dataType>::operator/(dataType scalar) const
{
	Vector3<dataType> result(x / scalar, y / scalar, z / scalar);
	return(result);
}







template<typename dataType>
constexpr inline ITN::Vector3<dataType>& ITN::Vector3<dataType>::operator+=(const Vector3& v)
{
	*this = *this + v;
	return(*this);
}


template<typename dataType>
constexpr inline ITN::Vector3<dataType>& ITN::Vector3<dataType>::operator-=(const Vector3& v)
{
	*this = *this - v;
	return(*this);
}


template<typename dataType>
constexpr inline ITN::Vector3<dataType>& ITN::Vector3<dataType>::operator*=(dataType scalar)
{
	*this = *this * scalar;
	return(*this);
}


template<typename dataType>
constexpr inline ITN::Vector3<dataType>& ITN::Vector3<dataType>::operator/=(dataType scalar)
{
	*this = *this / scalar;
	return(*this);
}


template<typename dataType>
constexpr inline ITN::Vector3<dataType>& ITN::Vector3<dataType>::operator=(const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	
	return(*this);
}