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

#ifndef PLINTH_VECTOR2_HPP
#define PLINTH_VECTOR2_HPP

#include "Common.hpp"
#include "Size2.hpp"

#include <algorithm> // for std::swap

namespace plinth
{

template <class T>
struct Vector2
{
	T x, y;
	Vector2();
	Vector2(const T& newX, const T& newY);
	template <class U>
	Vector2(const Vector2<U>& vector);
	template <class U>
	Vector2(const Size2<U>& size);
	Size2<T> getSize2() const;
	Vector2 operator+(const Vector2& offset) const;
	Vector2 operator-(const Vector2& offset) const;
	Vector2 operator*(const T& scalar) const;
	Vector2 operator/(const T& scalar) const;
	Vector2& operator+=(const Vector2& offset);
	Vector2& operator-=(const Vector2& offset);
	Vector2& operator*=(const T& scalar);
	Vector2& operator/=(const T& scalar);
	friend void swap(Vector2& a, Vector2& b)
	{
		std::swap(a.x, b.x);
		std::swap(a.y, b.y);
	}
};

using Vector2u = Vector2<unsigned int>;
using Vector2i = Vector2<int>;
using Vector2d = Vector2<double>;

} // namespace plinth
#include "Vector2.inl"
#endif // PLINTH_VECTOR2_HPP
