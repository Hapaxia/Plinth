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

#ifndef PLINTH_SFML_KEYMAP_HPP
#define PLINTH_SFML_KEYMAP_HPP

#include "Common.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "../IndexedMap.hpp"

namespace plinth
{

class KeyMap
{
public:
	KeyMap();
	void addKey(const std::string& name, const sf::Keyboard::Key& key);
	void addKey(const sf::Keyboard::Key& key, const std::string& name); // allow to specify in opposite order (can help with code arrangement)
	void addKey(const sf::Keyboard::Key& key);
	void removeKey(unsigned int controlNumber);
	void removeKey(const std::string& name);
	sf::Keyboard::Key getKey(unsigned int index) const;
	sf::Keyboard::Key getKey(const std::string& name) const;
	void setKey(unsigned int index, const sf::Keyboard::Key& key);
	std::string getName(unsigned int index) const;
	unsigned int getSize() const;

private:
	IndexedMap<std::string, sf::Keyboard::Key> m_keys;
};

} // namespace plinth
#endif // PLINTH_SFML_KEYMAP_HPP
