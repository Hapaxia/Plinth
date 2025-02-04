//////////////////////////////////////////////////////////////////////////////
//
// Plinth
//
// Copyright(c) 2014-2025 M.J.Silk
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

#include "Tween.hpp"

namespace plinth
{
	namespace Tween
	{

template <typename T, typename AlphaT>
// Linear Tween (interpolation) of two values using a given "alpha" value of the "blend amount"
// Type AlphaT should be a POD type in range 0 to 1.
// Type T must have required operators available (*, +)
// and be able to be multiplied (scaled) by a POD type (alpha)
inline constexpr T linear(const T& start, const T& end, const AlphaT& alpha)
{
	return static_cast<T>((start * (static_cast<AlphaT>(1) - alpha)) + (end * alpha)); // blend from low to high using alpha
}

template <typename AlphaT, typename T>
// Inverse Linear Tween (interpolation) which gives the "alpha" value from the actual value's position in the range
// Type T must have required operators available (-)
// and be able to be cast to AlphaT
// The first template parameter is used to determine the return type
inline constexpr AlphaT inverseLinear(const T& start, const T& end, const T& value)
{
	return static_cast<AlphaT>(value - start) / (end - start);
}

template <typename T>
// Inverse Linear Tween (interpolation) which gives the "alpha" value from the actual value's position in the range
// Type T must have required operators available (-)
// and be able to be cast to double (the return type of alpha)
inline constexpr double inverseLinear(const T& start, const T& end, const T& value)
{
	return static_cast<double>(value - start) / (end - start);
}

template <typename ToT, typename FromT>
// Converts value's position in range to its position in a different range.
// Each range may have its own type.
inline constexpr ToT convertRange(const ToT& toStart, const ToT& toEnd, const FromT& fromStart, const FromT& fromEnd, const FromT& value)
{
	return linear(toStart, toEnd, inverseLinear(fromStart, fromEnd, value));
}

template <typename T, typename AlphaT>
// "Smoothstep" as found at http://guihaire.com/code/?p=229
inline constexpr T quickerEase(const T& start, const T& end, const AlphaT& alpha)
{
	const double a{ static_cast<double>(alpha) };
	return linear(start, end, a * a * (3.0 - (2.0 * a)));
}

template <typename T, typename AlphaT>
// "Smootherstep" as found at http://guihaire.com/code/?p=229
inline constexpr T quickEase(const T& start, const T& end, const AlphaT& alpha)
{
	const double a{ static_cast<double>(alpha) };
	return linear(start, end, a * a * a * (10.0 + (a * ((6.0 * a) - 15.0))));
}

template <typename T, typename AlphaT, typename AmountT>
// Eases Tween in and out by "amount". An amount of zero is a linear Tween
inline T easeInOut(const T& start, const T& end, const AlphaT& alpha, const AmountT& amount)
{
	const double a{ static_cast<double>(alpha) };
	const double strength{ static_cast<double>(amount) + 1.0 }; // use range from 1 (straight line) in calculations instead of supplied 0
	const double pow1{ std::pow(a, strength) };
	const double pow2{ std::pow(1.0 - a, strength) };
	const double eased{ pow1 / (pow1 + pow2) };
	return linear(start, end, eased);
}

template <typename T, typename AlphaT, typename AmountT>
// Eases Tween in by "amount". An amount of zero is a linear Tween
inline T easeIn(const T& start, const T& end, const AlphaT& alpha, const AmountT& amount)
{
	return easeInOut(start, end + (end - start), static_cast<double>(alpha) / 2.0, amount);
}

template <typename T, typename AlphaT, typename AmountT>
// Eases Tween out by "amount". An amount of zero is a linear Tween
inline T easeOut(const T& start, const T& end, const AlphaT& alpha, const AmountT& amount)
{
	return easeInOut(start - (end - start), end, (static_cast<double>(alpha) / 2.0) + 0.5, amount);
}

template <typename T, typename AlphaT, typename AmountT>
// Eases Tween in by "in" and out by "out". Zero means no easing. If in and out are both zero, it becomes a linear Tween
inline T oldEase(const T& start, const T& end, const AlphaT& alpha, const AmountT& in, const AmountT& out)
{
	const T easedIn{ easeIn(start, end, alpha, in) };
	const T easedOut{ easeOut(start, end, alpha, out) };
	return linear(easedIn, easedOut, alpha);
}

template <typename T, typename AlphaT, typename AmountT>
// Eases Tween using bezier (creates and destroys a bezier object on each call). All types must be castable to double
inline T bezierEase(const T& start, const T& end, const AlphaT& alpha, const AmountT& in, const AmountT& out)
{
	const double s{ static_cast<double>(start) };
	const double e{ static_cast<double>(end) };
	Bezier<double> bezier;
	bezier.setPoint(0uz, { 0.0, s });
	bezier.setPoint(1uz, { static_cast<double>(in), s });
	bezier.setPoint(2uz, { 1.0 - static_cast<double>(out), e });
	bezier.setPoint(3uz, { 1.0, e });
	return static_cast<T>(bezier.solveYForX(static_cast<double>(alpha)));
}












template <typename T, typename AlphaT, typename StrengthT>
// Ease class - uses bezier cubic. All types must be castable to double
inline Ease<T, AlphaT, StrengthT>::Ease()
	: m_start{ static_cast<T>(0) }
	, m_end{ static_cast<T>(1) }
	, m_inStrength{ static_cast<StrengthT>(0.5) }
	, m_outStrength{ static_cast<StrengthT>(0.5) }
	, m_bezier{}
{
	priv_updatePoints();
}

template <typename T, typename AlphaT, typename StrengthT>
inline void Ease<T, AlphaT, StrengthT>::setStart(const T start)
{
	m_start = start;
	priv_updatePoints();
}

template <typename T, typename AlphaT, typename StrengthT>
inline void Ease<T, AlphaT, StrengthT>::setEnd(const T end)
{
	m_end = end;
	priv_updatePoints();
}

template <typename T, typename AlphaT, typename StrengthT>
inline void Ease<T, AlphaT, StrengthT>::setInStrength(const StrengthT inStrength)
{
	m_inStrength = inStrength;
	priv_updatePoints();
}

template <typename T, typename AlphaT, typename StrengthT>
inline void Ease<T, AlphaT, StrengthT>::setOutStrength(const StrengthT outStrength)
{
	m_outStrength = outStrength;
	priv_updatePoints();
}

template <typename T, typename AlphaT, typename StrengthT>
inline void Ease<T, AlphaT, StrengthT>::setRange(const T start, const T end)
{
	m_start = start;
	m_end = end;
	priv_updatePoints();
}

template <typename T, typename AlphaT, typename StrengthT>
inline void Ease<T, AlphaT, StrengthT>::setStrengths(const StrengthT inStrength, const StrengthT outStrength)
{
	m_inStrength = inStrength;
	m_outStrength = outStrength;
	priv_updatePoints();
}

template <typename T, typename AlphaT, typename StrengthT>
inline void Ease<T, AlphaT, StrengthT>::setRangeAndStrengths(const T start, const T end, const StrengthT inStrength, const StrengthT outStrength)
{
	m_start = start;
	m_end = end;
	m_inStrength = inStrength;
	m_outStrength = outStrength;
	priv_updatePoints();
}

template <typename T, typename AlphaT, typename StrengthT>
inline T Ease<T, AlphaT, StrengthT>::getStart() const
{
	return m_start;
}

template <typename T, typename AlphaT, typename StrengthT>
inline T Ease<T, AlphaT, StrengthT>::getEnd() const
{
	return m_end;
}

template <typename T, typename AlphaT, typename StrengthT>
inline StrengthT Ease<T, AlphaT, StrengthT>::getInStrength() const
{
	return m_inStrength;
}

template <typename T, typename AlphaT, typename StrengthT>
inline StrengthT Ease<T, AlphaT, StrengthT>::getOutStrength() const
{
	return m_outStrength;
}

template <typename T, typename AlphaT, typename StrengthT>
inline T Ease<T, AlphaT, StrengthT>::getValue(const T start, const T end, const AlphaT alpha, const StrengthT inStrength, const StrengthT outStrength)
{
	setRangeAndStrengths(start, end, inStrength, outStrength);
	return getValue(alpha);
}

template <typename T, typename AlphaT, typename StrengthT>
inline T Ease<T, AlphaT, StrengthT>::getValue(const T start, const T end, const AlphaT alpha)
{
	setRange(start, end);
	return getValue(alpha);
}

template <typename T, typename AlphaT, typename StrengthT>
inline T Ease<T, AlphaT, StrengthT>::getValue(const AlphaT alpha) const
{
	return static_cast<T>(m_bezier.solveYForX(static_cast<double>(alpha)));
}

template <typename T, typename AlphaT, typename StrengthT>
inline void Ease<T, AlphaT, StrengthT>::priv_updatePoints()
{
	const double start{ static_cast<double>(m_start) };
	const double end{ static_cast<double>(m_end) };
	m_bezier.setPoint(0_uz, { 0.0, start });
	m_bezier.setPoint(1_uz, { static_cast<double>(m_inStrength), start });
	m_bezier.setPoint(2_uz, { 1.0 - static_cast<double>(m_outStrength), end });
	m_bezier.setPoint(3_uz, { 1.0, end });
}




















template <typename T, typename AlphaT, typename StrengthT>
// Fast Ease class - uses bezier cubic. All types must be castable to double
// pre-calculates a number of points in steps and creates a kind of look-up table and then interpolates them linearly.
// steps may be automatically determined (equally spaced) or added manually at any position or both (manually added after automatic spaced steps).
// uses TweenPiecewise for LUT and the (linear) interpolation of that table
//     template format is: FastEase < value type, alpha location type, strength type >
// default type for alpha location and strength (if not specified) is double
// default type for value if not specified is double
inline FastEase<T, AlphaT, StrengthT>::FastEase(const StrengthT inStrength, const StrengthT outStrength, const T start, const T end, const std::size_t numberOfLocations)
	: m_start{ start }
	, m_end{ end }
	, m_inStrength{ inStrength }
	, m_outStrength{ outStrength }
	, m_bezier{}
	, m_lutLocations{}
	, m_lut{}
{
	if (numberOfLocations > 0_uz)
	{
		for (std::size_t i{ 0_uz }; i < numberOfLocations; ++i)
			addLocation(linear(start, end, inverseLinear(0_uz, numberOfLocations - 1_uz, i)));
	}
	priv_updatePoints();
	priv_updateTable();
}

template <typename T, typename AlphaT, typename StrengthT>
// Fast Ease class - uses bezier cubic. All types must be castable to double
// pre-calculates a number of points in steps and creates a kind of look-up table and then interpolates them linearly.
// steps may be automatically determined (equally spaced) or added manually at any position or both (manually added after automatic spaced steps).
// uses TweenPiecewise for LUT and the (linear) interpolation of that table
//     template format is: FastEase < value type, alpha location type, strength type >
// default type for alpha location and strength (if not specified) is double
// default type for value if not specified is double
inline FastEase<T, AlphaT, StrengthT>::FastEase(const StrengthT strength)
	: m_start{ static_cast<T>(0) }
	, m_end{ static_cast<T>(1) }
	, m_inStrength{ strength }
	, m_outStrength{ strength }
	, m_bezier{}
	, m_lutLocations{}
	, m_lut{}
{
	constexpr std::size_t numberOfLocations{ 50uz };
	if (numberOfLocations > 0_uz)
	{
		for (std::size_t i{ 0_uz }; i < numberOfLocations; ++i)
			addLocation(linear(m_start, m_end, inverseLinear(0_uz, numberOfLocations - 1_uz, i)));
	}
	priv_updatePoints();
	priv_updateTable();
}

template <typename T, typename AlphaT, typename StrengthT>
inline void FastEase<T, AlphaT, StrengthT>::setStart(const T start)
{
	m_start = start;
}

template <typename T, typename AlphaT, typename StrengthT>
inline void FastEase<T, AlphaT, StrengthT>::setEnd(const T end)
{
	m_end = end;
}

template <typename T, typename AlphaT, typename StrengthT>
inline void FastEase<T, AlphaT, StrengthT>::setInStrength(const StrengthT inStrength)
{
	m_inStrength = inStrength;
}

template <typename T, typename AlphaT, typename StrengthT>
inline void FastEase<T, AlphaT, StrengthT>::setOutStrength(const StrengthT outStrength)
{
	m_outStrength = outStrength;
}

template <typename T, typename AlphaT, typename StrengthT>
inline void FastEase<T, AlphaT, StrengthT>::setRange(const T start, const T end)
{
	m_start = start;
	m_end = end;
}

template <typename T, typename AlphaT, typename StrengthT>
inline void FastEase<T, AlphaT, StrengthT>::setStrengths(const StrengthT inStrength, const StrengthT outStrength)
{
	m_inStrength = inStrength;
	m_outStrength = outStrength;
}

template <typename T, typename AlphaT, typename StrengthT>
inline void FastEase<T, AlphaT, StrengthT>::setRangeAndStrengths(const T start, const T end, const StrengthT inStrength, const StrengthT outStrength)
{
	m_start = start;
	m_end = end;
	m_inStrength = inStrength;
	m_outStrength = outStrength;
}

template <typename T, typename AlphaT, typename StrengthT>
inline T FastEase<T, AlphaT, StrengthT>::getStart() const
{
	return m_start;
}

template <typename T, typename AlphaT, typename StrengthT>
inline T FastEase<T, AlphaT, StrengthT>::getEnd() const
{
	return m_end;
}

template <typename T, typename AlphaT, typename StrengthT>
inline StrengthT FastEase<T, AlphaT, StrengthT>::getInStrength() const
{
	return m_inStrength;
}

template <typename T, typename AlphaT, typename StrengthT>
inline StrengthT FastEase<T, AlphaT, StrengthT>::getOutStrength() const
{
	return m_outStrength;
}

template <typename T, typename AlphaT, typename StrengthT>
inline T FastEase<T, AlphaT, StrengthT>::getAccurateValue(const AlphaT alpha) const
{
	return static_cast<T>(m_bezier.solveYForX(static_cast<double>(alpha)));
}

template <typename T, typename AlphaT, typename StrengthT>
inline T FastEase<T, AlphaT, StrengthT>::getValue(const AlphaT alpha) const
{
	return m_lut.getValue(alpha);
}

template <typename T, typename AlphaT, typename StrengthT>
inline void FastEase<T, AlphaT, StrengthT>::update()
{
	priv_updatePoints();
	priv_updateTable();
}

template <typename T, typename AlphaT, typename StrengthT>
inline void FastEase<T, AlphaT, StrengthT>::addLocation(const AlphaT location)
{
	m_lutLocations.push_back(location);
}

template <typename T, typename AlphaT, typename StrengthT>
inline void FastEase<T, AlphaT, StrengthT>::clearLocations()
{
	m_lutLocations.clear();
}

template <typename T, typename AlphaT, typename StrengthT>
inline void FastEase<T, AlphaT, StrengthT>::priv_updatePoints()
{
	const double start{ static_cast<double>(m_start) };
	const double end{ static_cast<double>(m_end) };
	m_bezier.setPoint(0_uz, { 0.0, start });
	m_bezier.setPoint(1_uz, { static_cast<double>(m_inStrength), start });
	m_bezier.setPoint(2_uz, { 1.0 - static_cast<double>(m_outStrength), end });
	m_bezier.setPoint(3_uz, { 1.0, end });
}

template <typename T, typename AlphaT, typename StrengthT>
inline void FastEase<T, AlphaT, StrengthT>::priv_updateTable()
{
	m_lut.clearNodes();
	for (auto& location : m_lutLocations)
		m_lut.addNode({ location, getAccurateValue(location) });
	if (m_lut.getNodeCount() == 0uz)
		m_lut.addNode({ static_cast<AlphaT>(0), static_cast<T>(0) });
}

	} // namespace Tween
} // namespace plinth
