//////////////////////////////////////////////////////////////////////////////
//
// Plinth
//
// Copyright(c) 2014-2026 M.J.Silk
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

// Miscellaenous maths functions, constants and functions

#pragma once

#include "Common.hpp"

namespace plinth
{

template <class T>
// returns angle given in degrees as radians
inline constexpr T radiansFromDegrees(const T& degrees);

template <class T>
// returns angle given in radians as degrees
inline constexpr T degreesFromRadians(const T& radians);

template <class T>
// mod (%) from floating point number
inline constexpr T mod(const T& a, const T& b);

template <class T>
// rounds to the given decimal place
inline constexpr T round(const T& value, std::size_t decimalPlaces = 0_uz);

// power (^) for integers
// negative exponents cause the real part to be truncated (resulting in a value of zero)
// overflow returns zero safely
inline constexpr long long int pow(long long int base, short int exponent);

// power (^) for integers
// negative exponents cause the real part to be truncated (resulting in a value of zero)
// overflow returns zero safely; "overflowed" is set to true
inline constexpr long long int pow(long long int base, short int exponent, bool& overflowed);

template <class T>
// returns either the parameter - if not negtive - or its positive counterpart
inline constexpr T abs(const T& value);

template <class T>
// returns the dot product of two vectors with the same number of elements
inline constexpr T dot(const std::vector<T>& a, const std::vector<T>& b);

template <class ResultT, class T>
// return the mean (mean average) of two values
inline constexpr ResultT mean(const T& a, const T& b);

template <class T>
// return the mean (mean average) of two values
inline constexpr T mean(const T& a, const T& b);

template <class ResultT, class T>
// return the mean (mean average) of all values in a vector
inline constexpr ResultT mean(const std::vector<T>& values);

template <class T>
// return the mean (mean average) of all values in a vector
inline constexpr T mean(const std::vector<T>& values);



// CONSTANTS

// pi
constexpr long double piLongDouble{ 3.1415926535897932384626433832795L };
constexpr double piDouble{ static_cast<double>(piLongDouble) };
constexpr float piFloat{ static_cast<float>(piLongDouble) };

// tau
constexpr long double tauLongDouble{ piLongDouble * 2.0L };
constexpr double tauDouble{ static_cast<double>(tauLongDouble) };
constexpr float tauFloat{ static_cast<float>(tauLongDouble) };

// e
constexpr long double eLongDouble{ 2.718281828459045235360287471352L };
constexpr double eDouble{ static_cast<double>(eLongDouble) };
constexpr float eFloat{ static_cast<float>(eLongDouble) };

// square root of 2
constexpr long double sqrt2LongDouble{ 1.414213562373095048801688724209L };
constexpr double sqrt2Double{ static_cast<double>(sqrt2LongDouble) };
constexpr float sqrt2Float{ static_cast<float>(sqrt2LongDouble) };

// half of square root of 2 (is equal to reciprocal of square root of 2)
constexpr long double halfSqrt2LongDouble{ sqrt2LongDouble / 2.0L };
constexpr double halfSqrt2Double{ static_cast<double>(halfSqrt2LongDouble) };
constexpr float halfSqrt2Float{ static_cast<float>(halfSqrt2LongDouble) };

// square root of 3
constexpr long double sqrt3LongDouble{ 1.732050807568877293527446341505872366942805253810380628055806L };
constexpr double sqrt3Double{ static_cast<double>(sqrt3LongDouble) };
constexpr float sqrt3Float{ static_cast<float>(sqrt3LongDouble) };

// half of square root of 3
constexpr long double halfSqrt3LongDouble{ sqrt3LongDouble / 2.0L };
constexpr double halfSqrt3Double{ static_cast<double>(halfSqrt3LongDouble) };
constexpr float halfSqrt3Float{ static_cast<float>(halfSqrt3LongDouble) };

// square root of 5
constexpr long double sqrt5LongDouble{ 2.23606797749978969640917366873127623544L };
constexpr double sqrt5Double{ static_cast<double>(sqrt5LongDouble) };
constexpr float sqrt5Float{ static_cast<float>(sqrt5LongDouble) };

// half of square root of 5
constexpr long double halfSqrt5LongDouble{ sqrt5LongDouble / 2.0L };
constexpr double halfSqrt5Double{ static_cast<double>(halfSqrt5LongDouble) };
constexpr float halfSqrt5Float{ static_cast<float>(halfSqrt5LongDouble) };

// golden ratio
constexpr long double goldenRatioLongDouble{ (1.0L + sqrt5LongDouble) / 2.0L };
constexpr double goldenRatioDouble{ static_cast<double>(goldenRatioLongDouble) };
constexpr float goldenRatioFloat{ static_cast<float>(goldenRatioLongDouble) };

// default types
constexpr double pi{ piDouble };
constexpr double tau{ tauDouble };
constexpr double e{ eDouble };
constexpr double sqrt2{ sqrt2Double };
constexpr double halfSqrt2{ halfSqrt2Double };
constexpr double sqrt3{ sqrt3Double };
constexpr double halfSqrt3{ halfSqrt3Double };
constexpr double sqrt5{ sqrt5Double };
constexpr double halfSqrt5{ halfSqrt5Double };
constexpr double goldenRatio{ goldenRatioDouble };

// trigonometry constants (sin, cos and tan in increments of 15 degrees between 0 degrees and 360 degrees, both inclusive)

constexpr double sin0{ 0.0 };
constexpr double cos0{ 1.0 };
constexpr double sin15{ (sqrt2 * (sqrt3 - 1)) / 4 };
constexpr double cos15{ (sqrt2 * (sqrt3 + 1)) / 4 };
constexpr double sin30{ 1.0 / 2 };
constexpr double cos30{ halfSqrt3 };
constexpr double sin45{ halfSqrt2 };
constexpr double cos45{ halfSqrt2 };

constexpr double sin60{ cos30 };
constexpr double cos60{ sin30 };
constexpr double sin75{ cos15 };
constexpr double cos75{ sin15 };
constexpr double sin90{ cos0 };
constexpr double cos90{ sin0 };

constexpr double sin105{ cos15 };
constexpr double cos105{ -sin15 };
constexpr double sin120{ cos30 };
constexpr double cos120{ -sin30 };
constexpr double sin135{ cos45 };
constexpr double cos135{ -sin45 };
constexpr double sin150{ cos60 };
constexpr double cos150{ -sin60 };
constexpr double sin165{ cos75 };
constexpr double cos165{ -sin75 };
constexpr double sin180{ cos90 };
constexpr double cos180{ -sin90 };

constexpr double sin195{ -sin15 };
constexpr double cos195{ -cos15 };
constexpr double sin210{ -sin30 };
constexpr double cos210{ -cos30 };
constexpr double sin225{ -sin45 };
constexpr double cos225{ -cos45 };
constexpr double sin240{ -sin60 };
constexpr double cos240{ -cos60 };
constexpr double sin255{ -sin75 };
constexpr double cos255{ -cos75 };
constexpr double sin270{ -sin90 };
constexpr double cos270{ -cos90 };

constexpr double sin285{ -sin105 };
constexpr double cos285{ -cos105 };
constexpr double sin300{ -sin120 };
constexpr double cos300{ -cos120 };
constexpr double sin315{ -sin135 };
constexpr double cos315{ -cos135 };
constexpr double sin330{ -sin150 };
constexpr double cos330{ -cos150 };
constexpr double sin345{ -sin165 };
constexpr double cos345{ -cos165 };

constexpr double sin360{ sin0 };
constexpr double cos360{ cos0 };

// tan90 or tan270 do not exist as tan(90) and tan(270) are both undefined

constexpr double tan0{ 0.0 };
constexpr double tan15{ 2 - sqrt3 };
constexpr double tan30{ sqrt3 / 3.0 };
constexpr double tan45{ 1.0 };
constexpr double tan60{ sqrt3 };

constexpr double tan120{ -tan60 };
constexpr double tan135{ -tan45 };
constexpr double tan150{ -tan30 };
constexpr double tan180{ tan0 };
constexpr double tan210{ tan30 };
constexpr double tan225{ tan45 };
constexpr double tan240{ tan60 };
constexpr double tan300{ tan120 };
constexpr double tan315{ tan135 };
constexpr double tan330{ tan150 };
constexpr double tan360{ tan0 };

constexpr double tan75{ sin75 / cos75 };
constexpr double tan105{ sin105 / cos105 };
constexpr double tan165{ sin165 / cos165 };
constexpr double tan195{ sin195 / cos195 };
constexpr double tan255{ sin255 / cos255 };
constexpr double tan285{ sin285 / cos285 };
constexpr double tan345{ sin345 / cos345 };

} // plinth
#include "Math.inl"
