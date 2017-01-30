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

#ifndef PLINTH_RANGE_HPP
#define PLINTH_RANGE_HPP

#include "Common.hpp"

#include <initializer_list> // for std::initializer_list

namespace plinth
{

enum class RangeBoundaries
{
	None,
	Min,
	Max,
	Both
};

template <class T>
class Range
{
public:
	mutable T min;
	mutable T max;

	Range();
	Range(std::initializer_list<T> list);
	Range(const T& newMin, const T& newMax);
	template <class U>
	Range(const Range<U>& range);
	void order() const;
	void set(const T& newMin, const T& newMax);
	T getSize() const;
	bool isClosed() const;
	bool contains(const T& value, RangeBoundaries includeRangeBoundaries = RangeBoundaries::Min) const;
	bool contains(const Range& range, RangeBoundaries includeRangeBoundaries = RangeBoundaries::Min) const;
	bool overlaps(const Range& range) const;
	T clamp(const T& value) const;
	T clampLoop(const T& value) const;
	T clampCycle(const T& value) const;
	Range& pull(const T& hook, bool keepSize = false);
	template <class alphaT = double>
	alphaT getAlpha(const T& value) const;

	Range& operator=(const Range& other);
	template <class U>
	Range& operator=(const Range<U>& other);

	Range operator+(const T& offset) const;
	Range operator-(const T& offset) const;
	Range& operator+=(const T& offset);
	Range& operator-=(const T& offset);

	friend void std::swap(Range& a, Range& b);
};

} // namespace plinth
#include "Range.inl"
#endif // PLINTH_RANGE_HPP
