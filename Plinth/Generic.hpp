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

// Generic

// generic/common functions

#ifndef PLINTH_GENERIC_HPP
#define PLINTH_GENERIC_HPP

#include "Common.hpp"
#include "Math.hpp"

template <class T>
class Range;
template <class T>
class Vector3;

namespace plinth
{

template <class T>
// returns the highest value in a pair
inline constexpr T max(const T& a, const T& b);

template <class T>
// returns the lowest value in a pair
inline constexpr T min(const T& a, const T& b);

template <class T>
// returns the highest value of a vector
inline constexpr T max(const std::vector<T>& vector);

template <class T>
// returns the lowest value of a vector
inline constexpr T min(const std::vector<T>& vector);

template <class T>
// swaps two values
inline void swap(T& a, T& b);

template <class T>
// order two values (low - high)
inline constexpr void orderLowHigh(T& low, T& high);

template<class T>
// switches/toggles parameter (b = !b) and also returns the result
// e.g. a = !b, a becomes opposite of b. a = toggle(b), b becomes its opposite and a also becomes that opposite.
inline T toggle(T& b);

template <class IntegerT, class CharT>
inline IntegerT intFromBytes(std::size_t numberOfBytes, const CharT* bytes, bool isLittleEndian = true);

template <class IntegerT, class CharT>
inline IntegerT intFromBytes(const std::vector<CharT>& bytes, bool isLittleEndian = true);

} // namespace plinth
#include "Generic.inl"
#endif // PLINTH_GENERIC_HPP
