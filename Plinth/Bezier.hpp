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

// Cubic Bezier calculator/solver

#ifndef PLINTH_BEZIER_HPP
#define PLINTH_BEZIER_HPP

#include "Common.hpp"
#include "Vector2.hpp"

namespace plinth
{

template <class T>
class Bezier
{
public:
	Bezier();
	Bezier(const std::vector<Vector2<T>>& points);
	void setAllPoints(Vector2<T> point = { static_cast<T>(0), static_cast<T>(0) });
	void setPoints(const std::vector<Vector2<T>>& points, unsigned int startIndex = 0u);
	void setPoint(unsigned int index, Vector2<T> point);
	Vector2<T> getPoint(unsigned int index) const;
	void setNumberOfIterationsForSolve(unsigned int numberOfIterations = 100u);
	unsigned int getNumberOfIterationsForSolver() const;

	T getX(T t) const;
	T getY(T t) const;

	// I want to develop these (solveYForX and solveXForY) to allow a starting point (and, preferably, a range) to be passed as a parameter.
	// This would basically just set minimum, maximum, and middle.
	// Just a range (no starting point) should be allowed to be passed too (would automatically start from the centre of the range).
	T solveYForX(T x) const;
	T solveXForY(T y) const;

private:
	unsigned int m_numberOfIterationsForSolve; // accuracy level (20 seems to be quite accurate. 2000 doesn't seem to be slow)
	std::vector<Vector2<T>> m_points;

	T priv_calculate(const std::vector<T>& a, T t) const;
};

} // namespace plinth
#include "Bezier.inl"
#endif // PLINTH_BEZIER_HPP
