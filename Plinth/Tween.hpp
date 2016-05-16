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

// Tween

// interpolation functions

#ifndef PLINTH_TWEEN_HPP
#define PLINTH_TWEEN_HPP

#include "Common.hpp"
#include <math.h>
#include "Bezier.hpp"
#include "TweenPiecewise.hpp"
#include "TweenTrack.hpp"

namespace plinth
{
	namespace Tween
	{

template <typename T, typename alphaT>
// Linear Tween (interpolation) of two values using a given "alpha" value of the "blend amount"
// Type alphaT should be a POD type in range 0 to 1.
// Type T must have required operators available (*, +)
// and be able to be multiplied (scaled) by a POD type (alphaT)
inline T linear(const T& start, const T& end, const alphaT& alpha);

template <typename alphaT, typename T>
// Inverse Linear Tween (interpolation) which gives the "alpha" value from the actual value's position in the range
// Type T must have required operators available (-)
// and be able to be cast to alphaT
// The first template parameter is used to determine the return type
inline alphaT inverseLinear(const T& start, const T& end, const T& value);

template <typename T>
// Inverse Linear Tween (interpolation) which gives the "alpha" value from the actual value's position in the range
// Type T must have required operators available (-)
// and be able to be cast to double (the return type of alpha)
inline double inverseLinear(const T& start, const T& end, const T& value);

template <typename toT, typename fromT>
// Converts value's position in range to its position in a different range.
// Each range may have its own type.
toT convertRange(const toT& toStart, const toT& toEnd, const fromT& fromStart, const fromT& fromEnd, const fromT& value);

template <typename T, typename alphaT, typename amountT>
// Eases Tween in and out by "amount". An amount of zero is a linear Tween
T easeInOut(const T& start, const T& end, const alphaT& alpha, const amountT& amount);

template <typename T, typename alphaT, typename amountT>
// Eases Tween in by "amount". An amount of zero is a linear Tween
T easeIn(const T& start, const T& end, const alphaT& alpha, const amountT& amount);

template <typename T, typename alphaT, typename amountT>
// Eases Tween out by "amount". An amount of zero is a linear Tween
T easeOut(const T& start, const T& end, const alphaT& alpha, const amountT& amount);

template <typename T, typename alphaT, typename amountT>
// Eases Tween in by "in" and out by "out". Zero means no easing. If in and out are both zero, it becomes a linear Tween
T oldEase(const T& start, const T& end, const alphaT& alpha, const amountT& in, const amountT& out);

template <typename T, typename alphaT>
// "Smoothstep" as found at http://guihaire.com/code/?p=229
T quickerEase(const T& start, const T& end, const alphaT& alpha);

template <typename T, typename alphaT>
// "Smootherstep" as found at http://guihaire.com/code/?p=229
T quickEase(const T& start, const T& end, const alphaT& alpha);

template <typename T, typename alphaT, typename amountT>
// Eases Tween using bezier (creates and destroys a bezier object on each call). All types must be castable to double
T slowEase(const T& start, const T& end, const alphaT& alpha, const amountT& in, const amountT& out);

template <typename T, typename alphaT = double, typename strengthT = double>
// Ease class - uses bezier cubic. All types must be castable to double
class Ease
{
public:
	Ease();
	void setStart(T start);
	void setEnd(T end);
	void setInStrength(strengthT inStrength);
	void setOutStrength(strengthT outStrength);
	void setRange(T start, T end);
	void setStrengths(strengthT inStrength, strengthT outStrength);
	void setRangeAndStrengths(T start, T end, strengthT inStrength, strengthT outStrength);
	T getStart() const;
	T getEnd() const;
	strengthT getInStrength() const;
	strengthT getOutStrength() const;
	T getValue(T start, T end, alphaT alpha, strengthT inStrength, strengthT outStrength);
	T getValue(T start, T end, alphaT alpha);
	T getValue(alphaT alpha) const;

private:
	Bezier<double> m_bezier;
	T m_start, m_end;
	strengthT m_inStrength, m_outStrength;

	void priv_updatePoints();
};

template <typename T, typename alphaT = double, typename strengthT = double>
// Fast Ease class - uses bezier cubic. All types must be castable to double
// pre-calculates a number of points in steps and creates a kind of look-up table and then interpolates them linearly.
// steps may be automatically determined (equally spaced) or added manually at any position or both (manually added after automatic spaced steps).
// uses TweenPiecewise for LUT and the (linear) interpolation of that table
//     template format is: FastEase < value type, alpha location type, strength type >
// default type for alpha location and strength (if not specified) is double
class FastEase
{
public:
	void DEV_OutputPiecewise() { m_lut.DEV_outputNodes(); }

	FastEase(strengthT strength = 0.5);
	FastEase(strengthT inStrength, strengthT outStrength, T start = 0, T end = 1, unsigned int numberOfLocations = 50u);
	void setStart(T start);
	void setEnd(T end);
	void setInStrength(strengthT inStrength);
	void setOutStrength(strengthT outStrength);
	void setRange(T start, T end);
	void setStrengths(strengthT inStrength, strengthT outStrength);
	void setRangeAndStrengths(T start, T end, strengthT inStrength, strengthT outStrength);
	T getStart() const;
	T getEnd() const;
	strengthT getInStrength() const;
	strengthT getOutStrength() const;
	//T getValue(T start, T end, alphaT alpha, strengthT inStrength, strengthT outStrength);
	//T getValue(T start, T end, alphaT alpha);
	T getAccurateValue(alphaT alpha) const; // ignores lut and explicitly calculates
	T getValue(alphaT alpha) const;
	void update(); // updates the look-up-table (lut)
	void addLocation(alphaT location);
	void clearLocations();

private:
	Bezier<double> m_bezier;
	std::vector<alphaT> m_lutLocations;
	Piecewise<alphaT, T> m_lut;
	//std::vector<T> m_lut;
	T m_start, m_end;
	strengthT m_inStrength, m_outStrength;

	void priv_updatePoints();
	void priv_updateTable();
};

	} // namespace Tween
} // namespace plinth

#include "Tween.inl"

#endif // PLINTH_TWEEN_HPP
