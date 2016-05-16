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

#ifndef PLINTH_TWEEN_INL
#define PLINTH_TWEEN_INL

namespace plinth
{
	namespace Tween
	{

template <typename T, typename alphaT>
// Linear Tween (interpolation) of two values using a given "alpha" value of the "blend amount"
// Type alphaT should be a POD type in range 0 to 1.
// Type T must have required operators available (*, +)
// and be able to be multiplied (scaled) by a POD type (alpha)
inline T linear(const T& start, const T& end, const alphaT& alpha)
{
	return static_cast<T>(start * (1 - alpha) + end * alpha); // blend from low to high using alpha
}

template <typename alphaT, typename T>
// Inverse Linear Tween (interpolation) which gives the "alpha" value from the actual value's position in the range
// Type T must have required operators available (-)
// and be able to be cast to alphaT
// The first template parameter is used to determine the return type
inline alphaT inverseLinear(const T& start, const T& end, const T& value)
{
	return static_cast<alphaT>(value - start) / (end - start);
}

template <typename T>
// Inverse Linear Tween (interpolation) which gives the "alpha" value from the actual value's position in the range
// Type T must have required operators available (-)
// and be able to be cast to double (the return type of alpha)
inline double inverseLinear(const T& start, const T& end, const T& value)
{
	return static_cast<double>(value - start) / (end - start);
}

template <typename toT, typename fromT>
// Converts value's position in range to its position in a different range.
// Each range may have its own type.
toT convertRange(const toT& toStart, const toT& toEnd, const fromT& fromStart, const fromT& fromEnd, const fromT& value)
{
	return linear(toStart, toEnd, inverseLinear(fromStart, fromEnd, value));
}

template <typename T, typename alphaT, typename amountT>
// Eases Tween in and out by "amount". An amount of zero is a linear Tween
T easeInOut(const T& start, const T& end, const alphaT& alpha, const amountT& amount)
{
	double strength{ static_cast<double>(amount)+1 }; // use range from 1 (straight line) in calculations instead of supplied 0
	double pow1{ pow(alpha, strength) };
	double pow2{ pow(1 - alpha, strength) };
	double eased{ pow1 / (pow1 + pow2) };
	return linear(start, end, eased);
}

template <typename T, typename alphaT, typename amountT>
// Eases Tween in by "amount". An amount of zero is a linear Tween
T easeIn(const T& start, const T& end, const alphaT& alpha, const amountT& amount)
{
	return easeInOut(start, end + (end - start), alpha / 2, amount);
}

template <typename T, typename alphaT, typename amountT>
// Eases Tween out by "amount". An amount of zero is a linear Tween
T easeOut(const T& start, const T& end, const alphaT& alpha, const amountT& amount)
{
	return easeInOut(start - (end - start), end, 0.5 + alpha / 2, amount);
}

template <typename T, typename alphaT, typename amountT>
// Eases Tween in by "in" and out by "out". Zero means no easing. If in and out are both zero, it becomes a linear Tween
T oldEase(const T& start, const T& end, const alphaT& alpha, const amountT& in, const amountT& out)
{
	T easedIn{ easeIn(start, end, alpha, in) };
	T easedOut{ easeOut(start, end, alpha, out) };
	return linear(easedIn, easedOut, alpha);
}

template <typename T, typename alphaT>
// "Smoothstep" as found at http://guihaire.com/code/?p=229
T quickerEase(const T& start, const T& end, const alphaT& alpha)
{
	return linear(start, end, alpha * alpha * (3 - 2 * alpha));
}

template <typename T, typename alphaT>
// "Smootherstep" as found at http://guihaire.com/code/?p=229
T quickEase(const T& start, const T& end, const alphaT& alpha)
{
	return linear(start, end, alpha * alpha * alpha * (10 + alpha * (6 * alpha - 15)));
}

template <typename T, typename alphaT, typename amountT>
// Eases Tween using bezier (creates and destroys a bezier object on each call). All types must be castable to double
T slowEase(const T start, const T end, const alphaT alpha, const amountT in, const amountT out)
{
	Bezier<double> bezier;
	bezier.setPoint(0, { 0.0, static_cast<double>(start) });
	bezier.setPoint(1, { static_cast<double>(in), static_cast<double>(start) });
	bezier.setPoint(2, { 1.0 - static_cast<double>(out), static_cast<double>(end) });
	bezier.setPoint(3, { 1.0, static_cast<double>(end) });
	return static_cast<T>(bezier.solveYForX(static_cast<double>(alpha)));
}












template <typename T, typename alphaT, typename strengthT>
// Ease class - uses bezier cubic. All types must be castable to double
Ease<T, alphaT, strengthT>::Ease()
	: m_start(static_cast<T>(0.0))
	, m_end(static_cast<T>(1.0))
	, m_inStrength(static_cast<strengthT>(0.5))
	, m_outStrength(static_cast<strengthT>(0.5))
	, m_bezier()
{
	priv_updatePoints();
}

template <typename T, typename alphaT, typename strengthT>
void Ease<T, alphaT, strengthT>::setStart(const T start)
{
	m_start = start;
	priv_updatePoints();
}

template <typename T, typename alphaT, typename strengthT>
void Ease<T, alphaT, strengthT>::setEnd(const T end)
{
	m_end = end;
	priv_updatePoints();
}

template <typename T, typename alphaT, typename strengthT>
void Ease<T, alphaT, strengthT>::setInStrength(const strengthT inStrength)
{
	m_inStrength = inStrength;
	priv_updatePoints();
}

template <typename T, typename alphaT, typename strengthT>
void Ease<T, alphaT, strengthT>::setOutStrength(const strengthT outStrength)
{
	m_outStrength = outStrength;
	priv_updatePoints();
}

template <typename T, typename alphaT, typename strengthT>
void Ease<T, alphaT, strengthT>::setRange(const T start, const T end)
{
	m_start = start;
	m_end = end;
	priv_updatePoints();
}

template <typename T, typename alphaT, typename strengthT>
void Ease<T, alphaT, strengthT>::setStrengths(const strengthT inStrength, const strengthT outStrength)
{
	m_inStrength = inStrength;
	m_outStrength = outStrength;
	priv_updatePoints();
}

template <typename T, typename alphaT, typename strengthT>
void Ease<T, alphaT, strengthT>::setRangeAndStrengths(const T start, const T end, const strengthT inStrength, const strengthT outStrength)
{
	m_start = start;
	m_end = end;
	m_inStrength = inStrength;
	m_outStrength = outStrength;
	priv_updatePoints();
}

template <typename T, typename alphaT, typename strengthT>
T Ease<T, alphaT, strengthT>::getValue(const T start, const T end, const alphaT alpha, const strengthT inStrength, const strengthT outStrength)
{
	setRangeAndStrengths(start, end, inStrength, outStrength);
	return getValue(alpha);
}

template <typename T, typename alphaT, typename strengthT>
T Ease<T, alphaT, strengthT>::getValue(const T start, const T end, const alphaT alpha)
{
	setRange(start, end);
	return getValue(alpha);
}

template <typename T, typename alphaT, typename strengthT>
T Ease<T, alphaT, strengthT>::getValue(const alphaT alpha) const
{
	return static_cast<T>(m_bezier.solveYForX(static_cast<double>(alpha)));
}

template <typename T, typename alphaT, typename strengthT>
void Ease<T, alphaT, strengthT>::priv_updatePoints()
{
	m_bezier.setPoint(0, { 0.0, static_cast<double>(m_start) });
	m_bezier.setPoint(1, { static_cast<double>(m_inStrength), static_cast<double>(m_start) });
	m_bezier.setPoint(2, { 1.0 - static_cast<double>(m_outStrength), static_cast<double>(m_end) });
	m_bezier.setPoint(3, { 1.0, static_cast<double>(m_end) });
}




















template <typename T, typename alphaT, typename strengthT>
// Fast Ease class - uses bezier cubic. All types must be castable to double
// pre-calculates a number of points in steps and creates a kind of look-up table and then interpolates them linearly.
// steps may be automatically determined (equally spaced) or added manually at any position or both (manually added after automatic spaced steps).
// uses TweenPiecewise for LUT and the (linear) interpolation of that table
//     template format is: FastEase < value type, alpha location type, strength type >
// default type for alpha location and strength (if not specified) is double
FastEase<T, alphaT, strengthT>::FastEase(const strengthT inStrength, const strengthT outStrength, const T start, const T end, const unsigned int numberOfLocations)
	: m_start(start)
	, m_end(end)
	, m_inStrength(inStrength)
	, m_outStrength(outStrength)
	, m_bezier()
	, m_lutLocations()
	, m_lut()
{
	if (numberOfLocations > 0u)
	{
		for (unsigned int i{ 0u }; i < numberOfLocations; ++i)
			addLocation(linear(start, end, inverseLinear(0u, numberOfLocations - 1u, i)));
	}
	priv_updatePoints();
	priv_updateTable();
}

template <typename T, typename alphaT, typename strengthT>
// Fast Ease class - uses bezier cubic. All types must be castable to double
// pre-calculates a number of points in steps and creates a kind of look-up table and then interpolates them linearly.
// steps may be automatically determined (equally spaced) or added manually at any position or both (manually added after automatic spaced steps).
// uses TweenPiecewise for LUT and the (linear) interpolation of that table
//     template format is: FastEase < value type, alpha location type, strength type >
// default type for alpha location and strength (if not specified) is double
FastEase<T, alphaT, strengthT>::FastEase(const strengthT strength) :
m_start(0),
m_end(1),
m_inStrength(strength),
m_outStrength(strength),
m_bezier(),
m_lutLocations(),
m_lut()
{
	const unsigned int numberOfLocations{ 50u };
	if (numberOfLocations > 0u)
	{
		for (unsigned int i{ 0u }; i < numberOfLocations; ++i)
			addLocation(linear(m_start, m_end, inverseLinear(0u, numberOfLocations - 1u, i)));
	}
	priv_updatePoints();
	priv_updateTable();
}

template <typename T, typename alphaT, typename strengthT>
void FastEase<T, alphaT, strengthT>::setStart(const T start)
{
	m_start = start;
	//updatePoints();
}

template <typename T, typename alphaT, typename strengthT>
void FastEase<T, alphaT, strengthT>::setEnd(const T end)
{
	m_end = end;
	//updatePoints();
}

template <typename T, typename alphaT, typename strengthT>
void FastEase<T, alphaT, strengthT>::setInStrength(const strengthT inStrength)
{
	m_inStrength = inStrength;
	//updatePoints();
}

template <typename T, typename alphaT, typename strengthT>
void FastEase<T, alphaT, strengthT>::setOutStrength(const strengthT outStrength)
{
	m_outStrength = outStrength;
	//updatePoints();
}

template <typename T, typename alphaT, typename strengthT>
void FastEase<T, alphaT, strengthT>::setRange(const T start, const T end)
{
	m_start = start;
	m_end = end;
	//updatePoints();
}

template <typename T, typename alphaT, typename strengthT>
void FastEase<T, alphaT, strengthT>::setStrengths(const strengthT inStrength, const strengthT outStrength)
{
	m_inStrength = inStrength;
	m_outStrength = outStrength;
	//updatePoints();
}

template <typename T, typename alphaT, typename strengthT>
void FastEase<T, alphaT, strengthT>::setRangeAndStrengths(const T start, const T end, const strengthT inStrength, const strengthT outStrength)
{
	m_start = start;
	m_end = end;
	m_inStrength = inStrength;
	m_outStrength = outStrength;
	//updatePoints();
}

/*
template <typename T, typename alphaT, typename strengthT>
T FastEase<T, alphaT, strengthT>::getValue(const T start, const T end, const alphaT alpha, const strengthT inStrength, const strengthT outStrength)
{
	setRangeAndStrengths(start, end, inStrength, outStrength);
	return getValue(alpha);
}

template <typename T, typename alphaT, typename strengthT>
T FastEase<T, alphaT, strengthT>::getValue(const T start, const T end, const alphaT alpha)
{
	setRange(start, end);
	return getValue(alpha);
}
*/

template <typename T, typename alphaT, typename strengthT>
T FastEase<T, alphaT, strengthT>::getAccurateValue(const alphaT alpha) const
{
	return static_cast<T>(m_bezier.solveYForX(static_cast<double>(alpha)));
}

template <typename T, typename alphaT, typename strengthT>
T FastEase<T, alphaT, strengthT>::getValue(const alphaT alpha) const
{
	return m_lut.getValue(alpha);
}

template <typename T, typename alphaT, typename strengthT>
void FastEase<T, alphaT, strengthT>::update()
{
	priv_updatePoints();
	priv_updateTable();
}

template <typename T, typename alphaT, typename strengthT>
void FastEase<T, alphaT, strengthT>::addLocation(const alphaT location)
{
	m_lutLocations.push_back(location);
}

template <typename T, typename alphaT, typename strengthT>
void FastEase<T, alphaT, strengthT>::clearLocations()
{
	m_lutLocations.clear();
}

template <typename T, typename alphaT, typename strengthT>
void FastEase<T, alphaT, strengthT>::priv_updatePoints()
{
	m_bezier.setPoint(0, { 0.0, static_cast<double>(m_start) });
	m_bezier.setPoint(1, { static_cast<double>(m_inStrength), static_cast<double>(m_start) });
	m_bezier.setPoint(2, { 1.0 - static_cast<double>(m_outStrength), static_cast<double>(m_end) });
	m_bezier.setPoint(3, { 1.0, static_cast<double>(m_end) });
}

template <typename T, typename alphaT, typename strengthT>
void FastEase<T, alphaT, strengthT>::priv_updateTable()
{
	m_lut.clearNodes();
	for (auto& location : m_lutLocations)
		m_lut.addNode({ location, getAccurateValue(location) });
	if (m_lut.getNodeCount() == 0)
		m_lut.addNode({ 0, 0 });
}

	} // namespace Tween
} // namespace plinth
#endif // PLINTH_TWEEN_INL
