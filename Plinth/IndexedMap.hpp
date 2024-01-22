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

#ifndef PLINTH_INDEXEDMAP_HPP
#define PLINTH_INDEXEDMAP_HPP

#include "Common.hpp"
#include <algorithm> // for remove_if

namespace plinth
{

template <class KeyT, class T>
class IndexedMap
{
public:
	IndexedMap();
	void add(const KeyT& key, const T& value);
	void add(const T& value);
	void remove(const KeyT& key);
	void remove(std::size_t index);
	T get(const KeyT& key) const;
	T get(std::size_t index) const;
	T& access(const KeyT& key);
	T& access(std::size_t index);
	bool valid(const KeyT& key) const;
	bool valid(std::size_t index) const;
	void set(const KeyT& key, const T& value);
	void set(std::size_t index, const T& value);
	void setKey(std::size_t index, const KeyT& key);
	KeyT getKey(std::size_t index) const;
	std::size_t getSize() const;
	void clear();

private:
	const std::string m_exceptionPrefix;

	struct Element
	{
		KeyT key;
		T value;
	};
	std::vector<Element> m_elements;

	bool priv_indexIsValid(std::size_t index) const;
};

} // namespace plinth
#include "IndexedMap.inl"
#endif // PLINTH_INDEXEDMAP_HPP
