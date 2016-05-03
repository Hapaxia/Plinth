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

#ifndef PLINTH_TWEENPIECEWISE_HPP
#define PLINTH_TWEENPIECEWISE_HPP

#include "Common.hpp"
#include "Tween.hpp" // for interpolating the values between two nodes
#include <algorithm> // for "std::sort"

namespace plinth
{
	namespace Tween
	{

template <class positionT, class T, class interpolationAlphaT = double, class positionCastT = double>
class Piecewise
{
public:
	struct Node
	{
		positionT position;
		T value;
		bool operator<(const Node& rhs) { return this->position < rhs.position; }
	};

	//void DEV_outputNodes();

	Piecewise();
	void clearNodes();
	void addNode(const Node& node);
	T getValue(positionT position) const;
	void changeNodePosition(unsigned int index, positionT position);
	void changeNodeValue(unsigned int index, T value);
	unsigned int getNodeCount() const;

private:
	std::vector<Node> m_nodes;
};

	} // namespace Tween
} // namespace plinth
#include "TweenPiecewise.inl"
#endif // PLINTH_TWEENPIECEWISE_HPP
