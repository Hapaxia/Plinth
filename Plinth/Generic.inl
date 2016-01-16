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

namespace plinth
{

template<class T>
// returns the highest value in a pair
inline T max(const T& a, const T& b)
{
	return a > b ? a : b;
}

template<class T>
// returns the lowest value in a pair
inline T min(const T& a, const T& b)
{
	return a < b ? a : b;
}

template<class T>
// returns the highest value of a vector
inline T max(const std::vector<T>& values)
{
	if (values.size() == 0)
		return T();
	T result{ values[0] };
	for (unsigned int i{ 1 }; i < values.size(); ++i)
		result = max(result, values[i]);
	return result;
}

template<class T>
// returns the lowest value of a vector
inline T min(const std::vector<T>& values)
{
	if (values.size() == 0)
		return T();
	T result{ values[0] };
	for (unsigned int i{ 1 }; i < values.size(); ++i)
		result = min(result, values[i]);
	return result;
}

template<class T>
// swaps two values
inline void swap(T& a, T& b)
{
	T c = a;
	a = b;
	b = c;
}

template<class T>
// order two values (low - high)
inline void orderLowHigh(T& low, T& high)
{
	if (low > high)
		swap(low, high);
}

template <class T>
// if vector is outside of area range (boundaries included), adjust to the closest value in the area range
// note: re-orders area range if minimum values are higher than maximum values
inline Vector2<T> clamp(const Vector2<T>& vector, AreaRange<T>& range)
{
	return{ clamp(vector.x, range.getHorizontalRange()), clamp(vector.y, range.getVerticalRange()) };
}

template <class T>
// if (x, y) is outside of area range (boundaries included), adjust to the closest value in the area range
// note: re-orders area range if minimum values are higher than maximum values
inline Vector2<T> clamp(const T& x, const T& y, AreaRange<T>& range)
{
	return clamp(Vector2<T>(x, y), range);
}

template<class T>
// if value is outside of range (boundaries included), adjust to the closest value in the range
// note: re-orders range if minimum value is higher than maximum value
inline T clamp(const T& value, Range<T>& range)
{
	range.order();
	return value > range.max ? range.max : value < range.min ? range.min : value;
}

template<class T>
// if value is outside of range [min, max], adjust to the closest value in the range
inline T clamp(const T& value, const T& min, const T& max)
{
	return clamp(value, Range<T>{min, max});
}

template<class T>
// if value is outside of range (boundaries included), adjust to the furthest value in the range
// note: re-orders range if minimum value is higher than maximum value
inline T clampLoop(const T& value, Range<T>& range)
{
	range.order();
	return value > range.max ? range.min : value < range.min ? range.max : value;
}

template<class T>
// if value is outside of range [min, max], adjust to the furthest value in the range
inline T clampLoop(const T& value, const T& min, const T& max)
{
	return clampLoop(value, Range<T>{min, max});
}

template<class T>
// if value is outside of range (only minimum boundary included), adjust by stepping back by size of range (keeping position in range after removing multiples of range)
// note: max is not included in the range
// note: re-orders range if minimum value is higher than maximum value
inline T clampCycle(const T& value, Range<T>& range)
{
	if (range.isClosed())
		return range.min;
	const T rangeSize = range.getSize();
	if (value > range.max)
		return range.min + mod(value - range.min, rangeSize);
	else if (value < range.min)
		return range.min + rangeSize + mod(value - range.min, rangeSize);
	else
		return value;
}

template<class T>
// if value is outside of range [min, max), adjust by stepping back by size of range (keeping position in range after removing multiples of range)
// note: max is not included in the range
inline T clampCycle(const T& value, const T& min, const T& max)
{
	return clampCycle(value, Range<T>{min, max});
}

template<class T>
// returns true if in range and false if outside
// boundaries can be included or excluded; by default, only minimum boundary is included
inline bool inRange(const T& value, const Range<T>& range, RangeBoundaries includeRangeBoundaries)
{
	switch (includeRangeBoundaries)
	{
	case RangeBoundaries::Both:
		return ((value >= range.min) && (value <= range.max));
	case RangeBoundaries::Min:
		return ((value >= range.min) && (value < range.max));
	case RangeBoundaries::Max:
		return ((value > range.min) && (value <= range.max));
	case RangeBoundaries::None:
		return ((value > range.min) && (value < range.max));
	default:
		return false;
	}
}

template<class T>
// returns true if in the range min-max and false if outside
// boundaries can be included or excluded; by default, only minimum boundary is included
inline bool inRange(const T& value, const T& min, const T& max, RangeBoundaries includeRangeBoundaries)
{
	return inRange(value, Range<T>{min, max}, includeRangeBoundaries);
}

template<class T>
// returns true if in the area range (left, bottom) - (right, top) and false if outside
// boundaries can be included or excluded; by default, only lower boundaries (left and bottom) are included
// note: re-orders area range if left or bottom is higher than right or top respectively
bool inAreaRange(const Vector2<T>& point, const AreaRange<T>& areaRange, AreaRangeBoundaries includeAreaRangeBoundaries)
{
	switch (includeAreaRangeBoundaries)
	{
	case AreaRangeBoundaries::None:
		return (inRange(point.x, Range<T>{ areaRange.left, areaRange.right }, RangeBoundaries::None) && inRange(point.y, Range<T>{ areaRange.bottom, areaRange.top }, RangeBoundaries::None));
	case AreaRangeBoundaries::Left:
		return (inRange(point.x, Range<T>{ areaRange.left, areaRange.right }, RangeBoundaries::Min) && inRange(point.y, Range<T>{ areaRange.bottom, areaRange.top }, RangeBoundaries::None));
	case AreaRangeBoundaries::Bottom:
		return (inRange(point.x, Range<T>{ areaRange.left, areaRange.right }, RangeBoundaries::None) && inRange(point.y, Range<T>{ areaRange.bottom, areaRange.top }, RangeBoundaries::Min));
	case AreaRangeBoundaries::Right:
		return (inRange(point.x, Range<T>{ areaRange.left, areaRange.right }, RangeBoundaries::Max) && inRange(point.y, Range<T>{ areaRange.bottom, areaRange.top }, RangeBoundaries::None));
	case AreaRangeBoundaries::Top:
		return (inRange(point.x, Range<T>{ areaRange.left, areaRange.right }, RangeBoundaries::None) && inRange(point.y, Range<T>{ areaRange.bottom, areaRange.top }, RangeBoundaries::Max));
	case AreaRangeBoundaries::LeftBottom:
		return (inRange(point.x, Range<T>{ areaRange.left, areaRange.right }, RangeBoundaries::Min) && inRange(point.y, Range<T>{ areaRange.bottom, areaRange.top }, RangeBoundaries::Min));
	case AreaRangeBoundaries::BottomRight:
		return (inRange(point.x, Range<T>{ areaRange.left, areaRange.right }, RangeBoundaries::Max) && inRange(point.y, Range<T>{ areaRange.bottom, areaRange.top }, RangeBoundaries::Min));
	case AreaRangeBoundaries::RightTop:
		return (inRange(point.x, Range<T>{ areaRange.left, areaRange.right }, RangeBoundaries::Max) && inRange(point.y, Range<T>{ areaRange.bottom, areaRange.top }, RangeBoundaries::Max));
	case AreaRangeBoundaries::LeftTop:
		return (inRange(point.x, Range<T>{ areaRange.left, areaRange.right }, RangeBoundaries::Min) && inRange(point.y, Range<T>{ areaRange.bottom, areaRange.top }, RangeBoundaries::Max));
	case AreaRangeBoundaries::LeftRight:
		return (inRange(point.x, Range<T>{ areaRange.left, areaRange.right }, RangeBoundaries::Both) && inRange(point.y, Range<T>{ areaRange.bottom, areaRange.top }, RangeBoundaries::None));
	case AreaRangeBoundaries::BottomTop:
		return (inRange(point.x, Range<T>{ areaRange.left, areaRange.right }, RangeBoundaries::None) && inRange(point.y, Range<T>{ areaRange.bottom, areaRange.top }, RangeBoundaries::Both));
	case AreaRangeBoundaries::LeftBottomRight:
		return (inRange(point.x, Range<T>{ areaRange.left, areaRange.right }, RangeBoundaries::Both) && inRange(point.y, Range<T>{ areaRange.bottom, areaRange.top }, RangeBoundaries::Min));
	case AreaRangeBoundaries::LeftBottomTop:
		return (inRange(point.x, Range<T>{ areaRange.left, areaRange.right }, RangeBoundaries::Min) && inRange(point.y, Range<T>{ areaRange.bottom, areaRange.top }, RangeBoundaries::Both));
	case AreaRangeBoundaries::LeftRightTop:
		return (inRange(point.x, Range<T>{ areaRange.left, areaRange.right }, RangeBoundaries::Both) && inRange(point.y, Range<T>{ areaRange.bottom, areaRange.top }, RangeBoundaries::Max));
	case AreaRangeBoundaries::BottomRightTop:
		return (inRange(point.x, Range<T>{ areaRange.left, areaRange.right }, RangeBoundaries::Max) && inRange(point.y, Range<T>{ areaRange.bottom, areaRange.top }, RangeBoundaries::Both));
	case AreaRangeBoundaries::All:
		return (inRange(point.x, Range<T>{ areaRange.left, areaRange.right }, RangeBoundaries::Both) && inRange(point.y, Range<T>{ areaRange.bottom, areaRange.top }, RangeBoundaries::Both));
	default:
		return false;
	}
}

template<class T>
// return true if the two area ranges overlap
bool areOverlapping(const AreaRange<T>& a, const AreaRange<T>& b)
{
	return !((a.right  < b.left)   ||
	         (a.left   > b.right)  ||
	         (a.top    < b.bottom) ||
	         (a.bottom > b.top));
}

template<class T>
// switches/toggles parameter (b = !b) and also returns the result
// e.g. a = !b, a becomes opposite of b. a = toggle(b), a becomes opposite of what b was but b is now identical to a.
inline T toggle(T& b)
{
	b = !b;
	return b;
}

template<class T>
// 'pulls' a range using a hook (if hook is outside range). keeping size will move the range; not keeping size will stretch the range (move just one boundary)
inline void pullRange(Range<T>& range, const T& hook, const bool keepSize)
{
	range.order();
	if (hx::inRange(hook, range))
		return;
	T rangeSize = range.getSize();
	if (hook < range.min)
	{
		range.min = hook;
		if (keepSize)
			range.max = range.min + rangeSize;
	}
	else if (hook > range.max)
	{
		range.max = hook;
		if (keepSize)
			range.min = range.max - rangeSize;
	}
}

template<class T>
// 'pulls' a range using a hook (if hook is outside range). keeping size will move the range; not keeping size will stretch the range (move just one boundary)
inline void pullRange(T& low, T& high, const T& hook, const bool keepSize)
{
	Range<T> range{ low, high };
	pullRange(range, hook, keepSize);
	low = range.min;
	high = range.max;
}

template<class T>
// 'pulls' an area range using a hook (if hook is outside range). keeping size will move the range; not keeping size will stretch the range (move just closest boundary)
void pullAreaRange(AreaRange<T>& areaRange, const Vector2<T>& hook, const bool keepSize)
{
	Range<T> range{ areaRange.left, areaRange.right };
	pullRange<T>(range, hook.x, keepSize);
	areaRange.left = range.min;
	areaRange.right = range.max;
	range.set(areaRange.bottom, areaRange.top);
	pullRange<T>(range, hook.y, keepSize);
	areaRange.bottom = range.min;
	areaRange.top = range.max;
}

template <class IntegerType>
IntegerType intFromBytes(const unsigned int numberOfBytes, const unsigned char* bytes, const bool isLittleEndian)
{
	IntegerType result = 0;
	if (isLittleEndian)
	{
		for (unsigned int n{ numberOfBytes }; n > 0; --n)
			result = (result << 8) + bytes[n - 1];
	}
	else
	{
		for (unsigned int n{ 0 }; n < numberOfBytes; ++n)
			result = (result << 8) + bytes[n];
	}
	return result;
}

template <class IntegerType>
IntegerType intFromBytes(const std::vector<unsigned char>& bytes, const bool isLittleEndian)
{
	IntegerType result = 0;
	const unsigned int numberOfBytes{ bytes.size() };
	if (isLittleEndian)
	{
		for (unsigned int n{ numberOfBytes }; n > 0; --n)
			result = (result << 8) + bytes[n - 1];
	}
	else
	{
		for (unsigned int n{ 0 }; n < numberOfBytes; ++n)
			result = (result << 8) + bytes[n];
	}
	return result;
}

template <class T>
Vector2<T>::Vector2()
{
	x = static_cast<T>(0);
	y = static_cast<T>(0);
}

template <class T>
Vector2<T>::Vector2(const T& newX, const T& newY)
{
	x = newX;
	y = newY;
}

template <class T>
template <class U>
Vector2<T>::Vector2(const Vector2<U>& vector)
{
	x = static_cast<T>(vector.x);
	y = static_cast<T>(vector.y);
}
template <class T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& offset) const
{
	return{ x + offset.x, y + offset.y };
}
template <class T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& offset) const
{
	return{ x - offset.x, y - offset.y };
}
template <class T>
Vector2<T> Vector2<T>::operator*(const T& scalar) const
{
	return{ x * scalar, y * scalar };
}
template <class T>
Vector2<T> Vector2<T>::operator/(const T& scalar) const
{
	return{ x / scalar, y / scalar };
}
template <class T>
Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& offset)
{
	*this = *this + offset;
	return *this;
}
template <class T>
Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& offset)
{
	*this = *this - offset;
	return *this;
}
template <class T>
Vector2<T>& Vector2<T>::operator*=(const T& scalar)
{
	*this = *this * scalar;
	return *this;
}
template <class T>
Vector2<T>& Vector2<T>::operator/=(const T& scalar)
{
	*this = *this / scalar;
	return *this;
}

template <class T>
Size2<T> sizeFromVector(Vector2<T> vector)
{
	return{ vector.x, vector.y };
}

template <class T>
Size3<T> sizeFromVector(Vector3<T> vector)
{
	return{ vector.x, vector.y, vector.y };
}

template <class T>
Vector2<T> vectorFromSize(Size2<T> size)
{
	return{ size.width, size.height };
}

template <class T>
Vector3<T> vectorFromSize(Size3<T> size)
{
	return{ size.width, size.height, size.depth };
}

} // namespace plinth
