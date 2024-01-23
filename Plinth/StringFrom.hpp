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

#pragma once

#include "Common.hpp"
#include "Lax.hpp"
#include "Range.hpp"
#include "RangeArea.hpp"
#include "Vectors.hpp"
#include "Sizes.hpp"
#include "Color.hpp"

namespace plinth
{

struct DecimalPrecision
{
	std::size_t digits;
	enum Type
	{
		None,
		DecimalPlaces,
		SignificantFigures,
	} type;
	//DecimalPrecision() : digits{ 6u }, type{ Type::None } { }
	DecimalPrecision(const std::size_t newDigits, const Type newType = Type::DecimalPlaces) : digits{ newDigits }, type{ newType } { }
	DecimalPrecision(const Type newType) : digits{ 6u }, type { newType } { }
	//void operator=(Type newType) { type = newType; }
};

std::string stringFrom(const std::string& = "");
std::string stringFrom(const char*);
std::string stringFrom(bool);
std::string stringFrom(Color::Rgb rgb, DecimalPrecision decimalPrecision = DecimalPrecision::None);

template <class T>
std::string stringFrom(T*);
template <class T>
std::string stringFrom(T*, std::size_t minimumSize);

template <class T>
std::string stringFrom(const T&, DecimalPrecision decimalPrecision = DecimalPrecision::None);

template <class T>
std::string stringFrom(Lax<T> lax, DecimalPrecision decimalPrecision = DecimalPrecision::None);

template <class T>
std::string stringFrom(const std::vector<T>, DecimalPrecision decimalPrecision = DecimalPrecision::None);
template <class T>
std::string stringFrom(const std::vector<T>, const std::string& separator, DecimalPrecision decimalPrecision = DecimalPrecision::None);

template<class T>
std::string stringFrom(pl::Vector2<T>, DecimalPrecision decimalPrecision = DecimalPrecision::None);

template<class T>
std::string stringFrom(pl::Vector3<T>, DecimalPrecision decimalPrecision = DecimalPrecision::None);

template<class T>
std::string stringFrom(pl::Size2<T>, DecimalPrecision decimalPrecision = DecimalPrecision::None);
template<class T>
std::string stringFrom(pl::Size3<T>, DecimalPrecision decimalPrecision = DecimalPrecision::None);

template<class T>
std::string stringFrom(pl::Range<T>, DecimalPrecision decimalPrecision = DecimalPrecision::None);
template<class T>
std::string stringFrom(pl::Range<pl::Vector2<T>>, DecimalPrecision decimalPrecision = DecimalPrecision::None);
template<class T>
std::string stringFrom(pl::Range<pl::Vector3<T>>, DecimalPrecision decimalPrecision = DecimalPrecision::None);

template<class T>
std::string stringFrom(pl::RangeArea<T>, DecimalPrecision decimalPrecision = DecimalPrecision::None);

} // namespace plinth
#include "StringFrom.inl"
