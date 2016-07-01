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

#ifndef PLINTH_SFML_ANIMATIONTRACKS_HPP
#define PLINTH_SFML_ANIMATIONTRACKS_HPP

#include "Common.hpp"
#include "../TweenTracks.hpp"

namespace sf
{
	class Time;
	template <class T>
	class Vector2;
	template <class T>
	class Vector3;
	template <class T>
	class Rect;
	class Color;
} // namespace sf

namespace plinth
{
	namespace Animation
	{

enum class InterpolationType
{
	Step,
	Linear,
	Ease
};

template <class T>
class Track
{
public:
	Track();
	void clear();
	void addKey(sf::Time time, const T& value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKey(float timeInSeconds, const T& value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	T get(sf::Time time) const;
	T get(float timeInSeconds) const;

private:
	Tween::Track<sf::Time, T, float, sf::Time> m_track;
};

template <class T>
class TrackVector2
{
public:
	TrackVector2();
	void clear();
	void addKeyX(sf::Time time, const T& value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKeyY(sf::Time time, const T& value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKey(sf::Time time, const sf::Vector2<T>& vector2, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKeyX(float timeInSeconds, const T& value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKeyY(float timeInSeconds, const T& value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKey(float timeInSeconds, const sf::Vector2<T>& vector2, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	sf::Vector2<T> get(sf::Time time) const;
	sf::Vector2<T> get(float timeInSeconds) const;

private:
	Track<T> x, y;
};

template <class T>
class TrackVector3
{
public:
	TrackVector3();
	void clear();
	void addKeyX(sf::Time time, const T& value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKeyY(sf::Time time, const T& value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKeyZ(sf::Time time, const T& value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKey(sf::Time time, const sf::Vector3<T>& vector3, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKeyX(float timeInSeconds, const T& value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKeyY(float timeInSeconds, const T& value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKeyZ(float timeInSeconds, const T& value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKey(float timeInSeconds, const sf::Vector3<T>& vector3, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	sf::Vector3<T> get(sf::Time time) const;
	sf::Vector3<T> get(float timeInSeconds) const;

private:
	Track<T> x, y, z;
};

template <class T>
class TrackRect
{
public:
	TrackRect();
	void clear();
	void addKeyLeft(sf::Time time, const T& value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKeyTop(sf::Time time, const T& value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKeyWidth(sf::Time time, const T& value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKeyHeight(sf::Time time, const T& value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKey(sf::Time time, const sf::Rect<T>& rect, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKeyLeft(float timeInSeconds, const T& value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKeyTop(float timeInSeconds, const T& value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKeyWidth(float timeInSeconds, const T& value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKeyHeight(float timeInSeconds, const T& value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKey(float timeInSeconds, const sf::Rect<T>& rect, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	sf::Rect<T> get(sf::Time time) const;
	sf::Rect<T> get(float timeInSeconds) const;

private:
	Track<T> left, top, width, height;
};

class TrackBool
{
public:
	TrackBool();
	void clear();
	void addKey(sf::Time time, bool value);
	void addKey(float timeInSeconds, bool value);
	bool get(sf::Time time) const;
	bool get(float timeInSeconds) const;

private:
	Track<unsigned int> m_track;
};

class TrackColor
{
public:
	TrackColor();
	void clear();
	void addKeyR(sf::Time time, unsigned int value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKeyG(sf::Time time, unsigned int value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKeyB(sf::Time time, unsigned int value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKeyA(sf::Time time, unsigned int value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKey(sf::Time time, const sf::Color& color, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKeyR(float timeInSeconds, unsigned int value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKeyG(float timeInSeconds, unsigned int value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKeyB(float timeInSeconds, unsigned int value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKeyA(float timeInSeconds, unsigned int value, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	void addKey(float timeInSeconds, const sf::Color& color, float in = 0.f, float out = 0.f, InterpolationType inType = InterpolationType::Linear, InterpolationType outType = InterpolationType::Linear);
	sf::Color get(sf::Time time) const;
	sf::Color get(float timeInSeconds) const;

private:
	Track<unsigned int> r, g, b, a;
};

	} // namespace Animation
} // namespace plinth
#include "AnimationTracks.inl"
#endif // PLINTH_SFML_ANIMATIONTRACKS_HPP
