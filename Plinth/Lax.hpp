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

#ifndef PLINTH_LAX_HPP
#define PLINTH_LAX_HPP

#include "Common.hpp"

#include <initializer_list>

namespace plinth
{

template <class T = double>
class Lax
{
public:
	Lax();
	explicit Lax(const T& value);
	explicit Lax(const std::initializer_list<T>& list);
	template <class U>
	explicit Lax(const U& value);

	template <class U>
	void setEpsilon(const U& epsilon);
	template <class U = long double>
	U getEpsilon() const;

	bool operator==(const Lax& other) const;
	template <class U>
	bool operator==(const U& value) const;
	bool operator!=(const Lax& other) const;
	template <class U>
	bool operator!=(const U& value) const;
	Lax& operator=(const Lax& other);
	template <class U>
	Lax& operator=(const U& value);

	Lax& operator++();
	Lax& operator--();
	Lax operator++(int);
	Lax operator--(int);

	bool operator<(const Lax& other) const;
	bool operator>(const Lax& other) const;
	bool operator<=(const Lax& other) const;
	bool operator>=(const Lax& other) const;
	template <class U>
	bool operator<(const U& value) const;
	template <class U>
	bool operator>(const U& value) const;
	template <class U>
	bool operator<=(const U& value) const;
	template <class U>
	bool operator>=(const U& value) const;

	Lax operator+() const;
	Lax operator-() const;

	Lax operator+(const Lax& other) const;
	Lax operator-(const Lax& other) const;
	Lax operator*(const Lax& other) const;
	Lax operator/(const Lax& other) const;
	Lax operator%(const Lax& other) const;
	template <class U>
	Lax operator+(const U& value) const;
	template <class U>
	Lax operator-(const U& value) const;
	template <class U>
	Lax operator*(const U& value) const;
	template <class U>
	Lax operator/(const U& value) const;
	template <class U>
	Lax operator%(const U& value) const;

	Lax& operator+=(const Lax& other);
	Lax& operator-=(const Lax& other);
	Lax& operator*=(const Lax& other);
	Lax& operator/=(const Lax& other);
	Lax& operator%=(const Lax& other);
	template <class U>
	Lax& operator+=(const U& value);
	template <class U>
	Lax& operator-=(const U& value);
	template <class U>
	Lax& operator*=(const U& value);
	template <class U>
	Lax& operator/=(const U& value);
	template <class U>
	Lax& operator%=(const U& value);

	template <class U>
	operator U() const;

private:
	T m_value;
	long double m_epsilon;
};

template <class T, class U>
U operator+(const U& left, const Lax<T>& right);

template <class T, class U>
U operator-(const U& left, const Lax<T>& right);

template <class T, class U>
U operator*(const U& left, const Lax<T>& right);

template <class T, class U>
U operator/(const U& left, const Lax<T>& right);

template <class T, class U>
U operator%(const U& left, const Lax<T>& right);

template <class T, class U>
U& operator+=(U& left, const Lax<T>& right);

template <class T, class U>
U& operator-=(U& left, const Lax<T>& right);

template <class T, class U>
U& operator*=(U& left, const Lax<T>& right);

template <class T, class U>
U& operator/=(U& left, const Lax<T>& right);

template <class T, class U>
U& operator*=(U& left, const Lax<T>& right);

} // namespace plinth
#include "Lax.inl"
#endif // PLINTH_LAX_HPP
