//////////////////////////////////////////////////////////////////////////////
//
// Plinth
//
// Copyright(c) 2014-2015 M.J.Silk
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

// Generic

// generic/common functions/structures

#ifndef PLINTH_GENERIC_HPP
#define PLINTH_GENERIC_HPP

#include "common.hpp"

#include "Math.hpp"

namespace plinth
{

#ifdef min
#undef min
#endif // min
#ifdef max
#undef max
#endif // max

template<class T>
// returns the highest value in a pair
inline T max(const T& a, const T& b);

template<class T>
// returns the lowest value in a pair
inline T min(const T& a, const T& b);

template<class T>
// returns the highest value of a vector
inline T max(const std::vector<T>& vector);

template<class T>
// returns the lowest value of a vector
inline T min(const std::vector<T>& vector);

template<class T>
// swaps two values
inline void swap(T& a, T& b);

template<class T>
// order two values (low - high)
inline void orderLowHigh(T& low, T& high);

template <class T>
struct Vector2
{
	T x, y;
	Vector2(const T& newX, const T& newY);
	template <class U>
	Vector2(const Vector2<U>& vector);
	Vector2 operator+(const Vector2& offset) const;
	Vector2 operator-(const Vector2& offset) const;
	Vector2 operator*(const T& scalar) const;
	Vector2& operator+=(const Vector2& offset);
	Vector2& operator-=(const Vector2& offset);
	Vector2& operator*=(const T& scalar);
};

template <class T>
struct Vector3
{
	T x, y, z;
};

using Vector2u = Vector2<unsigned int>;
using Vector2i = Vector2<int>;
using Vector2d = Vector2<double>;
using Vector3u = Vector3<unsigned int>;
using Vector3i = Vector3<int>;
using Vector3d = Vector3<double>;

template <class T>
struct Size2
{
	T width, height;
	inline T getArea() const { return width * height; };
};

template <class T>
struct Size3
{
	T width, height, depth;
	inline T getVolume() const { return width * height * depth; };
};

using Size2u = Size2<unsigned int>;
using Size2d = Size2<double>;
using Size3u = Size3<unsigned int>;
using Size3d = Size3<double>;

template <class T>
Size2<T> sizeFromVector(Vector2<T> vector);
template <class T>
Size3<T> sizeFromVector(Vector3<T> vector);
template <class T>
Vector2<T> vectorFromSize(Size2<T> size);
template <class T>
Vector3<T> vectorFromSize(Size3<T> size);


enum class RangeBoundaries
{
	None,
	Min,
	Max,
	Both
};

template<class T>
struct Range
{
	T min;
	T max;
	inline void set(const T& newMin, const T& newMax) { min = newMin; max = newMax; }
	inline T getSize() { order(); return max - min; }
	inline void order() { orderLowHigh(min, max); }
	inline bool isClosed() { return min == max; }
};

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
};

template<class T>
// if value is outside of range (boundaries included), adjust to the closest value in the range
// note: re-orders range if minimum value is higher than maximum value
inline T clamp(const T& value, Range<T>& range);

template<class T>
// if value is outside of range [min, max], adjust to the closest value in the range
inline T clamp(const T& value, const T& min, const T& max);

template<class T>
// if value is outside of range (boundaries included), adjust to the furthest value in the range
// note: re-orders range if minimum value is higher than maximum value
inline T clampLoop(const T& value, Range<T>& range);

template<class T>
// if value is outside of range [min, max], adjust to the furthest value in the range
inline T clampLoop(const T& value, const T& min, const T& max);

template<class T>
// if value is outside of range (only minimum boundary included), adjust by stepping back by size of range (keeping position in range after removing multiples of range)
// note: max is not included in the range
// note: re-orders range if minimum value is higher than maximum value
inline T clampCycle(const T& value, Range<T>& range);

template<class T>
// if value is outside of range [min, max), adjust by stepping back by size of range (keeping position in range after removing multiples of range)
// note: max is not included in the range
inline T clampCycle(const T& value, const T& min, const T& max);

template<class T>
// returns true if in range and false if outside
// boundaries can be included or excluded; by default, only minimum boundary is included
inline bool inRange(const T& value, const Range<T>& range, enum class RangeBoundaries includeRangeBoundaries = RangeBoundaries::Min);

template<class T>
// returns true if in the range min-max and false if outside
// boundaries can be included or excluded; by default, only minimum boundary is included
inline bool inRange(const T& value, const T& min, const T& max, enum class RangeBoundaries includeRangeBoundaries = RangeBoundaries::Min);

template<class T>
// returns true if in the area range (left, bottom) - (right, top) and false if outside
// boundaries can be included or excluded; by default, only lower boundaries (left and bottom) are included
// note: re-orders area range if left or bottom is higher than right or top respectively
bool inAreaRange(const Vector2<T>& point, const AreaRange<T>& areaRange, enum class AreaRangeBoundaries includeAreaRangeBoundaries = AreaRangeBoundaries::LeftBottom);

template<class T>
// switches/toggles parameter (b = !b) and also returns the result
// e.g. a = !b, a becomes opposite of b. a = toggle(b), a becomes opposite of what b was but b is now identical to a.
inline T toggle(T& b);

template<class T>
// 'pulls' a range using a hook (if hook is outside range). keeping size will move the range; not keeping size will stretch the range (move just one boundary)
inline void pullRange(Range<T>& range, const T& hook, bool keepSize = false);

template<class T>
// 'pulls' a range using a hook (if hook is outside range). keeping size will move the range; not keeping size will stretch the range (move just closest boundary)
inline void pullRange(T& low, T& high, const T& hook, bool keepSize = false);

template<class T>
// 'pulls' an area range using a hook (if hook is outside range). keeping size will move the range; not keeping size will stretch the range (move just closest boundary)
void pullAreaRange(AreaRange<T>& areaRange, const Vector2<T>& hook, bool keepSize = false);

template <class TInteger>
TInteger intFromBytes(TInteger& result, const unsigned char* bytes, bool isLittleEndian = true);
/*
template <class TInteger>
TInteger intFromBytes(TInteger& result, const unsigned char* bytes, unsigned int rangeSize = sizeof(bytes), unsigned int rangeStart = 0, bool isLittleEndian = true);
*/

} // plinth

#include "Generic.inl"

#endif // PLINTH_GENERIC_HPP