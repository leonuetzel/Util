#pragma once

#include <ITN/defines.hpp>
#include <ITN/vector2.hpp>

#include <cmath>
#include <algorithm>





namespace ITN
{
	template<typename dataType>
	class Rectangle
	{
		public:
			
			Vector2<dataType> position;
			Vector2<dataType> size;
			
			
			
			
			
		private:
			
			
			
			
			
			
			
		public:
			
			Rectangle();
			Rectangle(Vector2<dataType> position, Vector2<dataType> size);
			
			
			Vector2<dataType> get_topRightCorner();
			dataType get_surface();
			bool contains(Vector2<dataType> v);
			bool contains(Rectangle& rectangle);
			bool doesOverlap(Rectangle& rectangle);
			Rectangle get_overlap(Rectangle& rectangle);
			dataType get_overlapSurface(Rectangle& rectangle);
			
			
			bool operator==(Rectangle& rectangle);
			Rectangle& operator=(const Rectangle& rectangle);
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
ITN::Rectangle<dataType>::Rectangle()
	:	position(0, 0),
		size(0, 0)
{
	
}


template<typename dataType>
ITN::Rectangle<dataType>::Rectangle(Vector2<dataType> position, Vector2<dataType> size)
	: position(Vector2<dataType>(position.x, position.y)),
		size(Vector2<dataType>(size.x, size.y))
{
	
}







template<typename dataType>
ITN::Vector2<dataType> ITN::Rectangle<dataType>::get_topRightCorner()
{
	return(Vector2<dataType>(position.x + size.x - 1, position.y + size.y - 1));
}


template<typename dataType>
dataType ITN::Rectangle<dataType>::get_surface()
{
	return(std::abs(size.x) * std::abs(size.y));
}


template<typename dataType>
bool ITN::Rectangle<dataType>::contains(Vector2<dataType> v)
{
	if(v.x >= position.x && v.x < position.x + size.x && v.y >= position.y && v.y < position.y + size.y)
	{
		return(true);
	}
	return(false);
}


template<typename dataType>
bool ITN::Rectangle<dataType>::contains(Rectangle& rectangle)
{
	if(rectangle.position.x < position.x || rectangle.position.y < position.y)																							//	Bottom and Left Side
	{
		return(false);
	}
	if(rectangle.position.x + rectangle.size.x > position.x + size.x)																												//	Right Side
	{
		return(false);
	}
	if(rectangle.position.y + rectangle.size.y > position.y + size.y)																												//	Top Side
	{
		return(false);
	}
	return(true);
}


template<typename dataType>
bool ITN::Rectangle<dataType>::doesOverlap(Rectangle& rectangle)
{
	//	Check if "this" is contained in "rectangle"
	if(position.x >= rectangle.position.x && position.x + size.x <= rectangle.position.x + rectangle.size.x)
	{
		if(position.y >= rectangle.position.y && position.y + size.y <= rectangle.position.y + rectangle.size.y)
		{
			return(true);
		}
	}
	
	
	
	//	Check if "rectangle" is contained in "this"
	if(rectangle.position.x >= position.x && rectangle.position.x + rectangle.size.x <= position.x + size.x)
	{
		if(rectangle.position.y >= position.y && rectangle.position.y + rectangle.size.y <= position.y + size.y)
		{
			return(true);
		}
	}
	
	
	
	if(position.x >= rectangle.position.x + rectangle.size.x)
	{
		return(false);
	}
	if(position.x + size.x <= rectangle.position.x)
	{
		return(false);
	}
	if(position.y + size.y <= rectangle.position.y)
	{
		return(false);
	}
	if(position.y >= rectangle.position.y + rectangle.size.y)
	{
		return(false);
	}
	return(true);
}


template<typename dataType>
ITN::Rectangle<dataType> ITN::Rectangle<dataType>::get_overlap(Rectangle& rectangle)
{
	Rectangle overlap;
	overlap.position = {std::max(position.x, rectangle.position.x), std::max(position.y, rectangle.position.y)};
	overlap.size = {std::min(position.x + size.x, rectangle.position.x + rectangle.size.x) - overlap.position.x, std::min(position.y + size.y, rectangle.position.y + rectangle.size.y) - overlap.position.y};
	
	if(overlap.position.x >= overlap.position.x + overlap.size.x || overlap.position.y >= overlap.position.y + overlap.size.y)
	{
		return(Rectangle({0, 0}, {0, 0}));
	}
	return(overlap);
}


template<typename dataType>
dataType ITN::Rectangle<dataType>::get_overlapSurface(Rectangle& rectangle)
{
	Rectangle	overlap = get_overlap(rectangle);
	return(overlap.size.x * overlap.size.y);
}







template<typename dataType>
bool ITN::Rectangle<dataType>::operator==(Rectangle& rectangle)
{
	if(position == rectangle.position && size == rectangle.size)
	{
		return(true);
	}
	return(false);
}


template<typename dataType>
ITN::Rectangle<dataType>& ITN::Rectangle<dataType>::operator=(const Rectangle& rectangle)
{
	position = rectangle.position;
	size = rectangle.size;
	
	return(*this);
}