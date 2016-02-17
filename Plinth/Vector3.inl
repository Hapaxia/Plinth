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

namespace plinth
{

template <class T>
Vector3<T>::Vector3()
	: x(static_cast<T>(0))
	, y(static_cast<T>(0))
	, z(static_cast<T>(0))
{
}

template <class T>
Vector3<T>::Vector3(const T& newX, const T& newY, const T& newZ)
	: x(newX)
	, y(newY)
	, z(newZ)
{
}

template <class T>
template <class U>
Vector3<T>::Vector3(const Vector3<U>& vector)
	: x(static_cast<T>(vector.x))
	, y(static_cast<T>(vector.y))
	, z(static_cast<T>(vector.z))
{
}

template <class T>
template <class U>
Vector3<T>::Vector3(const Size3<U>& size)
	: x(static_cast<T>(vector.width))
	, y(static_cast<T>(vector.height))
	, z(static_cast<T>(vector.depth))
{
}

template <class T>
Size3<T> Vector3<T>::getSize3() const
{
	return{ x, y, z };
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

} // namespace plinth
#endif // PLINTH_VECTOR3_INL
