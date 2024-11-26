#pragma once

#include <ITN/defines.hpp>

#include <cmath>
#include <algorithm>





namespace ITN
{
	template<typename dataType>
	class Vector2
	{
		public:
			
			dataType x;
			dataType y;
			
			
			
			
			
		private:
			
			
			
			
			
			
			
		public:
			
			constexpr inline Vector2();
			constexpr inline Vector2(dataType x, dataType y);
			constexpr inline Vector2(const Vector2& start, const Vector2& end);
			
			
			constexpr inline double absolute() const;
			constexpr inline Vector2& min_x(Vector2& v) const;
			constexpr inline Vector2& max_x(Vector2& v) const;
			constexpr inline Vector2& min_y(Vector2& v) const;
			constexpr inline Vector2& max_y(Vector2& v) const;
			
			
			constexpr inline bool operator==(Vector2& v) const;
			constexpr inline bool operator!=(Vector2& v) const;
			
			constexpr inline Vector2 operator+(const Vector2& v) const;
			constexpr inline Vector2 operator-(const Vector2& v) const;
			constexpr inline dataType operator*(const Vector2& v) const;
			constexpr inline Vector2 operator*(dataType scalar) const;
			constexpr inline Vector2 operator/(dataType scalar) const;
			
			constexpr inline Vector2& operator+=(const Vector2& v);
			constexpr inline Vector2& operator-=(const Vector2& v);
			constexpr inline Vector2& operator*=(dataType scalar);
			constexpr inline Vector2& operator/=(dataType scalar);
			constexpr inline Vector2& operator=(const Vector2& v);
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
constexpr inline ITN::Vector2<dataType>::Vector2()
	:	x(0),
		y(0)
{
	
}


template<typename dataType>
constexpr inline ITN::Vector2<dataType>::Vector2(dataType x, dataType y)
	: x(x),
		y(y)
{
	
}


template<typename dataType>
constexpr inline ITN::Vector2<dataType>::Vector2(const Vector2& start, const Vector2& end)
	:	x(end.x - start.x),
		y(end.y - start.y)
{
	
}







template<typename dataType>
constexpr inline double ITN::Vector2<dataType>::absolute() const
{
	return(std::sqrt((x * x) + (y * y)));
}


template<typename dataType>
constexpr inline ITN::Vector2<dataType>& ITN::Vector2<dataType>::min_x(Vector2& v) const
{
	dataType min = std::min(x, v.x);
	if(min == v.x)
	{
		return(v);
	}
	return(*this);
}


template<typename dataType>
constexpr inline ITN::Vector2<dataType>& ITN::Vector2<dataType>::max_x(Vector2& v) const
{
	dataType max = std::max(x, v.x);
	if(max == v.x)
	{
		return(v);
	}
	return(*this);
}


template<typename dataType>
constexpr inline ITN::Vector2<dataType>& ITN::Vector2<dataType>::min_y(Vector2& v) const
{
	dataType min = std::min(y, v.y);
	if(min == v.y)
	{
		return(v);
	}
	return(*this);
}


template<typename dataType>
constexpr inline ITN::Vector2<dataType>& ITN::Vector2<dataType>::max_y(Vector2& v) const
{
	dataType max = std::max(y, v.y);
	if(max == v.y)
	{
		return(v);
	}
	return(*this);
}







template<typename dataType>
constexpr inline bool ITN::Vector2<dataType>::operator==(Vector2& v) const
{
	if(x == v.x && y == v.y)
	{
		return(true);
	}
	return(false);
}


template<typename dataType>
constexpr inline bool ITN::Vector2<dataType>::operator!=(Vector2& v) const
{
	if(x != v.x || y != v.y)
	{
		return(true);
	}
	return(false);
}







template<typename dataType>
constexpr inline ITN::Vector2<dataType> ITN::Vector2<dataType>::operator+(const Vector2& v) const
{
	Vector2<dataType> result(x + v.x, y + v.y);
	return(result);
}


template<typename dataType>
constexpr inline ITN::Vector2<dataType> ITN::Vector2<dataType>::operator-(const Vector2& v) const
{
	Vector2<dataType> result(x - v.x, y - v.y);
	return(result);
}


template<typename dataType>
constexpr inline dataType ITN::Vector2<dataType>::operator*(const Vector2& v) const
{
	dataType result = x * v.x + y * v.y;
	return(result);
}


template<typename dataType>
constexpr inline ITN::Vector2<dataType> ITN::Vector2<dataType>::operator*(dataType scalar) const
{
	Vector2<dataType> result(x * scalar, y * scalar);
	return(result);
}


template<typename dataType>
constexpr inline ITN::Vector2<dataType> ITN::Vector2<dataType>::operator/(dataType scalar) const
{
	Vector2<dataType> result(x / scalar, y / scalar);
	return(result);
}







template<typename dataType>
constexpr ITN::Vector2<dataType>& ITN::Vector2<dataType>::operator+=(const Vector2& v)
{
	*this = *this + v;
	return(*this);
}


template<typename dataType>
constexpr ITN::Vector2<dataType>& ITN::Vector2<dataType>::operator-=(const Vector2& v)
{
	*this = *this - v;
	return(*this);
}


template<typename dataType>
constexpr ITN::Vector2<dataType>& ITN::Vector2<dataType>::operator*=(dataType scalar)
{
	*this = *this * scalar;
	return(*this);
}


template<typename dataType>
constexpr ITN::Vector2<dataType>& ITN::Vector2<dataType>::operator/=(dataType scalar)
{
	*this = *this / scalar;
	return(*this);
}


template<typename dataType>
constexpr ITN::Vector2<dataType>& ITN::Vector2<dataType>::operator=(const Vector2& v)
{
	x = v.x;
	y = v.y;
	
	return(*this);
}