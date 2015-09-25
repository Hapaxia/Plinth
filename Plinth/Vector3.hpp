#ifndef PLINTH_VECTOR3_HPP
#define PLINTH_VECTOR3_HPP

#include "Size3.hpp"

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
	Vector3 operator+(const Vector3& offset) const;
	Vector3 operator-(const Vector3& offset) const;
	Vector3 operator*(const T& scalar) const;
	Vector3& operator+=(const Vector3& offset);
	Vector3& operator-=(const Vector3& offset);
	Vector3& operator*=(const T& scalar);
};

using Vector3u = Vector3<unsigned int>;
using Vector3i = Vector3<int>;
using Vector3d = Vector3<double>;

} // namespace plinth
#include "Vector3.inl"
#endif // PLINTH_VECTOR3_HPP
