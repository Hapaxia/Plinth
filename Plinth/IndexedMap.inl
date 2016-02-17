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

#ifndef PLINTH_INDEXEDMAP_INL
#define PLINTH_INDEXEDMAP_INL

namespace plinth
{

template <class keyT, class T>
IndexedMap<keyT, T>::IndexedMap()
	: m_exceptionPrefix("Indexed Map: ")
{
}

template <class keyT, class T>
void IndexedMap<keyT, T>::add(const keyT& key, const T& value)
{
	m_elements.push_back(Element{ key, value });
}

template <class keyT, class T>
void IndexedMap<keyT, T>::add(const T& value)
{
	add("", value);
}

template <class keyT, class T>
void IndexedMap<keyT, T>::remove(const keyT& key)
{
	m_elements.erase(std::remove_if(m_elements.begin(), m_elements.end(),
		[&key](const Element& element)
	{
		return element.key == key;
	}),
		m_elements.end());
}

template <class keyT, class T>
void IndexedMap<keyT, T>::remove(const unsigned int index)
{
	if (priv_indexIsValid(index))
		m_elements.erase(m_elements.begin() + index);
}

template <class keyT, class T>
T IndexedMap<keyT, T>::get(const keyT& key) const
{
	for (auto& element : m_elements)
	{
		if (element.key == key)
			return element.value;
	}
	throw Exception(m_exceptionPrefix + "key not found");
}

template <class keyT, class T>
T IndexedMap<keyT, T>::get(const unsigned int index) const
{
	if (priv_indexIsValid(index))
		return m_elements[index].value;
	else
		throw Exception(m_exceptionPrefix + "index out of range");
}

template <class keyT, class T>
T& IndexedMap<keyT, T>::access(const keyT& key)
{
	for (auto& element : m_elements)
	{
		if (element.key == key)
			return element.value;
	}
	throw Exception(m_exceptionPrefix + "key not found");
}

template <class keyT, class T>
T& IndexedMap<keyT, T>::access(const unsigned int index)
{
	if (priv_indexIsValid(index))
		return m_elements[index].value;
	else
		throw Exception(m_exceptionPrefix + "index out of range");
}

template <class keyT, class T>
bool IndexedMap<keyT, T>::valid(const keyT& key) const
{
	for (auto& element : m_elements)
	{
		if (element.key == key)
			return true;
	}
	return false;
}

template <class keyT, class T>
bool IndexedMap<keyT, T>::valid(const unsigned int index) const
{
	return priv_indexIsValid(index);
}

template <class keyT, class T>
void IndexedMap<keyT, T>::set(const keyT& key, const T& value)
{
	for (auto& element : m_elements)
	{
		if (element.key == key)
			element.value = value;
	}
}

template <class keyT, class T>
void IndexedMap<keyT, T>::set(const unsigned int index, const T& value)
{
	if (priv_indexIsValid(index))
		m_elements[index].value = value;
}

template <class keyT, class T>
void IndexedMap<keyT, T>::setKey(const unsigned int index, const keyT& key)
{
	if (priv_indexIsValid(index))
		m_elements[index].key = key;
}

template <class keyT, class T>
keyT IndexedMap<keyT, T>::getKey(const unsigned int index) const
{
	if (priv_indexIsValid(index))
		return m_elements[index].key;
	else
		throw Exception(m_exceptionPrefix + "index out of range");
}

template <class keyT, class T>
unsigned int IndexedMap<keyT, T>::getSize() const
{
	return m_elements.size();
}

template <class keyT, class T>
void IndexedMap<keyT, T>::clear()
{
	m_elements.clear();
}

// PRIVATE
template <class keyT, class T>
bool IndexedMap<keyT, T>::priv_indexIsValid(const unsigned int index) const
{
	return index < m_elements.size();
}

} // namespace plinth
#endif // PLINTH_INDEXEDMAP_INL
