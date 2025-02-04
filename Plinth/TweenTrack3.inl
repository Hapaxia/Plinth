//////////////////////////////////////////////////////////////////////////////
//
// Plinth
//
// Copyright(c) 2014-2025 M.J.Silk
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

#include "TweenTrack3.hpp"

namespace plinth
{
	namespace Tween
	{

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline Track3<PositionT, T, InterpolationAlphaT, PositionCastT>::Track3()
	: a{}
	, b{}
	, c{}
{
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline Track3<PositionT, T, InterpolationAlphaT, PositionCastT>::Track3(const Track3<PositionT, T, InterpolationAlphaT, PositionCastT>& track3)
	: a{ track3.a }
	, b{ track3.b }
	, c{ track3.c }
{
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline Vector3<T> Track3<PositionT, T, InterpolationAlphaT, PositionCastT>::getValue(const PositionT& position) const
{
	return{ a.getValue(position), b.getValue(position), c.getValue(position) };
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline void Track3<PositionT, T, InterpolationAlphaT, PositionCastT>::clear()
{
	a.clear();
	b.clear();
	c.clear();
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline void Track3<PositionT, T, InterpolationAlphaT, PositionCastT>::addNode(const Node3& node3)
{
	a.addNode(node3.nodeA);
	b.addNode(node3.nodeB);
	c.addNode(node3.nodeC);
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline void Track3<PositionT, T, InterpolationAlphaT, PositionCastT>::addNode(const std::size_t trackNumber, const typename Track<PositionT, T, InterpolationAlphaT, PositionCastT>::Node& node)
{
	switch (trackNumber)
	{
	case 0_uz:
		a.addNode(node);
		break;
	case 1_uz:
		b.addNode(node);
		break;
	case 2_uz:
		c.addNode(node);
		break;
	default:
		;
	}
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline Track3<PositionT, T, InterpolationAlphaT, PositionCastT>& Track3<PositionT, T, InterpolationAlphaT, PositionCastT>::operator+=(const Node3& node3)
{
	addNode(node3);
	return *this;
}

	} // namespace Tween
} // namespace plinth
