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

#ifndef PLINTH_STRINGFROM_INL
#define PLINTH_STRINGFROM_INL

#include "StringFrom.hpp"

#include <sstream>
#include <iomanip>
#include "NumberBase.hpp"
#include "Strings.hpp"

namespace plinth
{

inline std::string stringFrom(const std::string& from)
{
	return from;
}

inline std::string stringFrom(const char* from)
{
	return std::string(from);
}

inline std::string stringFrom(const bool from)
{
	return (from ? "true" : "false");
}

inline std::string stringFrom(const Color::Rgb rgb, const DecimalPrecision decimalPrecision)
{
	return stringFrom(Vector3d(rgb.r, rgb.g, rgb.b), decimalPrecision);
}

template <class T>
inline std::string stringFrom(T* p)
{
	const std::string unpadded{ upperCase(hexFromDec(reinterpret_cast<std::size_t>(p))) };
	return padStringLeft(unpadded, (unpadded.size() > 32_uz) ? 64_uz : (unpadded.size() > 16_uz) ? 32_uz : (unpadded.size() > 8_uz) ? 16_uz : 8_uz, '0');
}

template <class T>
inline std::string stringFrom(T* p, const std::size_t minimumSize)
{
	const std::string padded{ stringFrom(p) };
	return padStringLeft(padded, (padded.size() < minimumSize) ? minimumSize : padded.size(), '0');
}

template<class T>
inline std::string stringFrom(const pl::Vector2<T> from, const DecimalPrecision decimalPrecision)
{
	return "(" + stringFrom(from.x, decimalPrecision) + ", " + stringFrom(from.y, decimalPrecision) + ")";
}

template <class T>
inline std::string stringFrom(const Lax<T> lax, const DecimalPrecision decimalPrecision)
{
	return stringFrom(static_cast<T>(lax), decimalPrecision);
}

template <class T>
inline std::string stringFrom(const std::vector<T> froms, const DecimalPrecision decimalPrecision)
{
	std::string to{};
	for (auto& from : froms)
		to += stringFrom(from, decimalPrecision);
	return to;
}

template<class T>
std::string stringFrom(const std::vector<T> froms, const std::string& separator, const DecimalPrecision decimalPrecision)
{
	std::string to{};
	for (auto begin{ froms.begin() }, end{ froms.end() }, it{ begin }; it != end; ++it)
	{
		to += stringFrom(*it, decimalPrecision);
		if ((it + 1_uz) != end)
			to += separator;
	}
	return to;
}

template <class T>
inline std::string stringFrom(const T& from, const DecimalPrecision decimalPrecision)
{
	if (decimalPrecision.type == DecimalPrecision::None)
		return std::to_string(from);

	std::stringstream ss;
	if (decimalPrecision.type == DecimalPrecision::DecimalPlaces)
		ss << std::fixed;
	ss << std::setprecision(decimalPrecision.digits) << static_cast<long double>(from);
	return ss.str();
}

template<class T>
inline std::string stringFrom(const pl::Vector3<T> from, const DecimalPrecision decimalPrecision)
{
	return "(" + stringFrom(from.x, decimalPrecision) + ", " + stringFrom(from.y, decimalPrecision) + ", " + stringFrom(from.z, decimalPrecision) + ")";
}

template<class T>
inline std::string stringFrom(const pl::Size2<T> from, const DecimalPrecision decimalPrecision)
{
	return stringFrom(from.width, decimalPrecision) + " x " + stringFrom(from.height, decimalPrecision);
}
template<class T>
inline std::string stringFrom(const pl::Size3<T> from, const DecimalPrecision decimalPrecision)
{
	return stringFrom(from.width, decimalPrecision) + " x " + stringFrom(from.height, decimalPrecision) + " x " + stringFrom(from.depth, decimalPrecision);
}

template<class T>
inline std::string stringFrom(const pl::Range<T> from, const DecimalPrecision decimalPrecision)
{
	return stringFrom(from.min, decimalPrecision) + " - " + stringFrom(from.max, decimalPrecision);
}

template<class T>
inline std::string stringFrom(const pl::Range<pl::Vector2<T>> from, const DecimalPrecision decimalPrecision)
{
	return stringFrom(pl::Vector2<std::string>(stringFrom(pl::Range<T>{ from.min.x, from.max.x }, decimalPrecision), stringFrom(pl::Range<T>{ from.min.y, from.max.y }, decimalPrecision)));
}

template<class T>
inline std::string stringFrom(const pl::Range<pl::Vector3<T>> from, const DecimalPrecision decimalPrecision)
{
	return stringFrom(pl::Vector3<std::string>(stringFrom(pl::Range<T>{ from.min.x, from.max.x }, decimalPrecision), stringFrom(pl::Range<T>{ from.min.y, from.max.y }, decimalPrecision), stringFrom(pl::Range<T>{ from.min.z, from.max.z }, decimalPrecision)));
}

template<class T>
inline std::string stringFrom(const pl::RangeArea<T> from, const DecimalPrecision decimalPrecision)
{
	return stringFrom(pl::Range<pl::Vector2<T>>{ from.getLeftBottom(), from.getRightTop() }, decimalPrecision);
}

} // namespace plinth
#endif // PLINTH_STRINGFROM_INL
