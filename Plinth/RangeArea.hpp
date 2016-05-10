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

#ifndef PLINTH_RANGEAREA_HPP
#define PLINTH_RANGEAREA_HPP

#include "Common.hpp"
#include "Range.hpp"
#include "Vector2.hpp"
#include "Size2.hpp"

namespace plinth
{

enum class RangeAreaBoundaries
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

template <class T>
struct RangeArea
{
	mutable T left;
	mutable T bottom;
	mutable T right;
	mutable T top;
	RangeArea();
	template <class U>
	RangeArea(const RangeArea<U>& rangeArea);
	RangeArea(const T& newLeft, const T& newBottom, const T& newRight, const T& newTop);
	RangeArea(const Range<T>& horizontalRange, const Range<T>& verticalRange);
	RangeArea(const Vector2<T>& leftBottom, const Vector2<T>& rightTop);
	RangeArea(const Size2<T>& size);
	Size2<T> getSize2() const;
	T getSize() const;
	T getWidth() const;
	T getHeight() const;
	void set(Vector2<T> leftBottom, Vector2<T> rightTop);
	void setLeftBottom(Vector2<T> leftBottom);
	void setRightTop(Vector2<T> rightTop);
	Vector2<T> getLeftBottom() const;
	Vector2<T> getRightTop() const;
	void order() const;
	void orderHoriz() const;
	void orderVert() const;
	bool isPoint() const;
	bool isFlatHorizontally() const;
	bool isFlatVertically() const;
	bool contains(const Vector2<T>& vector, RangeAreaBoundaries includeRangeAreaBoundaries = RangeAreaBoundaries::LeftBottom) const;
	bool overlaps(const RangeArea& rangeArea) const;
	Range<T> getHorizontalRange() const;
	Range<T> getVerticalRange() const;
	Vector2<T> clamp(const Vector2<T>& vector) const;
	Vector2<T> clampLoop(const Vector2<T>& vector) const;
	Vector2<T> clampCycle(const Vector2<T>& vector) const;
	Range<T> pullHorizontal(const T& hook, bool keepSize = false);
	Range<T> pullVertical(const T& hook, bool keepSize = false);
	RangeArea& pull(const Vector2<T>& hook, bool keepSize = false);
};

} // namespace plinth
#include "RangeArea.inl"
#endif // PLINTH_RANGEAREA_HPP
