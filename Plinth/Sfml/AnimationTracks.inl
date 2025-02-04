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

#include "AnimationTracks.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>

namespace
{

/*
template <class T, class interpolationAlphaT>
inline void forceStepInterpolationIfSpecified(typename pl::Tween::Track<sf::Time, T, interpolationAlphaT, sf::Time>::Node& node, const pl::Animation::InterpolationType& inType, const pl::Animation::InterpolationType& outType)
{
	if (inType == pl::Animation::InterpolationType::Step)
		node.inType = pl::Tween::InterpolationType::Step;
	if (outType == pl::Animation::InterpolationType::Step)
		node.outType = pl::Tween::InterpolationType::Step;
}
*/

} // namespace

namespace plinth
{
	namespace Animation
	{

template <class T>
inline Track<T>::Track()
	: m_track{}
{
}

template <class T>
inline void Track<T>::clear()
{
	m_track.clear();
}

template <class T>
inline void Track<T>::addKey(const sf::Time time, const T& value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	typename Tween::Track<sf::Time, T, float, sf::Time>::Node node{ time, value, static_cast<double>(in), static_cast<double>(out) };
	if (inType == pl::Animation::InterpolationType::Step)
		node.inType = pl::Tween::InterpolationType::Step;
	if (outType == pl::Animation::InterpolationType::Step)
		node.outType = pl::Tween::InterpolationType::Step;
	m_track.addNode(node);
}

template <class T>
inline void Track<T>::addKey(const float timeInSeconds, const T& value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKey(sf::seconds(timeInSeconds), value, in, out, inType, outType);
}

template <class T>
inline T Track<T>::get(const sf::Time time) const
{
	return m_track.getValue(time);
}

template <class T>
inline T Track<T>::get(const float timeInSeconds) const
{
	return get(sf::seconds(timeInSeconds));
}

template <class T>
inline TrackVector2<T>::TrackVector2()
	: x{}
	, y{}
{
}

template <class T>
inline void TrackVector2<T>::clear()
{
	x.clear();
	y.clear();
}

template <class T>
inline void TrackVector2<T>::addKeyX(const sf::Time time, const T& value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	x.addKey(time, value, in, out, inType, outType);
}

template <class T>
inline void TrackVector2<T>::addKeyY(const sf::Time time, const T& value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	y.addKey(time, value, in, out, inType, outType);
}

template <class T>
inline void TrackVector2<T>::addKey(const sf::Time time, const sf::Vector2<T>& vector2, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKeyX(time, vector2.x, in, out, inType, outType);
	addKeyY(time, vector2.y, in, out, inType, outType);
}

template <class T>
inline void TrackVector2<T>::addKeyX(const float timeInSeconds, const T& value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKeyX(sf::seconds(timeInSeconds), value, in, out, inType, outType);
}

template <class T>
inline void TrackVector2<T>::addKeyY(const float timeInSeconds, const T& value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKeyY(sf::seconds(timeInSeconds), value, in, out, inType, outType);
}

template <class T>
inline void TrackVector2<T>::addKey(const float timeInSeconds, const sf::Vector2<T>& vector2, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKey(sf::seconds(timeInSeconds), vector2, in, out, inType, outType);
}

template <class T>
inline sf::Vector2<T> TrackVector2<T>::get(const sf::Time time) const
{
	return{ x.get(time), y.get(time) };
}

template <class T>
inline sf::Vector2<T> TrackVector2<T>::get(const float timeInSeconds) const
{
	return get(sf::seconds(timeInSeconds));
}

template <class T>
inline TrackVector3<T>::TrackVector3()
	: x{}
	, y{}
	, z{}
{
}

template <class T>
inline void TrackVector3<T>::clear()
{
	x.clear();
	y.clear();
	z.clear();
}

template <class T>
inline void TrackVector3<T>::addKeyX(const sf::Time time, const T& value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	x.addKey(time, value, in, out, inType, outType);
}

template <class T>
inline void TrackVector3<T>::addKeyY(const sf::Time time, const T& value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	y.addKey(time, value, in, out, inType, outType);
}

template <class T>
inline void TrackVector3<T>::addKeyZ(const sf::Time time, const T& value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	z.addKey(time, value, in, out, inType, outType);
}

template <class T>
inline void TrackVector3<T>::addKey(const sf::Time time, const sf::Vector3<T>& vector3, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKeyX(time, vector3.x, in, out, inType, outType);
	addKeyY(time, vector3.y, in, out, inType, outType);
	addKeyZ(time, vector3.z, in, out, inType, outType);
}

template <class T>
inline void TrackVector3<T>::addKeyX(const float timeInSeconds, const T& value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKeyX(sf::seconds(timeInSeconds), value, in, out, inType, outType);
}

template <class T>
inline void TrackVector3<T>::addKeyY(const float timeInSeconds, const T& value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKeyY(sf::seconds(timeInSeconds), value, in, out, inType, outType);
}

template <class T>
inline void TrackVector3<T>::addKeyZ(const float timeInSeconds, const T& value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKeyZ(sf::seconds(timeInSeconds), value, in, out, inType, outType);
}

template <class T>
inline void TrackVector3<T>::addKey(const float timeInSeconds, const sf::Vector3<T>& vector3, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKey(sf::seconds(timeInSeconds), vector3, in, out, inType, outType);
}

template <class T>
inline sf::Vector3<T> TrackVector3<T>::get(const sf::Time time) const
{
	return{ x.get(time), y.get(time), z.get(time) };
}

template <class T>
inline sf::Vector3<T> TrackVector3<T>::get(const float timeInSeconds) const
{
	return get(sf::seconds(timeInSeconds));
}



template <class T>
inline TrackRect<T>::TrackRect()
	: left{}
	, top{}
	, width{}
	, height{}
{
}

template <class T>
inline void TrackRect<T>::clear()
{
	left.clear();
	top.clear();
	width.clear();
	height.clear();
}

template <class T>
inline void TrackRect<T>::addKeyLeft(const sf::Time time, const T& value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	left.addKey(time, value, in, out, inType, outType);
}

template <class T>
inline void TrackRect<T>::addKeyTop(const sf::Time time, const T& value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	top.addKey(time, value, in, out, inType, outType);
}

template <class T>
inline void TrackRect<T>::addKeyWidth(const sf::Time time, const T& value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	width.addKey(time, value, in, out, inType, outType);
}

template <class T>
inline void TrackRect<T>::addKeyHeight(const sf::Time time, const T& value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	height.addKey(time, value, in, out, inType, outType);
}

template <class T>
inline void TrackRect<T>::addKey(const sf::Time time, const sf::Rect<T>& rect, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKeyLeft(time, rect.left, in, out, inType, outType);
	addKeyTop(time, rect.top, in, out, inType, outType);
	addKeyWidth(time, rect.width, in, out, inType, outType);
	addKeyHeight(time, rect.height, in, out, inType, outType);
}

template <class T>
inline void TrackRect<T>::addKeyLeft(const float timeInSeconds, const T& value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKeyLeft(sf::seconds(timeInSeconds), value, in, out, inType, outType);
}

template <class T>
inline void TrackRect<T>::addKeyTop(const float timeInSeconds, const T& value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKeyTop(sf::seconds(timeInSeconds), value, in, out, inType, outType);
}

template <class T>
inline void TrackRect<T>::addKeyWidth(const float timeInSeconds, const T& value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKeyWidth(sf::seconds(timeInSeconds), value, in, out, inType, outType);
}

template <class T>
inline void TrackRect<T>::addKeyHeight(const float timeInSeconds, const T& value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKeyHeight(sf::seconds(timeInSeconds), value, in, out, inType, outType);
}

template <class T>
inline void TrackRect<T>::addKey(const float timeInSeconds, const sf::Rect<T>& rect, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKey(sf::seconds(timeInSeconds), rect, in, out, inType, outType);
}

template <class T>
inline sf::Rect<T> TrackRect<T>::get(const sf::Time time) const
{
	return{ left.get(time), top.get(time), width.get(time), height.get(time) };
}

template <class T>
inline sf::Rect<T> TrackRect<T>::get(const float timeInSeconds) const
{
	return get(sf::seconds(timeInSeconds));
}

inline TrackBool::TrackBool()
	: m_track{}
{
}

inline void TrackBool::clear()
{
	m_track.clear();
}

inline void TrackBool::addKey(const sf::Time time, const bool value)
{
	m_track.addKey(time, (value ? 1u : 0u), 0.f, 0.f, InterpolationType::Step, InterpolationType::Step);
}

inline void TrackBool::addKey(const float timeInSeconds, const bool value)
{
	addKey(sf::seconds(timeInSeconds), value ? 1u : 0u);
}

inline bool TrackBool::get(const sf::Time time) const
{
	return m_track.get(time) != 0u;
}

inline bool TrackBool::get(const float timeInSeconds) const
{
	return get(sf::seconds(timeInSeconds));
}

inline TrackColor::TrackColor()
	: r{}
	, g{}
	, b{}
	, a{}
{
}

inline void TrackColor::clear()
{
	r.clear();
	g.clear();
	b.clear();
	a.clear();
}

inline void TrackColor::addKeyR(const sf::Time time, const unsigned int value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	r.addKey(time, value, in, out, inType, outType);
}

inline void TrackColor::addKeyG(const sf::Time time, const unsigned int value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	g.addKey(time, value, in, out, inType, outType);
}

inline void TrackColor::addKeyB(const sf::Time time, const unsigned int value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	b.addKey(time, value, in, out, inType, outType);
}

inline void TrackColor::addKeyA(const sf::Time time, const unsigned int value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	a.addKey(time, value, in, out, inType, outType);
}

inline void TrackColor::addKey(const sf::Time time, const sf::Color& color, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKeyR(time, color.r, in, out, inType, outType);
	addKeyG(time, color.g, in, out, inType, outType);
	addKeyB(time, color.b, in, out, inType, outType);
	addKeyA(time, color.a, in, out, inType, outType);
}

inline void TrackColor::addKeyR(const float timeInSeconds, const unsigned int value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKeyR(sf::seconds(timeInSeconds), value, in, out, inType, outType);
}

inline void TrackColor::addKeyG(const float timeInSeconds, const unsigned int value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKeyG(sf::seconds(timeInSeconds), value, in, out, inType, outType);
}

inline void TrackColor::addKeyB(const float timeInSeconds, const unsigned int value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKeyB(sf::seconds(timeInSeconds), value, in, out, inType, outType);
}

inline void TrackColor::addKeyA(const float timeInSeconds, const unsigned int value, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKeyA(sf::seconds(timeInSeconds), value, in, out, inType, outType);
}

inline void TrackColor::addKey(const float timeInSeconds, const sf::Color& color, const float in, const float out, const InterpolationType inType, const InterpolationType outType)
{
	addKey(sf::seconds(timeInSeconds), color, in, out, inType, outType);
}

inline sf::Color TrackColor::get(const sf::Time time) const
{
	return sf::Color(r.get(time), g.get(time), b.get(time), a.get(time));
}

inline sf::Color TrackColor::get(const float timeInSeconds) const
{
	return get(sf::seconds(timeInSeconds));
}

	} // namespace Animation
} // namespace plinth
