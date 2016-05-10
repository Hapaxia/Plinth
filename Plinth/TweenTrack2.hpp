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

#ifndef PLINTH_TWEENTRACK2_HPP
#define PLINTH_TWEENTRACK2_HPP

#include "Common.hpp"
#include "TweenTrack.hpp"
#include "Vector2.hpp"

namespace plinth
{
	namespace Tween
	{

template <class positionT, class T, class interpolationAlphaT = double, class positionCastT = double>
class Track2
{
public:
	struct Node2
	{
		typename Track<positionT, T, interpolationAlphaT, positionCastT>::Node nodeA, nodeB;
		Node2()
			: nodeA()
			, nodeB()
		{
		}
		Node2(const positionT& p, const T& a, const T& b)
			: nodeA(p, a)
			, nodeB(p, b)
		{
		}
		Node2(const positionT& p, const T& a, const T& b, const double in, const double out)
			: nodeA(p, a, in, out)
			, nodeB(p, b, in, out)
		{
		}
		Node2(const typename Track<positionT, T, interpolationAlphaT, positionCastT>::Node& a,
			const typename Track<positionT, T, interpolationAlphaT, positionCastT>::Node& b)
			: nodeA(a)
			, nodeB(b)
		{
		}
		bool operator<(const Node2& rhs) { return this->nodeA.position < rhs.nodeA.position; }
	};

	Track<positionT, T, interpolationAlphaT, positionCastT> a, b;
	Track2();
	Track2(const Track2<positionT, T, interpolationAlphaT, positionCastT>& track2);
	Vector2<T> getValue(const positionT& position) const;
	void clear();
	void addNode(const Node2& node2);
	void addNode(const unsigned int trackNumber, const typename Track<positionT, T, interpolationAlphaT, positionCastT>::Node& node);
	Track2& operator+=(const Node2& node2);
};

	} // namespace Tween
} // namespace plinth
#include "TweenTrack2.inl"
#endif // PLINTH_TWEENTRACK2_HPP
