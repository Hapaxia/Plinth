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

#ifndef PLINTH_BEZIER_INL
#define PLINTH_BEZIER_INL

namespace plinth
{

template <class T>
Bezier<T>::Bezier()
	: m_numberOfIterationsForSolve(100u)
	, m_points(4, { 0.0, 0.0 })
{
}

template <class T>
Bezier<T>::Bezier(const std::vector<Vector2<T>>& points)
	: m_numberOfIterationsForSolve(100u)
{
	for (auto& point : points)
		m_points.push_back(point);
	if (m_points.size() != 4)
		m_points.resize(4, { 0.0, 0.0 });
}

template <class T>
void Bezier<T>::setAllPoints(const Vector2<T> point)
{
	for (auto& p : m_points)
		p = point;
}

template <class T>
void Bezier<T>::setPoints(const std::vector<Vector2<T>>& points, const unsigned int startIndex)
{
	for (unsigned int p = 0; p < points.size(); ++p)
	{
		if ((startIndex + p) < m_points.size())
			m_points[startIndex + p] = points[p];
	}
}

template <class T>
void Bezier<T>::setPoint(const unsigned int index, const Vector2<T> point)
{
	if (index > m_points.size())
		return;

	m_points[index] = point;
}

template <class T>
Vector2<T> Bezier<T>::getPoint(const unsigned int index) const
{
	if (index > m_points.size())
		return{ 0.0, 0.0 };
	
	return m_points[index];
}

template <class T>
void Bezier<T>::setNumberOfIterationsForSolve(const unsigned int numberOfIterations)
{
	m_numberOfIterationsForSolve = numberOfIterations;
}

template <class T>
unsigned int Bezier<T>::getNumberOfIterationsForSolver() const
{
	return m_numberOfIterationsForSolve;
}

template <class T>
T Bezier<T>::getX(const T t) const
{
	return priv_calculate({ m_points[0].x, m_points[1].x, m_points[2].x, m_points[3].x }, t);
}

template <class T>
T Bezier<T>::getY(const T t) const
{
	return priv_calculate({ m_points[0].y, m_points[1].y, m_points[2].y, m_points[3].y }, t);
}

template <class T>
T Bezier<T>::solveYForX(const T x) const
{
	// unfinished. see header.
	T minimum{ static_cast<T>(0.0) };
	T maximum{ static_cast<T>(1.0) };
	T middle{ static_cast<T>(0.5) }; // start tests from the centre
	for (unsigned int i{ 0 }; i < m_numberOfIterationsForSolve; ++i)
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
T Bezier<T>::solveXForY(const T y) const
{
	// unfinished. see header.
	// untested - adapted from solveYForX
	T minimum{ static_cast<T>(0.0) };
	T maximum{ static_cast<T>(1.0) };
	T middle{ static_cast<T>(0.5) }; // start tests from the centre
	for (unsigned int i{ 0 }; i < m_numberOfIterationsForSolve; ++i)
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
T Bezier<T>::priv_calculate(const std::vector<T>& a, const T t) const
{
	T t2{ 1 - t };
	return a[0] * t2 * t2 * t2 +
	       a[1] * 3 * t2 * t2 * t +
	       a[2] * 3 * t2 * t * t +
	       a[3] * t * t * t;
}

} // namespace plinth
#endif // PLINTH_BEZIER_INL
