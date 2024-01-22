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

#ifndef PLINTH_TWEENTRACK_INL
#define PLINTH_TWEENTRACK_INL

#include "TweenTrack.hpp"

namespace plinth
{
	namespace Tween
	{

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline Track<PositionT, T, InterpolationAlphaT, PositionCastT>::Track()
	: m_nodes{}
	, m_ease{}
{
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline void Track<PositionT, T, InterpolationAlphaT, PositionCastT>::clear()
{
	m_nodes.clear();
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline void Track<PositionT, T, InterpolationAlphaT, PositionCastT>::addNode(const Node& node)
{
	m_nodes.push_back(node);
	std::sort(m_nodes.begin(), m_nodes.end());
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline T Track<PositionT, T, InterpolationAlphaT, PositionCastT>::getValue(const PositionT& position) const
{
	const Node* lowerNode = &m_nodes.front();
	const Node* higherNode = &m_nodes.back();
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
	{
		//return linear(lowerNode->value, higherNode->value, static_cast<InterpolationAlphaT>(static_cast<PositionCastT>(position - lowerNode->position) / (higherNode->position - lowerNode->position)));

		if (lowerNode->outType == InterpolationType::Step)
			return lowerNode->value;
		if (lowerNode->outType == InterpolationType::Linear && higherNode->inType == InterpolationType::Linear)
			return Tween::linear(lowerNode->value, higherNode->value, static_cast<InterpolationAlphaT>(static_cast<PositionCastT>(position - lowerNode->position) / (higherNode->position - lowerNode->position)));
		
		const double out{ lowerNode->outType == InterpolationType::Ease ? lowerNode->outAmount : 0.0 };
		const double in{ higherNode->inType == InterpolationType::Ease ? higherNode->inAmount : 0.0 };
		m_ease.setRangeAndStrengths(lowerNode->value, higherNode->value, out, in);
		const double alpha{ static_cast<double>(static_cast<PositionCastT>(position - lowerNode->position) / (higherNode->position - lowerNode->position)) };
		return static_cast<T>(m_ease.getValue(alpha));
	}
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline void Track<PositionT, T, InterpolationAlphaT, PositionCastT>::changeNodePosition(const std::size_t index, const PositionT& position)
{
	if (!priv_isValidNodeIndex(index))
		return;

	m_nodes[index].position = position;
	std::sort(m_nodes.begin(), m_nodes.end());
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline void Track<PositionT, T, InterpolationAlphaT, PositionCastT>::changeNodeValue(const std::size_t index, const T& value)
{
	if (!priv_isValidNodeIndex(index))
		return;

	m_nodes[index].value = value;
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline void Track<PositionT, T, InterpolationAlphaT, PositionCastT>::changeNodeEaseOut(const std::size_t index, const double easeOutAmount)
{
	if (!priv_isValidNodeIndex(index))
		return;

	m_nodes[index].outAmount = easeOutAmount;
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline void Track<PositionT, T, InterpolationAlphaT, PositionCastT>::changeNodeEaseIn(const std::size_t index, const double easeInAmount)
{
	if (!priv_isValidNodeIndex(index))
		return;

	m_nodes[index].inAmount = easeInAmount;
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline void Track<PositionT, T, InterpolationAlphaT, PositionCastT>::changeNodeEases(const std::size_t index, const double easeOutAmount, const double easeInAmount)
{
	changeNodeEaseOut(index, easeOutAmount);
	changeNodeEaseIn(index, easeInAmount);
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline void Track<PositionT, T, InterpolationAlphaT, PositionCastT>::changeNodeInterpolationTypeOut(const std::size_t index, const InterpolationType interpolationOutType)
{
	if (!priv_isValidNodeIndex(index))
		return;

	m_nodes[index].outType = interpolationOutType;
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline void Track<PositionT, T, InterpolationAlphaT, PositionCastT>::changeNodeInterpolationTypeIn(const std::size_t index, const InterpolationType interpolationInType)
{
	if (!priv_isValidNodeIndex(index))
		return;

	m_nodes[index].inType = interpolationInType;
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline void Track<PositionT, T, InterpolationAlphaT, PositionCastT>::changeNodeInterpolationTypes(const std::size_t index, const InterpolationType interpolationOutType, const InterpolationType interpolationInType)
{
	changeNodeInterpolationTypeOut(index, interpolationOutType);
	changeNodeInterpolationTypeIn(index, interpolationInType);
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline std::size_t Track<PositionT, T, InterpolationAlphaT, PositionCastT>::getNodeCount() const
{
	return m_nodes.size();
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline Track<PositionT, T, InterpolationAlphaT, PositionCastT>& Track<PositionT, T, InterpolationAlphaT, PositionCastT>::operator+=(const Node& node)
{
	addNode(node);
	return *this;
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline bool Track<PositionT, T, InterpolationAlphaT, PositionCastT>::priv_isValidNodeIndex(const std::size_t nodeIndex) const
{
	return nodeIndex < m_nodes.size();
}

	} // namespace Tween
} // namespace plinth
#endif // PLINTH_TWEENTRACK_INL
