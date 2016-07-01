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

#include "AnimationTracks.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>

namespace
{

template <class T, class interpolationAlphaT>
inline void forceStepInterpolationIfSpecified(typename pl::Tween::Track<sf::Time, T, interpolationAlphaT, sf::Time>::Node& node, const pl::Animation::InterpolationType& inType, const pl::Animation::InterpolationType& outType)
{
	if (inType == pl::Animation::InterpolationType::Step)
		node.inType = pl::Tween::InterpolationType::Step;
	if (outType == pl::Animation::InterpolationType::Step)
		node.outType = pl::Tween::InterpolationType::Step;
}

} // namespace

namespace plinth
{
	namespace Animation
	{

TrackBool::TrackBool()
	: m_track()
{
}

void TrackBool::clear()
{
	m_track.clear();
}

void TrackBool::addKey(const sf::Time time, const bool value)
{
	m_track.addKey(time, value ? 1u : 0u, 0.f, 0.f, InterpolationType::Step, InterpolationType::Step);
}

void TrackBool::addKey(const float timeInSeconds, const bool value)
{
	addKey(sf::seconds(timeInSeconds), value ? 1u : 0u);
}

bool TrackBool::get(const sf::Time time) const
{
	return m_track.get(time) != 0;
}

bool TrackBool::get(const float timeInSeconds) const
{
	return get(sf::seconds(timeInSeconds));
}

TrackColor::TrackColor()
	: r()
	, g()
	, b()
	, a()
{
}

void TrackColor::clear()
{
	r.clear();
	g.clear();
	b.clear();
	a.clear();
}

void TrackColor::addKeyR(const sf::Time time, const unsigned int value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	r.addKey(time, value, in, out, inType, outType);
}

void TrackColor::addKeyG(const sf::Time time, const unsigned int value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	g.addKey(time, value, in, out, inType, outType);
}

void TrackColor::addKeyB(const sf::Time time, const unsigned int value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	b.addKey(time, value, in, out, inType, outType);
}

void TrackColor::addKeyA(const sf::Time time, const unsigned int value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	a.addKey(time, value, in, out, inType, outType);
}

void TrackColor::addKey(const sf::Time time, const sf::Color& color, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKeyR(time, color.r, in, out, inType, outType);
	addKeyG(time, color.g, in, out, inType, outType);
	addKeyB(time, color.b, in, out, inType, outType);
	addKeyA(time, color.a, in, out, inType, outType);
}

void TrackColor::addKeyR(const float timeInSeconds, const unsigned int value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKeyR(sf::seconds(timeInSeconds), value, in, out, inType, outType);
}

void TrackColor::addKeyG(const float timeInSeconds, const unsigned int value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKeyG(sf::seconds(timeInSeconds), value, in, out, inType, outType);
}

void TrackColor::addKeyB(const float timeInSeconds, const unsigned int value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKeyB(sf::seconds(timeInSeconds), value, in, out, inType, outType);
}

void TrackColor::addKeyA(const float timeInSeconds, const unsigned int value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKeyA(sf::seconds(timeInSeconds), value, in, out, inType, outType);
}

void TrackColor::addKey(const float timeInSeconds, const sf::Color& color, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKey(sf::seconds(timeInSeconds), color, in, out, inType, outType);
}

sf::Color TrackColor::get(const sf::Time time) const
{
	return sf::Color(r.get(time), g.get(time), b.get(time), a.get(time));
}

sf::Color TrackColor::get(const float timeInSeconds) const
{
	return get(sf::seconds(timeInSeconds));
}

	} // namespace Animation
} // namespace plinth
