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

#include "KeyMap.hpp"

namespace plinth
{

KeyMap::KeyMap()
	: m_keys()
{
}

void KeyMap::addKey(const std::string& name, const sf::Keyboard::Key& key)
{
	m_keys.add(name, key);
}

void KeyMap::addKey(const sf::Keyboard::Key& key, const std::string& name)
{
	addKey(name, key);
}

void KeyMap::addKey(const sf::Keyboard::Key& key)
{
	addKey("", key);
}

void KeyMap::removeKey(const unsigned int index)
{
	if (m_keys.valid(index))
		m_keys.remove(index);
}

void KeyMap::removeKey(const std::string& name)
{
	m_keys.remove(name);
}

sf::Keyboard::Key KeyMap::getKey(const unsigned int index) const
{
	if (m_keys.valid(index))
		return m_keys.get(index);
	else
		return sf::Keyboard::Unknown;
}

sf::Keyboard::Key KeyMap::getKey(const std::string& name) const
{
	if (m_keys.valid(name))
		return m_keys.get(name);
	else
		return sf::Keyboard::Unknown;
}

void KeyMap::setKey(const unsigned int index, const sf::Keyboard::Key& key)
{
	if (m_keys.valid(index))
		m_keys.set(index, key);
}

std::string KeyMap::getName(const unsigned int index) const
{
	if (m_keys.valid(index))
		return m_keys.getKey(index);
	else
		return "";
}

unsigned int KeyMap::getSize() const
{
	return m_keys.getSize();
}

} // namespace plinth
