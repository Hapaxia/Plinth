//////////////////////////////////////////////////////////////////////////////
//
// Plinth
//
// Copyright(c) 2014-2015 M.J.Silk
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

#include "Color.hpp"

#include "Generic.hpp"
#include "Math.hpp"
#include "NumberBase.hpp"
#include "Random.hpp"
#include "Strings.hpp"
#include "Tween.hpp"
#include <math.h>

namespace plinth
{
	namespace Color
	{

Rgb::Rgb(const Init& init) :
r(0.0),
g(0.0),
b(0.0)
{
	if (init == RandomStandard)
	{
		Random random;
		*this = Rgb{ random.value(0.0, 1.0), random.value(0.0, 1.0), random.value(0.0, 1.0) };
	}
	else if (init == RandomTrivial)
	{
		const unsigned int resolution{ 10000 };
		*this = Rgb{ static_cast<double>(rand() % (resolution + 1)) / resolution, static_cast<double>(rand() % (resolution + 1)) / resolution, static_cast<double>(rand() % (resolution + 1)) / resolution };
	}
}

Rgb::Rgb(const double newR, const double newG, const double newB) :
r(newR),
g(newG),
b(newB)
{
}

Rgb::Rgb(std::string hex) :
r(0.0),
g(0.0),
b(0.0)
{
	if (!doesContainOnly(upperCase(hex), "0123456789ABCDEF"))
		return;
	if (hex.size() > 6)
		return;

	const unsigned int baseMax{ 255 };
	while (hex.size() < 6)
		hex.insert(0, "0");
	*this = Rgb{
		r = Tween::linear(0.0, 1.0, static_cast<double>(decFromHex(hex.substr(0, 2))) / baseMax),
		g = Tween::linear(0.0, 1.0, static_cast<double>(decFromHex(hex.substr(2, 2))) / baseMax),
		b = Tween::linear(0.0, 1.0, static_cast<double>(decFromHex(hex.substr(4, 2))) / baseMax) };
}

Rgb::Rgb(long int value) :
r(0.0),
g(0.0),
b(0.0)
{
	if (!inRange(value, 0L, 16777215L))
		return;

	const int base{ 256 };

	int red{ value / (base * base) };
	value -= red * base * base;
	int green{ value / base };
	value -= green * base;
	int blue{ value };

	r = Tween::linear(0.0, 1.0, static_cast<double>(red) / (base - 1));
	g = Tween::linear(0.0, 1.0, static_cast<double>(green) / (base - 1));
	b = Tween::linear(0.0, 1.0, static_cast<double>(blue) / (base - 1));
}

std::string Rgb::getHex()
{
	const unsigned int baseMax{ 255 }; // base - 1
	std::vector<std::string> components
	{
		hexFromDec(static_cast<int>(round(clamp(r, 0.0, 1.0) * baseMax))),
		hexFromDec(static_cast<int>(round(clamp(g, 0.0, 1.0) * baseMax))),
		hexFromDec(static_cast<int>(round(clamp(b, 0.0, 1.0) * baseMax)))
	};
	for (auto& component : components)
	{
		while (component.size() < 2)
			component.insert(0, "0");
	}
	return concatenate(components);
	//return upperCase(concatenate(components));
}

Rgb::Rgb(const Cmy& other) :
r(clamp(1.0 - other.c, 0.0, 1.0)),
g(clamp(1.0 - other.m, 0.0, 1.0)),
b(clamp(1.0 - other.y, 0.0, 1.0))
{
}

Rgb::Rgb(const Cmyk& other) :
r((1.0 - clamp(other.c, 0.0, 1.0)) * (1.0 - clamp(other.k, 0.0, 1.0))),
g((1.0 - clamp(other.m, 0.0, 1.0)) * (1.0 - clamp(other.k, 0.0, 1.0))),
b((1.0 - clamp(other.y, 0.0, 1.0)) * (1.0 - clamp(other.k, 0.0, 1.0)))
{
}

double Rgb::getRelativeLuminance()
{
	return 0.2126 * r + 0.7152 * g + 0.0722 * b;
}

Rgb::Rgb(const Hsl& other)
{
	const double c{ (1.0 - abs(2 * other.l - 1)) * other.s };
	priv_setRgbFromCmh(c, other.l - c / 2.0, other.h);
}

Rgb::Rgb(const Hsv& other)
{
	double c{ other.v * other.s };
	priv_setRgbFromCmh(c, other.v - c, other.h);
}

void Rgb::priv_setRgbFromCmh(double c, double m, double h)
{
	double x{ c * (1.0 - abs(mod(h * 6.0, 2.0) - 1.0)) };

	if (h < (1.0 / 6.0))
		*this = Rgb{ c, x, 0.0 };
	else if (h < (2.0 / 6.0))
		*this = Rgb{ x, c, 0.0 };
	else if (h < (3.0 / 6.0))
		*this = Rgb{ 0.0, c, x };
	else if (h < (4.0 / 6.0))
		*this = Rgb{ 0.0, x, c };
	else if (h < (5.0 / 6.0))
		*this = Rgb{ x, 0.0, c };
	else
		*this = Rgb{ c, 0.0, x };

	r += m;
	g += m;
	b += m;
}

Hsl::Hsl(double newH, double newS, double newL) :
h(newH),
s(newS),
l(newL)
{
}

Hsv::Hsv(double newH, double newS, double newV) :
h(newH),
s(newS),
v(newV)
{
}

Cmy::Cmy(double newC, double newM, double newY) :
c(newC),
m(newM),
y(newY)
{
}

Cmyk::Cmyk(double newC, double newM, double newY, double newK) :
c(newC),
m(newM),
y(newY),
k(newK)
{
}


Cmy::Cmy(const Rgb& other) :
c(clamp(1.0 - other.r, 0.0, 1.0)),
y(clamp(1.0 - other.g, 0.0, 1.0)),
m(clamp(1.0 - other.b, 0.0, 1.0))
{
}

Cmyk::Cmyk(const Rgb& other)
{
	double k{ 1.0 - clamp(max(max(other.r, other.g), other.b), 0.0, 1.0) };
	*this = Cmyk{
		(1.0 - clamp(other.r, 0.0, 1.0) - k) / (1.0 - k),
		(1.0 - clamp(other.g, 0.0, 1.0) - k) / (1.0 - k),
		(1.0 - clamp(other.b, 0.0, 1.0) - k) / (1.0 - k),
		k };
}

Hsl::Hsl(const Rgb& other)
{
	double maximum{ clamp(max(max(other.r, other.g), other.b), 0.0, 1.0) };
	double minimum{ clamp(min(min(other.r, other.g), other.b), 0.0, 1.0) };
	double range{ maximum - minimum };

	l = (maximum + minimum) / 2.0;

	if (minimum == maximum) // i.e. range is zero
	{
		h = 0.0;
		s = 0.0;
	}
	else
	{
		if (other.r > other.g && other.r > other.b)
			h = mod((other.g - other.b) / range, 6.0) / 6.0;
		else if (other.g > other.r && other.g > other.b)
			h = (((other.b - other.r) / range) + 2.0) / 6.0;
		else
			h = (((other.r - other.g) / range) + 4.0) / 6.0;
		s = range / (1.0 - abs(2.0 * l - 1.0));
	}
}

Hsv::Hsv(const Rgb& other)
{
	double maximum{ clamp(max(max(other.r, other.g), other.b), 0.0, 1.0) };
	double minimum{ clamp(min(min(other.r, other.g), other.b), 0.0, 1.0) };
	double range{ maximum - minimum };

	if (other.r > other.g && other.r > other.b)
		h = mod((other.g - other.b) / range, 6.0) / 6.0;
	else if (other.g > other.r && other.r > other.b)
		h = (((other.b - other.r) / range) + 2.0) / 6.0;
	else
		h = (((other.r - other.g) / range) + 4.0) / 6.0;

	v = maximum;

	if (minimum != maximum)
		s = range / maximum;
	else
		s = 0.0;
}

	} // namespace Color
} // namespace plinth
