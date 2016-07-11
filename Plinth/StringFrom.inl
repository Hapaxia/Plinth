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

#ifndef PLINTH_STRINGFROM_INL
#define PLINTH_STRINGFROM_INL

#include <sstream>
#include <iomanip>

namespace plinth
{

template <class T>
std::string stringFrom(const std::vector<T> froms)
{
	std::string to = "";
	for (auto& from : froms)
		to += stringFrom(from);
	return to;
}

template <class T>
std::string stringFrom(const T& from)
{
	return std::to_string(from);
}

template <class T>
std::string stringFrom(const T& from, const unsigned int decimalPrecision)
{
	std::stringstream ss;
	ss << std::setprecision(decimalPrecision) << static_cast<long double>(from);
	return ss.str();
}

template<class T>
std::string stringFrom(const pl::Vector2<T> from)
{
	return "(" + stringFrom(from.x) + ", " + stringFrom(from.y) + ")";
}
template<class T>
std::string stringFrom(const pl::Vector2<T> from, const unsigned int decimalPrecision)
{
	return "(" + stringFrom(from.x, decimalPrecision) + ", " + stringFrom(from.y, decimalPrecision) + ")";
}

template<class T>
std::string stringFrom(const pl::Vector3<T> from)
{
	return "(" + stringFrom(from.x) + ", " + stringFrom(from.y) + ", " + stringFrom(from.z) + ")";
}
template<class T>
std::string stringFrom(const pl::Vector3<T> from, const unsigned int decimalPrecision)
{
	return "(" + stringFrom(from.x, decimalPrecision) + ", " + stringFrom(from.y, decimalPrecision) + ", " + stringFrom(from.z, decimalPrecision) + ")";
}

template<class T>
std::string stringFrom(const pl::Size2<T> from)
{
	return stringFrom(from.width) + " x " + stringFrom(from.height);
}
template<class T>
std::string stringFrom(const pl::Size2<T> from, const unsigned int decimalPrecision)
{
	return stringFrom(from.width, decimalPrecision) + " x " + stringFrom(from.height, decimalPrecision);
}
template<class T>
std::string stringFrom(const pl::Size3<T> from)
{
	return stringFrom(from.width) + " x " + stringFrom(from.height) + " x " + stringFrom(from.depth);
}
template<class T>
std::string stringFrom(const pl::Size3<T> from, const unsigned int decimalPrecision)
{
	return stringFrom(from.width, decimalPrecision) + " x " + stringFrom(from.height, decimalPrecision) + " x " + stringFrom(from.depth, decimalPrecision);
}

template<class T>
std::string stringFrom(const pl::Range<T> from)
{
	return stringFrom(from.min) + " - " + stringFrom(from.max);
}
template<class T>
std::string stringFrom(const pl::Range<T> from, const unsigned int decimalPrecision)
{
	return stringFrom(from.min, decimalPrecision) + " - " + stringFrom(from.max, decimalPrecision);
}

template<class T>
std::string stringFrom(const pl::Range<pl::Vector2<T>> from)
{
	return stringFrom(pl::Vector2<std::string>{stringFrom(pl::Range<T>{ from.min.x, from.max.x }), stringFrom(pl::Range<T>{ from.min.y, from.max.y })});
}
template<class T>
std::string stringFrom(const pl::Range<pl::Vector2<T>> from, const unsigned int decimalPrecision)
{
	return stringFrom(pl::Vector2<std::string>{stringFrom(pl::Range<T>{ from.min.x, from.max.x }, decimalPrecision), stringFrom(pl::Range<T>{ from.min.y, from.max.y }, decimalPrecision)});
}

template<class T>
std::string stringFrom(const pl::Range<pl::Vector3<T>> from)
{
	return stringFrom(pl::Vector3<std::string>{stringFrom(pl::Range<T>{ from.min.x, from.max.x }), stringFrom(pl::Range<T>{ from.min.y, from.max.y }), stringFrom(pl::Range<T>{ from.min.z, from.max.z })});
}
template<class T>
std::string stringFrom(const pl::Range<pl::Vector3<T>> from, const unsigned int decimalPrecision)
{
	return stringFrom(pl::Vector3<std::string>{stringFrom(pl::Range<T>{ from.min.x, from.max.x }, decimalPrecision), stringFrom(pl::Range<T>{ from.min.y, from.max.y }, decimalPrecision), stringFrom(pl::Range<T>{ from.min.z, from.max.z }, decimalPrecision)});
}

template<class T>
std::string stringFrom(const pl::RangeArea<T> from)
{
	return stringFrom(pl::Range<pl::Vector2<T>>{from.getLeftBottom(), from.getRightTop()});
}
template<class T>
std::string stringFrom(const pl::RangeArea<T> from, const unsigned int decimalPrecision)
{
	return stringFrom(pl::Range<pl::Vector2<T>>{from.getLeftBottom(), from.getRightTop()}, decimalPrecision);
}

} // namespace plinth
#endif // PLINTH_STRINGFROM_INL
