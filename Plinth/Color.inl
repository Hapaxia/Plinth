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

#ifndef PLINTH_COLOR_INL
#define PLINTH_COLOR_INL

#include "Generic.hpp"
#include "Math.hpp"
#include "NumberBase.hpp"
#include "Range.hpp"
#include "RandomDistribution.hpp"
#include "Strings.hpp"
#include "Tween.hpp"
#include <math.h>

#include "Color.hpp"
namespace plinth
{

	namespace Color
	{

const Range<double> alphaRange{ 0.0, 1.0 };



inline Rgb Rgb::operator+(const Rgb& other) const
{
	return Rgb(r + other.r, g + other.g, b + other.b);
}
inline Rgb Rgb::operator-(const Rgb& other) const
{
	return Rgb(r - other.r, g - other.g, b - other.b);
}
inline Rgb Rgb::operator*(const Rgb& other) const
{
	return Rgb(r * other.r, g * other.g, b * other.b);
}
template <class T>
inline Rgb Rgb::operator*(const T& scalar) const
{
	const double x{ static_cast<double>(scalar) };
	return Rgb(r * x, g * x, b * x);
}
template <class T>
inline Rgb Rgb::operator/(const T& scalar) const
{
	return *this * (1.0 / static_cast<double>(scalar));
}
inline Rgb& Rgb::operator+=(const Rgb& other)
{
	*this = *this + other;
	return *this;
}
inline Rgb& Rgb::operator-=(const Rgb& other)
{
	*this = *this - other;
	return *this;
}
inline Rgb& Rgb::operator*=(const Rgb& other)
{
	*this = *this * other;
	return *this;
}
template <class T>
inline Rgb& Rgb::operator*=(const T& scalar)
{
	*this = *this * scalar;
	return *this;
}
template <class T>
inline Rgb& Rgb::operator/=(const T& scalar)
{
	*this = *this / scalar;
	return *this;
}



inline Rgb::Rgb(const Init& init)
	: r{ 0.0 }
	, g{ 0.0 }
	, b{ 0.0 }
{
	if (init == RandomStandard)
	{
		RandomDistribution<double> random{ 0.0, 1.0 };
		*this = Rgb{ random.value(), random.value(), random.value() };
	}
	else if (init == RandomTrivial)
	{
		constexpr int resolution{ 10000 };
		*this = Rgb{ static_cast<double>(rand() % (resolution + 1)) / resolution, static_cast<double>(rand() % (resolution + 1)) / resolution, static_cast<double>(rand() % (resolution + 1)) / resolution };
	}
}

inline Rgb::Rgb(const double newR, const double newG, const double newB)
	: r{ newR }
	, g{ newG }
	, b{ newB }
{
}

inline Rgb::Rgb(std::string hex)
	: Rgb()
{
	if (hex.size() > 6_uz)
		return;
	if (!doesContainOnly(upperCase(hex), "0123456789ABCDEF"))
		return;

	constexpr std::size_t baseMax{ 255_uz };
	hex = padStringLeft(hex, 6_uz, '0');
	*this = Rgb{
		r = Tween::linear(0.0, 1.0, static_cast<double>(decFromHex(hex.substr(0_uz, 2_uz))) / baseMax),
		g = Tween::linear(0.0, 1.0, static_cast<double>(decFromHex(hex.substr(2_uz, 2_uz))) / baseMax),
		b = Tween::linear(0.0, 1.0, static_cast<double>(decFromHex(hex.substr(4_uz, 2_uz))) / baseMax) };
}

inline Rgb::Rgb(long int value)
	: Rgb()
{
	if (!pl::Range<long int>{ 0L, 16777215L }.contains(value))
		return;

	constexpr int base{ 256 };
	constexpr int baseSquared{ base * base };
	constexpr double baseMinusOneRecip{ 1.0 / (base - 1) };

	const int red{ value / baseSquared };
	value -= red * baseSquared;
	const int green{ value / base };
	value -= green * base;
	const int blue{ value };

	r = Tween::linear(0.0, 1.0, static_cast<double>(red) * baseMinusOneRecip);
	g = Tween::linear(0.0, 1.0, static_cast<double>(green) * baseMinusOneRecip);
	b = Tween::linear(0.0, 1.0, static_cast<double>(blue) * baseMinusOneRecip);
}

inline std::string Rgb::getHex()
{
	const int baseMax{ 255 }; // base - 1
	std::vector<std::string> components
	{
		hexFromDec(static_cast<int>(round(alphaRange.clamp(r) * baseMax))),
		hexFromDec(static_cast<int>(round(alphaRange.clamp(g) * baseMax))),
		hexFromDec(static_cast<int>(round(alphaRange.clamp(b) * baseMax)))
	};
	for (auto& component : components)
	{
		while (component.size() < 2_uz)
			component.insert(0_uz, "0");
	}
	return concatenate(components);
}

inline Rgb::Rgb(const Cmy& other)
	: r{ alphaRange.clamp(1.0 - other.c) }
	, g{ alphaRange.clamp(1.0 - other.m) }
	, b{ alphaRange.clamp(1.0 - other.y) }
{
}

inline Rgb::Rgb(const Cmyk& other)
	: r{ (1.0 - alphaRange.clamp(other.c)) * (1.0 - alphaRange.clamp(other.k)) }
	, g{ (1.0 - alphaRange.clamp(other.m)) * (1.0 - alphaRange.clamp(other.k)) }
	, b{ (1.0 - alphaRange.clamp(other.y)) * (1.0 - alphaRange.clamp(other.k)) }
{
}



inline double Rgb::getRelativeLuminance()
{
	return (0.2126 * r) + (0.7152 * g) + (0.0722 * b);
}

inline Rgb::Rgb(const Hsl& other)
	: Rgb()
{
	const double c{ (1.0 - abs(2.0 * other.l - 1.0)) * other.s };
	priv_setRgbFromCmh(c, other.l - (c / 2.0), other.h);
}

inline Rgb::Rgb(const Hsv& other)
	: Rgb()
{
	const double c{ other.v * other.s };
	priv_setRgbFromCmh(c, other.v - c, other.h);
}

inline void Rgb::clampStandardRange()
{
	r = alphaRange.clamp(r);
	g = alphaRange.clamp(g);
	b = alphaRange.clamp(b);
}

inline void Rgb::priv_setRgbFromCmh(const double c, const double m, const double h)
{
	const double x{ c * (1.0 - abs(mod(h * 6.0, 2.0) - 1.0)) };

	constexpr double sixth{ 1.0 / 6.0 };
	if (h < (1.0 * sixth))
		*this = Rgb{ c, x, 0.0 };
	else if (h < (2.0 * sixth))
		*this = Rgb{ x, c, 0.0 };
	else if (h < (3.0 * sixth))
		*this = Rgb{ 0.0, c, x };
	else if (h < (4.0 * sixth))
		*this = Rgb{ 0.0, x, c };
	else if (h < (5.0 * sixth))
		*this = Rgb{ x, 0.0, c };
	else
		*this = Rgb{ c, 0.0, x };

	r += m;
	g += m;
	b += m;
}



inline Hsl::Hsl(const double newH, const double newS, const double newL)
	: h{ newH }
	, s{ newS }
	, l{ newL }
{
}

inline Hsv::Hsv(const double newH, const double newS, const double newV)
	: h{ newH }
	, s{ newS }
	, v{ newV }
{
}

inline Cmy::Cmy(const double newC, const double newM, const double newY)
	: c{ newC }
	, m{ newM }
	, y{ newY }
{
}

inline Cmyk::Cmyk(const double newC, const double newM, const double newY, const double newK)
	: c{ newC }
	, m{ newM }
	, y{ newY }
	, k{ newK }
{
}

inline Cmy::Cmy(const Rgb& other)
	: c{ alphaRange.clamp(1.0 - other.r) }
	, y{ alphaRange.clamp(1.0 - other.g) }
	, m{ alphaRange.clamp(1.0 - other.b) }
{
}

inline Cmyk::Cmyk(const Rgb& other)
{
	const double z{ alphaRange.clamp(max(max(other.r, other.g), other.b)) };
	*this = Cmyk{
		(z - alphaRange.clamp(other.r)) / z,
		(z - alphaRange.clamp(other.g)) / z,
		(z - alphaRange.clamp(other.b)) / z,
		k };
	/*
	const double k{ 1.0 - alphaRange.clamp(max(max(other.r, other.g), other.b)) };
	*this = Cmyk{
		(1.0 - alphaRange.clamp(other.r) - k) / (1.0 - k),
		(1.0 - alphaRange.clamp(other.g) - k) / (1.0 - k),
		(1.0 - alphaRange.clamp(other.b) - k) / (1.0 - k),
		k };
	*/
}

inline Hsl::Hsl(const Rgb& other)
{
	const double maximum{ alphaRange.clamp(max(max(other.r, other.g), other.b)) };
	const double minimum{ alphaRange.clamp(min(min(other.r, other.g), other.b)) };

	l = (maximum + minimum) * 0.5;

	if (minimum == maximum) // i.e. range is zero
	{
		h = 0.0;
		s = 0.0;
	}
	else
	{
		const double range{ maximum - minimum };
		const double rangeRecip{ 1.0 / range };
		constexpr double sixth{ 1.0 / 6.0 };
		if (other.r > other.g && other.r > other.b)
			h = mod((other.g - other.b) * rangeRecip, 6.0) * sixth;
		else if (other.g > other.r && other.g > other.b)
			h = (((other.b - other.r) * rangeRecip) + 2.0) * sixth;
		else
			h = (((other.r - other.g) * rangeRecip) + 4.0) * sixth;
		s = range / (1.0 - abs((2.0 * l) - 1.0));
	}
}

inline Hsv::Hsv(const Rgb& other)
{
	const double maximum{ alphaRange.clamp(max(max(other.r, other.g), other.b)) };
	const double minimum{ alphaRange.clamp(min(min(other.r, other.g), other.b)) };

	if (minimum == maximum) // i.e. range is zero
	{
		h = 0.0;
		s = 0.0;
	}
	else
	{
		const double range{ maximum - minimum };
		const double rangeRecip{ 1.0 / range };
		constexpr double sixth{ 1.0 / 6.0 };
		if (other.r > other.g && other.r > other.b)
			h = mod((other.g - other.b) * rangeRecip, 6.0) * sixth;
		else if (other.g > other.r && other.g > other.b)
			h = (((other.b - other.r) * rangeRecip) + 2.0) * sixth;
		else
			h = (((other.r - other.g) * rangeRecip) + 4.0) * sixth;
		s = range / maximum;
	}

	v = maximum;
}

	} // namespace Color
} // namespace plinth

#endif // PLINTH_COLOR_INL
