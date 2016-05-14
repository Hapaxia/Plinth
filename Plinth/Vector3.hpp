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

#ifndef PLINTH_VECTOR3_HPP
#define PLINTH_VECTOR3_HPP

#include "Common.hpp"
#include "Size3.hpp"

#include <algorithm> // for std::swap

namespace plinth
{

template <class T>
struct Vector3
{
	T x, y, z;
	Vector3();
	Vector3(const T& newX, const T& newY, const T& newZ);
	template <class U>
	Vector3(const Vector3<U>& vector);
	template <class U>
	Vector3(const Size3<U>& size);
	Size3<T> getSize3() const;
	Vector3 operator+(const Vector3& offset) const;
	Vector3 operator-(const Vector3& offset) const;
	Vector3 operator*(const T& scalar) const;
	Vector3 operator/(const T& scalar) const;
	Vector3& operator+=(const Vector3& offset);
	Vector3& operator-=(const Vector3& offset);
	Vector3& operator*=(const T& scalar);
	Vector3& operator/=(const T& scalar);
	friend void swap(Vector3& a, Vector3& b)
	{
		std::swap(a.x, b.x);
		std::swap(a.y, b.y);
		std::swap(a.z, b.z);
	}
};

using Vector3u = Vector3<unsigned int>;
using Vector3i = Vector3<int>;
using Vector3d = Vector3<double>;

} // namespace plinth
#include "Vector3.inl"
#endif // PLINTH_VECTOR3_HPP
