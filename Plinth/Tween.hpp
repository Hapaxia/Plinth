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

// Tween

// interpolation functions

#pragma once

#include "Common.hpp"
#include <math.h>
#include "Bezier.hpp"
//#include "TweenTrack.hpp"

namespace plinth
{
	namespace Tween
	{

template <class PositionT = double, class T = double, class InterpolationAlphaT = double, class PositionCastT = double>
class Piecewise;

template <typename T, typename AlphaT>
// Linear Tween (interpolation) of two values using a given "alpha" value of the "blend amount"
// Type AlphaT should be a POD type in range 0 to 1.
// Type T must have required operators available (*, +)
// and be able to be multiplied (scaled) by a POD type (AlphaT)
inline constexpr T linear(const T& start, const T& end, const AlphaT& alpha);

template <typename AlphaT, typename T>
// Inverse Linear Tween (interpolation) which gives the "alpha" value from the actual value's position in the range
// Type T must have required operators available (-)
// and be able to be cast to AlphaT
// The first template parameter is used to determine the return type
inline constexpr AlphaT inverseLinear(const T& start, const T& end, const T& value);

template <typename T>
// Inverse Linear Tween (interpolation) which gives the "alpha" value from the actual value's position in the range
// Type T must have required operators available (-)
// and be able to be cast to double (the return type of alpha)
inline constexpr double inverseLinear(const T& start, const T& end, const T& value);

template <typename ToT, typename FromT>
// Converts value's position in range to its position in a different range.
// Each range may have its own type.
inline constexpr ToT convertRange(const ToT& toStart, const ToT& toEnd, const FromT& fromStart, const FromT& fromEnd, const FromT& value);

template <typename T, typename AlphaT>
// "Smoothstep" as found at http://guihaire.com/code/?p=229
inline constexpr T quickerEase(const T& start, const T& end, const AlphaT& alpha);

template <typename T, typename AlphaT>
// "Smootherstep" as found at http://guihaire.com/code/?p=229
inline constexpr T quickEase(const T& start, const T& end, const AlphaT& alpha);

template <typename T, typename AlphaT, typename AmountT>
// Eases Tween in and out by "amount". An amount of zero is a linear Tween
inline T easeInOut(const T& start, const T& end, const AlphaT& alpha, const AmountT& amount);

template <typename T, typename AlphaT, typename AmountT>
// Eases Tween in by "amount". An amount of zero is a linear Tween
inline T easeIn(const T& start, const T& end, const AlphaT& alpha, const AmountT& amount);

template <typename T, typename AlphaT, typename AmountT>
// Eases Tween out by "amount". An amount of zero is a linear Tween
inline T easeOut(const T& start, const T& end, const AlphaT& alpha, const AmountT& amount);

template <typename T, typename AlphaT, typename AmountT>
// Eases Tween in by "in" and out by "out". Zero means no easing. If in and out are both zero, it becomes a linear Tween
inline T oldEase(const T& start, const T& end, const AlphaT& alpha, const AmountT& in, const AmountT& out);

template <typename T, typename AlphaT, typename AmountT>
// Eases Tween using bezier (creates and destroys a bezier object on each call). All types must be castable to double
inline T bezierEase(const T& start, const T& end, const AlphaT& alpha, const AmountT& in, const AmountT& out);

template <typename T = double, typename AlphaT = double, typename StrengthT = double>
// Ease class - uses bezier cubic. All types must be castable to double
class Ease
{
public:
	Ease();
	void setStart(T start);
	void setEnd(T end);
	void setInStrength(StrengthT inStrength);
	void setOutStrength(StrengthT outStrength);
	void setRange(T start, T end);
	void setStrengths(StrengthT inStrength, StrengthT outStrength);
	void setRangeAndStrengths(T start, T end, StrengthT inStrength, StrengthT outStrength);
	T getStart() const;
	T getEnd() const;
	StrengthT getInStrength() const;
	StrengthT getOutStrength() const;
	T getValue(T start, T end, AlphaT alpha, StrengthT inStrength, StrengthT outStrength);
	T getValue(T start, T end, AlphaT alpha);
	T getValue(AlphaT alpha) const;

private:
	Bezier<double> m_bezier;
	T m_start;
	T m_end;
	StrengthT m_inStrength;
	StrengthT m_outStrength;

	void priv_updatePoints();
};

template <typename T = double, typename AlphaT = double, typename StrengthT = double>
// Fast Ease class - uses bezier cubic. All types must be castable to double
// pre-calculates a number of points in steps and creates a kind of look-up table and then interpolates them linearly.
// steps may be automatically determined (equally spaced) or added manually at any position or both (manually added after automatic spaced steps).
// uses TweenPiecewise for LUT and the (linear) interpolation of that table
//     template format is: FastEase < value type, alpha location type, strength type >
// default type for alpha location and strength (if not specified) is double
// default type for value if not specified is double
class FastEase
{
public:
	FastEase(StrengthT strength = static_cast<StrengthT>(0.5));
	FastEase(StrengthT inStrength, StrengthT outStrength, T start = static_cast<T>(0), T end = static_cast<T>(1), std::size_t numberOfLocations = 50_uz);
	void setStart(T start);
	void setEnd(T end);
	void setInStrength(StrengthT inStrength);
	void setOutStrength(StrengthT outStrength);
	void setRange(T start, T end);
	void setStrengths(StrengthT inStrength, StrengthT outStrength);
	void setRangeAndStrengths(T start, T end, StrengthT inStrength, StrengthT outStrength);
	T getStart() const;
	T getEnd() const;
	StrengthT getInStrength() const;
	StrengthT getOutStrength() const;
	T getAccurateValue(AlphaT alpha) const; // ignores lut and explicitly calculates
	T getValue(AlphaT alpha) const;
	void update(); // updates the look-up-table (lut)
	void addLocation(AlphaT location);
	void clearLocations();

private:
	Bezier<double> m_bezier;
	std::vector<AlphaT> m_lutLocations;
	Piecewise<AlphaT, T> m_lut;
	T m_start;
	T m_end;
	StrengthT m_inStrength;
	StrengthT m_outStrength;

	void priv_updatePoints();
	void priv_updateTable();
};

	} // namespace Tween
} // namespace plinth
#include "Tween.inl"
#include "TweenPiecewise.hpp"
