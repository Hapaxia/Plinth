//////////////////////////////////////////////////////////////////////////////
//
// Plinth
//
// Copyright(c) 2014-2016 M.J.Silk
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

namespace plinth
{

template <class T>
RangeArea<T>::RangeArea()
	: left(0)
	, bottom(0)
	, right(0)
	, top(0)
{
}

template <class T>
template <class U>
RangeArea<T>::RangeArea(const RangeArea<U>& rangeArea)
	: left(static_cast<T>(rangeArea.left))
	, bottom(static_cast<T>(rangeArea.bottom))
	, right(static_cast<T>(rangeArea.right))
	, top(static_cast<T>(rangeArea.top))
{
}

template <class T>
RangeArea<T>::RangeArea(const T& newLeft, const T& newBottom, const T& newRight, const T& newTop)
	: left(newLeft)
	, bottom(newBottom)
	, right(newRight)
	, top(newTop)
{
}

template <class T>
RangeArea<T>::RangeArea(const Range<T>& horizontalRange, const Range<T>& verticalRange)
	: left(horizontalRange.min)
	, bottom(verticalRange.min)
	, right(horizontalRange.max)
	, top(verticalRange.max)
{
}

template <class T>
RangeArea<T>::RangeArea(const Vector2<T>& leftBottom, const Vector2<T>& rightTop)
	: left(leftBottom.x)
	, bottom(leftBottom.y)
	, right(rightTop.x)
	, top(rightTop.y)
{
}

template <class T>
RangeArea<T>::RangeArea(const Size2<T>& size)
	: left(0)
	, bottom(0)
	, right(size.width)
	, top(size.height)
{
}

template <class T>
Size2<T> RangeArea<T>::getSize2() const
{
	return{ getWidth(), getHeight() };
}

template <class T>
T RangeArea<T>::getSize() const
{
	return getWidth() * getHeight();
}

template <class T>
T RangeArea<T>::getWidth() const
{
	orderHoriz();
	return right - left;
}

template <class T>
T RangeArea<T>::getHeight() const
{
	orderVert();
	return top - bottom;
}

template <class T>
void RangeArea<T>::set(Vector2<T> leftBottom, Vector2<T> rightTop)
{
	setLeftBottom(leftBottom);
	setRightTop(rightTop);
}

template <class T>
void RangeArea<T>::setLeftBottom(Vector2<T> leftBottom)
{
	left = leftBottom.x;
	bottom = leftBottom.y;
}

template <class T>
void RangeArea<T>::setRightTop(Vector2<T> rightTop)
{
	right = rightTop.x;
	top = rightTop.y;
}

template <class T>
Vector2<T> RangeArea<T>::getLeftBottom() const
{
	return{ left, bottom };
}

template <class T>
Vector2<T> RangeArea<T>::getRightTop() const
{
	return{ right, top };
}

template <class T>
void RangeArea<T>::order() const
{
	orderHoriz();
	orderVert();
}

template <class T>
void RangeArea<T>::orderHoriz() const
{
	orderLowHigh(left, right);
}

template <class T>
void RangeArea<T>::orderVert() const
{
	orderLowHigh(bottom, top);
}

template <class T>
bool RangeArea<T>::isPoint() const
{
	return isFlatHorizontally() && isFlatVertically();
}

template <class T>
bool RangeArea<T>::isFlatHorizontally() const
{
	return left == right;
}

template <class T>
bool RangeArea<T>::isFlatVertically() const
{
	return bottom == top;
}

template <class T>
Range<T> RangeArea<T>::getHorizontalRange() const
{
	return{ left, right };
}

template <class T>
Range<T> RangeArea<T>::getVerticalRange() const
{
	return{ bottom, top };
}

template <class T>
Vector2<T> RangeArea<T>::clamp(const Vector2<T>& vector) const
{
	order();
	return{ getHorizontalRange().clamp(vector.x), getVerticalRange().clamp(vector.y) };
}

template <class T>
Vector2<T> RangeArea<T>::clampLoop(const Vector2<T>& vector) const
{
	order();
	return{ getHorizontalRange().clampLoop(vector.x), getVerticalRange().clampLoop(vector.y) };
}

template <class T>
Vector2<T> RangeArea<T>::clampCycle(const Vector2<T>& vector) const
{
	order();
	return{ getHorizontalRange().clampCycle(vector.x), getVerticalRange().clampCycle(vector.y) };
}

template <class T>
bool RangeArea<T>::contains(const Vector2<T>& vector, RangeAreaBoundaries includeRangeAreaBoundaries) const
{
	switch (includeRangeAreaBoundaries)
	{
	case RangeAreaBoundaries::None:
		return (getHorizontalRange().contains(vector.x, RangeBoundaries::None) && getVerticalRange().contains(vector.y, RangeBoundaries::None));
	case RangeAreaBoundaries::Left:
		return (getHorizontalRange().contains(vector.x, RangeBoundaries::Min) && getVerticalRange().contains(vector.y, RangeBoundaries::None));
	case RangeAreaBoundaries::Bottom:
		return (getHorizontalRange().contains(vector.x, RangeBoundaries::None) && getVerticalRange().contains(vector.y, RangeBoundaries::Min));
	case RangeAreaBoundaries::Right:
		return (getHorizontalRange().contains(vector.x, RangeBoundaries::Max) && getVerticalRange().contains(vector.y, RangeBoundaries::None));
	case RangeAreaBoundaries::Top:
		return (getHorizontalRange().contains(vector.x, RangeBoundaries::None) && getVerticalRange().contains(vector.y, RangeBoundaries::Max));
	case RangeAreaBoundaries::LeftBottom:
		return (getHorizontalRange().contains(vector.x, RangeBoundaries::Min) && getVerticalRange().contains(vector.y, RangeBoundaries::Min));
	case RangeAreaBoundaries::BottomRight:
		return (getHorizontalRange().contains(vector.x, RangeBoundaries::Max) && getVerticalRange().contains(vector.y, RangeBoundaries::Min));
	case RangeAreaBoundaries::RightTop:
		return (getHorizontalRange().contains(vector.x, RangeBoundaries::Max) && getVerticalRange().contains(vector.y, RangeBoundaries::Max));
	case RangeAreaBoundaries::LeftTop:
		return (getHorizontalRange().contains(vector.x, RangeBoundaries::Min) && getVerticalRange().contains(vector.y, RangeBoundaries::Max));
	case RangeAreaBoundaries::LeftRight:
		return (getHorizontalRange().contains(vector.x, RangeBoundaries::Both) && getVerticalRange().contains(vector.y, RangeBoundaries::None));
	case RangeAreaBoundaries::BottomTop:
		return (getHorizontalRange().contains(vector.x, RangeBoundaries::None) && getVerticalRange().contains(vector.y, RangeBoundaries::Both));
	case RangeAreaBoundaries::LeftBottomRight:
		return (getHorizontalRange().contains(vector.x, RangeBoundaries::Both) && getVerticalRange().contains(vector.y, RangeBoundaries::Min));
	case RangeAreaBoundaries::LeftBottomTop:
		return (getHorizontalRange().contains(vector.x, RangeBoundaries::Min) && getVerticalRange().contains(vector.y, RangeBoundaries::Both));
	case RangeAreaBoundaries::LeftRightTop:
		return (getHorizontalRange().contains(vector.x, RangeBoundaries::Both) && getVerticalRange().contains(vector.y, RangeBoundaries::Max));
	case RangeAreaBoundaries::BottomRightTop:
		return (getHorizontalRange().contains(vector.x, RangeBoundaries::Max) && getVerticalRange().contains(vector.y, RangeBoundaries::Both));
	case RangeAreaBoundaries::All:
		return (getHorizontalRange().contains(vector.x, RangeBoundaries::Both) && getVerticalRange().contains(vector.y, RangeBoundaries::Both));
	default:
		return false;
	}
}

template <class T>
bool RangeArea<T>::overlaps(const RangeArea& rangeArea) const
{
	order();
	rangeArea.order();
	return getHorizontalRange().overlaps(rangeArea.getHorizontalRange()) &&
		getVerticalRange().overlaps(rangeArea.getVerticalRange());
}

template <class T>
Range<T> RangeArea<T>::pullHorizontal(const T& hook, const bool keepSize)
{
	Range<T> range = getHorizontalRange().pull(hook, keepSize);
	left = range.min;
	right = range.max;
	return range;
}

template <class T>
Range<T> RangeArea<T>::pullVertical(const T& hook, const bool keepSize)
{
	Range<T> range = getVerticalRange().pull(hook, keepSize);
	bottom = range.min;
	top = range.max;
	return range;
}

template <class T>
RangeArea<T>& RangeArea<T>::pull(const Vector2<T>& hook, const bool keepSize)
{
	pullHorizontal(hook.x, keepSize);
	pullVertical(hook.y, keepSize);
	return *this;
}

} // namespace plinth
#endif // PLINTH_RANGEAREA_INL
