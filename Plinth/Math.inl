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

#include "Math.hpp"

#include <cmath>
#include <limits>

namespace plinth
{

template <class T>
// returns angle given in degrees as radians
inline constexpr T radiansFromDegrees(const T& degrees)
{
	constexpr long double multiplier{ piLongDouble / 180.0L };
	return static_cast<T>(degrees * multiplier);
}

template <class T>
// returns angle given in radians as degrees
inline constexpr T degreesFromRadians(const T& radians)
{
	constexpr long double multiplier{ 180.0L / piLongDouble };
	return static_cast<T>(radians * multiplier);
}

template <class T>
// mod (%) from floating point numbers
inline constexpr T mod(const T& a, const T& b)
{
	return static_cast<T>(a - (std::trunc(static_cast<long double>(a) / b) * b));
}

template<class T>
// rounds to the given decimal place
constexpr T round(const T& value, const std::size_t decimalPlaces)
{
	long double multiplier{ std::pow(10.0, static_cast<long double>(decimalPlaces)) };
	return std::round(value * decimalPlaces) / decimalPlaces;
}

// power (^) for integers
// negative exponents cause the real part to be truncated (resulting in a value of zero)
// overflow returns zero safely
inline constexpr long long int pow(const long long int base, const short int exponent)
{
	if (exponent < 0ll)
		return 0ll;
	if (exponent == 0ll)
		return 1ll;
	constexpr long long int maxLimit{ std::numeric_limits<long long int>::max() };
	constexpr long long int minLimit{ std::numeric_limits<long long int>::min() };
	const long long maxBeforeOverflow{ maxLimit / base };
	const long long minBeforeOverflow{ minLimit / base };
	long long int result{ base };
	for (long long int i{ 1ll }; i < exponent; ++i)
	{
		if (((base > 0) && (result > maxBeforeOverflow)) ||
			((base < 0) && ((abs(result) > minBeforeOverflow) || ((-abs(result)) < maxBeforeOverflow))))
			return 0ll;
		else
			result *= base;
	}
	return result;
}

// power (^) for integers
// negative exponents cause the real part to be truncated (resulting in a value of zero)
// overflow returns zero safely; "overflowed" is set to true
inline constexpr long long int pow(const long long int base, const short int exponent, bool& overflowed)
{
	overflowed = false;
	if (exponent < 0ll)
		return 0ll;
	if (exponent == 0ll)
		return 1ll;
	constexpr long long int maxLimit{ std::numeric_limits<long long int>::max() };
	constexpr long long int minLimit{ std::numeric_limits<long long int>::min() };
	const long long maxBeforeOverflow{ maxLimit / base };
	const long long minBeforeOverflow{ minLimit / base };
	long long int result{ base };
	for (long long int i{ 1ll }; i < exponent; ++i)
	{
		if (((base > 0) && (result > maxBeforeOverflow)) ||
			((base < 0) && ((abs(result) > minBeforeOverflow) || ((-abs(result)) < maxBeforeOverflow))))
		{
			overflowed = true;
			return 0ll;
		}
		else
			result *= base;
	}
	return result;
}

template <class T>
// returns either the parameter - if not negtive - or its positive counterpart
inline constexpr T abs(const T& value)
{
	return (value < 0) ? -value : value;
}

template <class T>
// returns the dot product of two vectors with the same number of elements
inline constexpr T dot(const std::vector<T>& a, const std::vector<T>& b)
{
	T result{ static_cast<T>(0) };
	const std::size_t aSize{ a.size() };

	if ((aSize == 0_uz) || (aSize != b.size()))
		return result;

	for (std::size_t i{ 0_uz }; i < aSize; ++i)
		result += a[i] * b[i];

	return result;
}

template <class ResultT, class T>
// return the mean (mean average) of two values
inline constexpr ResultT mean(const T& a, const T& b)
{
	return static_cast<ResultT>(static_cast<long double>(a + b) * 0.5);
}

template <class T>
// return the mean (mean average) of two values
inline constexpr T mean(const T& a, const T& b)
{
	return static_cast<T>(static_cast<long double>(a + b) * 0.5);
}

template <class ResultT, class T>
// return the mean (mean average) of all values in a vector
inline constexpr ResultT mean(const std::vector<T>& values)
{
	long double sum{ 0.0 };
	for (const auto& value : values)
		sum += static_cast<long double>(value);
	return static_cast<ResultT>(sum / values.size());
}

template <class T>
// return the mean (mean average) of all values in a vector
inline constexpr T mean(const std::vector<T>& values)
{
	long double sum{ 0.0 };
	for (const auto& value : values)
		sum += static_cast<long double>(value);
	return static_cast<T>(sum / values.size());
}

} // namespace plinth
