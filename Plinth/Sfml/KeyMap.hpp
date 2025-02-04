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

#include "Common.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "../IndexedMap.hpp"

namespace plinth
{

template <class KeycodeT = sf::Keyboard::Key>
class KeyMap
{
public:
	KeyMap();
	void addKey(const std::string& name, KeycodeT key);
	void addKey(KeycodeT key, const std::string& name); // allow to specify in opposite order (can help with code arrangement)
	void addKey(KeycodeT key);
	void removeKey(std::size_t controlNumber);
	void removeKey(const std::string& name);
	KeycodeT getKey(std::size_t index) const;
	KeycodeT getKey(const std::string& name) const;
	void setKey(std::size_t index, KeycodeT key);
	std::string getName(std::size_t index) const;
	std::size_t getSize() const;

private:
	IndexedMap<std::string, KeycodeT> m_keys;
};

} // namespace plinth
#include "KeyMap.inl"
