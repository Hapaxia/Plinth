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

/*
#include <iostream> // for "DEV_" functions
*/

#ifndef PLINTH_TWEENPIECEWISE_INL
#define PLINTH_TWEENPIECEWISE_INL

namespace plinth
{
	namespace Tween
	{

/*
template <class positionT, class T>
void Piecewise<positionT, T>::DEV_outputNodes()
{
	for (auto& node : m_nodes)
	{
		std::cout << node.position << "       \t" << node.value << std::endl;
	}
}
*/

template <class positionT, class T>
Piecewise<positionT, T>::Piecewise() :
m_nodes()
{

}

template <class positionT, class T>
void Piecewise<positionT, T>::clearNodes()
{
	m_nodes.clear();
}

template <class positionT, class T>
void Piecewise<positionT, T>::addNode(const Node& node)
{
	m_nodes.push_back(node);
	std::sort(m_nodes.begin(), m_nodes.end());
}

template <class positionT, class T>
T Piecewise<positionT, T>::getValue(positionT position) const
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
		return linear(lowerNode->value, higherNode->value, static_cast<float>(position - lowerNode->position) / (higherNode->position - lowerNode->position));
}

template <class positionT, class T>
void Piecewise<positionT, T>::changeNodePosition(unsigned int index, positionT position)
{
	if (index >= m_nodes.size())
		return;

	m_nodes[index].position = position;
	std::sort(m_nodes.begin(), m_nodes.end());
}

template <class positionT, class T>
void Piecewise<positionT, T>::changeNodeValue(unsigned int index, T value)
{
	if (index >= m_nodes.size())
		return;

	m_nodes[index].value = value;
}

template <class positionT, class T>
unsigned int Piecewise<positionT, T>::getNodeCount() const
{
	return m_nodes.size();
}

	} // namespace Tween
} // namespace plinth
#endif // PLINTH_TWEENPIECEWISE_INL
