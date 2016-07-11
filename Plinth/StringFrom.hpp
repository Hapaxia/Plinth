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

#ifndef PLINTH_STRINGFROM_HPP
#define PLINTH_STRINGFROM_HPP

#include "Common.hpp"
#include "Range.hpp"
#include "RangeArea.hpp"
#include "Vectors.hpp"
#include "Sizes.hpp"

namespace plinth
{

std::string stringFrom(const std::string& = "");

template <class T>
std::string stringFrom(const std::vector<T>);

template <class T>
std::string stringFrom(const T&);
template <class T>
std::string stringFrom(const T&, unsigned int decimalPrecision);
std::string stringFrom(bool);

template<class T>
std::string stringFrom(pl::Vector2<T>);
template<class T>
std::string stringFrom(pl::Vector2<T>, unsigned int decimalPrecision);

template<class T>
std::string stringFrom(pl::Vector3<T>);
template<class T>
std::string stringFrom(pl::Vector3<T>, unsigned int decimalPrecision);

template<class T>
std::string stringFrom(pl::Size2<T>);
template<class T>
std::string stringFrom(pl::Size2<T>, unsigned int decimalPrecision);
template<class T>
std::string stringFrom(pl::Size3<T>);
template<class T>
std::string stringFrom(pl::Size3<T>, unsigned int decimalPrecision);

template<class T>
std::string stringFrom(pl::Range<T>);
template<class T>
std::string stringFrom(pl::Range<T>, unsigned int decimalPrecision);
template<class T>
std::string stringFrom(pl::Range<pl::Vector2<T>>);
template<class T>
std::string stringFrom(pl::Range<pl::Vector2<T>>, unsigned int decimalPrecision);
template<class T>
std::string stringFrom(pl::Range<pl::Vector3<T>>);
template<class T>
std::string stringFrom(pl::Range<pl::Vector3<T>>, unsigned int decimalPrecision);

template<class T>
std::string stringFrom(pl::RangeArea<T>);
template<class T>
std::string stringFrom(pl::RangeArea<T>, unsigned int decimalPrecision);

} // namespace plinth
#include "StringFrom.inl"
#endif // PLINTH_STRINGFROM_HPP
