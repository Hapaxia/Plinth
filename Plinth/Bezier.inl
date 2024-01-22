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

#ifndef PLINTH_BEZIER_INL
#define PLINTH_BEZIER_INL

#include "Bezier.hpp"

namespace plinth
{

template <class T>
inline Bezier<T>::Bezier()
	: m_numberOfIterationsForSolve{ 100uz }
	, m_points(4uz, { static_cast<T>(0), static_cast<T>(0) })
{
}

template <class T>
inline Bezier<T>::Bezier(const std::vector<Vector2<T>>& points)
	: m_numberOfIterationsForSolve{ 100uz }
{
	for (auto& point : points)
		m_points.push_back(point);
	if (m_points.size() != 4_uz)
		m_points.resize(4_uz, { static_cast<T>(0), static_cast<T>(0) });
}

template <class T>
inline void Bezier<T>::setAllPoints(const Vector2<T> point)
{
	for (auto& p : m_points)
		p = point;
}

template <class T>
inline void Bezier<T>::setPoints(const std::vector<Vector2<T>>& points, const std::size_t startIndex)
{
	for (std::size_t p{ 0_uz }; (startIndex + p) < points.size(); ++p)
		m_points[startIndex + p] = points[p];
}

template <class T>
inline void Bezier<T>::setPoint(const std::size_t index, const Vector2<T> point)
{
	if (index >= m_points.size())
		return;

	m_points[index] = point;
}

template <class T>
inline Vector2<T> Bezier<T>::getPoint(const std::size_t index) const
{
	if (index >= m_points.size())
		return{ static_cast<T>(0), static_cast<T>(0) };
	
	return m_points[index];
}

template <class T>
inline void Bezier<T>::setNumberOfIterationsForSolve(const std::size_t numberOfIterations)
{
	m_numberOfIterationsForSolve = numberOfIterations;
}

template <class T>
inline std::size_t Bezier<T>::getNumberOfIterationsForSolve() const
{
	return m_numberOfIterationsForSolve;
}

template <class T>
inline T Bezier<T>::getX(const T t) const
{
	return priv_calculate({ m_points[0uz].x, m_points[1uz].x, m_points[2uz].x, m_points[3uz].x }, t);
}

template <class T>
inline T Bezier<T>::getY(const T t) const
{
	return priv_calculate({ m_points[0uz].y, m_points[1uz].y, m_points[2uz].y, m_points[3uz].y }, t);
}

template <class T>
inline T Bezier<T>::solveYForX(const T x) const
{
	// unfinished. see header.
	T minimum{ static_cast<T>(0.0) };
	T maximum{ static_cast<T>(1.0) };
	T middle{ static_cast<T>(0.5) }; // start tests from the centre
	for (std::size_t i{ 0_uz }; i < m_numberOfIterationsForSolve; ++i)
	{
		T result{ getX(middle) }; // get x for "middle" (current position along spline)
		if (result < x)
			minimum = middle;
		else if (result > x)
			maximum = middle;
		middle = (maximum + minimum) / 2;
	}
	return getY(middle); // return y for last "middle" along spline
}

template <class T>
inline T Bezier<T>::solveXForY(const T y) const
{
	// unfinished. see header.
	// untested - adapted from solveYForX
	T minimum{ static_cast<T>(0.0) };
	T maximum{ static_cast<T>(1.0) };
	T middle{ static_cast<T>(0.5) }; // start tests from the centre
	for (std::size_t i{ 0_uz }; i < m_numberOfIterationsForSolve; ++i)
	{
		T result{ getY(middle) }; // get y for "middle" (current position along spline)
		if (result < y)
			minimum = middle;
		else if (result > y)
			maximum = middle;
		middle = (maximum + minimum) / 2;
	}
	return getX(middle); // return x for last "middle" along spline
}

template <class T>
inline T Bezier<T>::priv_calculate(const std::vector<T>& a, const T t) const
{
	T t2{ static_cast<T>(1) - t };
	return a[0_uz] * t2 * t2 * t2 +
	       a[1_uz] * 3.0 * t2 * t2 * t +
	       a[2_uz] * 3.0 * t2 * t * t +
	       a[3_uz] * t * t * t;
}

} // namespace plinth
#endif // PLINTH_BEZIER_INL
