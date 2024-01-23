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

#pragma once

#include "Common.hpp"
#include "Tween.hpp" // for interpolating the values between two nodes
#include <algorithm> // for "std::sort"

namespace plinth
{
	namespace Tween
	{

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
class Piecewise
{
public:
	struct Node
	{
		PositionT position;
		T value;
		bool operator<(const Node& other) { return position < other.position; }
	};

	Piecewise();
	void clearNodes();
	void addNode(const Node& node);
	T getValue(PositionT position) const;
	void changeNodePosition(std::size_t index, PositionT position);
	void changeNodeValue(std::size_t index, T value);
	PositionT getNodePosition(std::size_t index) const;
	T getNodeValue(std::size_t index) const;
	std::size_t getNodeCount() const;

private:
	std::vector<Node> m_nodes;
};

	} // namespace Tween
} // namespace plinth
#include "TweenPiecewise.inl"
