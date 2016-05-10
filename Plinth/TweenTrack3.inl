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

#ifndef PLINTH_TWEENTRACK3_INL
#define PLINTH_TWEENTRACK3_INL

namespace plinth
{
	namespace Tween
	{

template <class positionT, class T, class interpolationAlphaT, class positionCastT>
Track3<positionT, T, interpolationAlphaT, positionCastT>::Track3()
	: a()
	, b()
	, c()
{
}

template <class positionT, class T, class interpolationAlphaT, class positionCastT>
Track3<positionT, T, interpolationAlphaT, positionCastT>::Track3(const Track3<positionT, T, interpolationAlphaT, positionCastT>& track3)
	: a(track3.a)
	, b(track3.b)
	, c(track3.c)
{
}

template <class positionT, class T, class interpolationAlphaT, class positionCastT>
Vector3<T> Track3<positionT, T, interpolationAlphaT, positionCastT>::getValue(const positionT& position) const
{
	return{ a.getValue(position), b.getValue(position), c.getValue(position) };
}

template <class positionT, class T, class interpolationAlphaT, class positionCastT>
void Track3<positionT, T, interpolationAlphaT, positionCastT>::clear()
{
	a.clear();
	b.clear();
	c.clear();
}

template <class positionT, class T, class interpolationAlphaT, class positionCastT>
void Track3<positionT, T, interpolationAlphaT, positionCastT>::addNode(const Node3& node3)
{
	a.addNode(node3.nodeA);
	b.addNode(node3.nodeB);
	c.addNode(node3.nodeC);
}

template <class positionT, class T, class interpolationAlphaT, class positionCastT>
void Track3<positionT, T, interpolationAlphaT, positionCastT>::addNode(const unsigned int trackNumber, const typename Track<positionT, T, interpolationAlphaT, positionCastT>::Node& node)
{
	switch (trackNumber)
	{
	case 0u:
		a.addNode(node);
		break;
	case 1u:
		b.addNode(node);
		break;
	case 2u:
		c.addNode(node);
		break;
	default:
		;
	}
}

template <class positionT, class T, class interpolationAlphaT, class positionCastT>
Track3<positionT, T, interpolationAlphaT, positionCastT>& Track3<positionT, T, interpolationAlphaT, positionCastT>::operator+=(const Node3& node3)
{
	this->addNode(node3);
	return *this;
}

	} // namespace Tween
} // namespace plinth
#endif // PLINTH_TWEENTRACK3_INL
