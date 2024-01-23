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

#include "KeyMap.hpp"

namespace plinth
{

template <class KeycodeT>
inline KeyMap<KeycodeT>::KeyMap()
	: m_keys{}
{
}

template <class KeycodeT>
inline void KeyMap<KeycodeT>::addKey(const std::string& name, const KeycodeT key)
{
	m_keys.add(name, key);
}

template <class KeycodeT>
inline void KeyMap<KeycodeT>::addKey(const KeycodeT key, const std::string& name)
{
	addKey(name, key);
}

template <class KeycodeT>
inline void KeyMap<KeycodeT>::addKey(const KeycodeT key)
{
	addKey("", key);
}

template <class KeycodeT>
inline void KeyMap<KeycodeT>::removeKey(const std::size_t index)
{
	if (m_keys.valid(index))
		m_keys.remove(index);
}

template <class KeycodeT>
inline void KeyMap<KeycodeT>::removeKey(const std::string& name)
{
	m_keys.remove(name);
}

template <class KeycodeT>
inline KeycodeT KeyMap<KeycodeT>::getKey(const std::size_t index) const
{
	if (m_keys.valid(index))
		return m_keys.get(index);
	else
		return static_cast<KeycodeT>(-1);
}

template <class KeycodeT>
inline KeycodeT KeyMap<KeycodeT>::getKey(const std::string& name) const
{
	if (m_keys.valid(name))
		return m_keys.get(name);
	else
		return static_cast<KeycodeT>(-1);
}

template <class KeycodeT>
inline void KeyMap<KeycodeT>::setKey(const std::size_t index, const KeycodeT key)
{
	if (m_keys.valid(index))
		m_keys.set(index, key);
}

template <class KeycodeT>
inline std::string KeyMap<KeycodeT>::getName(const std::size_t index) const
{
	if (m_keys.valid(index))
		return m_keys.getKey(index);
	else
		return "";
}

template <class KeycodeT>
inline std::size_t KeyMap<KeycodeT>::getSize() const
{
	return m_keys.getSize();
}

} // namespace plinth
