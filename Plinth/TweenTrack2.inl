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

#ifndef PLINTH_TWEENTRACK2_INL
#define PLINTH_TWEENTRACK2_INL

#include "TweenTrack2.hpp"

namespace plinth
{
	namespace Tween
	{

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline Track2<PositionT, T, InterpolationAlphaT, PositionCastT>::Track2()
	: a{}
	, b{}
{
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline Track2<PositionT, T, InterpolationAlphaT, PositionCastT>::Track2(const Track2<PositionT, T, InterpolationAlphaT, PositionCastT>& track2)
	: a{ track2.a }
	, b{ track2.b }
{
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline Vector2<T> Track2<PositionT, T, InterpolationAlphaT, PositionCastT>::getValue(const PositionT& position) const
{
	return{ a.getValue(position), b.getValue(position) };
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline void Track2<PositionT, T, InterpolationAlphaT, PositionCastT>::clear()
{
	a.clear();
	b.clear();
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline void Track2<PositionT, T, InterpolationAlphaT, PositionCastT>::addNode(const Node2& node2)
{
	a.addNode(node2.nodeA);
	b.addNode(node2.nodeB);
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline void Track2<PositionT, T, InterpolationAlphaT, PositionCastT>::addNode(const std::size_t trackNumber, const typename Track<PositionT, T, InterpolationAlphaT, PositionCastT>::Node& node)
{
	switch (trackNumber)
	{
	case 0uz:
		a.addNode(node);
		break;
	case 1uz:
		b.addNode(node);
		break;
	default:
		;
	}
}

template <class PositionT, class T, class InterpolationAlphaT, class PositionCastT>
inline Track2<PositionT, T, InterpolationAlphaT, PositionCastT>& Track2<PositionT, T, InterpolationAlphaT, PositionCastT>::operator+=(const Node2& node2)
{
	addNode(node2);
	return *this;
}

	} // namespace Tween
} // namespace plinth
#endif // PLINTH_TWEENTRACK2_INL
