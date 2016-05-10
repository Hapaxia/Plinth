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

#ifndef PLINTH_TWEENTRACK3_HPP
#define PLINTH_TWEENTRACK3_HPP

#include "Common.hpp"
#include "TweenTrack.hpp"
#include "Vector3.hpp"

namespace plinth
{
	namespace Tween
	{

template <class positionT, class T, class interpolationAlphaT = double, class positionCastT = double>
class Track3
{
public:
	struct Node3
	{
		typename Track<positionT, T, interpolationAlphaT, positionCastT>::Node nodeA, nodeB, nodeC;
		Node3()
			: nodeA()
			, nodeB()
			, nodeC()
		{
		}
		Node3(const positionT& p, const T& a, const T& b, const T& c)
			: nodeA(p, a)
			, nodeB(p, b)
			, nodeC(p, c)
		{
		}
		Node3(const positionT& p, const T& a, const T& b, const T& c, const double in, const double out)
			: nodeA(p, a, in, out)
			, nodeB(p, b, in, out)
			, nodeC(p, c, in, out)
		{
		}
		Node3(const typename Track<positionT, T, interpolationAlphaT, positionCastT>::Node& a,
			const typename Track<positionT, T, interpolationAlphaT, positionCastT>::Node& b,
			const typename Track<positionT, T, interpolationAlphaT, positionCastT>::Node& c)
			: nodeA(a)
			, nodeB(b)
			, nodeC(c)
		{
		}
		bool operator<(const Node3& rhs) { return this->nodeA.position < rhs.nodeA.position; }
	};

	Track<positionT, T, interpolationAlphaT, positionCastT> a, b, c;
	Track3();
	Track3(const Track3<positionT, T, interpolationAlphaT, positionCastT>& track3);
	Vector3<T> getValue(const positionT& position) const;
	void clear();
	void addNode(const Node3& node3);
	void addNode(const unsigned int trackNumber, const typename Track<positionT, T, interpolationAlphaT, positionCastT>::Node& node);
	Track3& operator+=(const Node3& node3);
};

	} // namespace Tween
} // namespace plinth
#include "TweenTrack3.inl"
#endif // PLINTH_TWEENTRACK3_HPP
