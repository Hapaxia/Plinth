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
///////////////////////////////////////////////////////////////////////////////

#ifndef PLINTH_RANGE_INL
#define PLINTH_RANGE_INL

#include "Range.hpp"

#include "Generic.hpp"
#include "Math.hpp"
#include "Tween.hpp"

namespace plinth
{

template <class T>
Range<T>::Range()
	: min(static_cast<T>(0))
	, max(static_cast<T>(0))
{
}

template <class T>
Range<T>::Range(std::initializer_list<T> list)
	: Range()
{
	const auto size{ list.size() };
	const auto begin{ list.begin() };
	if (size > 0)
	{
		min = *begin;
		if (size > 1)
			max = *(begin + 1);
		else
			max = static_cast<T>(0);
	}
	else
	{
		min = static_cast<T>(0);
		max = static_cast<T>(0);
	}
}

template <class T>
Range<T>::Range(const T& newMin, const T& newMax)
	: min(newMin)
	, max(newMax)
{
}

template <class T>
template <class U>
Range<T>::Range(const Range<U>& range)
	: min(static_cast<T>(range.min))
	, max(static_cast<T>(range.max))
{
}

template <class T>
void Range<T>::order() const
{
	orderLowHigh(min, max);
}

template <class T>
void Range<T>::set(const T& newMin, const T& newMax)
{
	min = newMin;
	max = newMax;
}

template <class T>
T Range<T>::getSize() const
{
	order();
	return max - min;
}

template <class T>
bool Range<T>::isClosed() const
{
	return min == max;
}

template <class T>
bool Range<T>::contains(const T& value, RangeBoundaries includeRangeBoundaries) const
{
	order();
	switch (includeRangeBoundaries)
	{
	case RangeBoundaries::Both:
		return ((value >= min) && (value <= max));
	case RangeBoundaries::Min:
		return ((value >= min) && (value < max));
	case RangeBoundaries::Max:
		return ((value > min) && (value <= max));
	case RangeBoundaries::None:
		return ((value > min) && (value < max));
	default:
		return false;
	}
}

template <class T>
bool Range<T>::contains(const Range& range, RangeBoundaries includeRangeBoundaries) const
{
	order();
	range.order();
	switch (includeRangeBoundaries)
	{
	case RangeBoundaries::Both:
		return ((range.min >= min) && (range.max <= max));
	case RangeBoundaries::Min:
		return ((range.min >= min) && (range.max < max));
	case RangeBoundaries::Max:
		return ((range.min > min) && (range.max <= max));
	case RangeBoundaries::None:
		return ((range.min > min) && (range.max < max));
	default:
		return false;
	}
}

template <class T>
bool Range<T>::overlaps(const Range& range) const
{
	return !(min > range.max || max < range.min);
}

template <class T>
T Range<T>::clamp(const T& value) const
{
	order();
	return value > max ? max : value < min ? min : value;
}

template <class T>
T Range<T>::clampLoop(const T& value) const
{
	order();
	return value > max ? min : value < min ? max : value;
}

template <class T>
inline T Range<T>::clampCycle(const T& value) const
{
	if (isClosed())
		return min;
	const T rangeSize = getSize();
	if (value > max)
		return min + mod(value - min, rangeSize);
	else if (value < min)
		return min + rangeSize + mod(value - min, rangeSize);
	else
		return value;
}

template <class T>
Range<T>& Range<T>::pull(const T& hook, const bool keepSize)
{
	const T rangeSize = getSize();
	if (hook < min)
	{
		min = hook;
		if (keepSize)
			max = min + rangeSize;
	}
	else if (hook > max)
	{
		max = hook;
		if (keepSize)
			min = max - rangeSize;
	}
	return *this;
}

template <class T>
template <class alphaT>
alphaT Range<T>::getAlpha(const T& value) const
{
	return Tween::inverseLinear(min, max, value);
}

template <class T>
Range<T>& Range<T>::operator=(const Range& other)
{
	min = other.min;
	max = other.max;
	return *this;
}

template <class T>
template <class U>
Range<T>& Range<T>::operator=(const Range<U>& other)
{
	min = static_cast<T>(other.min);
	max = static_cast<T>(other.max);
	return *this;
}

template <class T>
Range<T> Range<T>::operator+(const T& offset) const
{
	return{ min + offset, max + offset };
}

template <class T>
Range<T> Range<T>::operator-(const T& offset) const
{
	return{ min - offset, max - offset };
}

template <class T>
Range<T>& Range<T>::operator+=(const T& offset)
{
	*this = *this + offset;
	return *this;
}

template <class T>
Range<T>& Range<T>::operator-=(const T& offset)
{
	*this = *this - offset;
	return *this;
}

} // namespace plinth



// FRIEND

namespace std
{

template <class T>
void swap(plinth::Range<T>& a, plinth::Range<T>& b)
{
	swap(a.min, b.max);
	swap(a.min, b.max);
}

} // namespace std
#endif // PLINTH_RANGE_INL
