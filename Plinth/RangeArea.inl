//////////////////////////////////////////////////////////////////////////////
//
// Plinth
//
// Copyright(c) 2014-2024 M.J.Silk
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions :
//
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software.If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
// M.J.Silk
// MJSilk2@gmail.com
//
//////////////////////////////////////////////////////////////////////////////

#ifndef PLINTH_RANGEAREA_INL
#define PLINTH_RANGEAREA_INL

#include "RangeArea.hpp"

namespace plinth
{

template <class T>
inline RangeArea<T>::RangeArea()
	: left{ static_cast<T>(0) }
	, top{ static_cast<T>(0) }
	, right{ static_cast<T>(0) }
	, bottom{ static_cast<T>(0) }
{
}

template <class T>
template <class U>
inline RangeArea<T>::RangeArea(const RangeArea<U>& rangeArea)
	: left{ static_cast<T>(rangeArea.left) }
	, top{ static_cast<T>(rangeArea.top) }
	, right{ static_cast<T>(rangeArea.right) }
	, bottom{ static_cast<T>(rangeArea.bottom) }
{
}

template <class T>
inline RangeArea<T>::RangeArea(const T& newLeft, const T& newBottom, const T& newRight, const T& newTop)
	: left{ newLeft }
	, top{ newTop }
	, right{ newRight }
	, bottom{ newBottom }
{
}

template <class T>
inline RangeArea<T>::RangeArea(const Range<T>& horizRange, const Range<T>& vertRange)
	: left{ horizRange.min }
	, top{ vertRange.min }
	, right{ horizRange.max }
	, bottom{ vertRange.max }
{
}

template <class T>
inline RangeArea<T>::RangeArea(const Vector2<T>& leftBottom, const Vector2<T>& rightTop)
	: left{ leftBottom.x }
	, top{ leftBottom.y }
	, right{ rightTop.x }
	, bottom{ rightTop.y }
{
}

template <class T>
inline RangeArea<T>::RangeArea(const Size2<T>& size)
	: left{ static_cast<T>(0) }
	, top{ static_cast<T>(0) }
	, right{ size.width }
	, top{ size.height }
{
}

template <class T>
inline Size2<T> RangeArea<T>::getSize2() const
{
	return{ getWidth(), getHeight() };
}

template <class T>
inline T RangeArea<T>::getSize() const
{
	return getWidth() * getHeight();
}

template <class T>
inline T RangeArea<T>::getWidth() const
{
	orderHoriz();
	return right - left;
}

template <class T>
inline T RangeArea<T>::getHeight() const
{
	orderVert();
	return bottom - top;
}

template <class T>
inline void RangeArea<T>::set(Vector2<T> leftTop, Vector2<T> rightBottom)
{
	setLeftTop(leftTop);
	setRightBottom(rightBottom);
}

template <class T>
inline void RangeArea<T>::setLeftTop(Vector2<T> leftTop)
{
	left = leftTop.x;
	top = leftTop.y;
}

template <class T>
inline void RangeArea<T>::setRightBottom(Vector2<T> rightBottom)
{
	right = rightBottom.x;
	bottom = rightBottom.y;
}

template <class T>
inline Vector2<T> RangeArea<T>::getLeftTop() const
{
	return{ left, top };
}

template <class T>
inline Vector2<T> RangeArea<T>::getRightBottom() const
{
	return{ right, bottom };
}

template <class T>
inline void RangeArea<T>::order() const
{
	orderHoriz();
	orderVert();
}

template <class T>
inline void RangeArea<T>::orderHoriz() const
{
	orderLowHigh(left, right);
}

template <class T>
inline void RangeArea<T>::orderVert() const
{
	orderLowHigh(top, bottom);
}

template <class T>
inline bool RangeArea<T>::isPoint() const
{
	return isFlatHorizontally() && isFlatVertically();
}

template <class T>
inline bool RangeArea<T>::isFlatHorizontally() const
{
	return left == right;
}

template <class T>
inline bool RangeArea<T>::isFlatVertically() const
{
	return top == bottom;
}

template <class T>
inline Range<T> RangeArea<T>::getHorizRange() const
{
	return{ left, right };
}

template <class T>
inline Range<T> RangeArea<T>::getVertRange() const
{
	return{ top, bottom };
}

template <class T>
inline Vector2<T> RangeArea<T>::clamp(const Vector2<T>& vector) const
{
	order();
	return{ getHorizRange().clamp(vector.x), getVertRange().clamp(vector.y) };
}

template <class T>
inline Vector2<T> RangeArea<T>::clampLoop(const Vector2<T>& vector) const
{
	order();
	return{ getHorizRange().clampLoop(vector.x), getVertRange().clampLoop(vector.y) };
}

template <class T>
inline Vector2<T> RangeArea<T>::clampCycle(const Vector2<T>& vector) const
{
	order();
	return{ getHorizRange().clampCycle(vector.x), getVertRange().clampCycle(vector.y) };
}

template <class T>
inline bool RangeArea<T>::contains(const Vector2<T>& vector, RangeAreaBoundaries includeRangeAreaBoundaries) const
{
	switch (includeRangeAreaBoundaries)
	{
	case RangeAreaBoundaries::None:
		return (getHorizRange().contains(vector.x, RangeBoundaries::None) && getVertRange().contains(vector.y, RangeBoundaries::None));
	case RangeAreaBoundaries::Left:
		return (getHorizRange().contains(vector.x, RangeBoundaries::Min) && getVertRange().contains(vector.y, RangeBoundaries::None));
	case RangeAreaBoundaries::Top:
		return (getHorizRange().contains(vector.x, RangeBoundaries::None) && getVertRange().contains(vector.y, RangeBoundaries::Min));
	case RangeAreaBoundaries::Right:
		return (getHorizRange().contains(vector.x, RangeBoundaries::Max) && getVertRange().contains(vector.y, RangeBoundaries::None));
	case RangeAreaBoundaries::Bottom:
		return (getHorizRange().contains(vector.x, RangeBoundaries::None) && getVertRange().contains(vector.y, RangeBoundaries::Max));
	case RangeAreaBoundaries::LeftTop:
		return (getHorizRange().contains(vector.x, RangeBoundaries::Min) && getVertRange().contains(vector.y, RangeBoundaries::Min));
	case RangeAreaBoundaries::RightTop:
		return (getHorizRange().contains(vector.x, RangeBoundaries::Max) && getVertRange().contains(vector.y, RangeBoundaries::Min));
	case RangeAreaBoundaries::RightBottom:
		return (getHorizRange().contains(vector.x, RangeBoundaries::Max) && getVertRange().contains(vector.y, RangeBoundaries::Max));
	case RangeAreaBoundaries::LeftBottom:
		return (getHorizRange().contains(vector.x, RangeBoundaries::Min) && getVertRange().contains(vector.y, RangeBoundaries::Max));
	case RangeAreaBoundaries::LeftRight:
		return (getHorizRange().contains(vector.x, RangeBoundaries::Both) && getVertRange().contains(vector.y, RangeBoundaries::None));
	case RangeAreaBoundaries::TopBottom:
		return (getHorizRange().contains(vector.x, RangeBoundaries::None) && getVertRange().contains(vector.y, RangeBoundaries::Both));
	case RangeAreaBoundaries::LeftTopRight:
		return (getHorizRange().contains(vector.x, RangeBoundaries::Both) && getVertRange().contains(vector.y, RangeBoundaries::Min));
	case RangeAreaBoundaries::LeftTopBottom:
		return (getHorizRange().contains(vector.x, RangeBoundaries::Min) && getVertRange().contains(vector.y, RangeBoundaries::Both));
	case RangeAreaBoundaries::LeftRightBottom:
		return (getHorizRange().contains(vector.x, RangeBoundaries::Both) && getVertRange().contains(vector.y, RangeBoundaries::Max));
	case RangeAreaBoundaries::TopRightBottom:
		return (getHorizRange().contains(vector.x, RangeBoundaries::Max) && getVertRange().contains(vector.y, RangeBoundaries::Both));
	case RangeAreaBoundaries::All:
		return (getHorizRange().contains(vector.x, RangeBoundaries::Both) && getVertRange().contains(vector.y, RangeBoundaries::Both));
	default:
		return false;
	}
}

template <class T>
inline bool RangeArea<T>::contains(const RangeArea& rangeArea, RangeAreaBoundaries includeRangeAreaBoundaries) const
{
	rangeArea.order();
	switch (includeRangeAreaBoundaries)
	{
	case RangeAreaBoundaries::None:
		return (getHorizRange().contains(rangeArea.getHorizRange(), RangeBoundaries::None) && getVertRange().contains(rangeArea.getVertRange(), RangeBoundaries::None));
	case RangeAreaBoundaries::Left:
		return (getHorizRange().contains(rangeArea.getHorizRange(), RangeBoundaries::Min) && getVertRange().contains(rangeArea.getVertRange(), RangeBoundaries::None));
	case RangeAreaBoundaries::Top:
		return (getHorizRange().contains(rangeArea.getHorizRange(), RangeBoundaries::None) && getVertRange().contains(rangeArea.getVertRange(), RangeBoundaries::Min));
	case RangeAreaBoundaries::Right:
		return (getHorizRange().contains(rangeArea.getHorizRange(), RangeBoundaries::Max) && getVertRange().contains(rangeArea.getVertRange(), RangeBoundaries::None));
	case RangeAreaBoundaries::Bottom:
		return (getHorizRange().contains(rangeArea.getHorizRange(), RangeBoundaries::None) && getVertRange().contains(rangeArea.getVertRange(), RangeBoundaries::Max));
	case RangeAreaBoundaries::LeftTop:
		return (getHorizRange().contains(rangeArea.getHorizRange(), RangeBoundaries::Min) && getVertRange().contains(rangeArea.getVertRange(), RangeBoundaries::Min));
	case RangeAreaBoundaries::RightTop:
		return (getHorizRange().contains(rangeArea.getHorizRange(), RangeBoundaries::Max) && getVertRange().contains(rangeArea.getVertRange(), RangeBoundaries::Min));
	case RangeAreaBoundaries::RightBottom:
		return (getHorizRange().contains(rangeArea.getHorizRange(), RangeBoundaries::Max) && getVertRange().contains(rangeArea.getVertRange(), RangeBoundaries::Max));
	case RangeAreaBoundaries::LeftBottom:
		return (getHorizRange().contains(rangeArea.getHorizRange(), RangeBoundaries::Min) && getVertRange().contains(rangeArea.getVertRange(), RangeBoundaries::Max));
	case RangeAreaBoundaries::LeftRight:
		return (getHorizRange().contains(rangeArea.getHorizRange(), RangeBoundaries::Both) && getVertRange().contains(rangeArea.getVertRange(), RangeBoundaries::None));
	case RangeAreaBoundaries::TopBottom:
		return (getHorizRange().contains(rangeArea.getHorizRange(), RangeBoundaries::None) && getVertRange().contains(rangeArea.getVertRange(), RangeBoundaries::Both));
	case RangeAreaBoundaries::LeftTopRight:
		return (getHorizRange().contains(rangeArea.getHorizRange(), RangeBoundaries::Both) && getVertRange().contains(rangeArea.getVertRange(), RangeBoundaries::Min));
	case RangeAreaBoundaries::LeftTopBottom:
		return (getHorizRange().contains(rangeArea.getHorizRange(), RangeBoundaries::Min) && getVertRange().contains(rangeArea.getVertRange(), RangeBoundaries::Both));
	case RangeAreaBoundaries::LeftRightBottom:
		return (getHorizRange().contains(rangeArea.getHorizRange(), RangeBoundaries::Both) && getVertRange().contains(rangeArea.getVertRange(), RangeBoundaries::Max));
	case RangeAreaBoundaries::TopRightBottom:
		return (getHorizRange().contains(rangeArea.getHorizRange(), RangeBoundaries::Max) && getVertRange().contains(rangeArea.getVertRange(), RangeBoundaries::Both));
	case RangeAreaBoundaries::All:
		return (getHorizRange().contains(rangeArea.getHorizRange(), RangeBoundaries::Both) && getVertRange().contains(rangeArea.getVertRange(), RangeBoundaries::Both));
	default:
		return false;
	}
}

template <class T>
inline bool RangeArea<T>::overlaps(const RangeArea& rangeArea) const
{
	order();
	rangeArea.order();
	return getHorizRange().overlaps(rangeArea.getHorizRange()) &&
		getVertRange().overlaps(rangeArea.getVertRange());
}

template<class T>
inline void RangeArea<T>::setHorizRange(const Range<T>& horizRange)
{
	left = horizRange.min;
	right = horizRange.max;
}

template<class T>
inline void RangeArea<T>::setVertRange(const Range<T>& vertRange)
{
	top = vertRange.min;
	bottom = vertRange.max;
}

template <class T>
inline Range<T> RangeArea<T>::pullHoriz(const T& hook, const bool keepSize)
{
	const Range<T> range{ getHorizRange().pull(hook, keepSize) };
	setHorizRange(range);
	return range;
}

template <class T>
inline Range<T> RangeArea<T>::pullVert(const T& hook, const bool keepSize)
{
	const Range<T> range{ getVertRange().pull(hook, keepSize) };
	setVertRange(range);
	return range;
}

template <class T>
inline RangeArea<T>& RangeArea<T>::pull(const Vector2<T>& hook, const bool keepSize)
{
	pullHoriz(hook.x, keepSize);
	pullVert(hook.y, keepSize);
	return *this;
}

} // namespace plinth
#endif // PLINTH_RANGEAREA_INL
