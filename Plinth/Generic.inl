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
	return std::max(a, b);
}

template<class T>
// returns the lowest value in a pair
inline T min(const T& a, const T& b)
{
	return std::min(a, b);
}

template<class T>
// returns the highest value of a vector
inline T max(const std::vector<T>& values)
{
	if (values.size() == 0)
		return T();
	std::vector<T>::const_iterator result = values.begin();
	for (std::vector<T>::const_iterator end = values.end(), it = result; it != end; ++it)
	{
		if (*result < *it)
			result = it;
	}
	return *result;
}

template<class T>
// returns the lowest value of a vector
inline T min(const std::vector<T>& values)
{
	if (values.size() == 0)
		return T();
	std::vector<T>::const_iterator result = values.begin();
	for (std::vector<T>::const_iterator end = values.end(), it = result; it != end; ++it)
	{
		if (*it < *result)
			result = it;
	}
	return *result;
}

template<class T>
// swaps two values
inline void swap(T& a, T& b)
{
	std::swap(a, b);
}

template<class T>
// order two values (low - high)
inline void orderLowHigh(T& low, T& high)
{
	if (high < low)
		swap(low, high);
}

template<class T>
// switches/toggles parameter (b = !b) and also returns the result
// e.g. a = !b, a becomes opposite of b. a = toggle(b), b becomes its opposite and a also becomes that opposite.
inline T toggle(T& b)
{
	return b = !b;
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
