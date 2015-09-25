namespace plinth
{

template <class T>
Vector2<T>::Vector2()
{
	x = static_cast<T>(0);
	y = static_cast<T>(0);
}

template <class T>
Vector2<T>::Vector2(const T& newX, const T& newY)
{
	x = newX;
	y = newY;
}

template <class T>
template <class U>
Vector2<T>::Vector2(const Vector2<U>& vector)
{
	x = static_cast<T>(vector.x);
	y = static_cast<T>(vector.y);
}

template <class T>
template <class U>
Vector2<T>::Vector2(const Size2<U>& size)
{
	x = static_cast<T>(size.width);
	y = static_cast<T>(size.height);
}

template <class T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& offset) const
{
	return{ x + offset.x, y + offset.y };
}

template <class T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& offset) const
{
	return{ x - offset.x, y - offset.y };
}

template <class T>
Vector2<T> Vector2<T>::operator*(const T& scalar) const
{
	return{ x * scalar, y * scalar };
}

template <class T>
Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& offset)
{
	*this = *this + offset;
	return *this;
}

template <class T>
Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& offset)
{
	*this = *this - offset;
	return *this;
}

template <class T>
Vector2<T>& Vector2<T>::operator*=(const T& scalar)
{
	*this = *this * scalar;
	return *this;
}

} // namespace plinth
