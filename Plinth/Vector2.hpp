#ifndef PLINTH_VECTOR2_HPP
#define PLINTH_VECTOR2_HPP

#include "Size2.hpp"

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
	Vector2 operator+(const Vector2& offset) const;
	Vector2 operator-(const Vector2& offset) const;
	Vector2 operator*(const T& scalar) const;
	Vector2& operator+=(const Vector2& offset);
	Vector2& operator-=(const Vector2& offset);
	Vector2& operator*=(const T& scalar);
};

using Vector2u = Vector2<unsigned int>;
using Vector2i = Vector2<int>;
using Vector2d = Vector2<double>;

} // namespace plinth
#include "Vector2.inl"
#endif // PLINTH_VECTOR2_HPP
