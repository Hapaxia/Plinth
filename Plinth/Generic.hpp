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

#include "Common.hpp"
#include "Math.hpp"

#include "Vectors.hpp"
#include "Sizes.hpp"
#include "Range.hpp"
#include "AreaRange.hpp"

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
inline Size2<T> sizeFromVector(Vector2<T> vector);
template <class T>
inline Size3<T> sizeFromVector(Vector3<T> vector);
/*
template <class T>
inline Vector2<T> vectorFromSize(Size2<T> size);
template <class T>
inline Vector3<T> vectorFromSize(Size3<T> size);
*/

template <class T>
// if vector is outside of area range (boundaries included), adjust to the closest value in the area range
// note: re-orders area range if minimum values are higher than maximum values
inline Vector2<T> clamp(const Vector2<T>& vector, AreaRange<T>& range);

template <class T>
// if (x, y) is outside of area range (boundaries included), adjust to the closest value in the area range
// note: re-orders area range if minimum values are higher than maximum values
inline Vector2<T> clamp(const T& x, const T& y, AreaRange<T>& range);

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
inline bool inRange(const T& value, const Range<T>& range, RangeBoundaries includeRangeBoundaries = RangeBoundaries::Min);

template<class T>
// returns true if in the range min-max and false if outside
// boundaries can be included or excluded; by default, only minimum boundary is included
inline bool inRange(const T& value, const T& min, const T& max, RangeBoundaries includeRangeBoundaries = RangeBoundaries::Min);

template<class T>
// returns true if in the area range (left, bottom) - (right, top) and false if outside
// boundaries can be included or excluded; by default, only lower boundaries (left and bottom) are included
// note: re-orders area range if left or bottom is higher than right or top respectively
bool inAreaRange(const Vector2<T>& point, const AreaRange<T>& areaRange, AreaRangeBoundaries includeAreaRangeBoundaries = AreaRangeBoundaries::LeftBottom);

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