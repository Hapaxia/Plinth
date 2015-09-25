#ifndef PLINTH_AREARANGE_HPP
#define PLINTH_AREARANGE_HPP

#include "Range.hpp"
#include "Vector2.hpp"
#include "Size2.hpp"

namespace plinth
{

enum class AreaRangeBoundaries
{
	None,
	Left,
	Bottom,
	Right,
	Top,
	LeftBottom, // lower values
	BottomRight,
	RightTop, // higher values
	LeftTop,
	LeftRight,
	BottomTop,
	LeftBottomRight,
	LeftBottomTop,
	LeftRightTop,
	BottomRightTop,
	All
};

template<class T>
struct AreaRange
{
	T left;
	T bottom;
	T right;
	T top;
	AreaRange() : left(0), bottom(0), right(0), top(0) { };
	template <class U>
	AreaRange(const AreaRange<U>& areaRange) :left(static_cast<T>(areaRange.left)), bottom(static_cast<T>(areaRange.bottom)), right(static_cast<T>(areaRange.right)), top(static_cast<T>(areaRange.top)) { }
	AreaRange(const T& newLeft, const T& newBottom, const T& newRight, const T& newTop) :left(newLeft), bottom(newBottom), right(newRight), top(newTop) { }
	AreaRange(const Range<T>& horizontalRange, const Range<T>& verticalRange) : left(horizontalRange.min), bottom(verticalRange.min), right(horizontalRange.max), top(verticalRange.max) { }
	AreaRange(const Vector2<T>& leftBottom, const Vector2<T>& rightTop) : left(leftBottom.x), bottom(leftBottom.y), right(rightTop.x), top(rightTop.y) { }
	AreaRange(const Size2<T>& size) : left(0), bottom(0), right(size.width), top(size.height) { }
	inline T getSize() { return getWidth() * getHeight(); };
	inline T getWidth() { orderHoriz(); return right - left; };
	inline T getHeight() { orderVert(); return top - bottom; };
	inline void set(Vector2<T> leftBottom, Vector2<T> rightTop) { setLeftBottom(leftBottom); setRightTop(rightTop); };
	inline void setLeftBottom(Vector2<T> leftBottom) { left = leftBottom.x; bottom = leftBottom.y; };
	inline void setRightTop(Vector2<T> rightTop) { right = rightTop.x; top = rightTop.y; };
	inline Vector2<T> getLeftBottom() { return{ left, bottom }; };
	inline Vector2<T> getRightTop() { return{ right, top }; };
	inline void order() { orderHoriz(); orderVert(); };
	inline void orderHoriz() { orderLowHigh(left, right); };
	inline void orderVert() { orderLowHigh(bottom, top); };
	inline bool isPoint() { return isFlatHorizontally() && isFlatVertically(); };
	inline bool isFlatHorizontally() { return left == right; };
	inline bool isFlatVertically() { return bottom == top; };
	inline Range<T> getHorizontalRange() { return{ left, right }; }
	inline Range<T> getVerticalRange() { return{ bottom, top }; }
};

} // namespace plinth
#endif // PLINTH_AREARANGE_HPP
