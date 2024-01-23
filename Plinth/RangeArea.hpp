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

#pragma once

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
	Top,
	Right,
	Bottom,
	LeftTop, // lower values
	RightTop,
	LeftBottom,
	RightBottom, // higher values
	LeftRight,
	TopBottom,
	LeftTopRight,
	LeftTopBottom,
	LeftRightBottom,
	TopRightBottom,
	All,
};

template <class T>
struct RangeArea // note that bottom and top have been swapped since 2024 (via C++20 update); top is now lowest value and bottom is higher value (to match visual co-ordinates of rectangles)
{
	mutable T left;
	mutable T top;
	mutable T right;
	mutable T bottom;
	RangeArea();
	template <class U>
	explicit RangeArea(const RangeArea<U>& rangeArea);
	explicit RangeArea(const T& newLeft, const T& newTop, const T& newRight, const T& newBottom);
	explicit RangeArea(const Range<T>& horizRange, const Range<T>& vertRange);
	explicit RangeArea(const Vector2<T>& leftTop, const Vector2<T>& rightBottom);
	explicit RangeArea(const Size2<T>& size);
	Size2<T> getSize2() const;
	T getSize() const;
	T getWidth() const;
	T getHeight() const;
	void set(Vector2<T> leftTop, Vector2<T> rightBottom);
	void setLeftTop(Vector2<T> leftTop);
	void setRightBottom(Vector2<T> rightBottom);
	Vector2<T> getLeftTop() const;
	Vector2<T> getRightBottom() const;
	void order() const;
	void orderHoriz() const;
	void orderVert() const;
	bool isPoint() const;
	bool isFlatHorizontally() const;
	bool isFlatVertically() const;
	bool contains(const Vector2<T>& vector, RangeAreaBoundaries includeRangeAreaBoundaries = RangeAreaBoundaries::LeftTop) const;
	bool contains(const RangeArea& rangeArea, RangeAreaBoundaries includeRangeAreaBoundaries = RangeAreaBoundaries::LeftTop) const;
	bool overlaps(const RangeArea& rangeArea) const;
	void setHorizRange(const Range<T>& horizRange);
	void setVertRange(const Range<T>& vertRange);
	Range<T> getHorizRange() const;
	Range<T> getVertRange() const;
	Vector2<T> clamp(const Vector2<T>& vector) const;
	Vector2<T> clampLoop(const Vector2<T>& vector) const;
	Vector2<T> clampCycle(const Vector2<T>& vector) const;
	Range<T> pullHoriz(const T& hook, bool keepSize = false);
	Range<T> pullVert(const T& hook, bool keepSize = false);
	RangeArea& pull(const Vector2<T>& hook, bool keepSize = false);
};

using RangeAreaS = RangeArea<std::size_t>;
using RangeAreaU = RangeArea<unsigned int>;
using RangeAreaI = RangeArea<int>;
using RangeAreaD = RangeArea<double>;
using RangeAreaF = RangeArea<float>;
using RangeAreaDl = RangeArea<Lax<double>>;
using RangeAreaFl = RangeArea<Lax<float>>;

} // namespace plinth
#include "RangeArea.inl"
