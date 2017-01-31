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

#ifndef PLINTH_VECTOR3_INL
#define PLINTH_VECTOR3_INL

#include "Vector3.hpp"

#include "Math.hpp"
#include <cmath>
#include <algorithm> // for std::swap

namespace plinth
{

template <class T>
Vector3<T>::Vector3()
	: x(static_cast<T>(0))
	, y(static_cast<T>(0))
	, z(static_cast<T>(0))
	, m_epsilon(static_cast<T>(defaultEpsilon))
{
}

template <class T>
Vector3<T>::Vector3(const T& newX, const T& newY, const T& newZ)
	: x(newX)
	, y(newY)
	, z(newZ)
	, m_epsilon(static_cast<T>(defaultEpsilon))
{
}

template <class T>
Vector3<T>::Vector3(const T& single)
	: Vector3(single, single, single)
{
}

template <class T>
Vector3<T>::Vector3(std::initializer_list<T> list)
	: Vector3()
{
	const auto size{ list.size() };
	const auto begin{ list.begin() };
	if (size > 0)
	{
		x = *begin;
		if (size > 1)
		{
			y = *(begin + 1);
			if (size > 2)
				z = *(begin + 2);
		}
	}
}

template <class T>
template <class U>
Vector3<T>::Vector3(const Vector3<U>& vector)
	: Vector3(static_cast<T>(vector.x), static_cast<T>(vector.y), static_cast<T>(vector.z))
{
}

template <class T>
template <class U>
Vector3<T>::Vector3(const Size3<U>& size)
	: Vector3(static_cast<T>(vector.width), static_cast<T>(vector.height), static_cast<T>(vector.depth))
{
}

template <class T>
void Vector3<T>::setLength(const long double length)
{
	*this = getUnit<long double>() * length;
}

template <class T>
Size3<T> Vector3<T>::getSize3() const
{
	return{ x, y, z };
}

template <class T>
template <class U>
U Vector3<T>::getLengthSquared() const
{
	return static_cast<U>(x * x + y * y + z * z);
}

template <class T>
template <class U>
U Vector3<T>::getLength() const
{
	return static_cast<U>(std::sqrt(x * x + y * y + z * z));
}

template <class T>
template <class U>
Vector3<U> Vector3<T>::getUnit() const
{
	// if vector is "close enough" to zero, consider it a zero vector and return that instead (also avoids division by zero)
	if (isNotZero())
		return{ Vector3<U>(*this) / getLength<U>() };
	else
		return Vector3<T>();
}

template <class T>
T Vector3<T>::dot(const Vector3& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

template <class T>
Vector3<T> Vector3<T>::cross(const Vector3& other) const
{
	return{ y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
}

template <class T>
bool Vector3<T>::operator==(const Vector3& other) const
{
	return x == other.x && y == other.y && z == other.z;
}

template <class T>
bool Vector3<T>::operator!=(const Vector3& other) const
{
	return !(*this == other);
}

template <class T>
Vector3<T>& Vector3<T>::operator=(const Vector3& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

template <class T>
template <class U>
Vector3<T>& Vector3<T>::operator=(const Vector3<U>& other)
{
	x = static_cast<T>(other.x);
	y = static_cast<T>(other.y);
	z = static_cast<T>(other.z);
	return *this;
}

template <class T>
template <class U>
Vector3<T>& Vector3<T>::operator=(const U& value)
{
	x = static_cast<T>(value);
	y = static_cast<T>(value);
	z = static_cast<T>(value);
	return *this;
}

template <class T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& offset) const
{
	return{ x + offset.x, y + offset.y, z + offset.z };
}

template <class T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& offset) const
{
	return{ x - offset.x, y - offset.y, z - offset.z };
}

template <class T>
Vector3<T> Vector3<T>::operator*(const T& scalar) const
{
	return{ x * scalar, y * scalar, z * scalar };
}

template <class T>
Vector3<T> Vector3<T>::operator/(const T& scalar) const
{
	return{ x / scalar, y / scalar, z / scalar };
}

template <class T>
Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& offset)
{
	*this = *this + offset;
	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& offset)
{
	*this = *this - offset;
	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator*=(const T& scalar)
{
	*this = *this * scalar;
	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator/=(const T& scalar)
{
	*this = *this / scalar;
	return *this;
}



// PRIVATE

template <class T>
bool Vector3<T>::isNotZero() const
{
	return (x > m_epsilon) || (x < -m_epsilon) || (y > m_epsilon) || (y < -m_epsilon) || (z > m_epsilon) || (z < -m_epsilon);
}



} // namespace plinth



// FRIEND

namespace std
{

	template <class T>
	void swap(plinth::Vector3<T>& a, plinth::Vector3<T>& b)
	{
		swap(a.x, b.x);
		swap(a.y, b.y);
		swap(a.z, b.z);
	}

} // namespace std
#endif // PLINTH_VECTOR3_INL
