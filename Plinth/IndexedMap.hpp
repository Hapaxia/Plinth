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

#ifndef PLINTH_INDEXEDMAP_HPP
#define PLINTH_INDEXEDMAP_HPP

#include "Common.hpp"
#include <algorithm> // for remove_if

namespace plinth
{

template <class keyT, class T>
class IndexedMap
{
public:
	IndexedMap();
	void add(const keyT& key, const T& value);
	void add(const T& value);
	void remove(const keyT& key);
	void remove(unsigned int index);
	T get(const keyT& key) const;
	T get(unsigned int index) const;
	T& access(const keyT& key);
	T& access(unsigned int index);
	bool valid(const keyT& key) const;
	bool valid(unsigned int index) const;
	void set(const keyT& key, const T& value);
	void set(unsigned int index, const T& value);
	void setKey(unsigned int index, const keyT& key);
	keyT getKey(unsigned int index) const;
	unsigned int getSize() const;
	void clear();

private:
	const std::string m_exceptionPrefix;

	struct Element
	{
		keyT key;
		T value;
	};
	std::vector<Element> m_elements;

	bool priv_indexIsValid(unsigned int index) const;
};

} // namespace plinth
#include "IndexedMap.inl"
#endif // PLINTH_INDEXEDMAP_HPP
