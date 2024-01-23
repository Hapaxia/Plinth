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

#pragma once

#include "Common.hpp"
#include "Tween.hpp" // for interpolating the values between two nodes
#include <algorithm> // for "std::sort"

namespace plinth
{
	namespace Tween
	{

template <typename T, typename AlphaT, typename StrengthT>
class Ease;

enum class InterpolationType
{
	Step,
	Linear,
	Ease
};
		
template <class PositionT = double, class T = double, class InterpolationAlphaT = double, class PositionCastT = double>
class Track
{
public:
	struct Node
	{
		PositionT position;
		T value;
		InterpolationType inType;
		InterpolationType outType;
		double inAmount;
		double outAmount;
		Node()
			: position{ static_cast<PositionT>(0) }
			, value{ static_cast<T>(0) }
			, inType { InterpolationType::Linear }
			, outType{ InterpolationType::Linear }
			, inAmount{ 0.0 }
			, outAmount{ 0.0 }
		{
		}
		Node(const PositionT& p, const T& v)
			: Node()
		{
			position = p;
			value = v;
		}
		Node(const PositionT& p, const T& v, const double in, const double out)
			: Node(p, v)
		{
			inAmount = in;
			outAmount = out;
			inType = inAmount == 0.0 ? InterpolationType::Linear : InterpolationType::Ease;
			outType = outAmount == 0.0 ? InterpolationType::Linear : InterpolationType::Ease;
		}
		bool operator<(const Node& rhs) { return this->position < rhs.position; }
	};

	Track();
	void clear();
	void addNode(const Node& node);
	T getValue(const PositionT& position) const;
	void changeNodePosition(std::size_t index, const PositionT& position);
	void changeNodeValue(std::size_t index, const T& value);
	void changeNodeEaseOut(std::size_t index, double easeOutAmount);
	void changeNodeEaseIn(std::size_t index, double easeInAmount);
	void changeNodeEases(std::size_t index, double easeOutAmount, double easeInAmount);
	void changeNodeInterpolationTypeOut(std::size_t index, InterpolationType interpolationOutType);
	void changeNodeInterpolationTypeIn(std::size_t index, InterpolationType interpolationInType);
	void changeNodeInterpolationTypes(std::size_t index, InterpolationType interpolationOutType, InterpolationType interpolationInType);
	std::size_t getNodeCount() const;
	Track& operator+=(const Node& node);

private:
	std::vector<Node> m_nodes;
	mutable Ease<double, double, double> m_ease;

	bool priv_isValidNodeIndex(const std::size_t nodeIndex) const;
};

	} // namespace Tween
} // namespace plinth
#include "TweenTrack.inl"
