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

#ifndef PLINTH_COLOR_HPP
#define PLINTH_COLOR_HPP

#include "Common.hpp"

namespace plinth
{

template <class T>
struct Range;

	namespace Color
	{

struct Rgb;
struct Hsl;
struct Hsv;
struct Cmy;
struct Cmyk;

// RGB = Red, Green, Blue
struct Rgb
{
	enum Init
	{
		Zero,
		RandomStandard,
		RandomTrivial
	};
	double r, g, b;
	explicit Rgb(const Init& init = Zero);
	explicit Rgb(double r, double g, double b);
	explicit Rgb(const Hsl& other);
	explicit Rgb(const Hsv& other);
	explicit Rgb(const Cmy& other);
	explicit Rgb(const Cmyk& other);
	explicit Rgb(std::string hex);
	Rgb(long int value);
	std::string getHex();
	double getRelativeLuminance();
	void clampStandardRange();
	Rgb operator+(const Rgb& other) const;
	Rgb operator-(const Rgb& other) const;
	Rgb operator*(const Rgb& other) const;
	template <class T>
	Rgb operator*(const T& scalar) const;
	template <class T>
	Rgb operator/(const T& scalar) const;
	Rgb& operator+=(const Rgb& other);
	Rgb& operator-=(const Rgb& other);
	Rgb& operator*=(const Rgb& other);
	template <class T>
	Rgb& operator*=(const T& scalar);
	template <class T>
	Rgb& operator/=(const T& scalar);

private:
	void priv_setRgbFromCmh(double c, double m, double h);
};

// HSL = Hue, Saturation, Lightness
struct Hsl
{
	double h, s, l;
	Hsl() : h(0.0), s(0.0), l(0.0) {}
	explicit Hsl(double newH, double newS, double newL);
	explicit Hsl(const Rgb& other);
};

// HSV = Hue, Saturation, Value
struct Hsv
{
	double h, s, v;
	Hsv() : h(0.0), s(0.0), v(0.0) {}
	explicit Hsv(double newH, double newS, double newV);
	explicit Hsv(const Rgb& other);
};

// CYM = Cyan, Magenta, Yellow
struct Cmy
{
	double c, m, y;
	Cmy() : c(0.0), m(0.0), y(0.0) {}
	explicit Cmy(double newC, double newM, double newY);
	explicit Cmy(const Rgb& other);
};

// CMYK = Cyan, Magenta, Yellow, Key(blacK)
struct Cmyk
{
	double c, m, y, k;
	Cmyk() : c(0.0), m(0.0), y(0.0), k(0.0) {}
	explicit Cmyk(double newC, double newM, double newY, double newK);
	explicit Cmyk(const Rgb& other);
};

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
	const double x{ static_cast<double>(scalar) };
	return Rgb(r / x, g / x, b / x);
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
	*this = *this * other;
	return *this;
}

template <class T>
inline Rgb& Rgb::operator/=(const T& scalar)
{
	*this = *this / other;
	return *this;
}

	} // namespace Color
} // namespace plinth
#endif // PLINTH_COLOR_HPP
