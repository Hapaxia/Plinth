//////////////////////////////////////////////////////////////////////////////
//
// Plinth
//
// Copyright(c) 2014-2025 M.J.Silk
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

#include "Vector2.hpp"

#include "Math.hpp"
#include <cmath>
#include <algorithm> // for std::swap

namespace plinth
{

template <class T>
inline Vector2<T>::Vector2()
	: x{ static_cast<T>(0) }
	, y{ static_cast<T>(0) }
	, m_epsilon{ static_cast<long double>(defaultEpsilon) }
{
}

template <class T>
inline Vector2<T>::Vector2(const T& newX, const T& newY)
	: x{ newX }
	, y{ newY }
	, m_epsilon{ static_cast<long double>(defaultEpsilon) }
{
}

template <class T>
inline Vector2<T>::Vector2(const T& single)
	: Vector2(single, single)
{
}

template <class T>
inline Vector2<T>::Vector2(std::initializer_list<T> list)
	: Vector2()
{
	const auto size{ list.size() };
	if (size == 0_uz)
		return;
	auto item{ list.begin() };
	x = *item;
	if (size == 1_uz)
		return;
	y = *(++item);
}

template <class T>
template <class U>
inline Vector2<T>::Vector2(const Vector2<U>& vector)
	: Vector2(static_cast<T>(vector.x), static_cast<T>(vector.y))
{
}

template <class T>
template <class U>
inline Vector2<T>::Vector2(const Size2<U>& size)
	: Vector2(static_cast<T>(size.width), static_cast<T>(size.height))
{
}

template <class T>
inline void Vector2<T>::setPolar(const long double length, const long double angleInDegrees)
{
	x = static_cast<T>(length * std::cos(radiansFromDegrees(angleInDegrees)));
	y = static_cast<T>(length * std::sin(radiansFromDegrees(angleInDegrees)));
}

template <class T>
inline void Vector2<T>::setPolarUsingRadians(const long double length, const long double angleInRadians)
{
	x = static_cast<T>(length * std::cos(angleInRadians));
	y = static_cast<T>(length * std::sin(angleInRadians));
}

template <class T>
inline void Vector2<T>::setLength(const long double length)
{
	*this = getUnit<long double>() * length;
}

template <class T>
inline void Vector2<T>::setAngle(const long double angleInDegrees)
{
	setPolar(getLength<long double>(), angleInDegrees);
}

template <class T>
inline void Vector2<T>::setAngleUsingRadians(const long double angleInRadians)
{
	setPolarUsingRadians(getLength<long double>(), angleInRadians);
}

template <class T>
inline Size2<T> Vector2<T>::getSize2() const
{
	return{ x, y };
}

template <class T>
template <class U>
inline U Vector2<T>::getLengthSquared() const
{
	return static_cast<U>(x * x + y * y);
}

template <class T>
template <class U>
inline U Vector2<T>::getLength() const
{
	return static_cast<U>(std::sqrt(x * x + y * y));
}

template <class T>
template <class U>
inline U Vector2<T>::getAngle() const
{
	return static_cast<U>(priv_isNotZero() ? degreesFromRadians(std::atan2(y, x)) : 0);
}

template <class T>
template <class U>
inline U Vector2<T>::getAngleAsRadians() const
{
	return static_cast<U>(priv_isNotZero() ? std::atan2(y, x) : 0);
}

template <class T>
template <class U>
inline Vector2<U> Vector2<T>::getUnit() const
{
	// if vector is "close enough" to zero, consider it a zero vector and return that instead (also avoids division by zero)
	if (priv_isNotZero())
		return{ Vector2<U>(*this) / getLength<U>()};
	else
		return Vector2<U>{};
}

template <class T>
inline T Vector2<T>::dot(const Vector2& other) const
{
	return (x * other.x) + (y * other.y);
}

template <class T>
inline bool Vector2<T>::operator==(const Vector2& other) const
{
	return (x == other.x) && (y == other.y);
}

template <class T>
inline bool Vector2<T>::operator!=(const Vector2& other) const
{
	return !(*this == other);
}

template <class T>
inline Vector2<T>& Vector2<T>::operator=(const Vector2& other)
{
	x = other.x;
	y = other.y;
	return *this;
}

template <class T>
template <class U>
inline Vector2<T>& Vector2<T>::operator=(const Vector2<U>& other)
{
	x = static_cast<T>(other.x);
	y = static_cast<T>(other.y);
	return *this;
}

template <class T>
template <class U>
inline Vector2<T>& Vector2<T>::operator=(const U& value)
{
	x = static_cast<T>(value);
	y = static_cast<T>(value);
	return *this;
}

template <class T>
inline Vector2<T> Vector2<T>::operator+(const Vector2<T>& offset) const
{
	return{ x + offset.x, y + offset.y };
}

template <class T>
inline Vector2<T> Vector2<T>::operator-(const Vector2<T>& offset) const
{
	return{ x - offset.x, y - offset.y };
}

template <class T>
inline Vector2<T> Vector2<T>::operator*(const T& scalar) const
{
	return{ x * scalar, y * scalar };
}

template <class T>
inline Vector2<T> Vector2<T>::operator/(const T& scalar) const
{
	const long double multiplier{ 1.0L / scalar };
	return{ static_cast<T>(x * multiplier), static_cast<T>(y * multiplier) };
}

template <class T>
inline Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& offset)
{
	*this = *this + offset;
	return *this;
}

template <class T>
inline Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& offset)
{
	*this = *this - offset;
	return *this;
}

template <class T>
inline Vector2<T>& Vector2<T>::operator*=(const T& scalar)
{
	*this = *this * scalar;
	return *this;
}

template <class T>
inline Vector2<T>& Vector2<T>::operator/=(const T& scalar)
{
	*this = *this / scalar;
	return *this;
}



// PRIVATE

template <class T>
inline bool Vector2<T>::priv_isNotZero() const
{
	return (x > m_epsilon) || (x < -m_epsilon) || (y > m_epsilon) || (y < -m_epsilon);
}



} // namespace plinth
