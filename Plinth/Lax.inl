//////////////////////////////////////////////////////////////////////////////
//
// Plinth
//
// Copyright(c) 2014-2024 M.J.Silk
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

#ifndef PLINTH_LAX_INL
#define PLINTH_LAX_INL

#include "Lax.hpp"

#include "Math.hpp"

namespace plinth
{

template <class T>
inline Lax<T>::Lax()
	: m_epsilon{ defaultEpsilon }
	, m_value{ static_cast<T>(0) }
{
}

template <class T>
inline Lax<T>::Lax(const T& value)
	: Lax()
{
	m_value = value;
}

template <class T>
inline Lax<T>::Lax(const std::initializer_list<T>& list)
	: Lax()
{
	const auto size{ list.size() };
	if (size == 0_uz)
		return;
	auto item{ list.begin() };
	m_value = *item;
	if (size == 1_uz)
		return;
	m_epsilon = static_cast<long double>(*(++item));
}

template <class T>
template <class U>
inline Lax<T>::Lax(const U& value)
	: Lax()
{
	m_value = static_cast<T>(value);
}

template <class T>
template <class U>
inline void Lax<T>::setEpsilon(const U& epsilon)
{
	m_epsilon = static_cast<long double>(epsilon);
}

template <class T>
template <class U>
inline U Lax<T>::getEpsilon() const
{
	return static_cast<U>(m_epsilon);
}



template <class T>
inline bool Lax<T>::operator==(const Lax& other) const
{
	return *this == other.m_value;
}

template <class T>
template <class U>
inline bool Lax<T>::operator==(const U& value) const
{
	const long double v{ static_cast<long double>(value) };
	return (m_value <= (v + m_epsilon)) && (m_value >= (v - m_epsilon));
}

template <class T>
inline bool Lax<T>::operator!=(const Lax& other) const
{
	return *this != other.m_value;
}

template <class T>
template <class U>
inline bool Lax<T>::operator!=(const U& value) const
{
	const long double v{ static_cast<long double>(value) };
	return (m_value > (v + m_epsilon)) || (m_value < (v - m_epsilon));
}

template <class T>
inline Lax<T>& Lax<T>::operator=(const Lax& other)
{
	m_value = other.m_value;
	m_epsilon = other.m_epsilon;
	return *this;
}

template <class T>
template <class U>
inline Lax<T>& Lax<T>::operator=(const U& value)
{
	m_value = static_cast<T>(value);
	return *this;
}

template <class T>
inline Lax<T>& Lax<T>::operator++()
{
	++m_value;
	return *this;
}

template <class T>
inline Lax<T>& Lax<T>::operator--()
{
	--m_value;
	return *this;
}

template <class T>
inline Lax<T> Lax<T>::operator++(int)
{
	Lax<T> output = *this;
	++m_value;
	return output;
}

template <class T>
inline Lax<T> Lax<T>::operator--(int)
{
	Lax<T> output = *this;
	--m_value;
	return output;
}

template <class T>
inline bool Lax<T>::operator<(const Lax& other) const
{
	return m_value < (other.m_value - m_epsilon);
}

template <class T>
inline bool Lax<T>::operator>(const Lax& other) const
{
	return m_value > (other.m_value + m_epsilon);
}

template <class T>
inline bool Lax<T>::operator<=(const Lax& other) const
{
	return m_value < (other.m_value + m_epsilon);
}

template <class T>
inline bool Lax<T>::operator>=(const Lax& other) const
{
	return m_value > (other.m_value - m_epsilon);
}

template <class T>
template <class U>
inline bool Lax<T>::operator<(const U& value) const
{
	return m_value < (static_cast<long double>(value) - m_epsilon);
}

template <class T>
template <class U>
inline bool Lax<T>::operator>(const U& value) const
{
	return m_value > (static_cast<long double>(value) + m_epsilon);
}

template <class T>
template <class U>
inline bool Lax<T>::operator<=(const U& value) const
{
	return m_value < (static_cast<long double>(value) + m_epsilon);
}

template <class T>
template <class U>
inline bool Lax<T>::operator>=(const U& value) const
{
	return m_value > (static_cast<long double>(value) - m_epsilon);
}

template <class T>
inline Lax<T> Lax<T>::operator+() const
{
	return *this;
}

template <class T>
inline Lax<T> Lax<T>::operator-() const
{
	Lax<T> lax = *this;
	lax.m_value = -lax.m_value;
	return lax;
}

template <class T>
inline Lax<T> Lax<T>::operator+(const Lax& other) const
{
	Lax<T> lax = *this;
	lax.m_value += other.m_value;
	return lax;
}

template <class T>
inline Lax<T> Lax<T>::operator-(const Lax& other) const
{
	Lax<T> lax = *this;
	lax.m_value -= other.m_value;
	return lax;
}

template <class T>
inline Lax<T> Lax<T>::operator*(const Lax& other) const
{
	Lax<T> lax = *this;
	lax.m_value *= other.m_value;
	return lax;
}

template <class T>
inline Lax<T> Lax<T>::operator/(const Lax& other) const
{
	Lax<T> lax = *this;
	lax.m_value /= other.m_value;
	return lax;
}

template <class T>
inline Lax<T> Lax<T>::operator%(const Lax& other) const
{
	Lax<T> lax = *this;
	lax.m_value = mod(lax.m_value, other.m_value);
	return lax;
}

template <class T>
template <class U>
inline Lax<T> Lax<T>::operator+(const U& value) const
{
	Lax<T> lax = *this;
	lax.m_value += static_cast<T>(value);
	return lax;
}

template <class T>
template <class U>
inline Lax<T> Lax<T>::operator-(const U& value) const
{
	Lax<T> lax = *this;
	lax.m_value -= static_cast<T>(value);
	return lax;
}

template <class T>
template <class U>
inline Lax<T> Lax<T>::operator*(const U& value) const
{
	Lax<T> lax = *this;
	lax.m_value *= static_cast<T>(value);
	return lax;
}

template <class T>
template <class U>
inline Lax<T> Lax<T>::operator/(const U& value) const
{
	Lax<T> lax = *this;
	lax.m_value /= static_cast<T>(value);
	return lax;
}

template <class T>
template <class U>
inline Lax<T> Lax<T>::operator%(const U& value) const
{
	Lax<T> lax = *this;
	lax.m_value = mod(lax.m_value, static_cast<T>(value));
	return lax;
}

template <class T>
inline Lax<T>& Lax<T>::operator+=(const Lax& other)
{
	m_value += other.m_value;
	return *this;
}

template <class T>
inline Lax<T>& Lax<T>::operator-=(const Lax& other)
{
	m_value -= other.m_value;
	return *this;
}

template <class T>
inline Lax<T>& Lax<T>::operator*=(const Lax& other)
{
	m_value *= other.m_value;
	return *this;
}

template <class T>
inline Lax<T>& Lax<T>::operator/=(const Lax& other)
{
	m_value /= other.m_value;
	return *this;
}

template <class T>
inline Lax<T>& Lax<T>::operator%=(const Lax& other)
{
	m_value = mod(m_value, other.m_value);
	return *this;
}

template <class T>
template <class U>
inline Lax<T>& Lax<T>::operator+=(const U& value)
{
	m_value += static_cast<T>(value);
	return *this;
}

template <class T>
template <class U>
inline Lax<T>& Lax<T>::operator-=(const U& value)
{
	m_value -= static_cast<T>(value);
	return *this;
}

template <class T>
template <class U>
inline Lax<T>& Lax<T>::operator*=(const U& value)
{
	m_value *= static_cast<T>(value);
	return *this;
}

template <class T>
template <class U>
inline Lax<T>& Lax<T>::operator/=(const U& value)
{
	m_value /= static_cast<T>(value);
	return *this;
}

template <class T>
template <class U>
inline Lax<T>& Lax<T>::operator%=(const U& value)
{
	m_value = mod(m_value, static_cast<T>(value));
	return *this;
}

template <class T>
template <class U>
inline Lax<T>::operator U() const
{
	return static_cast<U>(m_value);
}



template <class T, class U>
inline U operator+(const U& left, const Lax<T>& right)
{
	return left + static_cast<U>(right);
}

template <class T, class U>
inline U operator-(const U& left, const Lax<T>& right)
{
	return left - static_cast<U>(right);
}

template <class T, class U>
inline U operator*(const U& left, const Lax<T>& right)
{
	return left * static_cast<U>(right);
}

template <class T, class U>
inline U operator/(const U& left, const Lax<T>& right)
{
	return left / static_cast<U>(right);
}

template <class T, class U>
inline U operator%(const U& left, const Lax<T>& right)
{
	return mod(left, static_cast<U>(right));
}

template <class T, class U>
inline U& operator+=(U& left, const Lax<T>& right)
{
	return left += static_cast<U>(right);
}

template <class T, class U>
inline U& operator-=(U& left, const Lax<T>& right)
{
	return left -= static_cast<U>(right);
}

template <class T, class U>
inline U& operator*=(U& left, const Lax<T>& right)
{
	return left *= static_cast<U>(right);
}

template <class T, class U>
inline U& operator/=(U& left, const Lax<T>& right)
{
	return left /= static_cast<U>(right);
}

template <class T, class U>
inline U& operator%=(U& left, const Lax<T>& right)
{
	return left = mod(left, static_cast<U>(right));
}

} // namespace plinth
#endif // PLINTH_LAX_INL
