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

#ifndef PLINTH_TWEENTRACK_INL
#define PLINTH_TWEENTRACK_INL

namespace plinth
{
	namespace Tween
	{

template <class positionT, class T, class interpolationAlphaT, class positionCastT>
Track<positionT, T, interpolationAlphaT, positionCastT>::Track()
	: m_nodes()
	, m_ease()
{
}

template <class positionT, class T, class interpolationAlphaT, class positionCastT>
void Track<positionT, T, interpolationAlphaT, positionCastT>::clear()
{
	m_nodes.clear();
}

template <class positionT, class T, class interpolationAlphaT, class positionCastT>
void Track<positionT, T, interpolationAlphaT, positionCastT>::addNode(const Node& node)
{
	m_nodes.push_back(node);
	std::sort(m_nodes.begin(), m_nodes.end());
}

template <class positionT, class T, class interpolationAlphaT, class positionCastT>
T Track<positionT, T, interpolationAlphaT, positionCastT>::getValue(const positionT& position) const
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
		//return linear(lowerNode->value, higherNode->value, static_cast<interpolationAlphaT>(static_cast<positionCastT>(position - lowerNode->position) / (higherNode->position - lowerNode->position)));

		if (lowerNode->outType == InterpolationType::Step)
			return lowerNode->value;
		if (lowerNode->outType == InterpolationType::Linear && higherNode->inType == InterpolationType::Linear)
			return linear(lowerNode->value, higherNode->value, static_cast<interpolationAlphaT>(static_cast<positionCastT>(position - lowerNode->position) / (higherNode->position - lowerNode->position)));
		
		const double out{ lowerNode->outType == InterpolationType::Ease ? lowerNode->outAmount : 0.0 };
		const double in{ higherNode->inType == InterpolationType::Ease ? higherNode->inAmount : 0.0 };
		m_ease.setRangeAndStrengths(lowerNode->value, higherNode->value, out, in);
		const double alpha{ static_cast<double>(static_cast<positionCastT>(position - lowerNode->position) / (higherNode->position - lowerNode->position)) };
		return static_cast<T>(m_ease.getValue(alpha));
	}
}

template <class positionT, class T, class interpolationAlphaT, class positionCastT>
void Track<positionT, T, interpolationAlphaT, positionCastT>::changeNodePosition(const unsigned int index, const positionT& position)
{
	if (!priv_isValidNodeIndex(index))
		return;

	m_nodes[index].position = position;
	std::sort(m_nodes.begin(), m_nodes.end());
}

template <class positionT, class T, class interpolationAlphaT, class positionCastT>
void Track<positionT, T, interpolationAlphaT, positionCastT>::changeNodeValue(const unsigned int index, const T& value)
{
	if (!priv_isValidNodeIndex(index))
		return;

	m_nodes[index].value = value;
}

template <class positionT, class T, class interpolationAlphaT, class positionCastT>
void Track<positionT, T, interpolationAlphaT, positionCastT>::changeNodeEaseOut(const unsigned int index, const double easeOutAmount)
{
	if (!priv_isValidNodeIndex(index))
		return;

	m_nodes[index].outAmount = easeOutAmount;
}

template <class positionT, class T, class interpolationAlphaT, class positionCastT>
void Track<positionT, T, interpolationAlphaT, positionCastT>::changeNodeEaseIn(const unsigned int index, const double easeInAmount)
{
	if (!priv_isValidNodeIndex(index))
		return;

	m_nodes[index].inAmount = easeInAmount;
}

template <class positionT, class T, class interpolationAlphaT, class positionCastT>
void Track<positionT, T, interpolationAlphaT, positionCastT>::changeNodeEases(const unsigned int index, const double easeOutAmount, const double easeInAmount)
{
	changeNodeEaseOut(index, easeOutAmount);
	changeNodeEaseIn(index, easeInAmount);
}

template <class positionT, class T, class interpolationAlphaT, class positionCastT>
void Track<positionT, T, interpolationAlphaT, positionCastT>::changeNodeInterpolationTypeOut(const unsigned int index, const InterpolationType interpolationOutType)
{
	if (!priv_isValidNodeIndex(index))
		return;

	m_nodes[index].outType = interpolationOutType;
}

template <class positionT, class T, class interpolationAlphaT, class positionCastT>
void Track<positionT, T, interpolationAlphaT, positionCastT>::changeNodeInterpolationTypeIn(const unsigned int index, const InterpolationType interpolationInType)
{
	if (!priv_isValidNodeIndex(index))
		return;

	m_nodes[index].inType = interpolationInType;
}

template <class positionT, class T, class interpolationAlphaT, class positionCastT>
void Track<positionT, T, interpolationAlphaT, positionCastT>::changeNodeInterpolationTypes(const unsigned int index, const InterpolationType interpolationOutType, const InterpolationType interpolationInType)
{
	changeNodeInterpolationTypeOut(index, interpolationOutType);
	changeNodeInterpolationTypeIn(index, interpolationInType);
}

template <class positionT, class T, class interpolationAlphaT, class positionCastT>
unsigned int Track<positionT, T, interpolationAlphaT, positionCastT>::getNodeCount() const
{
	return m_nodes.size();
}

template <class positionT, class T, class interpolationAlphaT, class positionCastT>
Track<positionT, T, interpolationAlphaT, positionCastT>& Track<positionT, T, interpolationAlphaT, positionCastT>::operator+=(const Node& node)
{
	this->addNode(node);
	return *this;
}

template <class positionT, class T, class interpolationAlphaT, class positionCastT>
inline bool Track<positionT, T, interpolationAlphaT, positionCastT>::priv_isValidNodeIndex(const unsigned int nodeIndex) const
{
	return nodeIndex < m_nodes.size();
}

	} // namespace Tween
} // namespace plinth
#endif // PLINTH_TWEENTRACK_INL
