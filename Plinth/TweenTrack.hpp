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

#ifndef PLINTH_TWEENTRACK_HPP
#define PLINTH_TWEENTRACK_HPP

#include "Common.hpp"
#include "Tween.hpp" // for interpolating the values between two nodes
#include <algorithm> // for "std::sort"

namespace plinth
{
	namespace Tween
	{

template <typename T, typename alphaT, typename strengthT>
class Ease;

enum class InterpolationType
{
	Linear,
	Ease
};
		
template <class positionT, class T, class interpolationAlphaT = double, class positionCastT = double>
class Track
{
public:
	struct Node
	{
		positionT position;
		T value;
		InterpolationType inType;
		InterpolationType outType;
		double inAmount;
		double outAmount;
		Node()
			: inType(InterpolationType::Linear)
			, outType(InterpolationType::Linear)
			, inAmount(0.0)
			, outAmount(0.0)
		{
		}
		Node(const positionT& p, const T& v)
			: Node()
		{
			position = p;
			value = v;
		}
		bool operator<(const Node& rhs) { return this->position < rhs.position; }
	};

	//void DEV_outputNodes();

	Track();
	void clearNodes();
	void addNode(const Node& node);
	T getValue(const positionT& position) const;
	void changeNodePosition(unsigned int index, const positionT& position);
	void changeNodeValue(unsigned int index, const T& value);
	void changeNodeEaseIn(unsigned int index, double easeInAmount);
	void changeNodeEaseOut(unsigned int index, double easeOutAmount);
	void changeNodeEases(unsigned int index, double easeInAmount, double easeOutAmount);
	void changeNodeInterpolationTypeIn(unsigned int index, InterpolationType interpolationInType);
	void changeNodeInterpolationTypeOut(unsigned int index, InterpolationType interpolationOutType);
	void changeNodeInterpolationTypes(unsigned int index, InterpolationType interpolationInType, InterpolationType interpolationOutType);
	unsigned int getNodeCount() const;

private:
	std::vector<Node> m_nodes;
	mutable Ease<double, double, double> m_ease;

	bool priv_isValidNodeIndex(const unsigned int nodeIndex) const;
};

	} // namespace Tween
} // namespace plinth
#include "TweenTrack.inl"
#endif // PLINTH_TWEENTRACK_HPP
