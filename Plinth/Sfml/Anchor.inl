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

#include <SFML/System/Vector2.hpp>

#ifndef PLINTH_SFML_ANCHOR_INL
#define PLINTH_SFML_ANCHOR_INL

#include "Anchor.hpp"

namespace plinth
{
	namespace Anchor
	{
		namespace Local
		{

template <class T>
sf::Vector2f getTopLeft(const T& object)
{
	const sf::FloatRect bounds{ object.getLocalBounds() };
	return{ bounds.left, bounds.top };
}
template <class T>
sf::Vector2f getTopCenter(const T& object)
{
	const sf::FloatRect bounds{ object.getLocalBounds() };
	return{ bounds.left + bounds.width / 2.f, bounds.top };
}
template <class T>
sf::Vector2f getTopRight(const T& object)
{
	const sf::FloatRect bounds{ object.getLocalBounds() };
	return{ bounds.left + bounds.width, bounds.top };
}
template <class T>
sf::Vector2f getCenterLeft(const T& object)
{
	const sf::FloatRect bounds{ object.getLocalBounds() };
	return{ bounds.left, bounds.top + bounds.height / 2.f };
}
template <class T>
sf::Vector2f getCenter(const T& object)
{
	const sf::FloatRect bounds{ object.getLocalBounds() };
	return{ bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f };
}
template <class T>
sf::Vector2f getCenterRight(const T& object)
{
	const sf::FloatRect bounds{ object.getLocalBounds() };
	return{ bounds.left + bounds.width, bounds.top + bounds.height / 2.f };
}
template <class T>
sf::Vector2f getBottomLeft(const T& object)
{
	const sf::FloatRect bounds{ object.getLocalBounds() };
	return{ bounds.left, bounds.top + bounds.height };
}
template <class T>
sf::Vector2f getBottomCenter(const T& object)
{
	const sf::FloatRect bounds{ object.getLocalBounds() };
	return{ bounds.left + bounds.width / 2.f, bounds.top + bounds.height };
}
template <class T>
sf::Vector2f getBottomRight(const T& object)
{
	const sf::FloatRect bounds{ object.getLocalBounds() };
	return{ bounds.left + bounds.width, bounds.top + bounds.height };
}

		} // namespace Local
		namespace Global
		{

template <class T>
sf::Vector2f getTopLeft(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.left, bounds.top };
}
template <class T>
sf::Vector2f getTopCenter(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.left + bounds.width / 2.f, bounds.top };
}
template <class T>
sf::Vector2f getTopRight(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.left + bounds.width, bounds.top };
}
template <class T>
sf::Vector2f getCenterLeft(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.left, bounds.top + bounds.height / 2.f };
}
template <class T>
sf::Vector2f getCenter(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f };
}
template <class T>
sf::Vector2f getCenterRight(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.left + bounds.width, bounds.top + bounds.height / 2.f };
}
template <class T>
sf::Vector2f getBottomLeft(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.left, bounds.top + bounds.height };
}
template <class T>
sf::Vector2f getBottomCenter(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.left + bounds.width / 2.f, bounds.top + bounds.height };
}
template <class T>
sf::Vector2f getBottomRight(const T& object)
{
	const sf::FloatRect bounds{ object.getGlobalBounds() };
	return{ bounds.left + bounds.width, bounds.top + bounds.height };
}

		} // namespace Global
	} // namespace Anchor
} // namespace plinth
#endif // PLINTH_SFML_ANCHOR_INL
