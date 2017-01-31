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
#include "Lax.hpp"

#include <initializer_list> // for std::initializer_list

namespace plinth
{

template <class T>
class Vector2
{
public:
	T x, y;

	Vector2();
	Vector2(const T& single);
	Vector2(std::initializer_list<T> list);
	Vector2(const T& newX, const T& newY);
	template <class U>
	Vector2(const Vector2<U>& vector);
	template <class U>
	Vector2(const Size2<U>& size);

	void setPolar(long double length, long double angleInDegrees);
	void setPolarUsingRadians(long double length, long double angleInRadians);
	void setLength(long double length);
	void setAngle(long double angleInDegrees);
	void setAngleUsingRadians(long double angleInRadians);

	Size2<T> getSize2() const;
	template <class U = double>
	U getLengthSquared() const;
	template <class U = double>
	U getLength() const;
	template <class U = double>
	U getAngle() const;
	template <class U = double>
	U getAngleAsRadians() const;
	template <class U = double>
	Vector2<U> getUnit() const;

	T dot(const Vector2& other) const;

	bool operator==(const Vector2& other) const;
	bool operator!=(const Vector2& other) const;

	Vector2& operator=(const Vector2& other);
	template <class U>
	Vector2& operator=(const Vector2<U>& other);
	template <class U>
	Vector2& operator=(const U& value);

	Vector2 operator+(const Vector2& offset) const;
	Vector2 operator-(const Vector2& offset) const;
	Vector2 operator*(const T& scalar) const;
	Vector2 operator/(const T& scalar) const;
	Vector2& operator+=(const Vector2& offset);
	Vector2& operator-=(const Vector2& offset);
	Vector2& operator*=(const T& scalar);
	Vector2& operator/=(const T& scalar);

	friend void std::swap(Vector2& a, Vector2& b);

private:
	const long double m_epsilon;

	bool isNotZero() const;
};

using Vector2u = Vector2<unsigned int>;
using Vector2i = Vector2<int>;
using Vector2d = Vector2<double>;
using Vector2f = Vector2<float>;
using Vector2dl = Vector2<Lax<double>>;
using Vector2fl = Vector2<Lax<float>>;

} // namespace plinth
#include "Vector2.inl"
#endif // PLINTH_VECTOR2_HPP
