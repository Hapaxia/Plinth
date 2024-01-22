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

#ifndef PLINTH_TWEENPIECEWISE_INL
#define PLINTH_TWEENPIECEWISE_INL

#include "TweenPiecewise.hpp"

namespace plinth
{
	namespace Tween
	{

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline Piecewise<PositionT, T, InterpolationAlphaT, PositionCastT>::Piecewise()
	: m_nodes{}
{
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline void Piecewise<PositionT, T, InterpolationAlphaT, PositionCastT>::clearNodes()
{
	m_nodes.clear();
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline void Piecewise<PositionT, T, InterpolationAlphaT, PositionCastT>::addNode(const Node& node)
{
	m_nodes.push_back(node);
	std::sort(m_nodes.begin(), m_nodes.end());
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline T Piecewise<PositionT, T, InterpolationAlphaT, PositionCastT>::getValue(const PositionT position) const
{
	const Node* lowerNode{ &m_nodes.front() };
	const Node* higherNode{ &m_nodes.back() };
	for (auto& node : m_nodes)
	{
		if (position < node.position)
		{
			if (node.position < higherNode->position)
				higherNode = &node;
		}
		else // (position >= node.position)
		{
			if (node.position > lowerNode->position)
				lowerNode = &node;
		}
	}
	if (lowerNode == higherNode)
		return lowerNode->value;
	else
		return linear(lowerNode->value, higherNode->value, static_cast<InterpolationAlphaT>(static_cast<PositionCastT>(position - lowerNode->position) / (higherNode->position - lowerNode->position)));
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline void Piecewise<PositionT, T, InterpolationAlphaT, PositionCastT>::changeNodePosition(const std::size_t index, const PositionT position)
{
	if (index >= m_nodes.size())
		return;

	m_nodes[index].position = position;
	std::sort(m_nodes.begin(), m_nodes.end());
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline void Piecewise<PositionT, T, InterpolationAlphaT, PositionCastT>::changeNodeValue(const std::size_t index, const T value)
{
	if (index >= m_nodes.size())
		return;

	m_nodes[index].value = value;
}

template<class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline PositionT Piecewise<PositionT, T, InterpolationAlphaT, PositionCastT>::getNodePosition(const std::size_t index) const
{
	if (index >= m_nodes.size())
		return PositionT{};

	return m_nodes[index].position;
}

template<class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline T Piecewise<PositionT, T, InterpolationAlphaT, PositionCastT>::getNodeValue(const std::size_t index) const
{
	if (index >= m_nodes.size())
		return T{};

	return m_nodes[index].value;
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline std::size_t Piecewise<PositionT, T, InterpolationAlphaT, PositionCastT>::getNodeCount() const
{
	return m_nodes.size();
}

	} // namespace Tween
} // namespace plinth
#endif // PLINTH_TWEENPIECEWISE_INL
