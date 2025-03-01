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

#include <SFML/Graphics/Rect.hpp>

#pragma once

#include "Anchor.hpp"

namespace plinth
{
	namespace Anchor
	{
		namespace Local
		{

template <class T>
inline sf::Vector2f getTopLeft(const T& object)
{
	const sf::FloatRect bounds{ object.getLocalBounds() };
	return bounds.position;
}
template <class T>
inline sf::Vector2f getTopCenter(const T& object)
{
	const sf::FloatRect bounds{ object.getLocalBounds() };
	return{ bounds.position.x + (bounds.size.x / 2.f), bounds.position.y };
}
template <class T>
inline sf::Vector2f getTopRight(const T& object)
{
	const sf::FloatRect bounds{ object.getLocalBounds() };
	return{ bounds.position.x + bounds.size.x, bounds.position.y };
}
template <class T>
inline sf::Vector2f getCenterLeft(const T& object)
{
	const sf::FloatRect bounds{ object.getLocalBounds() };
	return{ bounds.position.x, bounds.position.y + (bounds.size.y / 2.f) };
}
template <class T>
inline sf::Vector2f getCenter(const T& object)
{
	const sf::FloatRect bounds{ object.getLocalBounds() };
	return bounds.position + (bounds.size / 2.f);
}
template <class T>
inline sf::Vector2f getCenterRight(const T& object)
{
	const sf::FloatRect bounds{ object.getLocalBounds() };
	return{ bounds.position.x + bounds.size.x, bounds.position.y + (bounds.size.y / 2.f) };
}
template <class T>
inline sf::Vector2f getBottomLeft(const T& object)
{
	const sf::FloatRect bounds{ object.getLocalBounds() };
	return{ bounds.position.x, bounds.position.y + bounds.size.y };
}
template <class T>
inline sf::Vector2f getBottomCenter(const T& object)
{
	const sf::FloatRect bounds{ object.getLocalBounds() };
	return{ bounds.position.x + (bounds.size.x / 2.f), bounds.position.y + bounds.size.y };
}
template <class T>
inline sf::Vector2f getBottomRight(const T& object)
{
	const sf::FloatRect bounds{ object.getLocalBounds() };
	return bounds.position + bounds.size;
}

		} // namespace Local
		namespace Global
		{

template <class T>
inline sf::Vector2f getTopLeft(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return bounds.position;
}
template <class T>
inline sf::Vector2f getTopCenter(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.position.x + (bounds.size.x / 2.f), bounds.position.y };
}
template <class T>
inline sf::Vector2f getTopRight(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.position.x + bounds.size.x, bounds.position.y };
}
template <class T>
inline sf::Vector2f getCenterLeft(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.position.x, bounds.position.y + (bounds.size.y / 2.f) };
}
template <class T>
inline sf::Vector2f getCenter(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return bounds.position + (bounds.size / 2.f);
}
template <class T>
inline sf::Vector2f getCenterRight(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.position.x + bounds.size.x, bounds.position.y + (bounds.size.y / 2.f) };
}
template <class T>
inline sf::Vector2f getBottomLeft(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.position.x, bounds.position.y + bounds.size.y };
}
template <class T>
inline sf::Vector2f getBottomCenter(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.position.x + (bounds.size.x / 2.f), bounds.position.y + bounds.size.y };
}
template <class T>
inline sf::Vector2f getBottomRight(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return bounds.position + bounds.size;
}

/*
template <class T>
inline sf::Vector2f getTopLeft(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.left, bounds.top };
}
template <class T>
inline sf::Vector2f getTopCenter(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.left + bounds.width / 2.f, bounds.top };
}
template <class T>
inline sf::Vector2f getTopRight(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.left + bounds.width, bounds.top };
}
template <class T>
inline sf::Vector2f getCenterLeft(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.left, bounds.top + bounds.height / 2.f };
}
template <class T>
inline sf::Vector2f getCenter(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f };
}
template <class T>
inline sf::Vector2f getCenterRight(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.left + bounds.width, bounds.top + bounds.height / 2.f };
}
template <class T>
inline sf::Vector2f getBottomLeft(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.left, bounds.top + bounds.height };
}
template <class T>
inline sf::Vector2f getBottomCenter(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.left + bounds.width / 2.f, bounds.top + bounds.height };
}
template <class T>
inline sf::Vector2f getBottomRight(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.left + bounds.width, bounds.top + bounds.height };
}
*/

		} // namespace Global
	} // namespace Anchor
} // namespace plinth
