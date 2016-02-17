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

#ifndef PLINTH_GENERIC_INL
#define PLINTH_GENERIC_INL

namespace plinth
{

template<class T>
// returns the highest value in a pair
inline T max(const T& a, const T& b)
{
	return a > b ? a : b;
}

template<class T>
// returns the lowest value in a pair
inline T min(const T& a, const T& b)
{
	return a < b ? a : b;
}

template<class T>
// returns the highest value of a vector
inline T max(const std::vector<T>& values)
{
	if (values.size() == 0)
		return T();
	T result{ values[0] };
	for (unsigned int i{ 1 }; i < values.size(); ++i)
		result = max(result, values[i]);
	return result;
}

template<class T>
// returns the lowest value of a vector
inline T min(const std::vector<T>& values)
{
	if (values.size() == 0)
		return T();
	T result{ values[0] };
	for (unsigned int i{ 1 }; i < values.size(); ++i)
		result = min(result, values[i]);
	return result;
}

template<class T>
// swaps two values
inline void swap(T& a, T& b)
{
	T c = a;
	a = b;
	b = c;
}

template<class T>
// order two values (low - high)
inline void orderLowHigh(T& low, T& high)
{
	if (low > high)
		swap(low, high);
}

template<class T>
// switches/toggles parameter (b = !b) and also returns the result
// e.g. a = !b, a becomes opposite of b. a = toggle(b), a becomes opposite of what b was but b is now identical to a.
inline T toggle(T& b)
{
	b = !b;
	return b;
}

template <class IntegerType>
IntegerType intFromBytes(const unsigned int numberOfBytes, const unsigned char* bytes, const bool isLittleEndian)
{
	IntegerType result = 0;
	if (isLittleEndian)
	{
		for (unsigned intint n{ numberOfBytes }; n > 0; --n)
			result = (result << 8) + bytes[n - 1];
	}
	else
	{
		for (unsigned int n{ 0 }; n < numberOfBytes; ++n)
			result = (result << 8) + bytes[n];
	}
	return result;
}

template <class IntegerType>
IntegerType intFromBytes(const std::vector<unsigned char>& bytes, const bool isLittleEndian)
{
	IntegerType result = 0;
	const unsigned int numberOfBytes{ bytes.size() };
	if (isLittleEndian)
	{
		for (unsigned intint n{ numberOfBytes }; n > 0; --n)
			result = (result << 8) + bytes[n - 1];
	}
	else
	{
		for (unsigned int n{ 0 }; n < numberOfBytes; ++n)
			result = (result << 8) + bytes[n];
	}
	return result;
}

} // namespace plinth
#endif // PLINTH_GENERIC_INL
