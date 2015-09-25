namespace plinth
{

template <class T>
Vector3<T>::Vector3()
{
	x = static_cast<T>(0);
	y = static_cast<T>(0);
	z = static_cast<T>(0);
}

template <class T>
Vector3<T>::Vector3(const T& newX, const T& newY, const T& newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}

template <class T>
template <class U>
Vector3<T>::Vector3(const Vector3<U>& vector)
{
	x = static_cast<T>(vector.x);
	y = static_cast<T>(vector.y);
	z = static_cast<T>(vector.z);
}

template <class T>
template <class U>
Vector3<T>::Vector3(const Size3<U>& size)
{
	x = static_cast<T>(vector.width);
	y = static_cast<T>(vector.height);
	z = static_cast<T>(vector.depth);
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

} // namespace plinth
