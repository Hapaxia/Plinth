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

#include "IndexedMap.hpp"

namespace plinth
{

template <class KeyT, class T>
inline IndexedMap<KeyT, T>::IndexedMap()
	: m_exceptionPrefix{ "Indexed Map: " }
	, m_elements{}
{
}

template <class KeyT, class T>
inline void IndexedMap<KeyT, T>::add(const KeyT& key, const T& value)
{
	m_elements.push_back(Element{ key, value });
}

template <class KeyT, class T>
inline void IndexedMap<KeyT, T>::add(const T& value)
{
	add("", value);
}

template <class KeyT, class T>
inline void IndexedMap<KeyT, T>::remove(const KeyT& key)
{
	m_elements.erase(std::remove_if(m_elements.begin(), m_elements.end(),
		[&key](const Element& element)
		{
			return element.key == key;
		}),
		m_elements.end());
}

template <class KeyT, class T>
inline void IndexedMap<KeyT, T>::remove(const std::size_t index)
{
	if (priv_indexIsValid(index))
		m_elements.erase(m_elements.begin() + index);
}

template <class KeyT, class T>
inline T IndexedMap<KeyT, T>::get(const KeyT& key) const
{
	for (auto& element : m_elements)
	{
		if (element.key == key)
			return element.value;
	}
	throw Exception(m_exceptionPrefix + "Key not found.");
}

template <class KeyT, class T>
inline T IndexedMap<KeyT, T>::get(const std::size_t index) const
{
	if (priv_indexIsValid(index))
		return m_elements[index].value;
	else
		throw Exception(m_exceptionPrefix + "Index out of range.");
}

template <class KeyT, class T>
inline T& IndexedMap<KeyT, T>::access(const KeyT& key)
{
	for (auto& element : m_elements)
	{
		if (element.key == key)
			return element.value;
	}
	throw Exception(m_exceptionPrefix + "Key not found.");
}

template <class KeyT, class T>
inline T& IndexedMap<KeyT, T>::access(const std::size_t index)
{
	if (priv_indexIsValid(index))
		return m_elements[index].value;
	else
		throw Exception(m_exceptionPrefix + "Index out of range.");
}

template <class KeyT, class T>
inline bool IndexedMap<KeyT, T>::valid(const KeyT& key) const
{
	for (auto& element : m_elements)
	{
		if (element.key == key)
			return true;
	}
	return false;
}

template <class KeyT, class T>
inline bool IndexedMap<KeyT, T>::valid(const std::size_t index) const
{
	return priv_indexIsValid(index);
}

template <class KeyT, class T>
inline void IndexedMap<KeyT, T>::set(const KeyT& key, const T& value)
{
	for (auto& element : m_elements)
	{
		if (element.key == key)
			element.value = value;
	}
}

template <class KeyT, class T>
inline void IndexedMap<KeyT, T>::set(const std::size_t index, const T& value)
{
	if (priv_indexIsValid(index))
		m_elements[index].value = value;
}

template <class KeyT, class T>
inline void IndexedMap<KeyT, T>::setKey(const std::size_t index, const KeyT& key)
{
	if (priv_indexIsValid(index))
		m_elements[index].key = key;
}

template <class KeyT, class T>
inline KeyT IndexedMap<KeyT, T>::getKey(const std::size_t index) const
{
	if (priv_indexIsValid(index))
		return m_elements[index].key;
	else
		throw Exception(m_exceptionPrefix + "Index out of range.");
}

template <class KeyT, class T>
inline std::size_t IndexedMap<KeyT, T>::getSize() const
{
	return m_elements.size();
}

template <class KeyT, class T>
inline void IndexedMap<KeyT, T>::clear()
{
	m_elements.clear();
}

// PRIVATE
template <class KeyT, class T>
inline bool IndexedMap<KeyT, T>::priv_indexIsValid(const std::size_t index) const
{
	return index < m_elements.size();
}

} // namespace plinth
